#pragma once

#include <chrono>
#include <string>


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

#define TIMER(x); t.setCaller(#x);x;t.printElapsed();