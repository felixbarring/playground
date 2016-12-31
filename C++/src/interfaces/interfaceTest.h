
#ifndef SRC_INTERFACES_INTERFACETEST_H_
#define SRC_INTERFACES_INTERFACETEST_H_

#include "interface.h"
#include "a.h"
#include "b.h"

Interface * getA()
{
	return new A();
}

Interface * getB()
{
	return new B();
}

void interfaceTest()
{
	Interface *a = getA();
	Interface *b = getB();

	a->doSomething();
	b->doSomething();

	delete a;
	delete b;
}

#endif /* SRC_INTERFACES_INTERFACETEST_H_ */
