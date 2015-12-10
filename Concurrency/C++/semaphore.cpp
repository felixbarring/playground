
#include "semaphore.h"

namespace concurrency {

// ########################################################
// Constructor/Destructor #################################
// ########################################################

Semaphore::Semaphore(int permits) :
	numberOfPermits{permits}
{
}

// ########################################################
// Member Functions########################################
// ########################################################

void Semaphore::acquire()
{
	std::unique_lock<std::mutex> lock(mutex);
	condition.wait(lock, [&] {return usedPermits < numberOfPermits;});
	++usedPermits;
}

bool Semaphore::tryAcquire()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (usedPermits < numberOfPermits) {
		++usedPermits;
		return true;
	}
	return false;
}


void Semaphore::release()
{
	if (usedPermits > 0) {
		--usedPermits;
		condition.notify_one();
	}
}

}
