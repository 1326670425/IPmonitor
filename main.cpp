// ipparse.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "main.h"

#pragma comment(lib,"ws2_32.lib")

CString main::strpro = _T("����");
BOOL main::flag = TRUE;

char* main::parseServiceType_getProcedence(BYTE b)//���ȼ�����
{
	switch(b>>5)
	{
	case 0:
		return "Routine";//��ͨ
	case 1:
		return "Priority";//����
	case 2:
		return "Immediate";//����
	case 3:
		return "Flash";//��ʱ
	case 4:
		return "Flash Override";//��ʱ������
	case 5:
		return "CRITIC/ECP";//��Ҫ
	case 6:
		return "Internet work Control";//��������
	case 7:
		return "Network Control";//�������
	default:
		return "Unknown";
	}
}

char* main::parseServiceType_getTOS(BYTE b)//������������
{
	b=(b>>1)&0x0f;
	switch(b)
	{
	case 0:
		return "Normal service";//��ͨ����
	case 1:
		return "Minimize monetary cost";//��Ǯ�ɱ���С
	case 2:
		return "Maximize reliability";//�ɿ������
	case 4:
		return "Maximize throughput";//���������
	case 8:
		return "Minimize delay";//�ӳ���С
	case 15:
		return "Maximize security";//��ȫ�����
	default:
		return "Unknown";
	}
}


char* main::getProtocol(BYTE Protocol)//Э������
{
	switch(Protocol)
	{
	case 1:
		*ch="ICMP";break;
	case 2:
		*ch="IGMP";break;
	case 4:
		*ch="IP in IP";break;
	case 6:
		*ch="TCP";break;
	case 8:
		*ch="EGP";break;
	case 17:
		*ch="UDP";break;
	case 41:
		*ch="IPv6";break;
	case 46:
		*ch="RSVP";break;
	case 50:
		*ch="ESP";break;
	case 89:
		*ch="OSPF";break;
	default:
		*ch="UNKNOWN";break;
	}
	CString s(*ch);
	if(main::strpro==_T("����")||s==main::strpro)
		main::flag = TRUE;
	else
		main::flag = FALSE;
	return *ch;
}

void main::ipparse(FILE *file,char * buffer,bool fout)
{

	ip=*(IP_HEADER*)buffer;

	/*�����ײ�*/
	version = ip.Version>>4;//�汾
	headerLen = (ip.HdrLen&0x0f)*4;//�ײ�����
	DF = (ip.Flags>>14)&0x01;//��ֹ��Ƭ��ʶ
	MF = (ip.Flags>>13)&0x01;//��Ƭ��־
	fragOff = ip.FragOff&0x1fff;//Ƭƫ��

	/*������ļ�*/
	if(fout)
	{
	fprintf(file,"�汾=%d\r\n",version);
	fprintf(file,"ͷ����=%d(BYTE)\r\n",headerLen);
	fprintf(file,"��������=%s,%s\r\n",
		parseServiceType_getProcedence(ip.ServiceType),
		parseServiceType_getTOS(ip.ServiceType));
	fprintf(file,"���ݱ�����=%d(BYTE)\r\n",ip.TotalLen);
	fprintf(file,"���ݱ�ID=%d\r\n",ip.ID);
	fprintf(file,"�ֶα�־DF=%d��MF=%d\r\n",DF,MF);
	fprintf(file,"�ֶ�ƫ��ֵ=%d\r\n",fragOff);
	fprintf(file,"������=%d(hops)\r\n",ip.TimeToLive);
	fprintf(file,"Э��=%s\r\n",getProtocol(ip.Protocol));
	fprintf(file,"ͷУ���=0x%0x\r\n",ip.HdrChksum);
	fprintf(file,"ԴIP��ַ=%s\r\n",inet_ntoa(*(in_addr*)&ip.SrcAddr));
	fprintf(file,"Ŀ��IP��ַ=%s\r\n",inet_ntoa(*(in_addr*)&ip.DstAddr));
	fprintf(file,"-------------------------------------------------------\r\n");
	}
}



CString main::print(CString str)
{
	CString procedence(parseServiceType_getProcedence(ip.ServiceType));
	CString TOS(parseServiceType_getTOS(ip.ServiceType));
	CString protocol(getProtocol(ip.Protocol));
	str.Format(_T("%d\r\n\r\n%d(BYTE)\r\n\r\n%s,%s\r\n\r\n%d(BYTE)\r\n\r\n%d\r\n\r\n%d,%d\r\n\r\n%d\r\n\r\n%d(hops)\r\n\r\n%s\r\n\r\n0x%0x\r\n\r\n"),
		version,
		headerLen,
		procedence,
		TOS,
		ip.TotalLen,
		ip.ID,
		DF,
		MF,
		fragOff,
		ip.TimeToLive,
		protocol,
		ip.HdrChksum);
	str +=	inet_ntoa(*(in_addr*)&ip.SrcAddr);
	str += "\r\n\r\n";
	str +=	inet_ntoa(*(in_addr*)&ip.DstAddr);
	return str;
}