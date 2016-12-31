
#ifndef SRC_GRAPHICS_TEXTUREDMESH_H_
#define SRC_GRAPHICS_TEXTUREDMESH_H_

#include "interface.h"
#include <iostream>

class A: public virtual Interface {
public:

// ########################################################
// Constructor/Destructor #################################
// ########################################################

	A() {};
	virtual ~A() {};

// ########################################################
// Member Functions########################################
// ########################################################

	virtual void doSomething() override
	{
		std::cout<<"A is doing something! \n";
	}

};

#endif /* SRC_GRAPHICS_TEXTUREDMESH_H_ */
