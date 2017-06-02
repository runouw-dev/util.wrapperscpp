#include <iostream>

#include <utility>
#include <sstream>
#include <string>

#include "wrappers/lazy_ptr.hpp"

struct nocopy {
	int _value;

	nocopy(int value) : _value(value) {}
	nocopy(nocopy&) = delete;
	nocopy(nocopy&& nc) {
		std::swap(_value, nc._value);
		std::cout << "MOVE!" << std::endl;
	}

	std::string toString() const {
		std::stringstream out;

		out << "Value: "
			<< _value;

		return out.str();
	}

	friend std::ostream& operator<<(std::ostream& os, nocopy& nc) {
		return os << nc._value;
	}
};

int main(int argc, char** argv) {
	wrappers::lazy_ptr<nocopy> instance([](){
		std::cout << "Init!" << std::endl;
		return nocopy(10);
	});

	std::cout << "Instance: " << (instance->toString()) << std::endl;

	return 0;
}
