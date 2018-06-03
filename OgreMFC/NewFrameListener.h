#include "Ogre/Ogre.h"
#include "Ogre/OgreStringConverter.h"
#include "Ogre/OgreException.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

//#include "MainFrm.h"

using namespace Ogre;

class ExaListener:public Ogre::FrameListener, public OIS::MouseListener,public Ogre::WindowEventListener, public OIS::KeyListener
{
public:
	ExaListener(RenderWindow* win,Ogre::Camera *Cam)
	{
		size_t windowHnd= 0;
		std::stringstream windowHndStr;
		windowHnd=(size_t)AfxGetMainWnd()->GetSafeHwnd();
		//win->getCustomAttribute("WINDOW",&windowHnd);
		windowHndStr<< windowHnd;
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"),windowHndStr.str()));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		_man=OIS::InputManager::createInputSystem( pl);
		_mouse = static_cast<OIS::Mouse*>(_man->createInputObject( OIS::OISMouse,true ));

		_key = static_cast<OIS::Keyboard*>(_man->createInputObject( OIS::OISKeyboard, true )); 

		 _mouse->setEventCallback(this);
		 _key->setEventCallback(this);
		 mTimeSinceLastFrame=0;



		_Cam=Cam;
		//_mouse->getMouseState().width

		unsigned int width, height, depth;
		int left, top;
		win->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = _mouse->getMouseState();
		ms.width = width;
		ms.height = height;




	}

	virtual bool frameStarted(const FrameEvent& evt)
	{
		mTimeSinceLastFrame=evt.timeSinceLastFrame;
		_mouse->capture();
		//cout<<_mouse->getMouseState().X.rel*evt.timeSinceLastFrame<<endl;
		return true;
	
	
	}
	bool mouseMoved(const OIS::MouseEvent &e)
	{
		Ogre::Vector3 trans(0.0f,0.0f,0.0f);

		 trans.z+=-0.01f*e.state.Z.rel;
		 _Cam->moveRelative(trans);

		 float rotX=e.state.X.rel*mTimeSinceLastFrame*-0.01f;
		 float rotY=e.state.Y.rel*-mTimeSinceLastFrame*-0.01f;
		 _Cam->yaw(Ogre::Radian(rotX));
		 _Cam->pitch(Ogre::Radian(rotY));
		return true;
	}
    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{


		return true;	
	}
    bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{


		return true;	
	}
    bool keyPressed(const OIS::KeyEvent &e)
	{


		return true;	
	}
    bool keyReleased(const OIS::KeyEvent &e)
	{



		return true;	
	}
private:
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _Cam;

	Real mTimeSinceLastFrame;





};