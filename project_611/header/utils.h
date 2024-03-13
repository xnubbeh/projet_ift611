#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

static inline std::string readFile(const std::string& filePath)
{
	std::ifstream ifs(filePath, std::ifstream::in);
	if (!ifs.is_open())
		throw std::ios_base::failure("cannot open file: " + filePath);

	std::stringstream s;
	s << ifs.rdbuf();
	ifs.close();
	return s.str();
}

template<class T>
int measureTimeMicroSec(void (T::*func) (void), T obj) {
	auto before = std::chrono::high_resolution_clock::now();
	(obj.*func)();
	auto after = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
}

template<class T>
int measureTimeMicroSec(void (T::* func) (float), T obj, float arg) {
	auto before = std::chrono::high_resolution_clock::now();
	(obj.*func)(arg);
	auto after = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
}



#endif // UTIL_H