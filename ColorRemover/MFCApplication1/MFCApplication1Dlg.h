
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   CString FileBrowser();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnProcessButtonClick();
   CEdit m_edtSourceImagePath;
   CEdit m_edtDestImagePath;
   CButton m_srcImgBrowseButton;
   CButton m_destImagePathButton;
   CEdit m_editRed;
   CEdit m_editGreen;
   CEdit m_editBlue;
   afx_msg void OnSourceImageBrowseButtonClick();
   afx_msg void OnDestinationImageBrowseButtonClick();
};
