#include <iostream>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
//#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(){

	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(1024, 768), 32, false, false, false, 0);
	if (!device) return 1;
	device->setWindowCaption(L"First Irrlicht Program");
	device->getCursorControl()->setVisible(false);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* gui = device->getGUIEnvironment();




	IAnimatedMesh* mesh = smgr->getMesh("../media/test/test.x");
	if (!mesh) { device->drop(); return 1; }
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node){
		node->setMaterialFlag(EMF_LIGHTING, true);
		node->setMaterialType(EMT_SOLID);
		node->setFrameLoop(0, 372);
		node->setAnimationSpeed(5);
		node->setLoopMode(true);
		node->setScale(vector3df(20, 20, 20));
	}
	else return 1;
	smgr->setAmbientLight(SColorf(0.3f, 0.3f, 0.3f));
	ILightSceneNode* light = smgr->addLightSceneNode(0, vector3df(0.0f, 40.0f, -40.0f), SColorf(1.0f, 1.0f, 1.0f, 1.0f), 100000.0f);
	ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS(0, 90.0F, 0.01F);
	cam->setPosition(vector3df(0.0f, 40.0f, -40.0f));
	//cam->setRotation(vector3df(10.0f, 0.0f, 0.0f));

	while (device->run()){
		driver->beginScene();
		smgr->drawAll();
		driver->endScene();
	}
	
	device->drop();
	return 0;
}