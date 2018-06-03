#pragma once
#ifndef OGREPART_H
#define OGREPART_H
#include "OgreMFC.h"
#include "Ogre\Ogre.h"
#include "Ogre\OgreConfigFile.h"
#include "NewFrameListener.h"
using namespace Ogre;

class OgrePart//:public CObject
{
	//DECLARE_SERIAL(OgrePart)
public:

	//virtual void Serialize(CArchive& ar);

	OgrePart(void);
	~OgrePart(void);

	Root*  m_pRoot;
	RenderWindow* m_pWindow;
	SceneManager* m_pSceneManager;
	Camera* m_pCamera;
	SceneNode *node1; Entity *ent1;
	FrameListener *mFrameListener;

	void SetupResource(void);
	void SetupConfig(void);
	//void CreateRanderWind();
	void CreateSceneManager(void);
	void CreateCamera(void);
	void CreateViewPort();
	void LoadResource();
	void CreateScene();
	void CreateEntity();
	void CreateFloorPlane();
	void SetupMFC();
	void CreateFrameListener();
	void Reset();

	void CreateOpenFile();
	
};

#endif