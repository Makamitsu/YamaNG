#pragma once

#include <chrono>
#include <string>



namespace Utils {

	class Timer {

	public:
		Timer(std::string caller);
		~Timer();

		void startRecord();
		void printElapsed();
	private:
		std::string m_Caller;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;


	};
}

#define TIMER(x); Utils::Timer t(#x);x;t.printElapsed();
