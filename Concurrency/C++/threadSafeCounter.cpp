
#include <mutex>
#include <thread>
#include <iostream>

int counter{0};
int guardedCounter{0};
std::mutex mutex{};
std::mutex &mutex2 = mutex;

void incrementThreadSafe()
{
	std::lock_guard<std::mutex> lock(mutex2);
	guardedCounter++;
}

void incrementLoop()
{
	for (int i = 0; i < 100000; i++)
		incrementThreadSafe();
}

void incrementLoop2()
{
	for (int i = 0; i < 100000; i++)
		counter++;
}

int main()
{

	std::thread t1{incrementLoop};
	std::thread t2{incrementLoop};
	std::thread t3{incrementLoop};
	std::thread t4{incrementLoop};

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "The thread safe counter should be equal to 400000. Its actual value is: " << guardedCounter << "\n";

	std::thread t5{incrementLoop2};
	std::thread t6{incrementLoop2};
	std::thread t7{incrementLoop2};
	std::thread t8{incrementLoop2};

	t5.join();
	t6.join();
	t7.join();
	t8.join();

	std::cout << "The none thread safe counter should be equal to 400000. Its actual value is: " << counter << "\n";

}




