#pragma once



// OgreControl ������ͼ

class OgreControl : public CFormView
{
	DECLARE_DYNCREATE(OgreControl)

protected:
	OgreControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~OgreControl();

public:
	enum { IDD = IDD_OGRECONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	//OgreControl* m_ogreContro;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

