
// MFCDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCDemoDlg dialog
class CMFCDemoDlg : public CDialogEx
{
// Construction
public:
	CMFCDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCDEMO_DIALOG };

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
	DECLARE_MESSAGE_MAP()

private:
	void plateRecognize();
	void openCamera();
public:
	afx_msg void OnBnClickedSnapbtn();
	afx_msg void OnEnChangeEdit();
	CEdit m_chePai;

private:
	CRect rect;
	CStatic* pStc; //��ʶͼ����ʾ��Picture�ؼ�
	CDC* pDC; //��Ƶ��ʾ�ؼ��豸������
	HDC hDC; //��Ƶ��ʾ�ؼ��豸���
	CvCapture* capture; //��Ƶ��ȡ�ṹ

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};
