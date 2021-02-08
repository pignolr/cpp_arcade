//
// EPITECH PROJECT, 2018
// arcade
// File description:
// main.cpp
//

#include <cstring>
#include <exception>
#include <iostream>
#include "Core.hpp"

void printUsage(const char *executable)
{
	std::cout << "USAGE" << std::endl;
	std::cout << "\t" << executable << " graphic_library" << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2 || !strcmp(av[1], "-h") || !strcmp(av[1], "--help")) {
		printUsage(av[0]);
		return (ac == 2 ? 0 : 84);
	}
	try {
		Arcade::Core arcadeCore(av[1]);
		arcadeCore.run();
	} catch (std::exception &err) {
		std::cerr << err.what() << std::endl;
		return 84;
	}
}
