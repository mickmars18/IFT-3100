#pragma once
#include "Object.h"
#include "Window.h"
#include "Camera.h"

class SceneGraph {
public:
	static int numberOfRecursiveCall;

	SceneGraph();
	std::list<Object*> getObjects() const;
	void addObject(Object* object);
	void deleteObject(Object* object);
	void setParent(Object* parent, Object* child);
	void draw(const Window& window, const Camera& camera);
	void drawWireframe(const Window& window, const Camera& camera);
	void update();
	bool isAcyclic();

	~SceneGraph();

private:
	std::list<Object*> m_objects;

	void callFunction(Object* parent);

};
