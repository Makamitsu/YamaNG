#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include "glm\glm.hpp"

namespace Utils {

	class Timer {

	public:
		Timer();
		~Timer();

		void setCaller(std::string caller);
		void startRecord();
		void printElapsed();
	private:
		std::string m_Caller;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
	};
}

void printInfo(const glm::vec3& vec, std::string name = "");

void printInfo(const glm::mat4& mat, std::string name = "");

#define TIMER(x); t.setCaller(#x);x;t.printElapsed();