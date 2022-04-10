#include "SceneGraph.h"

int SceneGraph::numberOfRecursiveCall = 0;

SceneGraph::SceneGraph() {
	int numberOfRecursiveCall = 0;
}

std::list<Object*> SceneGraph::getObjects() const {
	return m_objects;
}

void SceneGraph::addObject(Object* object) {
	m_objects.push_back(object);
}

void SceneGraph::deleteObject(Object* object) {
	std::list<Object*> children = object->getChildren();
	if (!children.empty()) {
		for (std::list<Object*>::iterator it = children.begin(); it != children.end(); ++it) {
			deleteObject((*it));
		}
	}
	if (object->getParent() != nullptr) {
		object->getParent()->removeChild(object);
	}

	m_objects.remove(object);
}

void SceneGraph::setParent(Object* parent, Object* child) {
	Object* oldParent = child->getParent();
	if(oldParent != nullptr)
		oldParent->removeChild(child);
	child->setParent(parent);
	if (isAcyclic() == false) {
		std::cout << "Not Acyclic : Remove object" << std::endl;
		parent->removeChild(child);
		child->setParent(oldParent);
	}
}

void SceneGraph::draw(const Window& window, const Camera& camera) {
	for (std::list<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		(*it)->disableWireframe();
		(*it)->draw(window, camera);
	}
}

void SceneGraph::drawWireframe(const Window& window, const Camera& camera) {
	for (std::list<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		(*it)->enableWireframe();
		(*it)->draw(window, camera);
	}
}

void SceneGraph::update() {
	for (std::list<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		(*it)->update();
	}
}

bool SceneGraph::isAcyclic() {
	numberOfRecursiveCall = 0;

	for (std::list<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		if ((*it)->isRoot()) {
			callFunction((*it));
		}
	}

	return numberOfRecursiveCall == m_objects.size();
}

void SceneGraph::callFunction(Object* parent) {
	numberOfRecursiveCall++;
	if (numberOfRecursiveCall > m_objects.size()) {
		return;
	}

	std::list<Object*> children = parent->getChildren();
	if (children.size() == 0)
		return;

	for (std::list<Object*>::iterator it = children.begin(); it != children.end(); ++it) {
		callFunction((*it));
	}
}

SceneGraph::~SceneGraph() {
	for (std::list<Object*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete (*it);
	}
}