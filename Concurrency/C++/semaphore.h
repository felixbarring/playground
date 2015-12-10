
#ifndef SEMAPHORE_
#define SEMAPHORE_

#include <mutex>
#include <condition_variable>

namespace concurrency {

class Semaphore {
public:

// ########################################################
// Constructor/Destructor #################################
// ########################################################

	Semaphore(int permits);

	Semaphore(const Semaphore& other) = delete;

	virtual ~Semaphore() {};

// ########################################################
// Operators ##############################################
// ########################################################

	Semaphore& operator= (const Semaphore& other) = delete;

// ########################################################
// Member Functions########################################
// ########################################################

	void acquire();

	void release();

	bool tryAcquire();

// ########################################################
// Instance Variables #####################################
// ########################################################

private:

	const int numberOfPermits;
	int usedPermits{0};

	std::mutex mutex;
	std::condition_variable condition;

};

}

#endif
