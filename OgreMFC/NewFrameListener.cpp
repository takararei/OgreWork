#include "stdafx.h"
#include "NewFrameListener.h"



bool ExaListener::frameStarted(const FrameEvent& evt)
{
	mTimeSinceLastFrame=evt.timeSinceLastFrame;
	_key->capture();
	_mouse->capture();
	mTrayMgr->refreshCursor();
	mTrayMgr->frameRenderingQueued(evt);
	
	CameraMove();
	getHeightfromTerrain();
	/*SelectModelMove();*/
	MoveToDestination();
	ModelMove();
	return true;


}

void ExaListener::MoveToDestination()
{
	
	
	if (mDirection == Vector3::ZERO) 
	{
		if (nextLocation()) 
		{
			// Set walking animation
			Entity* mEntity=(Entity*)(mCurrentObject->getAttachedObject(mCurrentObject->getName().substr(0,mCurrentObject->getName().length()-4)));
			mAnimationState1 = mEntity->getAnimationState("Walk");
			mAnimationState1->setLoop(true);
			mAnimationState1->setEnabled(true);
			
		}
	}
	else
	{

		Real move = mWalkSpeed * mTimeSinceLastFrame;
		mDistance -= move;
		if (mDistance <= 0.0f)
		{
			if (mCurrentObject==NULL)
			{
				return;
			}
			mCurrentObject->setPosition(mDestination+Vector3(0,15,0));//需要修改一下高度
			mDirection = Vector3::ZERO;
			
			if (!nextLocation())
			{
				// Set Idle animation   
				Entity* mEntity=(Entity*)(mCurrentObject->getAttachedObject(mCurrentObject->getName().substr(0,mCurrentObject->getName().length()-4)));
				mAnimationState1 = mEntity->getAnimationState("Idle");
				mAnimationState1->setLoop(false);
				mAnimationState1->setEnabled(true);
			} 
		}
		else
		{
			Ray cameraRay(Vector3(mCurrentObject->getPosition().x, 5000.0f, mCurrentObject->getPosition().z), Vector3::NEGATIVE_UNIT_Y);
			_RaySceneQuery->setRay(cameraRay);

			RaySceneQueryResult &result = _RaySceneQuery->execute();

			RaySceneQueryResult::iterator itr=result.begin();
			if (itr!=result.end()&&itr->worldFragment)
			{
				Real terrainHeight=itr->worldFragment->singleIntersection.y;

				mCurrentObject->setPosition(mCurrentObject->getPosition().x,terrainHeight+10.0f,mCurrentObject->getPosition().z);

			}
			mCurrentObject->translate(mDirection * move);
		} 
	} 
	mAnimationState1->addTime(mTimeSinceLastFrame);

}

void ExaListener::ModelMove()
{
	if (mCurrentObject==NULL)
	{
		return;
	}
	Ogre::Vector3 translate(0,0,0);
	float _rotation = 0.0f;
	if(_key->isKeyDown(OIS::KC_UP))
	{
		translate += Ogre::Vector3(0,0,-1);
		_rotation = 3.14f;
	}
	if(_key->isKeyDown(OIS::KC_DOWN))
	{
		translate += Ogre::Vector3(0,0,1);
		_rotation = 0.0f;
	}
	if(_key->isKeyDown(OIS::KC_LEFT))
	{
		translate += Ogre::Vector3(-1,0,0);
		_rotation = -1.57f;
	}
	if(_key->isKeyDown(OIS::KC_RIGHT))
	{
		translate += Ogre::Vector3(1,0,0);
		_rotation = 1.57f;
	}

	mCurrentObject->translate(translate * mTimeSinceLastFrame * mWalkSpeed);
	mCurrentObject->resetOrientation();
	mCurrentObject->yaw(Radian(_rotation));
}

bool ExaListener::nextLocation()
{
	if (mWalkList.empty())
		return false;
	mDestination = mWalkList.front();  // this gets the front of the deque
	mWalkList.pop_front();             // this removes the front of the deque
	mDirection = (mDestination - mCurrentObject->getPosition());
	mDistance = mDirection.normalise();
	Vector3 src = mCurrentObject->getOrientation() * Vector3::UNIT_X;//获得人脸朝向
	if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) 
	{
		mCurrentObject->yaw(Degree(180));
	}
	else
	{
		Ogre::Quaternion quat = src.getRotationTo(mDirection);
		mCurrentObject->rotate(quat);
	} 
	return true;
} 

void ExaListener::getHeightfromTerrain()//相机
{
	Vector3 camPos = _Cam->getPosition();
	Ray cameraRay(Vector3(camPos.x, 5000.0f, camPos.z), Vector3::NEGATIVE_UNIT_Y);//指向地面
	_RaySceneQuery->clearResults();
	_RaySceneQuery->setRay(cameraRay);
	_RaySceneQuery->setQueryMask(0);

	RaySceneQueryResult &result = _RaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();
	if (itr != result.end() && itr->worldFragment)
	{
		Real terrainHeight = itr->worldFragment->singleIntersection.y;
		_Cam->setPosition( camPos.x, terrainHeight + 80, camPos.z );
	}

}

void ExaListener::SelectModelMove()
{
	if (mLMouseDown)
	{
		if (mCurrentObject==NULL)
		{
			return;
		}
		Ray mouseRay = mTrayMgr->getCursorRay(_Cam);
		_RaySceneQuery->setRay(mouseRay);
		_RaySceneQuery->setQueryMask(0);
		RaySceneQueryResult &result = _RaySceneQuery->execute();
		RaySceneQueryResult::iterator itr = result.begin();
		if (itr != result.end() && itr->worldFragment)
		{
			Ogre::Vector3 pos=itr->worldFragment->singleIntersection;
			if(mCurrentObject->getName().substr(0, 6)=="Sinbad")
			{
				mCurrentObject->setPosition(pos);
				Vector3 objpos=mCurrentObject->getPosition();
				mCurrentObject->setPosition(Vector3(objpos.x,objpos.y+20.0f,objpos.z));
			}
			else
				mCurrentObject->setPosition(pos);


			String modelname=mCurrentObject->getName();
			paramsPanel->setParamValue( 1, modelname);
			paramsPanel->setParamValue(0,modelname.substr(0,modelname.length()-4));
			Vector3 postemp = mCurrentObject->getPosition();
			char posx[20];
			char posy[20];
			char posz[20];
			sprintf_s(posx,"%.1f",(float)postemp.x);
			sprintf_s(posy,"%.1f",(float)postemp.y);
			sprintf_s(posz,"%.1f",(float)postemp.z);
			String position="";
			position=position+"( "+ posx +" , "+ posy +" , "+ posz +" )";
			paramsPanel->setParamValue(2,position);
		}
	} 
}

bool ExaListener::mouseMoved(const OIS::MouseEvent &e)
{
	CameraRotation(e.state.X.rel,e.state.Y.rel,e.state.Z.rel);
	SelectModelMove();
	mTrayMgr->injectMouseMove(e);
	return true;
}

void ExaListener::CameraRotation(Real x,Real y,Real z)
{
	Ogre::Vector3 trans(0.0f,0.0f,0.0f);

	trans.z+=-0.01f*z;
	_Cam->moveRelative(trans);

	float rotX=x*mTimeSinceLastFrame*-0.01f;
	float rotY=y*mTimeSinceLastFrame*-0.01f;
	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));

}

void ExaListener::CameraMove()
{
	Ogre::Vector3 translate(0,0,0);
	if(_key->isKeyDown(OIS::KC_W))
	{
		translate += Ogre::Vector3(0,0,-1);
	}
	if(_key->isKeyDown(OIS::KC_S))
	{
		translate += Ogre::Vector3(0,0,1);
	}
	if(_key->isKeyDown(OIS::KC_A))
	{
		translate += Ogre::Vector3(-1,0,0);
	}
	if(_key->isKeyDown(OIS::KC_D))
	{
		translate += Ogre::Vector3(1,0,0);
	}
	_Cam->moveRelative(translate*mTimeSinceLastFrame * 100.0f);
}

bool ExaListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{

	if (!mTrayMgr->injectMouseDown(e,id))
	{
		if(id==OIS::MB_Left)
		{
			if (mCurrentObject)
				mCurrentObject->showBoundingBox(false);

			mLMouseDown = true;

			Ray mouseRay=mTrayMgr->getCursorRay(_Cam);
			_RaySceneQuery->setRay(mouseRay);
			_RaySceneQuery->setSortByDistance(true);
			_RaySceneQuery->setQueryMask(1<<0);
			RaySceneQueryResult &result = _RaySceneQuery->execute();
			RaySceneQueryResult::iterator itr;
			for (itr = result.begin(); itr != result.end(); itr++)
			{
				
				if (itr->movable && itr->movable->getName().substr(0, 5) != "tile[")
				{
					if (mCurrentObject!=NULL)
					{
						mCurrentObject = itr->movable->getParentSceneNode();
					}
					
					break;
				}
				else if (itr->worldFragment)
				{
					Entity *ent;
					char name[20];
					char t[3];
					String modelname=_ModelName+itoa(theApp.mCount,t,10);
					sprintf(name, modelname.c_str(), theApp.mCount);
					ent = _sceneManager->createEntity(name, _ModelName);
					mCurrentObject = _sceneManager->getRootSceneNode()->createChildSceneNode(String(name) + "Node");
					mCurrentObject->attachObject(ent);
					
					Ogre::Vector3 pos;
					pos=itr->worldFragment->singleIntersection;

					theApp.mogredata.count=theApp.mCount+1;
					theApp.mCount++;

					if(_ModelName=="Robot.mesh")//1
					{
						mCurrentObject->setScale(0.5f, 0.5f, 0.5f);
						mCurrentObject->setPosition(pos);
						theApp.mogredata.scale[theApp.mCount]=0.5f;
						theApp.mogredata.posX[theApp.mCount]=pos.x;
						theApp.mogredata.posY[theApp.mCount]=pos.y;
						theApp.mogredata.posZ[theApp.mCount]=pos.z;
						theApp.mogredata.modelname[theApp.mCount]=1;
					}
					else if(_ModelName=="Ninja.mesh")//2
					{
						mCurrentObject->setScale(0.3f, 0.3f, 0.3f);
						mCurrentObject->setPosition(pos);
						theApp.mogredata.scale[theApp.mCount]=0.5f;
						theApp.mogredata.posX[theApp.mCount]=pos.x;
						theApp.mogredata.posY[theApp.mCount]=pos.y;
						theApp.mogredata.posZ[theApp.mCount]=pos.z;
						theApp.mogredata.modelname[theApp.mCount]=2;
					}
					else if(_ModelName=="Sinbad.mesh")//3
					{
						mCurrentObject->setScale(4.0f, 4.0f, 4.0f);
						mCurrentObject->setPosition(pos);
						Vector3 objpos=mCurrentObject->getPosition();
						mCurrentObject->setPosition(Vector3(objpos.x,objpos.y+20.0f,objpos.z));


						theApp.mogredata.scale[theApp.mCount]=0.4f;
						theApp.mogredata.posX[theApp.mCount]=pos.x;
						theApp.mogredata.posY[theApp.mCount]=pos.y;
						theApp.mogredata.posZ[theApp.mCount]=pos.z;
						theApp.mogredata.modelname[theApp.mCount]=3;
					}

					

					break;
				}

			}
			if (mCurrentObject)
				mCurrentObject->showBoundingBox(true);
		}
		if(id==OIS::MB_Right)
		{
			Ray mouseRay=mTrayMgr->getCursorRay(_Cam);

			_RaySceneQuery->setRay(mouseRay);
			//_RaySceneQuery->setSortByDistance(true);

			RaySceneQueryResult &result = _RaySceneQuery->execute();
			RaySceneQueryResult::iterator itr=result.begin();
			if (itr!=result.end()&&itr->worldFragment)
			{

				mWalkList.clear();
				Vector3 t=Vector3(itr->worldFragment->singleIntersection.x,itr->worldFragment->singleIntersection.y,itr->worldFragment->singleIntersection.z);
				mWalkList.push_back(t);

			}
		}
	}
	
	return true;	
}

bool ExaListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	mTrayMgr-> injectMouseUp (e,id);
	if(id==OIS::MB_Left)
		mLMouseDown=false;
	else if (id==OIS::MB_Right)
		mRMouseDown=false;
	return true;	
}

bool ExaListener::keyPressed(const OIS::KeyEvent &e)
{
	if(e.key==OIS::KC_R)
	{
		if(_PolyMode == PM_SOLID)//实体模式
		{
			_PolyMode = Ogre::PolygonMode::PM_WIREFRAME;
		}
		else if(_PolyMode == PM_WIREFRAME)//线框模式
		{
			_PolyMode = Ogre::PolygonMode::PM_POINTS;
		}
		else if(_PolyMode == PM_POINTS)//点模式
		{
			_PolyMode = Ogre::PolygonMode::PM_SOLID;
		}

		_Cam->setPolygonMode(_PolyMode);//设置渲染模式

	}
	if (e.key==OIS::KC_O)
	{
		
		//_light->setDiffuseColour(ColourValue(0.0,0.0,0.0));
	}

	if (e.key==OIS::KC_L)
	{
		//_light->setDiffuseColour(ColourValue(1.0,1.0,1.0));
	}
	return true;	
}

bool ExaListener::keyReleased(const OIS::KeyEvent &e)
{
	return true;	
}

void ExaListener::CreateUI(RenderWindow* win)
{
	mTrayMgr = new SdkTrayManager("SampleControls", win, _mouse,this);

	selectMenu=mTrayMgr->createThickSelectMenu(OgreBites::TL_TOP, "selectMenu", "", 200, 200 );
	/*selectMenu->setCaption(Ogre::DisplayString(L"请选择模型"));*/
	selectMenu->setCaption("Select Model");
	selectMenu->addItem("Robot");
	selectMenu->addItem( "Ninja" );
	selectMenu->addItem( "Sinbad" );

	paramsPanelItems.push_back("Name");  //0
	paramsPanelItems.push_back("NodeName");  //1
	paramsPanelItems.push_back("Position");  //2
	
	paramsPanel= mTrayMgr->createParamsPanel(OgreBites::TL_BOTTOM, 
		"paramsPanel",  260, paramsPanelItems );

	paramsPanel->setParamValue( 0, "-");
	paramsPanel->setParamValue( 1, "-");
	paramsPanel->setParamValue( 2, "-");
}

void ExaListener::itemSelected(OgreBites::SelectMenu* menu) 
{
	Ogre::String SelectItem=menu->getSelectedItem();

	if(SelectItem=="Robot")
	{
		_ModelName="Robot.mesh";
	}
	else if(SelectItem=="Sinbad")
	{
		_ModelName="Sinbad.mesh";
	}
	else if(SelectItem=="Ninja")
	{
		_ModelName="Ninja.mesh";
	}
}

void ExaListener::initKeyandMouse(RenderWindow* win)
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

	unsigned int width, height, depth;
	int left, top;
	win->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = _mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

