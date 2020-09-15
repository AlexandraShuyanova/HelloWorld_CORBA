#include "Hello_impl.h"
#include <iostream>
#include <string>

void Hello_impl::say_hello()
{
	std::cout << "Hello World!" << std::endl;
}

void Hello_impl::reverse_list(StringList& list) {
	std::cout << "reverse_list() is started!" << std::endl;

	for (unsigned int i = 0; i < list.length(); i++) {
		std::string str = list[i];
		reverse(str.begin(),str.end());
		list[i] = str.c_str();
	}

	std::cout << "reverse_list() is done!" << std::endl;

}
		