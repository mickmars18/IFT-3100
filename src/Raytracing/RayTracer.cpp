#include "RayTracer.h"

RayTracer::RayTracer() {
	m_image = new ofImage();
	m_nbThreads = std::thread::hardware_concurrency();
	if (m_nbThreads > 1)
		m_nbThreads--;
}

void RayTracer::run(int width, int height, int samples_per_pixel, RT_Camera* camera, const color& background,
	Hittable* world, int max_depth, float quality) {
	m_done = false;
	m_width = width * quality;
	m_height = height * quality;

	m_samplesPerPixel = samples_per_pixel;
	m_camera = camera;
	m_backgroundColor = background;
	m_world = world;
	m_maxDepth = max_depth;

	setImageToBlack();

	m_samplesCalculated = 0;
	m_running = true;

	m_zoneCalculated = 0;
	m_xBegin = 0;
	m_step = 1;

	m_stepY = 0;
	m_yBegin = 0;
}

void RayTracer::runLoop(int begin, int end) {
	for (int j = begin; j < end; j++) {
		for (int i = m_xBegin; i < m_xEnd; i++) {
			auto u = (i + random_double()) / (m_width - 1);
			auto v = (j + random_double()) / (m_height - 1);
			Ray r = m_camera->get_ray(u, v);
			color rColor = rayColor(r, m_maxDepth);
			addColorToPixel(i, j, rColor);
		}
	}
}

void RayTracer::reset() {
	m_terminate = true;
}

void RayTracer::increment() {
	m_zoneCalculated++;
	if (m_zoneCalculated >= m_nbZones * m_nbZones) {
		m_done = true;
		m_running = false;
		return;
	}
	m_samplesCalculated = 0;
	m_xBegin = m_xEnd;
	m_xEnd = m_xBegin + (float)m_width / (float)m_nbZones / m_step;
	if (m_xEnd > (float)m_width) {
		m_xBegin = 0;
		m_step = 1;
		m_xEnd = m_xBegin + (float)m_width / (float)m_nbZones / m_step;

		m_stepY++;
		m_yBegin = (float)m_height / (float)m_nbZones * m_stepY;
	}

}

void RayTracer::update() {
	if (m_running) {
		if (m_terminate) {
			m_terminate = false;
			m_running = false;
			m_done = true;
		}

		if (m_samplesCalculated < m_samplesPerPixel) {
			m_threads.clear();

			int begin = 0;
			float step = (float)m_height / (float)m_nbZones / (float)m_nbThreads;
			m_xEnd = m_xBegin + (float)m_width / (float)m_nbZones / m_step;

			for (int i = 0; i < m_nbThreads; ++i) {
				int end = (i + 1) * step;

				m_threads.push_back(std::thread(&RayTracer::runLoop, this, begin + m_yBegin, end + +m_yBegin));
				begin = end;
			}

			for (auto& t : m_threads) {
				t.join();
			}

			m_samplesCalculated++;

			setImageFromPixels();
		}
		else {
			increment();
		}
	}
}

float RayTracer::getPct() const {
	if (m_running) {
		return (float)m_samplesCalculated / (float)m_samplesPerPixel;
	}
	return 2.0f;
}

bool RayTracer::isDone() {
	return m_done;
}

ofImage* RayTracer::getImage() {
	return m_image;
}

void RayTracer::setImageToBlack() {
	m_pixel = new color[m_width * m_height];
	for (int i = 0; i < m_width * m_height; i++) {
		m_pixel[i] = color(0.0, 0.0, 0.0);
	}

	setImageFromPixels();
	m_image->resize(m_width, m_height);
}

color RayTracer::rayColor(const Ray& r, int depth) {
	HitRecord rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	// If the ray hits nothing, return the background color.
	if (!m_world->hit(r, 0.001, infinity, rec))
		return m_backgroundColor;

	Ray scattered;
	color attenuation;
	color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

	if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		return emitted;

	return emitted + attenuation * rayColor(scattered, depth - 1);
}

void RayTracer::addColorToPixel(int i, int j, const color& color) {
	j = m_height - 1 - j;
	int index = (j * m_width + i);
	m_pixel[index] += color;
}

void RayTracer::setImageFromPixels() {
	ofPixels pixels;
	pixels.allocate(m_width, m_height, ofImageType::OF_IMAGE_COLOR);

	int index = 0;
	for (int i = 0; i < m_width * m_height; i++) {
		color pix = m_pixel[i];
		float scale = 1.0 / m_samplesPerPixel;

		float r = clamp(sqrt(pix.x() * scale), 0.0, 1.0) * 255.999;
		float g = clamp(sqrt(pix.y() * scale), 0.0, 1.0) * 255.999;
		float b = clamp(sqrt(pix.z() * scale), 0.0, 1.0) * 255.999;

		pixels[index++] = r;
		pixels[index++] = g;
		pixels[index++] = b;
	}

	m_image->setFromPixels(pixels);
}