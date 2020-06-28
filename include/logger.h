#pragma once

#ifndef __LOGGER__
#define __LOGGER__ 1

#include <string>
#include <vector>
#include <iostream>

namespace VC {

	class Logger
	{
	public:
		Logger();
		~Logger();

		static void addMessage(std::string mesage);
		static void flush();

	};

}

#endif