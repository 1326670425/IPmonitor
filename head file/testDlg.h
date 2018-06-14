
// testDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CtestDlg 对话框
class CtestDlg : public CDialogEx
{
// 构造
public:
	CtestDlg(CWnd* pParent = NULL);	// 标准构造函数
	CFont m_editFont;
	FILE *file;
	WSADATA wsData;
	SOCKET sock;
	BOOL flag;
	BOOL fout;
	char hostName[128];
	hostent * pHostIP;
	sockaddr_in addr_in;
	DWORD dwValue;
	DWORD dwBufferLen[10];
	DWORD dwBufferInLen;
	DWORD dwBytesReturned;


// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

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
	afx_msg void OnBnClickedStart();
	CString m_edit;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPause();
	CComboBox m_protocol;
	afx_msg void OnCbnSelchangeProtocol();
	afx_msg void OnBnClickedCheck2();
	int m_port;
	afx_msg void OnBnClickedInit();
	afx_msg void OnEnChangePort();
};
