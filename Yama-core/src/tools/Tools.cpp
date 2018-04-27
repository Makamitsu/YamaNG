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

void printInfo(const glm::vec3& vec, std::string name) {
	std::cout << name + " vecteur X:" << vec[0] << "Y:" << vec[1] << "Z:" << vec[2] << "\n";
}

void printInfo(const glm::mat4& mat, std::string name) {
	std::cout << name << " matrice : \n" << std::setprecision(2)
		<< mat[0][0] << std::setw(5) << mat[0][1] << std::setw(5) << mat[0][2] << std::setw(5) << mat[0][3] << "\n"
		<< mat[1][0] << std::setw(5) << mat[1][1] << std::setw(5) << mat[1][2] << std::setw(5) << mat[1][3] << "\n"
		<< mat[2][0] << std::setw(5) << mat[2][1] << std::setw(5) << mat[2][2] << std::setw(5) << mat[2][3] << "\n"
		<< mat[3][0] << std::setw(5) << mat[3][1] << std::setw(5) << mat[3][2] << std::setw(5) << mat[3][3] << "\n";
}