#include "newMatr.h"
#include <iostream>

int main()
{
	NewMatr nm0{3, 3}, nm1;
	std::cout << nm0;
	std::cin >> nm1;
	std::cout << nm1;
	std::cout << "nm0 == nm1 : " << std::boolalpha << (nm0 == nm1) << '\n';
	std::cout << "nm0 += nm1 :\n" << (nm0 += nm1);

	try {
		return 0;
	} catch (Object::exceptions exc) {
		switch (exc) {
		case Object::exceptions::NOT_MATCHING_DERIVED:
			std::cerr << "\n!!Error: NOT_MATCHING_DERIVED!!\n";
		}
		return -1;
	}
}
