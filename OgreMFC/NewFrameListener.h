#ifndef FRAMELISTENER_H
#define FRAMELISTENER_H

#include "OgreMFC.h"
//#include "Ogre/Ogre.h"
//#include "Ogre/OgreStringConverter.h"
#include "ogre/ExampleApplication.h"
//#include "Ogre/OgreException.h"
#include "ogre\SdkTrays.h"
//#define OIS_DYNAMIC_LIB
//#include <OIS/OIS.h>

//#include "MainFrm.h"
using namespace  OgreBites;
//using namespace Ogre;
using namespace std;
class ExaListener:public Ogre::FrameListener, public OIS::MouseListener,public Ogre::WindowEventListener, public OIS::KeyListener,public SdkTrayListener
{

public :
	int mCount;
public:

	ExaListener(RenderWindow* win,Ogre::Camera *Cam,SceneManager* sceneManager)
	{
		mTimeSinceLastFrame=0;
		mCount=0;
		mLMouseDown=false;
		mRMouseDown=false;
		_PolyMode = PolygonMode::PM_SOLID;
		_Cam=Cam;
		_sceneManager=sceneManager;
		mCurrentObject=NULL;
		_RaySceneQuery=_sceneManager->createRayQuery(Ray());
		_ModelName="Robot.mesh";

		mWalkSpeed=35.0f;
		initKeyandMouse(win);
		CreateUI(win);

	}

	void initKeyandMouse(RenderWindow* win);

	virtual bool frameStarted(const FrameEvent& evt);
	
	void SelectModelMove();
	
	bool mouseMoved(const OIS::MouseEvent &e);
	
    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	
    bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	
    bool keyPressed(const OIS::KeyEvent &e);
	
    bool keyReleased(const OIS::KeyEvent &e);
	
	void CameraRotation(Real x,Real y,Real z);

	void CameraMove();

	void CreateUI(RenderWindow* win);

	void itemSelected(OgreBites::SelectMenu* menu);

	void getHeightfromTerrain();

	bool nextLocation();

	void ModelMove();

	void MoveToDestination();
	
private:


	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _Cam;

	Real mTimeSinceLastFrame;
	
	Ogre::String _ModelName;

	SceneManager* _sceneManager;
	SceneNode *mCurrentObject;
	RaySceneQuery* _RaySceneQuery;

	SdkTrayManager* mTrayMgr;
	Ogre::StringVector paramsPanelItems;
	OgreBites::ParamsPanel *paramsPanel;

	OgreBites::SelectMenu *selectMenu;
	PolygonMode _PolyMode;//äÖÈ¾Ä£Ê½

	bool mLMouseDown;
	bool mRMouseDown;

	std::deque<Vector3> mWalkList;  
	Real mWalkSpeed;                 
	Real mDistance;                 
	Vector3 mDirection;              
	Vector3 mDestination;           
	AnimationState *mAnimationState1; 
	AnimationState *mAnimationState2; 
};

#endif