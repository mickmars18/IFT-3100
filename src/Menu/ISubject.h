#pragma once
#include "IObserver.h"
#include "../Domain/Object.h"

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify(Object* object) = 0;
};