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
