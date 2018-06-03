
// OgreMFCView.cpp : COgreMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OgreMFC.h"
#endif

#include "OgreMFCDoc.h"
#include "OgreMFCView.h"
//#include "Ogre/ExampleFrameListener.h"
#include "NewFrameListener.h"

#ifdef _DEBUG
#define OGRE_DEBUG_MEMORY_MANAGER 1
#endif


// COgreMFCView

IMPLEMENT_DYNCREATE(COgreMFCView, CFormView)

BEGIN_MESSAGE_MAP(COgreMFCView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZING()
END_MESSAGE_MAP()

// COgreMFCView 构造/析构

COgreMFCView::COgreMFCView()
	: CFormView(COgreMFCView::IDD)
{
	// TODO: 在此处添加构造代码
	m_pRoot = new Ogre::Root("plugins_d.cfg");
	bHasInit=FALSE;

}

COgreMFCView::~COgreMFCView()
{
	delete m_pRoot;
}

void COgreMFCView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL COgreMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void COgreMFCView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void COgreMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COgreMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COgreMFCView 诊断

#ifdef _DEBUG
void COgreMFCView::AssertValid() const
{
	CFormView::AssertValid();
}

void COgreMFCView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

COgreMFCDoc* COgreMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COgreMFCDoc)));
	return (COgreMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COgreMFCView 消息处理程序


void COgreMFCView::SetupResource(void)
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
			typeName = i->first;    //类型名，如zip，filesystem等
			archName = i->second;   //档案名（路径）
			ResourceGroupManager::getSingleton().addResourceLocation(archName,typeName,secName);
		}
	}


}
void COgreMFCView::SetupConfig(void)
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


void COgreMFCView::CreateRanderWind(void)
{
	m_pRoot->initialise(false);
	NameValuePairList miscParams;
 
	miscParams["externalWindowHandle"] = StringConverter::toString((unsigned int)m_hWnd);
 
	CRect rt;
	//::GetClientRect(*(((CMainFrame*)AfxGetMainWnd())->m_ogreMfcView),&rt);
	
	GetClientRect(&rt);
	m_pWindow = m_pRoot->createRenderWindow("test",rt.Width(),rt.Height(),false,&miscParams);
	//this->m_hWnd;
}


void COgreMFCView::CreateSceneManager(void)
{
	m_pSceneManager = m_pRoot->createSceneManager(ST_GENERIC,"ExampleSMInstance");



}

void COgreMFCView::CreateFrameListener()
{
     FrameListener *mFrameListener= new ExaListener(m_pWindow,m_pCamera);

     //mFrameListener->showDebugOverlay(true);
     m_pRoot->addFrameListener(mFrameListener);

}

void COgreMFCView::CreateCamera(void)
{
	m_pCamera = m_pSceneManager->createCamera("PlayerCam");
	m_pCamera->setPosition(Vector3(0,200,500));
	m_pCamera->lookAt(Vector3(0,0,0));
	m_pCamera->setNearClipDistance(5);
	m_pCamera->setFarClipDistance(0);
}
void COgreMFCView::CreateViewPort()
{
	Viewport* vp = m_pWindow->addViewport(m_pCamera);
	vp->setBackgroundColour(ColourValue(255,0,0));
	m_pCamera->setAspectRatio(Real(vp->getActualWidth())/Real(vp->getActualHeight()));
 
	TextureManager::getSingleton().setDefaultNumMipmaps(5);
}


void COgreMFCView::LoadResource()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}


void COgreMFCView::CreateScene()
{
	m_pSceneManager->setAmbientLight(ColourValue(1.0,1.0,1.0));
	m_pSceneManager->setSkyDome(true,"Examples/CloudySky",65);


}

void COgreMFCView::CreateEntity()
{
	ent1 = m_pSceneManager->createEntity("sphere","ninja.mesh");
	node1 = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
	node1->translate(Vector3(0,0,0));
	node1->attachObject(ent1);


}

void COgreMFCView::CreateFloorPlane()
{
	Entity* ent;
	Plane p;
	p.d = 0;
	p.normal = Vector3::UNIT_Y;
 
	MeshManager::getSingleton().createPlane("cube.mesh",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,p,2000,2000,1,1,true,1,5,5,Vector3::UNIT_Z);
 
	ent = m_pSceneManager->createEntity("floor","cube.mesh");
	ent->setMaterialName("Examples/RustySteel");
	m_pSceneManager->getRootSceneNode()->attachObject(ent);


}

void COgreMFCView::SetupMFC(void)
{
	SetupResource();
	SetupConfig();
	//CreateRanderWnd
	CreateRanderWind();
	CreateSceneManager();
	CreateCamera();
	CreateViewPort();

	LoadResource();
	CreateScene();
	CreateFloorPlane();
	CreateEntity();
	CreateFrameListener();

}

void COgreMFCView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pRoot->renderOneFrame();

	CFormView::OnTimer(nIDEvent);
}


void COgreMFCView::OnDraw(CDC* /*pDC*/)
{
	if (!bHasInit)
	{
		SetupMFC();
		bHasInit = TRUE;
	}
	SetTimer(1,30,NULL);
	// TODO: 在此添加专用代码和/或调用基类
}


void COgreMFCView::OnDestroy()
{
	CFormView::OnDestroy();
	KillTimer(1);

	// TODO: 在此处添加消息处理程序代码
}


void COgreMFCView::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFormView::OnSizing(fwSide, pRect);
	if (m_pWindow)
	{
		CRect rt;
		GetClientRect(&rt);
		m_pWindow->windowMovedOrResized();
 
		if (rt.Height() != 0 && m_pCamera != NULL)
		{
			m_pCamera->setNearClipDistance(Real(m_pWindow->getWidth())/Real(m_pWindow->getHeight()));
		}
		m_pCamera->yaw(Radian(0));
	}

	// TODO: 在此处添加消息处理程序代码
}
