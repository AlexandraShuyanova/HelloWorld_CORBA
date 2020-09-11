#include "Hello.hh"
#include <iostream>
#include <string>

std::string arrayToString(const StringList& serverOutput) {
	std::string result = "[";
	
	for (unsigned int i = 0; i < serverOutput.length(); i++) {
		result += serverOutput[i];
		if (i != serverOutput.length() - 1)
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
			stringList.length(3);
			stringList[0] = "sasha";
			stringList[1] = "CORBA";
			stringList[2] = "C++";

			std::cout << "Input: " << arrayToString(stringList) << std::endl;
			StringList_var serverOutput = hello->reverse_list(stringList);
			std::cout << "Server output: " << arrayToString(serverOutput) << std::endl;
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
