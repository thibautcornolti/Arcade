/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <dlfcn.h>
#include <string>

class DLLoader {
	public:
		DLLoader(const std::string &filename, int flags);
		~DLLoader();

		auto isError();
		auto &getError();

		template<typename T>
		T getSym(const std::string &symbole)
		{
			void *res = dlsym(handle, symbole.c_str());
			if (!res)
				error = dlerror();
			dlerror();
			return reinterpret_cast<T>(res);
		}

		template<typename T>
		T *getInstance(const std::string &getter)
		{
			auto fct = getSym<T *(*)()>(getter);
			if (!isError())
				return fct();
			return nullptr;
		}

	private:
		void *handle;
		std::string error;
};