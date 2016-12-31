
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class LambdaTest
{
public:

	void prepareStuff()
	{
		cout << "Test \n";

		auto func = [str = m_value]
					{
						cout << str;
                    };

		m_functions.push_back(func);
	}

	void doStuff()
	{
		m_functions[0]();
	}

private:
	string m_value{"Hello World \n"};
	vector<function<void()>>  m_functions{};
};


int main()
{
	LambdaTest test{};
	test.prepareStuff();
    test.doStuff();
}
