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
			BYTE Version;//版本
			BYTE HdrLen;//首部长度
		};
		BYTE ServiceType;//区分服务
		WORD TotalLen;//总长度
		WORD ID;//标识
		union
		{
			WORD Flags;//标志
			WORD FragOff;//片偏移
		};
		BYTE TimeToLive;//生存时间
		BYTE Protocol;//协议
		WORD HdrChksum;//首部检验和
		DWORD SrcAddr;//源地址
		DWORD DstAddr;//目的地址
		BYTE Options;//选项
	};
	IP_HEADER ip;
public:

	char* parseServiceType_getProcedence(BYTE b);
	char* parseServiceType_getTOS(BYTE b);
	char* getProtocol(BYTE Protocol);
	void ipparse(FILE *file,char * buffer,bool fout);

	CString print(CString str);
};

