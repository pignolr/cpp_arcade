//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// DynamicLoader.hpp
//

#pragma once

#include <unordered_map>
#include <exception>

namespace Arcade {
	class DynamicLoader {
		class Exception: public std::exception {
			std::string _message;
		public:
			Exception(const std::string &message)
				: _message("Error in DynamicLoader: " + message)
			{}

			~Exception()
			{}

			const char *what() const throw()
			{ return _message.c_str(); }
		};

		std::unordered_map<std::string, void *> _loadedElems;
	public:
		DynamicLoader();
		DynamicLoader(const std::string &);
		~DynamicLoader();

		void unload(const std::string &) noexcept;
		void load(const std::string &);
		void *getAddrSym(const std::string &, const std::string &);
	};
}
