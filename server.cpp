#include "Hello_impl.h"
#include <iostream>

int main(int argc, char **argv)
{
	try {
		//init ORB
		CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv, "omniORB4");
		
		//init POA
		CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
		PortableServer::POAManager_var manager = poa->the_POAManager();
		
		//create service
		Hello_impl* service = new Hello_impl;
		
		//register within the naming service
		try {
			CORBA::Object_var ns_obj = orb->resolve_initial_references("NameService");
			if (!CORBA::is_nil(ns_obj)) {
				CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(ns_obj);
				CosNaming::Name name;
				name.length(1);
				name[0].id = CORBA::string_dup("TestServer");
				name[0].kind = CORBA::string_dup("");
				nc->rebind(name, service->_this());
				std::cout << "Server is running ..." << std::endl;
			} else {
				std::cerr << "ns_obj is nil" << std::endl;
			}
		} catch (CosNaming::NamingContext::NotFound&) {
			std::cerr << "not found" << std::endl;
		} catch (CosNaming::NamingContext::InvalidName&) {
			std::cerr << "invalid name" << std::endl;
		} catch (CosNaming::NamingContext::CannotProceed&) {
			std::cerr << "cannot proceed" << std::endl;
		}
		// run
		manager->activate();
		orb->run();
		
		// clean up
		delete service;

		// quit
		orb->destroy();
	} catch (CORBA::UNKNOWN) {
		std::cerr << "unknown exception" << std::endl;
	} catch (CORBA::SystemException&) {
		std::cerr << "system exception" << std::endl;
	}
	
	return 0;
}