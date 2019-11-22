
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "opencv2/opencv.hpp"
using namespace cv;

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT_SRC_IMG, m_edtSourceImagePath);
   DDX_Control(pDX, IDC_EDIT_DEST_IMG, m_edtDestImagePath);
   DDX_Control(pDX, IDC_BUTTON_SRC_IMG_BROWSE, m_srcImgBrowseButton);
   DDX_Control(pDX, IDC_BUTTON_DEST_IMG_BROWSE, m_destImagePathButton);
   DDX_Control(pDX, IDC_RED, m_editRed);
   DDX_Control(pDX, IDC_GREEN, m_editGreen);
   DDX_Control(pDX, IDC_BLUE, m_editBlue);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_PROCESS, &CMFCApplication1Dlg::OnProcessButtonClick)
   ON_BN_CLICKED(IDC_BUTTON_SRC_IMG_BROWSE, &CMFCApplication1Dlg::OnSourceImageBrowseButtonClick)
   ON_BN_CLICKED(IDC_BUTTON_DEST_IMG_BROWSE, &CMFCApplication1Dlg::OnDestinationImageBrowseButtonClick)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnProcessButtonClick()
{
   CString text("");
   int red, green,blue = -1;
   red = green = blue;

   m_editRed.GetWindowText(text);
   red = _wtoi(text);

   m_editGreen.GetWindowText(text);
   green = _wtoi(text);

   m_editBlue.GetWindowText(text);
   blue = _wtoi(text);

   //Check for valid channel range
   if(red < 0 || red > 255 ||
      blue < 0 || blue > 255 ||
      green < 0 || green > 255)
   {
      AfxMessageBox(L"Set correct values to the color channels and try again.");
      return;
   }

   m_edtSourceImagePath.GetWindowText(text);
   char pFileName[1024];  
   WideCharToMultiByte(CP_ACP,0,text,text.GetLength(),pFileName,text.GetLength(),NULL,NULL);
   pFileName[pFileName,text.GetLength()] = '\0';

   Mat image = imread(pFileName);

   if(image.empty())
   {
      AfxMessageBox(L"No Image Found");
   }
   else
   {
      // Open CV stores information in Blue, Green, Red and Alpha
      Mat bgra;
      cvtColor(image, bgra, CV_BGR2BGRA);

      // Find all pixel of the value provided in Red, Green and Blue channels and set alpha value to zero 
      // for the given pixel
      for (int y = 0; y < bgra.rows; ++y)
      {
         for (int x = 0; x < bgra.cols; ++x)
         {
            Vec4b & pixel = bgra.at<Vec4b>(y, x);
            if (pixel[0] == blue && pixel[1] == green && pixel[2] == red)
            {
               pixel[3] = 0;
            }
         }
      }

      m_edtSourceImagePath.GetWindowText(text);
      WideCharToMultiByte(CP_ACP,0,text,text.GetLength(),pFileName,text.GetLength(),NULL,NULL);
      pFileName[text.GetLength()] = '\0';

      imwrite(pFileName, bgra);
   }

}

CString CMFCApplication1Dlg::FileBrowser()
{
   CString strFilePath("");

   CFileDialog browsePNG(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,_T("Image Files (*.png)|*.png||"));
    int iRet = browsePNG.DoModal();
    CString l_strFileName;
    l_strFileName = browsePNG.GetPathName();

     if(iRet == IDOK)
         strFilePath = l_strFileName;

   return strFilePath;
}


void CMFCApplication1Dlg::OnSourceImageBrowseButtonClick()
{
   m_edtSourceImagePath.SetWindowText(FileBrowser());
}


void CMFCApplication1Dlg::OnDestinationImageBrowseButtonClick()
{
   m_edtDestImagePath.SetWindowText(FileBrowser());
}
