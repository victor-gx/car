
// MFCApplication3Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString StrPath0, StrPath1;
unsigned char color_flag = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据

	enum { IDD = IDD_ABOUTBOX };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDABORT, &CMFCApplication3Dlg::OnBnClickedAbort)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// ----------用来加载检测图片---------------//
	CWnd * pWnd = GetDlgItem(IDC_STATIC);
	pWnd->GetClientRect(&rect);
	namedWindow("PIC", WINDOW_AUTOSIZE);    //创建OpenCV窗口
	HWND hWnd = (HWND)cvGetWindowHandle("PIC");   //镶嵌OpenCV窗口
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedAbort()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CMFCApplication3Dlg::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("图片文件(*.jpg)|*.jpg|图片文件(*.bmp)|*.bmp|图片文件(*.png)|*.png|所有文件(*.*)|*.*||");
	//构造打开文件对话框
	CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);

	//显示打开文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		//点击"打开"按钮，则将文件路径赋值
		StrPath0 = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, StrPath0);
	}
	USES_CONVERSION;
	string PicPath(W2A(StrPath0));
	src = imread(PicPath);
	if (!(src.empty()))
	{
		img = src.clone();
		resize(img, img, Size(rect.Width(), rect.Height()));
		//imshow("PIC", img);
	}
	else
		AfxMessageBox(_T("图片加载失败！"));
	color_flag = 0;

	IplImage *pImage;
	pImage=&IplImage(img);
	//IplImage *pImage = cvLoadImage("1.jpg", CV_LOAD_IMAGE_UNCHANGED);  
	CDC *pDC = GetDlgItem(IDC_STATIC)->GetDC();
	HDC hDC =  pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(pImage);
	cimg.DrawToHDC(hDC, &rect);
}


//void CMFCApplication3Dlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CMFCApplication3Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	

	Mat dstImg = src.clone();
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	//imshow("input image", src);

	Mat cvtColor_0, dst;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);//高斯滤波
	cvtColor(dst, cvtColor_0, CV_BGR2GRAY);
	//imshow("cvtColor_0", cvtColor_0);

	Mat xgrad;
	Sobel(cvtColor_0, xgrad, CV_16S, 1, 0, 3);//Soble算子
	convertScaleAbs(xgrad, xgrad);
	//imshow("xgrad", xgrad);

	Mat threshold_0;
	threshold(xgrad, threshold_0, 100, 255, THRESH_OTSU);//二值化
	//imshow("therimg", threshold_0);

	Mat element_0;
	Mat element = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	morphologyEx(threshold_0, element_0, MORPH_CLOSE, element);//闭运算
	//imshow("element_0", element_0);

	Mat medianBlur_0;
	medianBlur(element_0, medianBlur_0, 9);
	//imshow("medianBlur_0", medianBlur_0);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(medianBlur_0, contours, hierarcy, CV_RETR_TREE, CHAIN_APPROX_NONE); //查找轮廓
	vector<Rect> boundRect(contours.size()); //定义外接矩形集合
	vector<RotatedRect> bound(contours.size()); //定义外接矩形集合
	Point2f rect[4];
	//drawContours(dstImg, contours, -1, Scalar(0, 0, 255), 2, 8);  //绘制轮廓
	int x0 = 0, y0 = 0, x = 0, y = 0;
	float w0 = 0, h0 = 0, w = 0, h = 0;
	Rect rectimg;
	Mat ROI;
	float angle;
	Mat warpAffine_0;
	for (int i = 0; i < contours.size(); i++)
	{

		bound[i] = minAreaRect(Mat(contours[i])); //查找每个轮廓的外接矩形
		//drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);  //绘制轮廓

		x = bound[i].center.x;
		y = bound[i].center.y;
		w = bound[i].size.width; //获得第i个最小外接矩形的宽度
		h = bound[i].size.height; //获得第i个最小外接矩形的高度
		bound[i].points(rect);
		if (w < h) {
			int t = w;
			w = h;
			h = t;
		}
		if (w > (h * 2.9) && w < (h * 4.2) && x > 250 && x < 550 && w>220) {

			for (int j = 0; j < 4; j++)
			{
				line(dstImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);
			}
			/*cout << x << endl;
			cout << y << endl;
			cout << w << endl;
			cout << h << endl;*/
			angle = bound[i].angle;
			cout << angle << endl;
			if (0 < abs(angle) && abs(angle) <= 45)  //逆时针
				angle = angle;
			else if (45 < abs(angle) && abs(angle) < 90) //顺时针
				angle = 90 - abs(angle);
			Point center = bound[i].center;  //定义旋转中心坐标
			double angle0 = angle;
			double scale = 1;
			Mat roateM;
			roateM = getRotationMatrix2D(center, angle0, scale);  //获得旋转矩阵	
			warpAffine(medianBlur_0, warpAffine_0, roateM, dstImg.size()); //利用放射变换进行旋转	
			warpAffine(dstImg, dstImg, roateM, dstImg.size());
		}
	}
	//imshow("medianBlur_0", warpAffine_0);
	//imshow("input image", dstImg);
	int w1, h1;
	findContours(warpAffine_0, contours, hierarcy, CV_RETR_TREE, CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++) {
		boundRect[i] = boundingRect(Mat(contours[i])); //查找每个轮廓的外接矩形
		x0 = boundRect[i].x;  //获得第i个外接矩形的左上角的x坐标
		y0 = boundRect[i].y; //获得第i个外接矩形的左上角的y坐标
		w0 = boundRect[i].width; //获得第i个外接矩形的宽度
		h0 = boundRect[i].height; //获得第i个外接矩形的高度
		if (w0 > (h0 * 2.9) && w0 < (h0 * 4) && x0 > 140 && x0 < 300 && w0 > 200)
		{
			rectangle(dstImg, Point(x0, y0), Point(x0 + w0, y0 + h0), Scalar(0, 225, 0), 2, 8); //绘制第i个外接矩形			
			/*cout << x0 << endl;
			cout << y0 << endl;
			cout << w0 << endl;
			cout << h0 << endl;
			cout << endl;*/
			rectimg = Rect(x0, y0, w0, h0);
			ROI = dstImg(rectimg);
		}
	}
	//imshow("input image", dstImg);
	//imshow("input ", ROI);

	dst = ROI.clone();  //原图备份
	//imshow("input image", ROI);

	Mat cvtColor_1;
	cvtColor(ROI, cvtColor_1, CV_BGR2GRAY); //转为灰度图
	//imshow("cvtColor", cvtColor_1);

	Mat medianBlur_1;
	medianBlur(cvtColor_1, medianBlur_1, 1);  //中值滤波
	GaussianBlur(cvtColor_1, medianBlur_1, Size(1, 1), 0, 0);
	//imshow("medianBlur", medianBlur_1);

	Mat threshold_1;
	threshold(medianBlur_1, threshold_1, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV); //二值化

	int jumpcount = 0;
	for (int i = 0; i < threshold_1.rows; i++) {
		for (int j = 0; j < threshold_1.cols; j++) {
			uchar* data = threshold_1.ptr<uchar>(i);
			jumpcount++;
			if (jumpcount < (threshold_1.rows*threshold_1.cols) / 5.5 || jumpcount >(threshold_1.rows*threshold_1.cols) / 1.2)
				data[j] = 225;
		}
	}

	//int jumpcount1 = 0;
	//for (int i = 0; i < threshold_1.rows; i++) {
	//	//for (int j = 0; j < threshold_1.cols; j++) {
	//		uchar* data = threshold_1.ptr<uchar>(i);
	//		jumpcount1++;
	//		if (jumpcount1 < w1/5 || jumpcount1 >w1/1.2)
	//			data[i] = 225;
	//	}
	//}

	//imshow("threshold", threshold_1);



	vector<vector<Point>> contours_1;
	vector<Vec4i> hierarcy_1;
	findContours(threshold_1, contours_1, hierarcy_1, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	int size = (int)(contours_1.size());
	/*drawContours(threshold_1, contours, -1, Scalar(0, 225, 0), 2, 8);
	imshow("thre", threshold_1);*/
	//保存符号边框的序号
	vector<Mat> carChar;
	vector<int> num_order;
	map<int, int> num_map;
	int hw, hh, hx, hy;
	for (int i = 0; i < size; i++) {
		// 获取边框数据
		Rect number_rect = boundingRect(contours_1[i]);
		float w0 = number_rect.width;
		float h0 = number_rect.height;
		/*rectangle(threshold_1, number_rect.tl(), number_rect.br(), Scalar(255, 255, 255), 1, 1, 0);
		imshow("thre", threshold_1);*/
		// 去除较小的干扰边框，筛选出合适的区域
		if (h0 > (w0*1.5) && h0 < (w0*2.5) && h0>36 || (h0 > (w0 * 4) && h0 < (w0*6.5) && h0>36 || h0 < (w0*7.3) && h0 >(w0*6.7)) && h0 > 36) {
			rectangle(threshold_1, number_rect.tl(), number_rect.br(), Scalar(255, 255, 255), 1, 1, 0);
			cout << w0 << endl;
			cout << h0 << endl;
			/*imshow("thre", threshold_1);
			imwrite("D:/cv/image.jpg", threshold_1);*/
			num_order.push_back(number_rect.x);
			num_map[number_rect.x] = i;
		}
	}
	// 按符号顺序提取
	sort(num_order.begin(), num_order.end());
	for (int i = 0; i < 1; i++) {
		Rect number_rect = boundingRect(contours_1[num_map.find(num_order[i])->second]);
		hx = number_rect.x;
	}
	for (int i = 0; i < num_order.size(); i++) {
		Rect number_rect = boundingRect(contours_1[num_map.find(num_order[i])->second]);
		//hx = number_rect.x;
		hy = number_rect.y;
		hw = number_rect.width;
		hh = number_rect.height;
		cout << hx << endl;
		Rect choose_rect(number_rect.x, number_rect.y, number_rect.width, number_rect.height);
		Mat number_img = threshold_1(choose_rect);
		carChar.push_back(number_img);
		//imshow("NO." + to_string(i), number_img);
		/*char numbre[10];
		sprintf_s(numbre, "D:\\%d.jpg", i);
		imwrite(numbre, number_img);*/
	}
	if (num_order.size() <= 6) {
		Rect hanzi;
		hanzi = Rect(hx - hw - 10, hy, hw, hh);
		Mat hanzi1 = threshold_1(hanzi);
		//imshow("mmm", hanzi1);
		carChar.insert(carChar.begin(), hanzi1);
		/*char numbre[10];
		sprintf_s(numbre, "D:\\%d.jpg", 1);
		imwrite(numbre, hanzi1);*/
	}

	////字符识别
	struct str {
		Mat image;
		char world;
		double matchDegree;
	};
	struct str one[4];

	int j = 0;
	one[j].image = imread("temp_h/shan.jpg", 0);
	threshold(one[j].image, one[j].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(one[j].image, one[j].image, Size(40, 80), 0, 0, INTER_LINEAR);
	j++;
	one[j].image = imread("temp_h/yu.jpg", 0);
	threshold(one[j].image, one[j].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(one[j].image, one[j].image, Size(40, 80), 0, 0, INTER_LINEAR);
	j++;
	one[j].image = imread("temp_h/zhe.jpg", 0);
	threshold(one[j].image, one[j].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(one[j].image, one[j].image, Size(40, 80), 0, 0, INTER_LINEAR);
	j++;
	one[j].image = imread("temp_h/su.jpg", 0);
	threshold(one[j].image, one[j].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(one[j].image, one[j].image, Size(40, 80), 0, 0, INTER_LINEAR);

	int add = 0;
	int addTemp = 0;
	Mat absCutImage;
	double temp;
	int index = 0;
	CString result;

	resize(carChar[0], carChar[0], Size(40, 80), 0, 0, INTER_LINEAR);
	for (int i = 0; i < carChar[0].rows; i++) {
		for (int j = 0; j < carChar[0].cols; j++) {
			uchar* data = carChar[0].ptr<uchar>(i);
			int pixel = data[j];
			//cout << "pixel=" << pixel << endl;
			if (pixel == 0) {
				add++;
				//cout << "add=" << add << endl;
			}
		}
	}


	for (int k = 0; k < 4; k++, addTemp = 0) {
		absdiff(carChar[0], one[k].image, absCutImage);
		for (int i = 0; i < absCutImage.rows; i++) {
			for (int j = 0; j < absCutImage.cols; j++) {
				uchar* data = absCutImage.ptr<uchar>(i);
				int pixelTemp = data[j];
				//cout << "pixelTemp=" << pixelTemp << endl;
				if (pixelTemp == 0) {
					addTemp++;
					//cout << addTemp << endl;
				}
			}
		}
		temp = 1.0 - 1.0*addTemp / add;
		//cout << first[x].num << temp << endl;
		if (temp <= 1 && temp > 0)
			one[k].matchDegree = temp;
		else
			one[k].matchDegree = 0;
		if (k > 0 && one[k].matchDegree > one[index].matchDegree)
			index = k;
	}
	switch (index)
	{
	case 0:
		result += "陕";
		break;
	case 1:
		result += "豫";
		break;
	case 2:
		result += "浙";
		break;
	case 3:
		result += "苏";
		break;
	default:
		AfxMessageBox(_T("识别失败"));
		break;
	}
	
	struct str1 {
		Mat image;
		char num;
		double matchDegree;
	};
	struct str1 first[35];

	int i = 0;
	first[i].image = imread("temp/0.jpg", 0);
	first[i].num = '0';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/1.jpg", 0);
	first[i].num = '1';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/2.jpg", 0);
	first[i].num = '2';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/3.jpg", 0);
	first[i].num = '3';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/4.jpg", 0);
	first[i].num = '4';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/5.jpg", 0);
	first[i].num = '5';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/6.jpg", 0);
	first[i].num = '6';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/7.jpg", 0);
	first[i].num = '7';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/8.jpg", 0);
	first[i].num = '8';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/9.jpg", 0);
	first[i].num = '9';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/a.jpg", 0);
	first[i].num = 'A';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/b.jpg", 0);
	first[i].num = 'B';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/c.jpg", 0);
	first[i].num = 'C';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/d.jpg", 0);
	first[i].num = 'D';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/e.jpg", 0);
	first[i].num = 'E';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/f.jpg", 0);
	first[i].num = 'F';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/g.jpg", 0);
	first[i].num = 'G';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/h.jpg", 0);
	first[i].num = 'H';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/j.jpg", 0);
	first[i].num = 'J';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/k.jpg", 0);
	first[i].num = 'K';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/l.jpg", 0);
	first[i].num = 'L';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/m.jpg", 0);
	first[i].num = 'M';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/n.jpg", 0);
	first[i].num = 'N';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/p.jpg", 0);
	first[i].num = 'P';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/q.jpg", 0);
	first[i].num = 'Q';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/r.jpg", 0);
	first[i].num = 'R';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/s.jpg", 0);
	first[i].num = 'S';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/t.jpg", 0);
	first[i].num = 'T';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/u.jpg", 0);
	first[i].num = 'U';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/v.jpg", 0);
	first[i].num = 'V';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/w.jpg", 0);
	first[i].num = 'W';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/x.jpg", 0);
	first[i].num = 'X';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/y.jpg", 0);
	first[i].num = 'Y';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);
	i++;
	first[i].image = imread("temp/z.jpg", 0);
	first[i].num = 'Z';
	threshold(first[i].image, first[i].image, 0, 225, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
	resize(first[i].image, first[i].image, Size(40, 80), 0, 0, INTER_LINEAR);

	int add1 = 0;
	int addTemp1 = 0;
	Mat absCutImage1;
	double temp1;
	int index1 = 0;

	for (int y = 1; y < carChar.size(); y++, add1 = 0, index1 = 0) {
		resize(carChar[y], carChar[y], Size(40, 80), 0, 0, INTER_LINEAR);
		for (int i = 0; i < carChar[y].rows; i++) {
			for (int j = 0; j < carChar[y].cols; j++) {
				uchar* data = carChar[y].ptr<uchar>(i);
				int pixel = data[j];
				//cout << "pixel=" << pixel << endl;
				if (pixel == 0) {
					add1++;
					//cout << "add1=" << add1 << endl;
				}
			}
		}


		for (int x = 0; x < 34; x++, addTemp1 = 0) {
			absdiff(carChar[y], first[x].image, absCutImage1);
			for (int i = 0; i < absCutImage1.rows; i++) {
				for (int j = 0; j < absCutImage1.cols; j++) {
					uchar* data = absCutImage1.ptr<uchar>(i);
					int pixelTemp = data[j];
					//cout << "pixelTemp=" << pixelTemp << endl;
					if (pixelTemp <= 128) {
						addTemp1++;
						//cout << addTemp1 << endl;
					}
				}
			}
			temp1 = 1.0 - 1.0*addTemp1 / add1;
			//cout << first[x].num << temp << endl;
			if (temp1 <= 1 && temp1 > 0)
				first[x].matchDegree = temp1;
			else
				first[x].matchDegree = 0;
			if (x > 0 && first[x].matchDegree > first[index1].matchDegree)
				index1 = x;
		}
		result += first[index1].num;

	}
	AfxMessageBox(_T("识别结果:\n")+result);
	
}
