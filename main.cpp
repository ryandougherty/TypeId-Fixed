#include <cxxabi.h>
#include <iostream>
#include <typeinfo>

std::string find_name(const char* str) {
	int status;
	std::unique_ptr<char[], void (*)(void*)> result(abi::__cxa_demangle(str, 0, 0, &status), std::free);
	return result.get() ? std::string(result.get()) : "error";
}

template<class T>
std::string typeid_new(T t) { return find_name(typeid(t).name()); }

int main()
{
	unsigned long x(5);
	
	std::cout << typeid(x).name() << std::endl;
	std::cout << typeid_new(x) << std::endl;
	
	std::cout << typeid("str").name() << std::endl;
	std::cout << typeid_new("str") << std::endl;
}

