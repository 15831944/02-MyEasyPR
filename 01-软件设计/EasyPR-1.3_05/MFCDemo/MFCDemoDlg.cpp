
// MFCDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDemo.h"
#include "MFCDemoDlg.h"
#include "afxdialogex.h"


using namespace cv;
using namespace std;
using namespace easypr;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCDemoDlg dialog



CMFCDemoDlg::CMFCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_chePai);
}

BEGIN_MESSAGE_MAP(CMFCDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTBTN, &CMFCDemoDlg::OnBnClickedSnapbtn)
	ON_EN_CHANGE(IDC_EDIT, &CMFCDemoDlg::OnEnChangeEdit)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCDemoDlg message handlers

BOOL CMFCDemoDlg::OnInitDialog()
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
	//������ͷ
	openCamera();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDemoDlg::OnPaint()
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
HCURSOR CMFCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDemoDlg::OnBnClickedSnapbtn()
{
	// TODO: Add your control notification handler code here
	static BOOL enSnapBtn = true;
	//if (enSnapBtn)

	IplImage* snapImg = 0;

	snapImg = cvQueryFrame(capture); //������ͷ�����ļ���ץȡ������һ֡

	char* outImageName = "../resources/image/test.jpg";
	//����ͼƬ  
	cvSaveImage(outImageName, snapImg);
	//����ʶ��
	plateRecognize();

	

}


void CMFCDemoDlg::OnEnChangeEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//ʶ����
void CMFCDemoDlg::plateRecognize()
{
	const string file = "../resources/image/test.jpg";

	cv::Mat src = imread(file);

	CPlateRecognize pr;
	pr.LoadANN("../resources/model/ann.xml");
	pr.LoadSVM("../resources/model/svm.xml");

	pr.setLifemode(true);
	pr.setDebug(true);

	vector<string> plateVec;

	//����plateRecognize()���ǳ���ʶ�����������
	//src��ͼƬmat��plateVec���ַ�����������Ϊ�п��ܴ��ڶ������
	//����0˵��ʶ����ɣ����ǲ�һ����ȷ����Ϊ�㷨���޷�֪����ȷ���ģ����϶���Ϊ�Լ��Ľ��һ������ȷ�ġ�

	int result = pr.plateRecognize(src, plateVec);

	CString chePai;	

	if (result == 0)
	{
		//AfxMessageBox(_T("RecognizeDone"));
		//���泵����Ŀ
		size_t num = plateVec.size();
		if (num>0)
			//for (size_t j = 0; j < num; j++)
		{
			chePai.Format(_T("%s"), CStringW(plateVec[0].data()));
			m_chePai.SetWindowTextW(chePai);
		}
		else
		{
			chePai.Format(_T("%s"), CStringW("û�з��ֳ��ƺţ�"));
			m_chePai.SetWindowTextW(chePai);

		}
	}

	
}

//������ͷ
void CMFCDemoDlg::openCamera()
{
	//��ʼ��hDC
	pStc = (CStatic *)GetDlgItem(IDC_STATIC_VIEW);//IDC_VIEWΪPicture�ؼ�ID
	pStc->GetClientRect(&rect);//��CWind��ͻ���������㴫������rect
	pDC = pStc->GetDC(); //�õ�Picture�ؼ��豸������
	hDC = pDC->GetSafeHdc(); //�õ��ؼ��豸�����ĵľ�� 

	//������ͷ
	if (!capture)
	{
		capture = cvCreateCameraCapture(1); //��ʼ��һ����Ƶ�ļ���׽��
	}
	if (!capture)
	{
		AfxMessageBox(_T("�޷��������ͷ"));
		return;
	}
	SetTimer(1, 66, NULL); //��ʱ������ʱʱ���֡��һ��
}

void CMFCDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (1 == nIDEvent)
	{

		IplImage* img = 0;
		img = cvQueryFrame(capture); //������ͷ�����ļ���ץȡ������һ֡
		//cvGrabFrame( capture ); //������ͷ������Ƶ�ļ���ץȡ֡
		//img=cvRetrieveFrame(capture); //ȡ���ɺ���cvGrabFrameץȡ��ͼ��
		CvvImage m_CvvImage;
		m_CvvImage.CopyOf(img, 1); //���Ƹ�֡ͼ��    
		m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���
	}


	CDialogEx::OnTimer(nIDEvent);
}


void CMFCDemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//������ͷţ��Ͳ����ͷ�����ͷ
	cvReleaseCapture(&capture);

	CDialogEx::OnClose();
}
