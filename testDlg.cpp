
// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"
#include "main.h"

#define BUFFER_SIZE 65535
#define IO_RCVALL _WSAIOW(IOC_VENDOR,1)



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestDlg 对话框




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDlg::IDD, pParent)
	, m_edit(_T(""))
	, m_port(6000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, m_edit);
	DDX_Control(pDX, IDC_PROTOCOL, m_protocol);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDV_MinMaxInt(pDX, m_port, 1024, 65536);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CtestDlg::OnBnClickedStart)
	//ON_EN_CHANGE(IDC_EDIT, &CtestDlg::OnEnChangeEdit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PAUSE, &CtestDlg::OnBnClickedPause)
	ON_CBN_SELCHANGE(IDC_PROTOCOL, &CtestDlg::OnCbnSelchangeProtocol)
	ON_BN_CLICKED(IDC_CHECK2, &CtestDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_INIT, &CtestDlg::OnBnClickedInit)
	ON_EN_CHANGE(IDC_PORT, &CtestDlg::OnEnChangePort)
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_editFont.CreatePointFont(130, _T("隶书"));
	GetDlgItem(IDC_EDIT)->SetFont(&m_editFont);
	SetDlgItemText(IDC_PROTOCOL,_T("不限"));	
	fout=FALSE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestDlg::OnPaint()
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
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码

	::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_EDIT,_T(""));
	SetTimer(1,1000,NULL);
	
}


void CtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	main m;
	char buffer[BUFFER_SIZE];
	int size=recv(sock,buffer,BUFFER_SIZE,0);
	if(size>0)
	{	
		m.ipparse(file,buffer,fout);
	}
	if(main::flag)
		::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_EDIT,m.print(str));

	CDialogEx::OnTimer(nIDEvent);
}


void CtestDlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	if(fout)
		fclose(file);
}


void CtestDlg::OnCbnSelchangeProtocol()
{
	// TODO: 在此添加控件通知处理程序代码
	m_protocol.GetLBText(m_protocol.GetCurSel(),main::strpro);

}


void CtestDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if((file=fopen("log.txt","wb+"))==NULL)
	{
		AfxMessageBox(_T("open file failed!"));
		exit(-1);
	}
	fout = TRUE;
}


void CtestDlg::OnBnClickedInit()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	flag=TRUE;

	dwValue = -1;
	dwBufferInLen=1;
	dwBytesReturned=0;
	if(WSAStartup(MAKEWORD(2,2),&wsData)!=0)
	{
		AfxMessageBox(_T("WSAStartup failed!"));
		exit(-1);
	}
	if((sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP))==INVALID_SOCKET)//创建原始套接字
	{
		AfxMessageBox(_T("create socket failed!"));
		exit(-1);
	}
	if(setsockopt(sock,IPPROTO_IP,IP_HDRINCL,(char*)&flag,sizeof(flag))==SOCKET_ERROR)//套接字设置，用户自己对IP头处理
	{
		AfxMessageBox(_T("create socket failed!"));
		exit(-1);
	}
	if(gethostname(hostName,100)==SOCKET_ERROR)//获取主机名
	{
		AfxMessageBox(_T("gethostname failed!"));
		exit(-1);
	}
	if((pHostIP=gethostbyname(hostName))==NULL)//获取本地IP地址
	{
		AfxMessageBox(_T("gethostbyname failed!"));
		exit(-1);
	}
	addr_in.sin_addr=*(in_addr *)pHostIP->h_addr_list[0];
	addr_in.sin_family=AF_INET;
	addr_in.sin_port=htons(m_port);//获取输入的端口号
	if(bind(sock,(PSOCKADDR)&addr_in,sizeof(addr_in))==SOCKET_ERROR)//绑定socket
	{
		AfxMessageBox(_T("bind failed!"));
		exit(-1);
	}
	if(WSAIoctl(sock,IO_RCVALL,&dwBufferInLen,sizeof(dwBufferInLen),
		&dwBufferLen,sizeof(dwBufferLen),&dwBytesReturned,NULL,NULL)==SOCKET_ERROR)//网卡设置混杂模式，接收所有数据
	{
		AfxMessageBox(_T("ioctlsock failed!"));
		exit(-1);
	}
}


void CtestDlg::OnEnChangePort()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
