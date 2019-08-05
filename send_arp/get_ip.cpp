#include "stdafx.h"
#include "header.h"

void ifprint(pcap_if_t *d, uint8_t* ip);
char* iptos(u_long in);

// ������ �������̽��� �ش��ϴ� IP��
// WinPacp���� ������ �������� ���ͳ��� �ҽ��� ������ �����Ͽ����ϴ�.
// ���� ���ҽ��ʹ� �޶����� ��?! ���� ����ȭ ����!
// �� �ҽ� ��ó: https://www.winpcap.org/pipermail/winpcap-users/2006-July/001214.html

int GetIP(char* adapter, uint8_t* ip)
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE + 1];

	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		printf("�������̽� ����� �ҷ����� �� ������ �߻��Ͽ����ϴ�: %s\n", errbuf);
		return RETURN_ERROR;
	}

	for (d = alldevs; d; d = d->next) {
		if (strcmp(d->name, adapter) == 0) {
			ifprint(d, ip);
			break;
		}
	}

	pcap_freealldevs(alldevs);
	return RETURN_SUCCESS;
}

void ifprint(pcap_if_t *d, uint8_t* ip)
{
	pcap_addr_t *a;
	pcap_t *hadapter;
	hadapter = pcap_open_live(d->name, 0, 0, 0, 0);
	pcap_close(hadapter);
	for (a = d->addresses; a; a = a->next) {
		if (a->addr->sa_family == AF_INET)
			if (a->addr)
				Char2UintIP(iptos(((struct sockaddr_in*)a->addr)->sin_addr.s_addr), ip);
	}
}

char *iptos(u_long in)
{
	static char output[12][3 * 4 + 3 + 1];
	static short which;
	u_char *p;

	p = (u_char *)&in;
	which = (which + 1 == 12 ? 0 : which + 1);
	sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}