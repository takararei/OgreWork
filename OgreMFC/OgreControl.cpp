// OgreControl.cpp : 实现文件
//

#include "stdafx.h"
#include "OgreMFC.h"
#include "OgreControl.h"
#include "MainFrm.h"
#include "OgreMFCView.h"
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
	DDX_Control(pDX, IDC_LIST1, ModelList);
	ModelList.DeleteColumn(0);
	ModelList.DeleteAllItems();
	ModelList.InsertColumn(0,_T("模型"), LVCFMT_CENTER,100);
	
	ModelList.InsertItem(0,_T("白桦.mesh"));
	ModelList.InsertItem(1,_T("红枫树.mesh"));
	ModelList.InsertItem(2,_T("茶树1.mesh"));
	ModelList.InsertItem(3,_T("大竹1.mesh"));
	ModelList.InsertItem(4,_T("胡杨1.mesh"));
	ModelList.InsertItem(5,_T("枯树1.mesh"));

}

BEGIN_MESSAGE_MAP(OgreControl, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &OgreControl::OnAddModel)
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


void OgreControl::OnAddModel()
{
	CString str;
	int nId;
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos=ModelList.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox(L"请至少选择一项",L"提示",MB_ICONEXCLAMATION);
		return;
	}

	nId=(int)ModelList.GetNextSelectedItem(pos);
	str=ModelList.GetItemText(nId,0);

	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd(); //定位主窗口
	COgreMFCView* ogreView=(COgreMFCView*)pMainFrame->m_wndSplitter.GetPane(0,1); //定位视图窗口
	ogreView->ogrepart.AddOtherModel(nId);
	
}

