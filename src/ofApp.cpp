#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Mika");
	ofSetFrameRate(60);

	ofEnableAlphaBlending();
	m_menu.setup(m_menuWidth, m_paddingX, m_paddingY);
	m_window.setDimensions(m_menuWidth, 0, ofGetWidth() - 2 * m_menuWidth, ofGetHeight());

	m_animationSaver = new AnimationSaver();
	m_saveScreen = new SaveScreen(m_animationSaver, &m_window);

	m_menu.setObjects(m_sceneGraph.getObjects());
	InputController::init();

	m_camera = new Camera(&m_window);
	m_cameraController.setCamera(m_camera);

	m_menu.setCamera(m_camera);
	m_menu.setBackgroundToVectorGraphicsMenu(&m_background);
	m_menu.setVectorGraphicsInitializer(&m_vectorGraphicsInitializer);

	setupViewports();
	ofSetLogLevel(OF_LOG_ERROR);

	m_skybox.setup({
		"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg",
	});

	m_lightsController = new LightsController();
	m_menu.setLightController(m_lightsController);
	m_menu.setRTApp(&m_RT_App);

	int sceneNumber = 0;
	loadScene(sceneNumber + 48);
}

//--------------------------------------------------------------
void ofApp::update(){
	m_currentTime = ofGetElapsedTimef();
	m_deltaTime = m_currentTime - m_lastTime;
	m_lastTime = m_currentTime;

	m_sceneGraph.update();
	m_menu.update();
	m_animationSaver->update();
	m_saveScreen->update();
	if(m_RT_Mode)
		m_RT_App.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (m_RT_Mode) {
		drawRT();
		return;
	}
	if (m_isOneScreen)
		drawFullScreen();
	else
		drawHalfScreens();
	m_menu.draw();
	m_vectorGraphicsInitializer.drawStatus(m_window);
	m_saveScreen->draw(m_window);
}

void ofApp::drawScene() {
	if (m_showSkyBox)
		m_skybox.draw(*m_camera);
	else
		m_background.draw();

	if(m_showGrid)
		m_grid.draw(m_window, *m_camera);
	m_sceneGraph.draw(m_window, *m_camera);
}

void ofApp::drawSceneInWireframe() {
	m_background.draw();
	if(m_showGrid)
		m_grid.draw(m_window, *m_camera);
	m_sceneGraph.drawWireframe(m_window, *m_camera);
}

void ofApp::drawFullScreen() {
	ofPushView();
	ofViewport(m_viewportFull);
	ofSetupScreen();
	if (m_isWireFrameMode)
		drawSceneInWireframe();
	else
		drawScene();
	ofPopView();
}

void ofApp::drawHalfScreens() {
	ofPushView();
	ofViewport(m_viewportHalfTop);
	ofSetupScreen();
	if (m_isWireFrameMode)
		drawSceneInWireframe();
	else
		drawScene();
	ofPopView();

	ofPushView();
	ofViewport(m_viewportHalfBottom);
	ofSetupScreen();
	if (!m_isWireFrameMode)
		drawSceneInWireframe();
	else
		drawScene();
	ofPopView();
}

void ofApp::drawRT() {
	m_menu.draw();
	m_RT_App.draw(m_window.getX(), m_window.getY(), m_window.getWidth(), m_window.getHeight());
}

void ofApp::addObjectToScene(Object* object) {
	m_sceneGraph.addObject(object);
	m_menu.resetSceneMenu(m_sceneGraph.getObjects());
	m_menu.setActiveObject(object);
}

void ofApp::setupViewports() {
	m_viewportFull.x = m_menuWidth;
	m_viewportFull.y = 0;
	m_viewportFull.width = ofGetWindowWidth() - 2 * m_menuWidth;
	m_viewportFull.height = ofGetWindowHeight();

	m_viewportHalfTop.x = m_menuWidth;
	m_viewportHalfTop.y = 0;
	m_viewportHalfTop.width = ofGetWindowWidth() - 2 * m_menuWidth;
	m_viewportHalfTop.height = ofGetWindowHeight() / 2;

	m_viewportHalfBottom.x = m_menuWidth;
	m_viewportHalfBottom.y = ofGetWindowHeight() / 2;
	m_viewportHalfBottom.width = ofGetWindowWidth() - 2 * m_menuWidth;
	m_viewportHalfBottom.height = ofGetWindowHeight() / 2;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	InputController::keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (InputController::isNumberKey(key) && InputController::isKeyDown(KEY::CTRL) ||
		key == 1 && InputController::isKeyDown(KEY::CTRL)) {
		InputController::keyReleased(key);
		loadScene(key);
		return;
	}

	InputController::keyReleased(key);
	m_menu.keyReleased(key);
	std::vector<Object*> activeObject = m_menu.getActiveObject();
	for (size_t i = 0; i < activeObject.size(); i++) {
		activeObject[i]->keyReleased(key);
	}
	if (key == KEY::B) {
		for (size_t i = 0; i < activeObject.size(); i++) {
			if (activeObject[i]->getClassName() == "Model") {
				Model* model = dynamic_cast<Model*>(activeObject[i]);
				model->setDrawBox(!model->getDrawBox());
			}
		}
	}

	if (key == KEY::M) {
		m_isOneScreen = !m_isOneScreen;
		if(m_isOneScreen)
			m_window.setDimensions(m_menuWidth, 0, ofGetWidth() - 2 * m_menuWidth, ofGetHeight());
		else
			m_window.setDimensions(m_menuWidth, 0, ofGetWidth() - 2 * m_menuWidth, ofGetHeight() / 2);
	}
	if (key == KEY::N) {
		m_isWireFrameMode = !m_isWireFrameMode;
	}
	if (key == KEY::O) {
		if (m_camera->isOrtho())
			m_camera->disableOrtho();
		else
			m_camera->enableOrtho();
	}

	if (key == KEY::F) {
		if (!m_menu.getActiveObject().empty()) {
			glm::vec3 pos = m_menu.getActiveObject()[0]->getGlobalPosition();
			m_camera->lookAt(m_menu.getActiveObject()[0]->getGlobalPosition());
		}
	}

	if (key == OF_KEY_DEL) {
		for (size_t i = 0; i < activeObject.size(); i++) {
			m_sceneGraph.deleteObject(activeObject[i]);
			if (activeObject[i]->getClassName() == "Light") {
				m_lightsController->removeLight(dynamic_cast<Light*>(activeObject[i]));
			}
		}
		m_menu.resetSceneMenu(m_sceneGraph.getObjects());
	}
	
	if (key == 19) { // CTRL+S
		m_saveScreen->showSaveScreen();
	}

	m_vectorGraphicsInitializer.keyPressed(key);
	m_menu.setVectorGraphicsMode(m_vectorGraphicsInitializer.isVectorDrawingMode());
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	m_lastMousePosition = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	m_menu.mouseDragged(x, y, button);
	m_vectorGraphicsInitializer.mouseDragged(x - m_viewportFull.x, y - m_viewportFull.y, button);

	if (button == OF_MOUSE_BUTTON_MIDDLE)
		m_cameraController.middleMouseDraged(ofVec2f(x, y) - m_lastMousePosition);
	if (button == OF_MOUSE_BUTTON_RIGHT)
		m_cameraController.rightMouseDraged(ofVec2f(x, y) - m_lastMousePosition);
	m_lastMousePosition = ofVec2f(x, y);

	if (m_bezierCurve != nullptr && button == OF_MOUSE_BUTTON_LEFT) {
		m_bezierCurve->mouseDragged(x - m_viewportFull.x, y - m_viewportFull.y);
	}
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	m_cameraController.zoom(scrollY);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	m_menu.mousePressed(x, y, button);
	if (m_window.isInWindow(x, y)) {
		if (m_bezierCurve != nullptr && button == OF_MOUSE_BUTTON_LEFT) {
			m_bezierCurve->mousePressed(x - m_viewportFull.x, y - m_viewportFull.y);
		}
		Object* object = m_vectorGraphicsInitializer.mousePressed(x - m_viewportFull.x, y - m_viewportFull.y, button);
		if(object != nullptr)
			addObjectToScene(object);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	m_menu.mouseReleased(x, y, button);
	m_vectorGraphicsInitializer.mouseReleased(x - m_viewportFull.x, y - m_viewportFull.y, button);
	m_cameraController.mouseReleased(button);
	if (m_bezierCurve != nullptr && button == OF_MOUSE_BUTTON_LEFT) {
		m_bezierCurve->mouseReleased();
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	m_menu.setup(m_menuWidth, m_paddingX, m_paddingY);
	m_window.setDimensions(m_menuWidth, 0, ofGetWidth() - 2 * m_menuWidth, ofGetHeight());
	setupViewports();

	setupRT();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	for (size_t i = 0; i < dragInfo.files.size(); i++) {
		std::string extension = getFileExtension(dragInfo.files[i]);
		if (extension.compare(".JPG") == 0 || extension.compare(".PNG") == 0) {
			Image* image = new Image(dragInfo.files[i]);
			addObjectToScene(image);
		}
		else if (extension.compare(".DAE") == 0 || extension.compare(".OBJ") == 0 || extension.compare(".STL") == 0) {
			Model* model = new Model(dragInfo.files[i]);
			addObjectToScene(model);
		}
		else {
			std::cerr << "Cannot load asset at path : " << dragInfo.files[i]
				<< " (" << extension << " files are not yet supported)." << std::endl;
		}
	}
}

std::string ofApp::getFileExtension(const std::string& filename) {
	for (std::string::size_type i = filename.size() - 1; i > 0; i--) {
		if (filename[i] == '.') {
			std::string result = filename.substr(i, filename.size());
			std::transform(result.begin(), result.end(), result.begin(), ::toupper);
			return result;
		}
	}
	return "";
}

void ofApp::loadScene(int scene) {
	if (scene == 1) {
		std::cout << "Loading scene #10" << std::endl;
		clearScene();
		loadScene10();
		return;
	}
	if (scene < 48 || scene > 57)
		return;

	std::cout << "Loading scene #" << scene - 48 << std::endl;
	clearScene();
	switch (scene) {
	case KEY::ZERO:
		loadScene0();
		break;
	case KEY::ONE:
		loadScene1();
		break;
	case KEY::TWO:
		loadScene2();
		break;
	case KEY::THREE:
		loadScene3();
		break;
	case KEY::FOUR:
		loadScene4();
		break;
	case KEY::FIVE:
		loadScene5();
		break;
	case KEY::SIX:
		loadScene6();
		break;
	case KEY::SEVEN:
		loadScene7();
		break;
	case KEY::EIGHT:
		loadScene8();
		break;
	case KEY::NINE:
		loadScene9();
		break;
	case KEY::A:
		std::cout << "Scene A" << std::endl;
		break;
	}
}

void ofApp::clearScene() {
	std::list<Object*> objects = m_sceneGraph.getObjects();
	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		m_sceneGraph.deleteObject(*it);
	}
	m_menu.resetSceneMenu(m_sceneGraph.getObjects());
	m_menu.setVectorGraphicsMode(false);
	m_vectorGraphicsInitializer.disableDrawingMode();
	m_camera->setInitialPosition();
	m_camera->disableOrtho();
	m_showGrid = true;
	m_showSkyBox = false;
	m_menu.showToneMapping(false);
	disableRTMode();
	m_menu.showNoiseTextureMenu(false);
	m_lightsController->clear();
	m_bezierCurve = nullptr;
}

void ofApp::loadScene0() {
	m_showSkyBox = true;
	m_showGrid = false;

	Light* directionalLight = createLight(LightMode::Directional);
	directionalLight->setIntensity(2.0f);

	Model* frog = createModel("Models/Frog/Tree_frog.obj");

	frog->setRotationZ(180.0f);
	frog->setRotationX(8.0f);
	frog->translate(0.0f, 107.0f, 0.0f);
	frog->setScale(2.15f);
}

void ofApp::loadScene1() {
	m_menu.showNoiseTextureMenu(true);
	m_showSkyBox = true;
	m_showGrid = false;

	Light* directionalLight = createLight(LightMode::Directional);
	directionalLight->setIntensity(0.92f);
	directionalLight->setRotation(-35.0f, -65.0f, 0.0f);

	Model* sphere = createModel("Models/Geometry/sphere.obj");
	sphere->translate(0.0f, 107.0f, 0.0f);
	sphere->setScale(0.5f);

	NoiseTexture* noise = new NoiseTexture();
	m_textures.push_back(noise);
	m_menu.setNoiseTexture(noise);

	sphere->getMaterial()->setAllDiffuseTextures(noise);
	sphere->getMaterial()->setAllReflectionTextures(noise);
}


void ofApp::loadScene2() {
	m_showGrid = false;
	m_camera->enableOrtho();
	m_camera->moveLeft(565.0f);
	m_camera->moveDown(500.0f);

	Texture* RT_Texture = loadTexture("mika.jpg");
	Texture* texture1 = RT_Texture->getTextureWithLut(Lut(LutName::Byers));
	Texture* texture2 = RT_Texture->getTextureWithLut(Lut(LutName::Ava));
	Texture* texture3 = RT_Texture->getTextureWithLut(Lut(LutName::Folger));
	Texture* texture4 = RT_Texture->getTextureWithLut(Lut(LutName::Zeke));
	Texture* texture5 = RT_Texture->getTextureWithLut(Lut(LutName::Zed));

	Texture* texture6 = RT_Texture->getTextureWithGaussianBlurFilter();
	Texture* texture7 = RT_Texture->getTextureWithRidgeDetectionFilter();
	Texture* texture8 = RT_Texture->getTextureWithSharpenFilter();

	m_textures.push_back(texture1);
	m_textures.push_back(texture2);
	m_textures.push_back(texture3);
	m_textures.push_back(texture4);
	m_textures.push_back(texture5);
	m_textures.push_back(texture6);
	m_textures.push_back(texture7);
	m_textures.push_back(texture8);

	int planeWidth = 252.0f;
	int planeHeight = 336.0f;

	Plane* plane = new Plane(planeWidth, planeHeight, RT_Texture);
	Plane* plane1 = new Plane(planeWidth, planeHeight, texture1);
	Plane* plane2 = new Plane(planeWidth, planeHeight, texture2);
	Plane* plane3 = new Plane(planeWidth, planeHeight, texture3);
	Plane* plane4 = new Plane(planeWidth, planeHeight, texture4);
	Plane* plane5 = new Plane(planeWidth, planeHeight, texture5);
	Plane* plane6 = new Plane(planeWidth, planeHeight, texture6);
	Plane* plane7 = new Plane(planeWidth, planeHeight, texture7);
	Plane* plane8 = new Plane(planeWidth, planeHeight, texture8);


	plane->translate(-875.0f, 0.0f, 0.0f);
	plane1->translate(-875.0f + (planeWidth + 50.0f) * 1, 0.0f, 0.0f);
	plane2->translate(-875.0f + (planeWidth + 50.0f) * 2, 0.0f, 0.0f);

	plane3->translate(-875.0f, -planeHeight - 50.0f, 0.0f);
	plane4->translate(-875.0f + (planeWidth + 50.0f) * 1, -planeHeight - 50.0f, 0.0f);
	plane5->translate(-875.0f + (planeWidth + 50.0f) * 2, -planeHeight - 50.0f, 0.0f);

	plane6->translate(-875.0f, -planeHeight * 2.0f - 100.0f, 0.0f);
	plane7->translate(-875.0f + (planeWidth + 50.0f) * 1, -planeHeight * 2.0f - 100.0f, 0.0f);
	plane8->translate(-875.0f + (planeWidth + 50.0f) * 2, -planeHeight * 2.0f - 100.0f, 0.0f);

	plane->setRotationZ(180.0f);
	plane1->setRotationZ(180.0f);
	plane2->setRotationZ(180.0f);
	plane3->setRotationZ(180.0f);
	plane4->setRotationZ(180.0f);
	plane5->setRotationZ(180.0f);
	plane6->setRotationZ(180.0f);
	plane7->setRotationZ(180.0f);
	plane8->setRotationZ(180.0f);

	plane->setRotationY(180.0f);
	plane1->setRotationY(180.0f);
	plane2->setRotationY(180.0f);
	plane3->setRotationY(180.0f);
	plane4->setRotationY(180.0f);
	plane5->setRotationY(180.0f);
	plane6->setRotationY(180.0f);
	plane7->setRotationY(180.0f);
	plane8->setRotationY(180.0f);

	addObjectToScene(plane);
	addObjectToScene(plane1);
	addObjectToScene(plane2);
	addObjectToScene(plane3);
	addObjectToScene(plane4);
	addObjectToScene(plane5);
	addObjectToScene(plane6);
	addObjectToScene(plane7);
	addObjectToScene(plane8);
}

void ofApp::loadScene3() {
	m_menu.showToneMapping(true);
	m_showGrid = false;
	m_camera->enableOrtho();
	m_camera->moveDown(210.0f);

	Texture* RT_Texture = loadTexture("mika/IMG_2603.JPG");
	Texture* texture1 = loadTexture("mika/IMG_3514.JPG");

	int planeWidth = 300.0f;
	int planeHeight = planeWidth * 4.0f / 3.0f;

	Plane* plane = new Plane(planeWidth, planeHeight, RT_Texture);
	Plane* plane1 = new Plane(planeWidth, planeHeight, RT_Texture);
	Plane* plane2 = new Plane(planeWidth, planeHeight, texture1);
	Plane* plane3 = new Plane(planeWidth, planeHeight, texture1);

	plane1->changeShaders("shaders/model_330_vs.glsl", "shaders/tone_mapping_330_fs.glsl");
	plane3->changeShaders("shaders/model_330_vs.glsl", "shaders/tone_mapping_330_fs.glsl");


	plane->translate(-planeWidth / 2 - 5, planeHeight / 2, 0.0f);
	plane1->translate(planeWidth / 2 + 5, planeHeight / 2, 0.0f);
	plane2->translate(-planeWidth / 2 - 5, -planeHeight / 2 - 10, 0.0f);
	plane3->translate(planeWidth / 2 + 5, -planeHeight / 2 - 10, 0.0f);

	plane->setRotationZ(180.0f);
	plane1->setRotationZ(180.0f);
	plane2->setRotationZ(180.0f);
	plane3->setRotationZ(180.0f);

	plane->setRotationY(180.0f);
	plane1->setRotationY(180.0f);
	plane2->setRotationY(180.0f);
	plane3->setRotationY(180.0f);

	addObjectToScene(plane);
	addObjectToScene(plane1);
	addObjectToScene(plane2);
	addObjectToScene(plane3);

	m_menu.setToneMappingMenuActiveObjects({ plane1, plane3 });
}

void ofApp::loadScene4() {
	m_showGrid = false;

	Model* model = createModel("Models/Dinosaurs/tyrannosaurus.dae");

	model->setRotationX(-90.0f);
	model->setRotationY(238.0f);
	model->setPosition(-74.0f, 97.0f, 212.0f);

	Texture* white = loadTexture("white.jpg");
	model->getMaterial()->setAllDiffuseTextures(white);
	model->getMaterial()->setAllReflectionTextures(white);

	Light* light1 = createLight(LightMode::Point);
	Light* light2 = createLight(LightMode::Spot);
	Light* light3 = createLight(LightMode::Directional);
	Light* light4 = createLight(LightMode::Ambient);

	light1->setPosition(118.0f, 280.0f, 398.0f);
	light1->setDiffuseColor(1.0f, 1.0f, 1.0f);
	light1->setRotationX(0.0f);

	light2->setPosition(-118.0f, 280.0f, 398.0f);
	light2->setDiffuseColor(1.0f, 1.0f, 1.0f);
	light2->setRotationX(140.0f);

	light4->setPosition(455.0, 186.0f, 0.0f);
	light4->setIntensity(0.5f);
}

void ofApp::loadScene5() {
	m_showGrid = false;

	Light* light = new Light(LightMode::Point);
	light->setPosition(0.0, 286.0f, 589.0f);
	addObjectToScene(light);

	m_lightsController->addLight(light);

	Model* model1 = new Model("Models/Robots/RedRobot_OBJ/RedRobot.obj");
	Model* model2 = new Model("Models/Robots/obj_smooth_pbr.obj");
	Model* model3 = new Model("Models/Dinosaurs/tyrannosaurus.dae");

	m_material1.setNumberOfMeshes(model1->getNumOfMesh());
	m_material2.setNumberOfMeshes(model2->getNumOfMesh());
	m_material3.setNumberOfMeshes(model3->getNumOfMesh());

	setMaterials(model1, model2, model3);

	model1->setMaterial(m_material1);
	model1->setLightsController(m_lightsController);
	model1->changeShaders("shaders/blinn_phong_420_vs.glsl", "shaders/blinn_phong_420_fs.glsl");

	model1->setRotationX(180.0f);
	model1->setRotationY(242.0f);
	model1->setScale(1.3f);
	model1->setPosition(-254.0f, 233.0f, 256.0f);

	model2->setMaterial(m_material2);
	model2->changeShaders("shaders/phong_420_vs.glsl", "shaders/phong_420_fs.glsl");
	model2->setLightsController(m_lightsController);

	model2->setRotationX(180.0f);
	model2->setRotationY(145.0f);
	model2->setScale(1.3f);
	model2->setPosition(226.0f, 238.0f, 191.0f);

	model3->setMaterial(m_material3);
	model3->setRotationX(-90.0f);
	model3->setRotationY(194.0f);
	model3->setPosition(-74.0f, 97.0f, 212.0f);

	model3->changeShaders("shaders/gouraud_420_vs.glsl", "shaders/gouraud_420_fs.glsl");
	model3->setLightsController(m_lightsController);

	addObjectToScene(model1);
	addObjectToScene(model2);
	addObjectToScene(model3);
}

void ofApp::loadScene6() {
	m_showGrid = false;
	m_camera->enableOrtho();
	m_camera->setPosition(m_camera->getPosition() - glm::vec3(0.0f, 200.0f, 0.0f));

	Texture* brick = loadTexture("textures/Brick_Mortar_vmdkahflw_2K_surface_ms/vmdkahflw_2K_Albedo.jpg");
	Texture* brickNormal = loadTexture("textures/Brick_Mortar_vmdkahflw_2K_surface_ms/vmdkahflw_2K_Normal.jpg");

	Texture* ground = loadTexture("textures/Rock_Rough_vl0hccalw_2K_surface_ms/vl0hccalw_2K_Albedo.jpg");
	Texture* groundNormal = loadTexture("textures/Rock_Rough_vl0hccalw_2K_surface_ms/vl0hccalw_2K_Normal.jpg");

	Texture* white = loadTexture("white.jpg");


	Model* sphere1 = new Model("Models/Geometry/sphere.obj");
	sphere1->setPosition(-237, 227, 222);
	sphere1->setScale(0.52f);
	sphere1->changeShaders("shaders/normal_420_vs.glsl", "shaders/normal_420_fs.glsl");
	sphere1->setLightsController(m_lightsController);
	sphere1->getMaterial()->setAllDiffuseTextures(ground);
	sphere1->getMaterial()->setNormalMap(0, groundNormal);
	sphere1->setTileX(1.5f);
	addObjectToScene(sphere1);

	Model* sphere2 = new Model("Models/Geometry/sphere.obj");
	sphere2->setPosition(237, 227, 222);
	sphere2->setScale(0.52f);
	sphere2->changeShaders("shaders/phong_420_vs.glsl", "shaders/phong_420_fs.glsl");
	sphere2->setLightsController(m_lightsController);
	sphere2->getMaterial()->setAllDiffuseTextures(ground);
	sphere2->setTileX(1.5f);
	addObjectToScene(sphere2);

	Model* sphere3 = new Model("Models/Geometry/sphere.obj");
	sphere3->setPosition(-237, -227, 222);
	sphere3->setScale(0.52f);
	sphere3->changeShaders("shaders/normal_420_vs.glsl", "shaders/normal_420_fs.glsl");
	sphere3->setLightsController(m_lightsController);
	sphere3->getMaterial()->setAllDiffuseTextures(brick);
	sphere3->getMaterial()->setNormalMap(0, brickNormal);
	sphere3->setTileX(2.0f);
	addObjectToScene(sphere3);

	Model* sphere4 = new Model("Models/Geometry/sphere.obj");
	sphere4->setPosition(237, -227, 222);
	sphere4->setScale(0.52f);
	sphere4->changeShaders("shaders/phong_420_vs.glsl", "shaders/phong_420_fs.glsl");
	sphere4->setLightsController(m_lightsController);
	sphere4->getMaterial()->setAllDiffuseTextures(brick);
	sphere4->setTileX(2.0f);
	addObjectToScene(sphere4);

	Light* light1 = createLight(LightMode::Directional);
	light1->setRotationX(-30);
	light1->setRotationY(35);
	light1->setIntensity(2.61f);
}

void ofApp::loadScene7() {
	enableRTMode();
}

void ofApp::loadScene8() {
	m_showGrid = false;

	Delaunay* delaunay = new Delaunay();
	addObjectToScene(delaunay);
}

void ofApp::loadScene9() {
	m_showGrid = false;
	Light* light = createLight(LightMode::Point);
	light->setIntensity(3.24f);
	light->setPosition(401.0f, 328.0f, 149.0f);

	Texture* white = loadTexture("white.jpg");

	PBR_Model* model = createPBRModel("PBR/robotitus.obj");
	model->setRotation(162.0f, 181.0f, 0.0f);
	model->setPosition(0.0, 197.0f, 514.0f);

	Texture* roughness0 = loadTexture("PBR/test003_test002_Roughness.png");
	Texture* roughness1 = loadTexture("PBR/test003_test003_007_Roughness.png");
	Texture* roughness2 = loadTexture("PBR/test003_test003_006_Roughness.png");
	Texture* roughness3 = loadTexture("PBR/test003_test003_005_Roughness.png");
	Texture* roughness4 = loadTexture("PBR/test003_test003_004_Roughness.png");
	Texture* roughness5 = loadTexture("PBR/test003_test003_003_Roughness.png");
	Texture* roughness6 = loadTexture("PBR/test003_test003_002_Roughness.png");
	Texture* roughness7 = loadTexture("PBR/test003_test003_001_Roughness.png");
	Texture* roughness8 = loadTexture("PBR/test003_test003_Roughness.png");

	Texture* metallic0 = loadTexture("PBR/test003_test002_Metallic.png");
	Texture* metallic1 = loadTexture("PBR/test003_test003_007_Metallic.png");
	Texture* metallic2 = loadTexture("PBR/test003_test003_006_Metallic.png");
	Texture* metallic3 = loadTexture("PBR/test003_test003_005_Metallic.png");
	Texture* metallic4 = loadTexture("PBR/test003_test003_004_Metallic.png");
	Texture* metallic5 = loadTexture("PBR/test003_test003_003_Metallic.png");
	Texture* metallic6 = loadTexture("PBR/test003_test003_002_Metallic.png");
	Texture* metallic7 = loadTexture("PBR/test003_test003_001_Metallic.png");
	Texture* metallic8 = loadTexture("PBR/test003_test003_Metallic.png");

	Texture* normal0 = loadTexture("PBR/test003_test002_Normal.png");
	Texture* normal1 = loadTexture("PBR/test003_test003_007_Normal.png");
	Texture* normal2 = loadTexture("PBR/test003_test003_006_Normal.png");
	Texture* normal3 = loadTexture("PBR/test003_test003_005_Normal.png");
	Texture* normal4 = loadTexture("PBR/test003_test003_004_Normal.png");
	Texture* normal5 = loadTexture("PBR/test003_test003_003_Normal.png");
	Texture* normal6 = loadTexture("PBR/test003_test003_002_Normal.png");
	Texture* normal7 = loadTexture("PBR/test003_test003_001_Normal.png");
	Texture* normal8 = loadTexture("PBR/test003_test003_Normal.png");


	model->getMaterial()->setRoughnessTexture(0, roughness0);
	model->getMaterial()->setRoughnessTexture(1, roughness1);
	model->getMaterial()->setRoughnessTexture(2, roughness2);
	model->getMaterial()->setRoughnessTexture(3, roughness3);
	model->getMaterial()->setRoughnessTexture(4, roughness4);
	model->getMaterial()->setRoughnessTexture(5, roughness5);
	model->getMaterial()->setRoughnessTexture(6, roughness6);
	model->getMaterial()->setRoughnessTexture(7, roughness7);
	model->getMaterial()->setRoughnessTexture(8, roughness8);

	model->getMaterial()->setMetallicTexture(0, metallic0);
	model->getMaterial()->setMetallicTexture(1, metallic1);
	model->getMaterial()->setMetallicTexture(2, metallic2);
	model->getMaterial()->setMetallicTexture(3, metallic3);
	model->getMaterial()->setMetallicTexture(4, metallic4);
	model->getMaterial()->setMetallicTexture(5, metallic5);
	model->getMaterial()->setMetallicTexture(6, metallic6);
	model->getMaterial()->setMetallicTexture(7, metallic7);
	model->getMaterial()->setMetallicTexture(8, metallic8);

	model->getMaterial()->setNormalMap(0, normal0);
	model->getMaterial()->setNormalMap(1, normal1);
	model->getMaterial()->setNormalMap(2, normal2);
	model->getMaterial()->setNormalMap(3, normal3);
	model->getMaterial()->setNormalMap(4, normal4);
	model->getMaterial()->setNormalMap(5, normal5);
	model->getMaterial()->setNormalMap(6, normal6);
	model->getMaterial()->setNormalMap(7, normal7);
	model->getMaterial()->setNormalMap(8, normal8);

	model->changeShaders("shaders/normal_420_vs.glsl", "shaders/pbr_420_fs.glsl");
	model->setLightsController(m_lightsController);
}

void ofApp::loadScene10() {
	m_showGrid = false;

	BezierCurve* bezierCurve = new BezierCurve(m_window);
	addObjectToScene(bezierCurve);
	m_bezierCurve = bezierCurve;
}

Texture* ofApp::loadTexture(const std::string& filename, bool HDR) {
	Texture* RT_Texture = new Texture(filename, HDR);
	m_textures.push_back(RT_Texture);
	return RT_Texture;
}

void ofApp::setMaterials(Model* model1, Model* model2, Model* model3) {
	Texture* diffuseTexture = loadTexture("Models/Robots/RedRobot_OBJ/red robot_Diffuse.png");
	Texture* reflectionTexture = loadTexture("Models/Robots/RedRobot_OBJ/red robot_Reflection.png");

	m_material1.setAllDiffuseTextures(diffuseTexture);
	m_material1.setAllReflectionTextures(reflectionTexture);

	Texture* texture0 = loadTexture("Models/Robots/End_textures/_Diffuse_0.png");
	Texture* texture1 = loadTexture("Models/Robots/End_textures/_Diffuse_1.png");
	Texture* texture2 = loadTexture("Models/Robots/End_textures/_Diffuse_2.png");
	Texture* texture3 = loadTexture("Models/Robots/End_textures/_Diffuse_3.png");
	Texture* texture4 = loadTexture("Models/Robots/End_textures/_Diffuse_4.png");
	Texture* texture5 = loadTexture("Models/Robots/End_textures/_Diffuse_5.png");
	Texture* texture6 = loadTexture("Models/Robots/End_textures/_Diffuse_6.png");
	Texture* texture7 = loadTexture("Models/Robots/End_textures/_Diffuse_7.png");
	Texture* texture8 = loadTexture("Models/Robots/End_textures/_Diffuse_8.png");

	m_material2.setDiffuseTexture(0, texture0);
	m_material2.setDiffuseTexture(1, texture1);
	m_material2.setDiffuseTexture(2, texture3);
	m_material2.setDiffuseTexture(3, texture2);
	m_material2.setDiffuseTexture(4, texture1);
	m_material2.setDiffuseTexture(5, texture6);
	m_material2.setDiffuseTexture(6, texture6);
	m_material2.setDiffuseTexture(7, texture1);
	m_material2.setDiffuseTexture(8, texture6);
	m_material2.setDiffuseTexture(9, texture4);
	m_material2.setDiffuseTexture(10, texture2);
	m_material2.setDiffuseTexture(11, texture1);
	m_material2.setDiffuseTexture(12, texture6);
	m_material2.setDiffuseTexture(13, texture0);
	m_material2.setDiffuseTexture(14, texture5);
	m_material2.setDiffuseTexture(15, texture1);
	m_material2.setDiffuseTexture(16, texture1);
	m_material2.setDiffuseTexture(17, texture6);
	m_material2.setDiffuseTexture(18, texture0);
	m_material2.setDiffuseTexture(19, texture5);
	m_material2.setDiffuseTexture(20, texture1);
	m_material2.setDiffuseTexture(21, texture6);
	m_material2.setDiffuseTexture(22, texture1);
	m_material2.setDiffuseTexture(23, texture0);
	m_material2.setDiffuseTexture(24, texture6);
	m_material2.setDiffuseTexture(25, texture1);
	m_material2.setDiffuseTexture(26, texture6);
	m_material2.setDiffuseTexture(27, texture0);
	m_material2.setDiffuseTexture(28, texture1);
	m_material2.setDiffuseTexture(29, texture5);
	m_material2.setDiffuseTexture(30, texture6);
	m_material2.setDiffuseTexture(31, texture0);
	m_material2.setDiffuseTexture(32, texture7);
	m_material2.setDiffuseTexture(33, texture7);
	m_material2.setDiffuseTexture(34, texture7);
	m_material2.setDiffuseTexture(35, texture6);
	m_material2.setDiffuseTexture(36, texture7);
	m_material2.setDiffuseTexture(37, texture6);
	m_material2.setDiffuseTexture(38, texture3);
	m_material2.setDiffuseTexture(39, texture1);
	m_material2.setDiffuseTexture(40, texture5);
	m_material2.setDiffuseTexture(41, texture8);
	m_material2.setDiffuseTexture(42, texture4);
	m_material2.setDiffuseTexture(43, texture6);
	m_material2.setDiffuseTexture(44, texture1);
	m_material2.setDiffuseTexture(45, texture6);

	Texture* stexture0 = loadTexture("Models/Robots/End_textures/_Specular_0.png");
	Texture* stexture1 = loadTexture("Models/Robots/End_textures/_Specular_1.png");
	Texture* stexture2 = loadTexture("Models/Robots/End_textures/_Specular_2.png");
	Texture* stexture3 = loadTexture("Models/Robots/End_textures/_Specular_3.png");
	Texture* stexture4 = loadTexture("Models/Robots/End_textures/_Specular_4.png");
	Texture* stexture5 = loadTexture("Models/Robots/End_textures/_Specular_5.png");
	Texture* stexture6 = loadTexture("Models/Robots/End_textures/_Specular_6.png");
	Texture* stexture7 = loadTexture("Models/Robots/End_textures/_Specular_7.png");
	Texture* stexture8 = loadTexture("Models/Robots/End_textures/_Specular_8.png");

	m_material2.setReflectionTexture(0, stexture0);
	m_material2.setReflectionTexture(1, stexture1);
	m_material2.setReflectionTexture(2, stexture3);
	m_material2.setReflectionTexture(3, stexture2);
	m_material2.setReflectionTexture(4, stexture1);
	m_material2.setReflectionTexture(5, stexture6);
	m_material2.setReflectionTexture(6, stexture6);
	m_material2.setReflectionTexture(7, stexture1);
	m_material2.setReflectionTexture(8, stexture6);
	m_material2.setReflectionTexture(9, stexture4);
	m_material2.setReflectionTexture(10, stexture2);
	m_material2.setReflectionTexture(11, stexture1);
	m_material2.setReflectionTexture(12, stexture6);
	m_material2.setReflectionTexture(13, stexture0);
	m_material2.setReflectionTexture(14, stexture5);
	m_material2.setReflectionTexture(15, stexture1);
	m_material2.setReflectionTexture(16, stexture1);
	m_material2.setReflectionTexture(17, stexture6);
	m_material2.setReflectionTexture(18, stexture0);
	m_material2.setReflectionTexture(19, stexture5);
	m_material2.setReflectionTexture(20, stexture1);
	m_material2.setReflectionTexture(21, stexture6);
	m_material2.setReflectionTexture(22, stexture1);
	m_material2.setReflectionTexture(23, stexture0);
	m_material2.setReflectionTexture(24, stexture6);
	m_material2.setReflectionTexture(25, stexture1);
	m_material2.setReflectionTexture(26, stexture6);
	m_material2.setReflectionTexture(27, stexture0);
	m_material2.setReflectionTexture(28, stexture1);
	m_material2.setReflectionTexture(29, stexture5);
	m_material2.setReflectionTexture(30, stexture6);
	m_material2.setReflectionTexture(31, stexture0);
	m_material2.setReflectionTexture(32, stexture7);
	m_material2.setReflectionTexture(33, stexture7);
	m_material2.setReflectionTexture(34, stexture7);
	m_material2.setReflectionTexture(35, stexture6);
	m_material2.setReflectionTexture(36, stexture7);
	m_material2.setReflectionTexture(37, stexture6);
	m_material2.setReflectionTexture(38, stexture3);
	m_material2.setReflectionTexture(39, stexture1);
	m_material2.setReflectionTexture(40, stexture5);
	m_material2.setReflectionTexture(41, stexture8);
	m_material2.setReflectionTexture(42, stexture4);
	m_material2.setReflectionTexture(43, stexture6);
	m_material2.setReflectionTexture(44, stexture1);
	m_material2.setReflectionTexture(45, stexture6);

	Texture* white = loadTexture("white.jpg");
	m_material3.setAllDiffuseTextures(white);
	m_material3.setAllReflectionTextures(white);

	model1->resetAllColors();
	model2->resetAllColors();

	for (size_t i = 0; i < model1->getNumOfMesh(); i++) {
		m_material1.setAmbientColor(i, model1->getMaterial()->getAmbientColor(i));
		m_material1.setDiffuseColor(i, model1->getMaterial()->getDiffuseColor(i));
		m_material1.setSpecularColor(i, model1->getMaterial()->getSpecularColor(i));
		m_material1.setShininess(i, model1->getMaterial()->getShininess(i));
	}
	for (size_t i = 0; i < model2->getNumOfMesh(); i++) {
		m_material2.setAmbientColor(i, model2->getMaterial()->getAmbientColor(i));
		m_material2.setDiffuseColor(i, model2->getMaterial()->getDiffuseColor(i));
		m_material2.setSpecularColor(i, model2->getMaterial()->getSpecularColor(i));
		m_material2.setShininess(i, model2->getMaterial()->getShininess(i));
	}
	for (size_t i = 0; i < model3->getNumOfMesh(); i++) {
		m_material3.setAmbientColor(i, model3->getMaterial()->getAmbientColor(i));
		m_material3.setDiffuseColor(i, model3->getMaterial()->getDiffuseColor(i));
		m_material3.setSpecularColor(i, model3->getMaterial()->getSpecularColor(i));
		m_material3.setShininess(i, model3->getMaterial()->getShininess(i));
	}
}

Light* ofApp::createLight(LightMode lightMode) {
	Light* light = new Light(lightMode);
	addObjectToScene(light);
	m_lightsController->addLight(light);
	return light;
}

Model* ofApp::createModel(const std::string& filename, bool HDR) {
	Model* model = new Model(filename);
	model->setLightsController(m_lightsController);

	addObjectToScene(model);

	std::map<int, std::string> diffusePaths = model->getDiffuseTexturesPath();
	for (int i = 0; i < model->getNumOfMesh(); i++) {
		std::map<int, std::string>::iterator path = diffusePaths.find(i);
		if (path != diffusePaths.end() && path->second != "") {
			std::string texturePath = getDirectory(filename) + path->second;
			Texture* RT_Texture = loadTexture(texturePath, HDR);
			model->getMaterial()->setDiffuseTexture(i, RT_Texture);
		}
	}

	std::map<int, std::string> normalsPaths = model->getNormalsTexturesPath();
	for (int i = 0; i < model->getNumOfMesh(); i++) {
		std::map<int, std::string>::iterator path = normalsPaths.find(i);
		if (path != normalsPaths.end() && path->second != "") {
			std::string texturePath = getDirectory(filename) + path->second;
			Texture* RT_Texture = loadTexture(texturePath);
			model->getMaterial()->setNormalMap(i, RT_Texture);
		}
	}

	return model;
}

PBR_Model* ofApp::createPBRModel(const std::string& filename) {
	PBR_Model* model = new PBR_Model(filename);
	model->setLightsController(m_lightsController);
	addObjectToScene(model);

	std::map<int, std::string> diffusePaths = model->getDiffuseTexturesPath();
	for (int i = 0; i < model->getNumOfMesh(); i++) {
		std::map<int, std::string>::iterator path = diffusePaths.find(i);
		if (path != diffusePaths.end() && path->second != "") {
			std::string texturePath = getDirectory(filename) + path->second;
			Texture* RT_Texture = loadTexture(texturePath, true);
			model->getMaterial()->setDiffuseTexture(i, RT_Texture);
		}
	}

	return model;
}

void ofApp::setupRT() {
	m_menu.setRTApp(&m_RT_App);
	m_RT_App.setWindowSize(m_window.getWidth(), m_window.getHeight());
}

void ofApp::enableRTMode() {
	m_RT_Mode = true;
	m_menu.setRTMode(true);
}

void ofApp::disableRTMode() {
	m_RT_Mode = false;
	m_menu.setRTMode(false);
}


void ofApp::exit() {
	delete m_animationSaver;
	delete m_saveScreen;
	delete m_camera;
	delete m_lightsController;

	for (size_t i = 0; i < m_textures.size(); i++) {
		delete m_textures[i];
	}
}
