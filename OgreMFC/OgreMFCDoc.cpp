
// OgreMFCDoc.cpp : COgreMFCDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OgreMFC.h"
#endif

#include "OgreMFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COgreMFCDoc

IMPLEMENT_DYNCREATE(COgreMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(COgreMFCDoc, CDocument)
END_MESSAGE_MAP()

//IMPLEMENT_SERIAL(OgrePart,CObject,1);
// COgreMFCDoc ����/����

//IMPLEMENT_SERIAL(OgreData,CObject,1);

COgreMFCDoc::COgreMFCDoc()
{
	// TODO: �ڴ����һ���Թ������
	isFirst=false;

}

COgreMFCDoc::~COgreMFCDoc()
{
}

BOOL COgreMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	if (isFirst)
	{
		theApp.isNewOpen=true;
	}
	else
	{
		isFirst=true;
	}
	
	
	
	return TRUE;
}

BOOL COgreMFCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;

	return TRUE;

}

BOOL COgreMFCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	theApp.isOpenFile=true;
	
	
	return TRUE;
}


// COgreMFCDoc ���л�

void COgreMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		theApp.mogredata.Serialize(ar);
		//ogredata.Serialize(ar);

	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		//ogrepart.Serialize(ar);
		theApp.mogredata.Serialize(ar);
		
		//ogredata.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void COgreMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void COgreMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void COgreMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COgreMFCDoc ���

#ifdef _DEBUG
void COgreMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COgreMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COgreMFCDoc ����
