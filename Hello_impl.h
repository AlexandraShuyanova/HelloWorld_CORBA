#include "Hello.hh"

class Hello_impl : public POA_Hello
{
public:
	inline Hello_impl() {}
	virtual ~Hello_impl() {}
	virtual void say_hello() override;
	virtual StringList* reverse_list(const StringList& list) override;
};
