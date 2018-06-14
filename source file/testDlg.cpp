
// testDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtestDlg �Ի���




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


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_editFont.CreatePointFont(130, _T("����"));
	GetDlgItem(IDC_EDIT)->SetFont(&m_editFont);
	SetDlgItemText(IDC_PROTOCOL,_T("����"));	
	fout=FALSE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_EDIT,_T(""));
	SetTimer(1,1000,NULL);
	
}


void CtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	if(fout)
		fclose(file);
}


void CtestDlg::OnCbnSelchangeProtocol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_protocol.GetLBText(m_protocol.GetCurSel(),main::strpro);

}


void CtestDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if((file=fopen("log.txt","wb+"))==NULL)
	{
		AfxMessageBox(_T("open file failed!"));
		exit(-1);
	}
	fout = TRUE;
}


void CtestDlg::OnBnClickedInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if((sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP))==INVALID_SOCKET)//����ԭʼ�׽���
	{
		AfxMessageBox(_T("create socket failed!"));
		exit(-1);
	}
	if(setsockopt(sock,IPPROTO_IP,IP_HDRINCL,(char*)&flag,sizeof(flag))==SOCKET_ERROR)//�׽������ã��û��Լ���IPͷ����
	{
		AfxMessageBox(_T("create socket failed!"));
		exit(-1);
	}
	if(gethostname(hostName,100)==SOCKET_ERROR)//��ȡ������
	{
		AfxMessageBox(_T("gethostname failed!"));
		exit(-1);
	}
	if((pHostIP=gethostbyname(hostName))==NULL)//��ȡ����IP��ַ
	{
		AfxMessageBox(_T("gethostbyname failed!"));
		exit(-1);
	}
	addr_in.sin_addr=*(in_addr *)pHostIP->h_addr_list[0];
	addr_in.sin_family=AF_INET;
	addr_in.sin_port=htons(m_port);//��ȡ����Ķ˿ں�
	if(bind(sock,(PSOCKADDR)&addr_in,sizeof(addr_in))==SOCKET_ERROR)//��socket
	{
		AfxMessageBox(_T("bind failed!"));
		exit(-1);
	}
	if(WSAIoctl(sock,IO_RCVALL,&dwBufferInLen,sizeof(dwBufferInLen),
		&dwBufferLen,sizeof(dwBufferLen),&dwBytesReturned,NULL,NULL)==SOCKET_ERROR)//�������û���ģʽ��������������
	{
		AfxMessageBox(_T("ioctlsock failed!"));
		exit(-1);
	}
}


void CtestDlg::OnEnChangePort()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
