
// testDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

// CtestDlg �Ի���
class CtestDlg : public CDialogEx
{
// ����
public:
	CtestDlg(CWnd* pParent = NULL);	// ��׼���캯��
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


// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
