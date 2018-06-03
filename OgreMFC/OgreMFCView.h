
// OgreMFCView.h : COgreMFCView 类的接口
//

#pragma once

#include "resource.h"
#include "OgreMFCDoc.h"
 #include "MainFrm.h"

#include "Ogre\Ogre.h"
#include "Ogre\OgreConfigFile.h"
using namespace Ogre;


class COgreMFCView : public CFormView
{
protected: // 仅从序列化创建
	COgreMFCView();
	DECLARE_DYNCREATE(COgreMFCView)

public:
	enum{ IDD = IDD_OGREMFC_FORM };

// 特性
public:
	COgreMFCDoc* GetDocument() const;
	Root*  m_pRoot;
	RenderWindow* m_pWindow;
	SceneManager* m_pSceneManager;
	Camera* m_pCamera;
	SceneNode *node1; Entity *ent1;
	BOOL bHasInit;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~COgreMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void SetupResource(void);
	void SetupConfig(void);
	void CreateRanderWind();
	void CreateSceneManager(void);
	void CreateCamera(void);
	void CreateViewPort();
	void LoadResource();
	void CreateScene();
	void CreateEntity();
	void CreateFloorPlane();
	void SetupMFC();
	void CreateFrameListener();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnDestroy();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};

#ifndef _DEBUG  // OgreMFCView.cpp 中的调试版本
inline COgreMFCDoc* COgreMFCView::GetDocument() const
   { return reinterpret_cast<COgreMFCDoc*>(m_pDocument); }
#endif

