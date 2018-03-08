/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "DLLoader.hpp"

DLLoader::DLLoader(const std::string &filename, int flags)
{
	handle = dlopen(filename.c_str(), flags);
	if (!handle)
		error = dlerror();
	dlerror();
}

DLLoader::~DLLoader()
{
	if (handle)
		dlclose(handle);
}

bool DLLoader::isError()
{
	return error.length() > 0;
}

std::string &DLLoader::getError() {
	return error;
}
