#pragma once
#include <string>
#include "../Domain/Object.h"

class IObserver {
public:
	virtual ~IObserver() {};
	virtual void updateActiveObject(Object* object) = 0;
};