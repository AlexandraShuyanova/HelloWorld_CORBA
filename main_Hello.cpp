#include "Hello.hh"
#include <iostream>

class Hello_server : public POA_Hello
{
public:
	inline Hello_server() {}
	virtual ~Hello_server() {}
	virtual void say_hello();
};

void Hello_server::say_hello()
{
	std::cout << "Hello World!" << std::endl;
}

void hello_invoke(CORBA::Object_ptr obj) {
	Hello_var e = Hello::_narrow(obj);
    
    if (CORBA::is_nil(e)) {
		std::cerr << "cannot invoke on a nil object reference."<< std::endl;
        return;
    }
	
	e->say_hello();
}

int main(int argc, char **argv)
{
	CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv, "omniORB4");
	
	CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
	PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
	
	PortableServer::Servant_var<Hello_server> hello_server = new Hello_server();
	PortableServer::ObjectId_var hello_serverId = poa->activate_object(hello_server);
	
	Hello_var hello_serverRef = hello_server->_this();
	
	PortableServer::POAManager_var pman = poa->the_POAManager();
	pman->activate();
	
	hello_invoke(hello_serverRef);
	
	orb->destroy();
	return 0;
}