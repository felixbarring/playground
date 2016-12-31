
#include<iostream>

#include"max.hpp"

main () {
    std::cout << maxOf(5, 100) << "\n";
	std::cout << maxOf(5.0, 100.0) << "\n";
	std::cout << maxOf("a", "b") << "\n";
}
