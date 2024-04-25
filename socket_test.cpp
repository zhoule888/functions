#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>


#define SERVER_PORT		8888
#define SERVER_IP		"192.168.0.39"


int main(int argc, char *argv[]) {
	argc=2;
	argv[1]="hello,world!\0xyz";


	int ret = 0;
	int sockfd = 0;			// 通信套接字
	char *message = NULL;
	struct sockaddr_in serveraddr;
	int n = 0;
	char buff[42*7*4];

	if (2 != argc) {
		fprintf(stderr, "Usage: ./echo_client message \n");
		exit(1);
	}

	// 获取第二个参数的字符串
	message = argv[1];
	printf("message: %s\n", message);

	// 1.创建通信套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd) {
		perror("create sockfd error");
		exit(-1);
	}

	// 2.清空标签，写上地址和端口号
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;							// IPv4
	inet_pton(AF_INET, SERVER_IP, &serveraddr.sin_addr);		// 服务器地址
	serveraddr.sin_port = htons(SERVER_PORT);					// 服务器端口号

	// 3.连接服务器
	ret = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (-1 == ret) {
		perror("connect error");
		close(sockfd);
		exit(-2);
	}

	// 4.给服务器发送数据
	while(1)
	{
		sleep(1);
		printf("send message: %s\n", message);
		ret = write(sockfd, message, strlen(message));
		if (-1 == ret) {
			perror("write error");
			close(sockfd);
			exit(-3);
		}


//		// 5.接受服务器发送过来的数据
		n = read(sockfd, buff, sizeof(buff)-1);
		if (-1 == n) {
			perror("read error");
			close(sockfd);
			exit(-4);
		}

		if (n > 0) {
			buff[n] = '\0';
			printf("receive: %s\n", buff);
		} else {
			perror("error!!!\n");
		}
	}




	printf("client finished.\n");
	// 6.关闭套接字
	close(sockfd);

	return 0;
}