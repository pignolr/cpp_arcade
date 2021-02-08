//
// EPITECH PROJECT, 2018
// arcade
// File description:
// DynamicLoader.cpp
//

#include <dlfcn.h>
#include <algorithm>
#include "DynamicLoader.hpp"

namespace Arcade {
	DynamicLoader::DynamicLoader()
	{}

	DynamicLoader::DynamicLoader(const std::string &src)
	{
		load(src);
	}

	DynamicLoader::~DynamicLoader()
	{
		std::for_each(_loadedElems.begin(), _loadedElems.end(),
			[](auto &it) { dlclose(std::get<1>(it)); });
	}

	void DynamicLoader::unload(const std::string &src) noexcept
	{
		if (!_loadedElems.count(src))
			return;
		dlclose(_loadedElems[src]);
	}

	void DynamicLoader::load(const std::string &src)
	{
		void *loadedElem;

		loadedElem = dlopen(src.c_str(), RTLD_LAZY);
		if (!loadedElem)
			throw Exception("dlopen failed with '" + src + "': "
				+ dlerror());
		unload(src);
		_loadedElems[src] = loadedElem;
	}

	void *DynamicLoader::getAddrSym(const std::string &src,
		const std::string &sym)
	{
		void *addr;

		if (!_loadedElems.count(src))
			load(src);
		addr = dlsym(_loadedElems[src], sym.c_str());
		if (!addr)
			throw Exception("dlsym failed with symbol '" + sym
				+ "' from  '" + src + "': " + dlerror());
		return addr;
	}
}
