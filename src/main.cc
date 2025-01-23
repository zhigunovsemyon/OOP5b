#include "Double.h"
#include "Int.h"
#include "newMatr.h"
#include "object.h"
#include <iostream>
#include <string_view>

int main()
{
	Object *a{}, *b{};

	std::cout << "Тип a -- newMatr, Int, Double (m|i|d)? ";
	switch (getchar()) {
	case 'M':
	case 'm':
		a = new NewMatr{};
		break;
	case 'D':
	case 'd':
		a = new Double();
		break;
	case 'I':
	case 'i':
		a = new Int();
		break;
	default:
		std::cerr << "Неправильный ввод!\n";
		return 0;
	}
	std::cout << "Значение a: ";
	std::cin >> *a;

	std::cout << "Тип b -- Int или Double (m|i|d)? ";
	while (getchar() != '\n')
		;
	switch (getchar()) {
	case 'M':
	case 'm':
		b = new NewMatr{};
		break;
	case 'D':
	case 'd':
		b = new Double();
		break;
	case 'I':
	case 'i':
		b = new Int();
		break;
	default:
		std::cerr << "Неправильный ввод!\n";
		delete a;
		return 0;
	}
	std::cout << "Значение b: ";
	std::cin >> *b;

	std::cout << "a: " << "id = " << a->id() //
		  << ", type: " << a->type()	 //
		  << ", value: " << *a << '\n';

	std::cout << "b: " << "id = " << b->id() //
		  << ", type: " << b->type()	 //
		  << ", value: " << *b << '\n';

	try {
		std::cout << std::boolalpha;
		std::cout << "a != b : " << (*a != *b) << '\n';
		// std::cout << "a >= b : " << (*a >= *b) << '\n';
		// std::cout << "a <= b : " << (*a <= *b) << '\n';

		std::cout << "\na+=b\n";
		*a += *b;
		std::cout << "a: " << "id = " << a->id() //
			  << ", type: " << a->type()	 //
			  << ", value: " << *a << '\n';
		delete a;
		delete b;
		return 0;
	} catch (Object::exceptions exc) {
		switch (exc) {
		case Object::exceptions::NOT_MATCHING_DERIVED:
			std::cerr << "\n!!Error: NOT_MATCHING_DERIVED!!\n";
		}
		delete a;
		delete b;
		return -1;
	}
}
