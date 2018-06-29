#include "StdAfx.h"
#include "OgrePart.h"

//IMPLEMENT_SERIAL(OgrePart,CObject,2)
//
//void OgrePart::Serialize(CArchive& ar)
//
//{
//
//	if(ar.IsLoading())
//
//	{
//		
//	}
//
//	else if(ar.IsStoring())
//
//	{
//
//	}
//
//}

OgrePart::OgrePart(void)
{
	m_pRoot = new Ogre::Root("plugins_d.cfg");
}


OgrePart::~OgrePart(void)
{
	delete m_pRoot;
}

void OgrePart::SetupResource(void)
{
	ConfigFile cf;
	cf.load("resources_d.cfg");
	ConfigFile::SectionIterator seci = cf.getSectionIterator();
	String secName;
	String typeName;
	String archName;
 
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap* settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin();i!=settings->end();++i)
		{
			typeName = i->first;    //ÀàÐÍÃû£¬Èçzip£¬filesystemµÈ
			archName = i->second;   //µµ°¸Ãû£¨Â·¾¶£©
			ResourceGroupManager::getSingleton().addResourceLocation(archName,typeName,secName);
		}
	}


}
void OgrePart::SetupConfig(void)
{
	RenderSystemList* rl = &const_cast<RenderSystemList&>(m_pRoot->getAvailableRenderers());
	RenderSystem* rSys = NULL;
	RenderSystemList::iterator it = rl->begin();
	while (it!=rl->end())
	{
		//if (-1 != (*it)->getName().find("GL"))
		if (-1 != (*it)->getName().find("Direct3D9"))
		{
			rSys = (RenderSystem*)(*it);
			break;
		}
		++it;
	}
 
	rSys->setConfigOption("Full Screen","Yes");
	rSys->setConfigOption("VSync","No");
	m_pRoot->setRenderSystem(rSys);


}


//void OgrePart::CreateRanderWind(void)
//{
//	m_pRoot->initialise(false);
//	NameValuePairList miscParams;
// 
//	miscParams["externalWindowHandle"] = StringConverter::toString((unsigned int)m_hWnd);
// 
//	//CRect rt;
//	//::GetClientRect(*(((CMainFrame*)AfxGetMainWnd())->m_ogreMfcView),&rt);
//	
//	//GetClientRect(&rt);
//	m_pWindow = m_pRoot->createRenderWindow("test",rt.Width(),rt.Height(),false,&miscParams);
//	//this->m_hWnd;
//}


void OgrePart::CreateSceneManager(void)
{
	//m_pSceneManager = m_pRoot->createSceneManager(ST_GENERIC,"ExampleSMInstance");
	m_pSceneManager = m_pRoot->createSceneManager(ST_EXTERIOR_CLOSE,"ExampleSMInstance");

}

void OgrePart::CreateFrameListener()
{
     mFrameListener= new ExaListener(m_pWindow,m_pCamera,m_pSceneManager);

     //mFrameListener->showDebugOverlay(true);
     m_pRoot->addFrameListener(mFrameListener);

}

void OgrePart::CreateCamera(void)
{
	m_pCamera = m_pSceneManager->createCamera("PlayerCam");
	m_pCamera->setPosition(Vector3(150.0f, 100.0f, 535.0f));
	m_pCamera->lookAt(Vector3(0,0,0));
	m_pCamera->setNearClipDistance(5);
	m_pCamera->setFarClipDistance(0);
	
}
void OgrePart::CreateViewPort()
{
	Viewport* vp = m_pWindow->addViewport(m_pCamera);
	vp->setBackgroundColour(ColourValue(255,0,0));
	m_pCamera->setAspectRatio(Real(vp->getActualWidth())/Real(vp->getActualHeight()));
 
	TextureManager::getSingleton().setDefaultNumMipmaps(5);
}


void OgrePart::LoadResource()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}


void OgrePart::CreateScene()
{
	m_pSceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	//m_pSceneManager->setAmbientLight(ColourValue(1.0,1.0,1.0));
	m_pSceneManager->setSkyDome(true,"Examples/CloudySky",65);
	m_pSceneManager->setWorldGeometry("terrain.cfg");

}

void OgrePart::CreateEntity()
{
	/*ent1 = m_pSceneManager->createEntity("sphere","¿ÝÊ÷1.mesh");
	node1 = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
	node1->translate(Vector3(135,20,250));
	node1->scale(0.3,0.3,0.3);
	node1->attachObject(ent1);*/
	//m_pSceneManager->destroyAllEntities();
}

void OgrePart::CreateFloorPlane()
{
	/*Entity* ent;
	Plane p;
	p.d = 0;
	p.normal = Vector3::UNIT_Y;

	MeshManager::getSingleton().createPlane("cube.mesh",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,p,2000,2000,1,1,true,1,5,5,Vector3::UNIT_Z);

	ent = m_pSceneManager->createEntity("floor","cube.mesh");
	ent->setMaterialName("Examples/BeachStones");
	m_pSceneManager->getRootSceneNode()->attachObject(ent);*/


}

void OgrePart::SetupMFC(void)
{
	//SetupResource();
	//SetupConfig();
	//CreateRanderWind();
	CreateSceneManager();
	CreateCamera();
	CreateViewPort();

	LoadResource();
	CreateScene();
	CreateFloorPlane();
	CreateEntity();
	CreateFrameListener();
}

void OgrePart::Reset()
{
	
	m_pSceneManager->destroyAllEntities();

}

void OgrePart::CreateOpenFile()
{
	
	for (int i=0;i<theApp.mogredata.count+1;i++)
	{
		if (i!=0)
		{
			int index=theApp.mogredata.modelname[i];
			String Modelname;
			if (index==1)
				Modelname="Robot.mesh";
			else if (index==2)
				Modelname="Ninja.mesh";
			else if (index==3)
				Modelname="Sinbad.mesh";

			char name[20];
			char t[3];
			String modelname=Modelname+itoa(i,t,10);
			sprintf(name, modelname.c_str(), i);

			Entity *ent;
			ent = m_pSceneManager->createEntity(name,Modelname);
			SceneNode *snode;
			snode=m_pSceneManager->getRootSceneNode()->createChildSceneNode(String(name) + "Node");
			snode->attachObject(ent);
			snode->setScale(theApp.mogredata.scale[i],theApp.mogredata.scale[i],theApp.mogredata.scale[i]);
			snode->setPosition(theApp.mogredata.posX[i],theApp.mogredata.posY[i],theApp.mogredata.posZ[i]);
		}
		
		
	}
	theApp.mCount=theApp.mogredata.count-1;
	//theApp.mogredata.posX[2];
	
}

void OgrePart::AddOtherModel(int str)
{
	String mname;
	switch(str)
	{
	case 0:
		mname="°×èë.mesh";
		break;
	case 1:
		mname="ºì·ãÊ÷.mesh";
		break;
	case 2:
		mname="²èÊ÷1.mesh";
		break;
	case 3:
		mname="´óÖñ1.mesh";
		break;
	case 4:
		mname="ºúÑî1.mesh";
		break;
	case 5:
		mname="¿ÝÊ÷1.mesh";
		break;
		
	}
	Entity *ent;
	char t[3];
	String modelname=str+itoa(otherCount,t,10);
	ent = m_pSceneManager->createEntity(modelname,mname);
	SceneNode *snode;
	snode=m_pSceneManager->getRootSceneNode()->createChildSceneNode(String(modelname) + "Node");
	snode->attachObject(ent);
	snode->setScale(0.3,0.3,0.3);
	snode->setPosition(135,20,250);

	otherCount++;

}