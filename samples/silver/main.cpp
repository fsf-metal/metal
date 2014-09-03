#include<iostream>

int main( int argc, char *argv[]) {
	try {
		std::cout << "Nothing has been implemented yet" << std::endl;
	} catch(std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

