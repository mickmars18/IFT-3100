#pragma once
#include "RT_Camera.h"
#include "vec3.h"
#include "Hittable.h"
#include <iostream>
#include "ofImage.h"
#include "RT_Material.h"
#include <thread>
#include <math/ofVec2f.h>

class RayTracer {
public:
	RayTracer();
	void run(int width, int height, int samples_per_pixel, RT_Camera* camera, const color& background,
		Hittable* world, int max_depth, float quality);
	void runLoop(int begin, int end);
	bool isDone();
	ofImage* getImage();
	void update();
	void reset();
	float getPct() const;
private:
	ofImage* m_image;
	color* m_pixel;

	int m_width;
	int m_height;
	int m_nbChannels = 3;

	unsigned int m_nbThreads;
	std::vector<std::thread> m_threads;

	int m_samplesCalculated;

	int m_samplesPerPixel;
	RT_Camera* m_camera;
	color m_backgroundColor;
	Hittable* m_world;
	int m_maxDepth;

	bool m_running = false;
	bool m_done = false;

	void setImageToBlack();
	void setPixel(int i, int j, const color& color);
	void addColorToPixel(int i, int j, const color& color);
	color rayColor(const Ray& r, int depth);

	void setImageFromPixels();

	void increment();
	int m_nbZones = 1;
	int m_zoneCalculated = 0;

	int m_step;
	int m_xBegin;
	int m_xEnd;

	int m_stepY;
	int m_yBegin;
	int m_yEnd;

	bool m_terminate = false;
};
