// OgreControl.cpp : 实现文件
//

#include "stdafx.h"
#include "OgreMFC.h"
#include "OgreControl.h"


// OgreControl

IMPLEMENT_DYNCREATE(OgreControl, CFormView)

OgreControl::OgreControl()
	: CFormView(OgreControl::IDD)
{

}

OgreControl::~OgreControl()
{
}

void OgreControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(OgreControl, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// OgreControl 诊断

#ifdef _DEBUG
void OgreControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void OgreControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// OgreControl 消息处理程序


void OgreControl::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//m_ogreContro=this;
	
	CRect rect;
	GetClientRect(&rect);
 
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); //将CSCrollView的大小设为当前客户区的大小
	MoveWindow(&rect,TRUE);
	//if (m_ogreContro != NULL)
	//{
		/*m_ogreContro->*/
	//}

	// TODO: 在此处添加消息处理程序代码
}
