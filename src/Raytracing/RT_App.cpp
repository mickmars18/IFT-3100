#include "RT_App.h"

HittableList RT_App::random_scene() {
	m_background = color(204.0 / 255.0, 233.0 / 255.0, 246.0 / 255.0);
	m_lookFrom = vec3(13, 2, 3);
	m_lookat = vec3(0, 0, 0);
	m_vfov = 40.0;
	m_dist_to_focus = 10.0;
	m_aperture = 0.1;

	HittableList world;
	auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<RT_Sphere>(point3(0, -1000, 0), 1000, ground_material));
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<RT_Material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<Lambertian>(albedo);
					world.add(make_shared<RT_Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					sphere_material = make_shared<Metal>(albedo);
					world.add(make_shared<RT_Sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					world.add(make_shared<RT_Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	//auto material1 = make_shared<Dielectric>(1.5);
	//world.add(make_shared<RT_Sphere>(point3(0, 1, 0), 1.0, material1));

	auto metal = make_shared<Metal>(color(0.8, 0.8, 0.8));
	//world.add(make_shared<RT_Sphere>(point3(4, 1, 0), 1.0, material2));


	Transform transform;
	//world.add(make_shared<RTBox>(vec3(-0.1, -0.1, -0.1), vec3(2, 2, 2), metal, transform));

	HittableList triangles_list;
	RT_Model model;
	model.loadModel("Models/Dinosaurs/velociraptor.obj");
	model.setScale(1.5f);
	model.setPosition(00.0f, 0.0f, 0.0f);
	model.setRotation(0.0f, 145.0f, 0.0f);
	std::vector<RT_Triangle> triangles = model.getTriangles();
	for (size_t i = 0; i < triangles.size(); i++) {
		triangles_list.add(make_shared<RT_Triangle>(
			triangles[i].getPoint(0),
			triangles[i].getPoint(1),
			triangles[i].getPoint(2),
			triangles[i].getMaterial()));
	}

	HittableList objects;
	world.add(make_shared<bvh_node>(triangles_list, 0, 1));

	return world;
}

HittableList RT_App::cornell_box() {

	m_background = color(0.0, 0.0, 0.0);
	m_lookFrom = vec3(278, 278, -660);
	m_lookat = vec3(278, 278, 0);
	m_vfov = 40.0;
	m_dist_to_focus = 200.0;
	m_aperture = 0.1;

	HittableList objects;

	auto red = make_shared<Lambertian>(color(.65, .05, .05));
	auto white = make_shared<Lambertian>(color(.73, .73, .73));
	auto green = make_shared<Lambertian>(color(.12, .45, .15));
	auto light = make_shared<DiffuseLight>(color(50, 50, 50));
	auto yellow = make_shared<Lambertian>(color(1.0, 0.84, 0.0));
	auto metal_material = make_shared<Metal>(color(.85, .85, .85));
	auto water = make_shared<Dielectric>(1.2);

	double roomSize = 555.0;
	vec3 p1(0, 0, roomSize);
	vec3 p2(0, roomSize, roomSize);
	vec3 p3(roomSize, roomSize, roomSize);
	vec3 p4(roomSize, 0, roomSize);

	vec3 p5(0, 0, 0);
	vec3 p6(0, roomSize, 0);
	vec3 p7(roomSize, roomSize, 0);
	vec3 p8(roomSize, 0, 0);

	double lightSize = 150.0;
	double init = (roomSize - lightSize) / 2.0;
	vec3 lightP1(init, roomSize - 1, init);
	vec3 lightP2(init, roomSize - 1, init + lightSize);
	vec3 lightP3(init + lightSize, roomSize - 1, init + lightSize);
	vec3 lightP4(init + lightSize, roomSize - 1, init);

	objects.add(make_shared<RT_Plane>(lightP1, lightP2, lightP3, lightP4, light));
	objects.add(make_shared<RT_Plane>(p1, p4, p8, p5, white)); // floor
	objects.add(make_shared<RT_Plane>(p6, p2, p3, p7, white)); // roof
	objects.add(make_shared<RT_Plane>(p1, p2, p3, p4, white)); // back
	objects.add(make_shared<RT_Plane>(p1, p2, p6, p5, red)); // right
	objects.add(make_shared<RT_Plane>(p4, p3, p7, p8, green)); // left

	shared_ptr<Hittable> sphere0 = make_shared<RT_Sphere>(point3(554 / 2 - 130, 80, 400), 80, metal_material);
	objects.add(sphere0);

	shared_ptr<Hittable> sphere = make_shared<RT_Sphere>(point3(554 / 2 + 70, 80, 100), 80, water);
	objects.add(sphere);

	shared_ptr<Hittable> sphere2 = make_shared<RT_Sphere>(point3(554 / 2 - 130, 25, 130), 25, yellow);
	objects.add(sphere2);

	RT_Model model;
	model.loadModel("Models/Dinosaurs/velociraptor.obj");
	model.setScale(120.0f);
	model.setPosition(380.0f, 0.0f, 260.0f);
	model.setRotation(0.0f, 145.0f, 0.0f);
	std::vector<RT_Triangle> triangles = model.getTriangles();
	for (size_t i = 0; i < triangles.size(); i++) {
		objects.add(make_shared<RT_Triangle>(
			triangles[i].getPoint(0),
			triangles[i].getPoint(1),
			triangles[i].getPoint(2),
			triangles[i].getMaterial()));
	}

	HittableList world;
	world.add(make_shared<bvh_node>(objects, 0, 1));
	return world;
}

float RT_App::getPct() const {
	return m_rayTracer.getPct();
}

RT_App::RT_App() {
	m_screen = new ofImage();
	m_camera = new RT_Camera();
}

void RT_App::run() {
	// World
	m_world = cornell_box();

	// Camera
	float aspect_ratio = (float)m_windowWidth / (float)m_windowHeight;
	m_camera->setValues(m_lookFrom, m_lookat, m_vup, m_vfov, aspect_ratio, m_aperture, m_dist_to_focus, 0.0, 1.0);

	m_screen = m_rayTracer.getImage();
	m_rayTracer.run(m_windowWidth, m_windowHeight, m_samples_per_pixel, m_camera, m_background, &m_world, m_max_depth, m_quality);
}

void RT_App::stop() {
	m_rayTracer.reset();
}

void RT_App::draw(int posX, int posY, int width, int height) {
	m_screen->draw(posX, posY, width, height);
}

void RT_App::update() {
	m_rayTracer.update();
}

RT_App::~RT_App() {
	delete m_screen;
	delete m_camera;
}