#include "stdafx.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
class main
{
public:
	
	BYTE version;
	BYTE headerLen;
	BYTE DF,MF;
	WORD fragOff;
	static CString strpro;
	static BOOL flag;
	char* ch[20];
public:
	struct IP_HEADER
	{
		union
		{
			BYTE Version;//�汾
			BYTE HdrLen;//�ײ�����
		};
		BYTE ServiceType;//���ַ���
		WORD TotalLen;//�ܳ���
		WORD ID;//��ʶ
		union
		{
			WORD Flags;//��־
			WORD FragOff;//Ƭƫ��
		};
		BYTE TimeToLive;//����ʱ��
		BYTE Protocol;//Э��
		WORD HdrChksum;//�ײ������
		DWORD SrcAddr;//Դ��ַ
		DWORD DstAddr;//Ŀ�ĵ�ַ
		BYTE Options;//ѡ��
	};
	IP_HEADER ip;
public:

	char* parseServiceType_getProcedence(BYTE b);
	char* parseServiceType_getTOS(BYTE b);
	char* getProtocol(BYTE Protocol);
	void ipparse(FILE *file,char * buffer,bool fout);

	CString print(CString str);
};

