
#ifndef SRC_INTERFACES_B_H_
#define SRC_INTERFACES_B_H_

#include "interface.h"
#include <iostream>

class B: public virtual Interface {
public:

// ########################################################
// Constructor/Destructor #################################
// ########################################################

	B() {};
	virtual ~B() {};

// ########################################################
// Member Functions########################################
// ########################################################

	void doSomething() override
	{
		std::cout<<"B is doing something! \n";
	}

};

#endif /* SRC_INTERFACES_B_H_ */
