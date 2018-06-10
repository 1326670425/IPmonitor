// ipparse.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "main.h"

#pragma comment(lib,"ws2_32.lib")

CString main::strpro = _T("不限");
BOOL main::flag = TRUE;

char* main::parseServiceType_getProcedence(BYTE b)//优先级子域
{
	switch(b>>5)
	{
	case 0:
		return "Routine";//普通
	case 1:
		return "Priority";//优先
	case 2:
		return "Immediate";//立刻
	case 3:
		return "Flash";//即时
	case 4:
		return "Flash Override";//即时，优先
	case 5:
		return "CRITIC/ECP";//重要
	case 6:
		return "Internet work Control";//网络间控制
	case 7:
		return "Network Control";//网络控制
	default:
		return "Unknown";
	}
}

char* main::parseServiceType_getTOS(BYTE b)//服务类型子域
{
	b=(b>>1)&0x0f;
	switch(b)
	{
	case 0:
		return "Normal service";//普通服务
	case 1:
		return "Minimize monetary cost";//金钱成本最小
	case 2:
		return "Maximize reliability";//可靠性最大
	case 4:
		return "Maximize throughput";//吞吐量最大
	case 8:
		return "Minimize delay";//延迟最小
	case 15:
		return "Maximize security";//安全级最高
	default:
		return "Unknown";
	}
}


char* main::getProtocol(BYTE Protocol)//协议类型
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
	if(main::strpro==_T("不限")||s==main::strpro)
		main::flag = TRUE;
	else
		main::flag = FALSE;
	return *ch;
}

void main::ipparse(FILE *file,char * buffer,bool fout)
{

	ip=*(IP_HEADER*)buffer;

	/*解析首部*/
	version = ip.Version>>4;//版本
	headerLen = (ip.HdrLen&0x0f)*4;//首部长度
	DF = (ip.Flags>>14)&0x01;//禁止分片标识
	MF = (ip.Flags>>13)&0x01;//分片标志
	fragOff = ip.FragOff&0x1fff;//片偏移

	/*输出到文件*/
	if(fout)
	{
	fprintf(file,"版本=%d\r\n",version);
	fprintf(file,"头长度=%d(BYTE)\r\n",headerLen);
	fprintf(file,"服务类型=%s,%s\r\n",
		parseServiceType_getProcedence(ip.ServiceType),
		parseServiceType_getTOS(ip.ServiceType));
	fprintf(file,"数据报长度=%d(BYTE)\r\n",ip.TotalLen);
	fprintf(file,"数据报ID=%d\r\n",ip.ID);
	fprintf(file,"分段标志DF=%d，MF=%d\r\n",DF,MF);
	fprintf(file,"分段偏移值=%d\r\n",fragOff);
	fprintf(file,"生存期=%d(hops)\r\n",ip.TimeToLive);
	fprintf(file,"协议=%s\r\n",getProtocol(ip.Protocol));
	fprintf(file,"头校验和=0x%0x\r\n",ip.HdrChksum);
	fprintf(file,"源IP地址=%s\r\n",inet_ntoa(*(in_addr*)&ip.SrcAddr));
	fprintf(file,"目的IP地址=%s\r\n",inet_ntoa(*(in_addr*)&ip.DstAddr));
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