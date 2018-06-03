#pragma once



// OgreControl 窗体视图

class OgreControl : public CFormView
{
	DECLARE_DYNCREATE(OgreControl)

protected:
	OgreControl();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	//OgreControl* m_ogreContro;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


