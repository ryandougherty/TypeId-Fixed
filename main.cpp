#include <cxxabi.h>
#include <iostream>
#include <vector>
#include <typeinfo>

class foo { };

std::string find_name(const char* str) {
	int status;
	std::unique_ptr<char[], void (*)(void*)> result(abi::__cxa_demangle(str, 0, 0, &status), std::free);
	return result.get() ? std::string(result.get()) : "error";
}

template<class T>
std::string typeid_new(T t) { return find_name(typeid(t).name()); }

template<class T>
void print(T str) {
	std::cout << str << std::endl;
}

int main()
{
	unsigned long x(5);
	int arr[] = {3, 4, 5};
	
	// int
	print(typeid(int(5)).name());				// i
	print(typeid_new(int(5)));					// int
	
	// short
	print(typeid(short(5)).name());				// s
	print(typeid_new(short(5)));				// short
	
	// unsigned long
	print(typeid(x).name());					// m
	print(typeid_new(x));						// unsigned long
	
	// const char*
	print(typeid("str").name());				// A4_c
	print(typeid_new("str"));					// char const*
	
	// std::vector
	print(typeid(std::vector<int>()).name());	// FNSt3__16vectorIiNS_9allocatorIiEEEEvE
	print(typeid_new(std::vector<int>()));		// std::__1::vector<int, std::__1::allocator<int> >
	
	// std::string
	print(typeid(std::string()).name());		// FNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEvE
	print(typeid_new(std::string()));			// std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >
	
	// int[]
	print(typeid(arr).name());					// A3_i
	print(typeid_new(arr));						// int*
	
	// custom empty class
	print(typeid(foo()).name());				// F3foovE
	print(typeid_new(foo()));					// foo
}

