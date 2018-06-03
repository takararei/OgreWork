
// OgreMFCView.h : COgreMFCView ��Ľӿ�
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
protected: // �������л�����
	COgreMFCView();
	DECLARE_DYNCREATE(COgreMFCView)

public:
	enum{ IDD = IDD_OGREMFC_FORM };

// ����
public:
	COgreMFCDoc* GetDocument() const;
	Root*  m_pRoot;
	RenderWindow* m_pWindow;
	SceneManager* m_pSceneManager;
	Camera* m_pCamera;
	SceneNode *node1; Entity *ent1;
	BOOL bHasInit;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~COgreMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // OgreMFCView.cpp �еĵ��԰汾
inline COgreMFCDoc* COgreMFCView::GetDocument() const
   { return reinterpret_cast<COgreMFCDoc*>(m_pDocument); }
#endif

