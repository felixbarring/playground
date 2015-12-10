
#include "semaphore.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <vector>


using std::cout;
using std::vector;
using std::thread;

std::chrono::milliseconds oneMilliSecond(1);

void threadFunction(concurrency::Semaphore* semaphore)
{
	bool succesfullyAcquired = semaphore->tryAcquire();

	if (succesfullyAcquired) {
		cout << "Thread acquired a permit from the semaphore.\n";
		std::this_thread::sleep_for(100 * oneMilliSecond);
		semaphore->release();
	} else {
		cout << "The thread did not acquire a permit. \n";
	}
}

int main()
{

	concurrency::Semaphore semaphore{5};

	cout << "Testring semaphore with 5 permits. \n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";

	semaphore.release();
	semaphore.release();
	semaphore.release();
	semaphore.release();
	semaphore.release();

	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";
	cout << semaphore.tryAcquire() << "\n";

	semaphore.release();
	semaphore.release();
	semaphore.release();
	semaphore.release();
	semaphore.release();

	cout << " ### \n";

	vector<thread> threads;
	const int numberOfThreads{10};

	for (int i = 0; i < numberOfThreads; i++)
		threads.push_back(thread(threadFunction, &semaphore));

	for (thread& t : threads)
		t.join();

	return 0;
}
