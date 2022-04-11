#pragma once
#include "ofMain.h"
#include "ofVec3f.h"
#include "Window.h"
#include "Transform.h"
#include "Camera.h"

class Object {
public:
	virtual std::string getName() const { return m_name; }
	virtual void setName(std::string name) { m_name = name; }

	virtual std::string getClassName() = 0;

	virtual bool isActive() const { return m_active; }
	virtual void setActive(bool active) { m_active = active; }

	virtual bool isVectorGraphics() const { return false; }

	virtual void update() = 0;
	virtual void draw(const Window& window, const Camera& camera) = 0;

	virtual glm::mat4 getModel() {
		if (m_parent == nullptr)
			return m_transform.getModel();
		else
			return m_parent->getModel() * m_transform.getModel();
	}

	virtual glm::vec3 getPosition() {
		return m_transform.getPosition();
	}

	virtual glm::vec3 getGlobalPosition() {
		if (m_parent == nullptr)
			return m_transform.getPosition();
		else
			return m_parent->getGlobalPosition() + m_transform.getPosition();
	}

	virtual glm::vec3 getScale() {
		return m_transform.getScale();
	}

	virtual glm::vec3 getRotation() {
		return m_transform.getRotation();
	}

	virtual void setPositionX(float x) { m_transform.getPosition().x = x; }
	virtual void setPositionY(float y) { m_transform.getPosition().y = y; }
	virtual void setPositionZ(float z) { m_transform.getPosition().z = z; }
	virtual void setPosition(float x, float y, float z) { m_transform.setPosition(x, y, z); }
	virtual void setPosition(const glm::vec3& position) { m_transform.setPosition(position); }
	virtual void translate(float x, float y, float z) { 
		setPosition(getPosition().x + x, getPosition().y + y, getPosition().z + z);
	}
	virtual void translate(glm::vec3 t) {
		setPosition(getPosition().x + t.x, getPosition().y + t.y, getPosition().z + t.z);
	}

	virtual void addRotationX(float x) { m_transform.addRotationX(x); }
	virtual void setRotationX(float x) { m_transform.setRotationX(x); }
	virtual void addRotationY(float y) { m_transform.addRotationY(y); }
	virtual void setRotationY(float y) { m_transform.setRotationY(y); }
	virtual void addRotationZ(float z) { m_transform.addRotationZ(z); }
	virtual void setRotationZ(float z) { m_transform.setRotationZ(z); }
	virtual void setRotation(float x, float y, float z) {
		m_transform.setRotationX(x);
		m_transform.setRotationY(y);
		m_transform.setRotationZ(z);
	}

	virtual void setScaleX(float x) { m_transform.getScale().x = x; }
	virtual void setScaleY(float y) { m_transform.getScale().y = y; }
	virtual void setScaleZ(float z) { m_transform.getScale().z = z; }
	virtual void setScale(float x, float y, float z) { m_transform.setScale(x, y, z); }
	virtual void setScale(float scale) { m_transform.setScale(scale, scale, scale); }
	
	virtual ofColor getColor() const { return ofColor(255, 255, 255); }
	virtual void changeColor(const ofColor& color) {}
	virtual bool hasColorAttribute() { return false; }

	virtual void keyReleased(int key) {}

	virtual void removeChild(Object* child) {
		m_children.remove(child);
		child->setParent(nullptr);
	}

	virtual Object* getParent() const { return m_parent; }
	virtual void setParent(Object* parent) {
		m_parent = parent;
		if(parent)
			parent->addChild(this);
	}
	virtual int getNumberOfParents() {
		if (m_parent == nullptr)
			return 0;
		else
			return 1 + m_parent->getNumberOfParents();
	}

	std::list<Object*> getChildren() { return m_children; }

	virtual bool isRoot() const {
		return m_parent == nullptr;
	}

	void setTransform(const Transform& transform) { m_transform = transform; }
	Transform getTransform() const { return m_transform; }

	void enableWireframe() { m_wireFrameMode = true; }
	void disableWireframe() { m_wireFrameMode = false; }
	void setWireframe(bool isWireframe) { m_wireFrameMode = isWireframe; }
	bool isWireframeEnable() const { return m_wireFrameMode; }

	void setToggleToneMapping(bool value) { m_toggle = value; }
	void setGammaToneMapping(float gamma) { m_gamma = gamma; }
	void setExposureToneMapping(float exposure) { m_exposure = exposure; }

	void changeShaders(const std::string& vs, const std::string& fs) {
		m_shader.unload();
		m_shader.load(vs, fs);
		m_vertexShaderName = vs;
		m_fragmentShaderName = fs;
	}

	std::string getVertexShaderName() { return m_vertexShaderName; }
	std::string getFragmentShaderName() { return m_fragmentShaderName; }

protected:
	bool m_active = false;
	std::string m_name;
	Transform m_transform;
	std::list<Object*> m_children = {};
	Object* m_parent = nullptr;
	ofShader m_shader;
	std::string m_vertexShaderName;
	std::string m_fragmentShaderName;

	bool m_wireFrameMode = false;

	virtual void addChild(Object* child) {
		m_children.push_back(child);
	}

	// Tonal mapping settings
	bool m_toggle = true;
	float m_gamma = 1.0f;
	float m_exposure = 1.0f;
};
