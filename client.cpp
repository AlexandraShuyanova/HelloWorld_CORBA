#include "Hello.hh"
#include <iostream>

#include <string>
#include <typeinfo>

using namespace std;


_CORBA_String_element to_string(_CORBA_String_element& string) {
	return string;
}

template < typename T >
string arrayToString(T& serverOutput, int size) {
	string result = "[";
	
	for (unsigned int i = 0; i < size; i++) {

		result += to_string(serverOutput[i]);
		if (i != size - 1) 
			result += ", ";
		
	}
	result += "]";

	return result;
}


int main(int argc, char** argv)
{
	try {
		//init ORB
		CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv, "omniORB4");
		if (CORBA::is_nil(orb)) {
			std::cerr << "ORB is not init" << std::endl;
			return -1;
		}

		//register within the naming service
		CORBA::Object_var ns_obj = orb->resolve_initial_references("NameService");

		if (!CORBA::is_nil(ns_obj)) {
			CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(ns_obj);
			CosNaming::Name contextName;
			contextName.length(1);
			contextName[0].id = (const char*)"TestServer";
			contextName[0].kind = (const char*)"";
			CORBA::Object_var obj = nc->resolve(contextName);
			Hello_var hello = Hello::_narrow(obj);

			hello->say_hello();
			std::cout << "say_hello() done!" << std::endl;

			StringList stringList;
			LongList_var longList;
			stringList.length(3);
		
			stringList[0] = "C++";
			stringList[1] = "12345";
			stringList[2] = "omniNames";

			std::cout << "Input: " << arrayToString(stringList, stringList.length()) << std::endl;
			hello->reverse_list(stringList, longList);
			std::cout << "Server output: " << arrayToString(stringList, stringList.length()) << std::endl;
			std::cout << "Lengths of strings: " << arrayToString(longList, stringList.length()) << std::endl;
		}
		else {
			std::cerr << "ns_obj is nil" << std::endl;
		}

		// quit
		orb->destroy();
	}
	catch (CosNaming::NamingContext::NotFound&) {
		std::cerr << "not found" << std::endl;
	}
	catch (CosNaming::NamingContext::InvalidName&) {
		std::cerr << "invalid name" << std::endl;
	}
	catch (CosNaming::NamingContext::CannotProceed&) {
		std::cerr << "cannot proceed" << std::endl;
	}
	catch (CORBA::UNKNOWN) {
		std::cerr << "unknown exception" << std::endl;
	}
	catch (CORBA::SystemException&) {
		std::cerr << "system exception" << std::endl;
	}

	return 0;
}
