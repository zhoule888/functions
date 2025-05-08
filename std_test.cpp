//
// Created by lae on 24-4-28.
//

#include <iostream>
#include <thread>
#include <atomic>



using namespace std;
const int N = 100000000;
atomic_int num{ 0 };//不会发生线程冲突，线程安全
void run()
{
	for (int i = 0; i < N; i++)
	{
		num++;
	}
}

int main1()
{
	clock_t start = clock();
	thread t1(run);
	thread t2(run);
	t1.join();
	t2.join();
	clock_t end = clock();
	cout << "num=" << num << ",用时 " << end - start << " us" << endl;
	return 0;
}
//运行结果:
//num=200000000,用时 7111836 us


int test_tuple()
{
	std::tuple<bool, int, std::string> myTuple(true, false, "Hello");
	auto [a, b, c] = myTuple;

	std::tuple<bool, int, std::string> d(true, 0, "sfsfs");
	bool e = std::get<0>(d);
	int  f = std::get<1>(d);
	std::string g = std::get<2>(d);

	std::get<0>(d) = false;
	std::get<2>(d) = "s344242";

	bool myBool;
	std::string myString;
	std::tie(myBool, std::ignore, std::ignore, myString) = std::make_tuple(true, 1, 3.0, "1112222");

	//显示初始化
	std::tuple<bool, int, double, std::string> h = make_tuple(true, 1, 3.0, "1112222");

	//隐式初始化
	auto j = make_tuple(true, 1, 3.0, "1112222");

	//显示初始化
	std::tuple<bool, int, double, std::string>  k(true, 1, 3.0, "1112222");
	//显示初始化
	std::tuple<bool, int, double, std::string>  l{true, 1, 3.0, "1112222"};


}


std::string_view getFileExtension(std::string_view filename) {
	size_t dot = filename.rfind('.');
	return (dot != std::string_view::npos)
		   ? filename.substr(dot)
		   : std::string_view{};
}

int test_string_view()
{
	std::string str = "Hello";
	std::string_view sv = str; // 隐式转换

	std::string copy(sv); // 显式转换为string

	std::string_view sv1 = "hello,world";  //从字符串直接初始化std::string_view对象
    
    //常用的方法
    std::cout << "长度：" <<sv1.length()<<std::endl;
    std::cout << "是否为空：" <<sv1.empty()<<std::endl;
    std::cout << "第一个字符：" <<sv1.front()<<std::endl;
    std::cout << "最后一个字符：" <<sv1.back()<<std::endl;
    std::cout << "子串操作：" <<sv1.substr(0,5)<<std::endl;  //"hello"

    // 1. 移除前缀和后缀
    std::string_view sv = "Hello World";

    sv.remove_prefix(6);  // 移除 "Hello "
    std::cout << sv << "\n";  // 输出 "World"

    sv.remove_suffix(2);  // 移除 "ld"
    std::cout << sv << "\n";  // 输出 "Wor"

    // 2. 查找操作
    std::string_view text = "Hello World Hello";
    std::cout << text.find("Hello") << "\n";      // 首次出现位置
    std::cout << text.rfind("Hello") << "\n";     // 最后出现位置

    // 3. 比较操作
    std::string_view sv1 = "Hello";
    std::string_view sv2 = "World";
    std::cout << (sv1 < sv2) << "\n";  // 字典序比较


}

