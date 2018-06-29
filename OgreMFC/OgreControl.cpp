// OgreControl.cpp : ʵ���ļ�
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
	ModelList.InsertColumn(0,_T("ģ��"), LVCFMT_CENTER,100);
	
	ModelList.InsertItem(0,_T("����.mesh"));
	ModelList.InsertItem(1,_T("�����.mesh"));
	ModelList.InsertItem(2,_T("����1.mesh"));
	ModelList.InsertItem(3,_T("����1.mesh"));
	ModelList.InsertItem(4,_T("����1.mesh"));
	ModelList.InsertItem(5,_T("����1.mesh"));

}

BEGIN_MESSAGE_MAP(OgreControl, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &OgreControl::OnAddModel)
END_MESSAGE_MAP()


// OgreControl ���

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


// OgreControl ��Ϣ�������


void OgreControl::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//m_ogreContro=this;
	
	CRect rect;
	GetClientRect(&rect);
 
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); //��CSCrollView�Ĵ�С��Ϊ��ǰ�ͻ����Ĵ�С
	MoveWindow(&rect,TRUE);
	//if (m_ogreContro != NULL)
	//{
		/*m_ogreContro->*/
	//}

	// TODO: �ڴ˴������Ϣ����������
}


void OgreControl::OnAddModel()
{
	CString str;
	int nId;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=ModelList.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox(L"������ѡ��һ��",L"��ʾ",MB_ICONEXCLAMATION);
		return;
	}

	nId=(int)ModelList.GetNextSelectedItem(pos);
	str=ModelList.GetItemText(nId,0);

	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd(); //��λ������
	COgreMFCView* ogreView=(COgreMFCView*)pMainFrame->m_wndSplitter.GetPane(0,1); //��λ��ͼ����
	ogreView->ogrepart.AddOtherModel(nId);
	
}

