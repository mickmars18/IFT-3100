#pragma once
#include <graphics/ofImage.h>
#include <iostream>
#include "RT_Sphere.h"
#include "HittableList.h"
#include "RT_Camera.h"
#include "RT_Material.h"
#include "Metal.h"
#include "Lambertian.h"
#include "rtweekend.h"
#include "Dielectric.h"
#include "bvh_node.h"
#include "DiffuseLight.h"
#include "RT_Plane.h"
#include "RT_Box.h"
#include "RT_Triangle.h"
#include "RayTracer.h"
#include "RT_Model.h"

class RT_App {
public:
	RT_App();
	~RT_App();
	void run();
	void stop();
	void draw(int posX, int posY, int width, int height);
	void update();

	int getSamplesPerPixels() const { return m_samples_per_pixel; }
	void setSamplesPerPixels(int samples_per_pixel) { m_samples_per_pixel = samples_per_pixel; }

	int getMaxDepth() const { return m_max_depth; }
	void setMaxDepth(int max_depth) { m_max_depth = max_depth; }

	void setWindowSize(int width, int height) {
		m_windowWidth = width;
		m_windowHeight = height;
	}

	bool isDone() {
		return m_rayTracer.isDone();
	}

	void setQuality(float quality) { m_quality = quality; }
	float getQuality() const { return m_quality; }

	float getPct() const;

private:
	ofImage* m_screen;
	RT_Camera* m_camera;
	color m_background;
	vec3 m_lookFrom;
	vec3 m_lookat;
	double m_vfov;
	double m_aperture = 0.0;
	vec3 m_vup = vec3(0, 1, 0);
	double m_dist_to_focus = 0.0;

	int m_samples_per_pixel = 100;
	int m_max_depth = 8;
	HittableList m_world;
	RayTracer m_rayTracer;

	HittableList cornell_box();
	HittableList random_scene();

	int m_windowWidth;
	int m_windowHeight;
	float m_quality = 0.25f;
};
