
// OgreMFC.h : OgreMFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "OgreData.h"
// COgreMFCApp:
// �йش����ʵ�֣������ OgreMFC.cpp
//

class COgreMFCApp : public CWinAppEx
{
public:
	COgreMFCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	bool isNewOpen;
	bool isOpenFile;
	OgreData mogredata;
	int mCount;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COgreMFCApp theApp;
