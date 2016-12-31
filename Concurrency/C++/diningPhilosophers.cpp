
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>

std::chrono::milliseconds oneMilliSecond(1);

class Philosopher {
public:

	Philosopher(int id, std::shared_ptr<std::mutex> left, std::shared_ptr<std::mutex> right) :
		id{id}, left{left}, right{right}
	{
	}

	void start()
	{
		while (true) {
			if (id != 5) {
				eat();
				think();
			} else {
				eat2();
				think();
			}
		}
	}

	void eat()
	{
		std::lock_guard<std::mutex> guard(*left.get());
		std::lock_guard<std::mutex> guard2(*right.get());
		std::cout << "Philosopher: " << id << " is eating food. \n";
		std::this_thread::sleep_for(100 * oneMilliSecond);
	}

	void eat2()
	{
		std::lock_guard<std::mutex> guard(*right.get());
		std::lock_guard<std::mutex> guard2(*left.get());
		std::cout << "Philosopher: " << id << " is eating food. \n";
		std::this_thread::sleep_for(100 * oneMilliSecond);
	}

	void think()
	{
		std::this_thread::sleep_for(10 * oneMilliSecond);
	}

	int id;
	std::shared_ptr<std::mutex> left;
	std::shared_ptr<std::mutex> right;

};


int main()
{

	std::vector<std::shared_ptr<std::mutex>> forks{
		std::shared_ptr<std::mutex>{new std::mutex},
		std::shared_ptr<std::mutex>{new std::mutex},
		std::shared_ptr<std::mutex>{new std::mutex},
		std::shared_ptr<std::mutex>{new std::mutex},
		std::shared_ptr<std::mutex>{new std::mutex}
	};

	std::vector<Philosopher> philosophers{
		Philosopher{1, forks[0], forks[1]},
		Philosopher{2, forks[1], forks[2]},
		Philosopher{3, forks[2], forks[3]},
		Philosopher{4, forks[3], forks[4]},
		Philosopher{5, forks[4], forks[0]}};

	std::vector<std::thread> threads;

	for (Philosopher p : philosophers)
		threads.push_back(std::thread(&Philosopher::start, p));

	for (std::thread &t : threads)
		t.join();

	return 0;
}
