#include "Tools.h"

#include <iostream>


/*************************** TIMER CLASS *****************************/
Utils::Timer::Timer():m_Start(std::chrono::high_resolution_clock::now())
{
}

Utils::Timer::~Timer()
{
}

void Utils::Timer::startRecord()
{
	m_Start = std::chrono::high_resolution_clock::now();
}

void Utils::Timer::setCaller(std::string caller) {
	m_Caller = caller;
}

void Utils::Timer::printElapsed()
{
	std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - m_Start;
	std::cout << elapsed.count() << "sec for \"" << m_Caller << "\"";
}
