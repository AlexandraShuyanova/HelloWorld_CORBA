#include "Hello_impl.h"
#include <iostream>
#include <string>

void Hello_impl::say_hello()
{
	std::cout << "Hello World!" << std::endl;
}

StringList* Hello_impl::reverse_list(const StringList& list) {
	std::cout << "reverse_list() is started!" << std::endl;

	StringList* reversed_list = new StringList;
	reversed_list->length(list.length());

	for (unsigned int i = 0; i < list.length(); i++) {
		std::string str = list[i];
		reverse(str.begin(),str.end());
		(*reversed_list)[i] = str.c_str();
	}

	std::cout << "reverse_list() is done!" << std::endl;

	return reversed_list;
}
		