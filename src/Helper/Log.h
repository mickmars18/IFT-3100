#pragma once
#include <iostream>

template <class T>
void Log(const T message);

template <class T>
void Log(const T message) {
	std::cout << message << std::endl;
}