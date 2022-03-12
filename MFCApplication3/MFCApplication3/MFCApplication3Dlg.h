
// MFCApplication3Dlg.h: 头文件
//

#pragma once
#include <opencv2/opencv.hpp>
#include "afxwin.h"
#include "CvvImage.h"
using namespace cv;

// CMFCApplication3Dlg 对话框
class CMFCApplication3Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据

	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnBnClickedAbort();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CRect rect;
	Mat src;
	Mat img;
};
