#include "stdafx.h"
#include "header.h"

pcap_t* PcapInit(char* adapter) {
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	handle = pcap_open_live(adapter, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		printf("\'%s\'��(��) ���� ���߽��ϴ�: %s\n", adapter, errbuf);
		puts("\n�Ʒ� �������̽� ����� Ȯ���ϰ� �ٽ� �������ּ���");
		PcapAdapterListPrint();
		return nullptr;
	}
	return handle;
}

bool PcapAdapterListPrint() {
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		printf("�������̽� ����� �ҷ����� �� ������ �߻��Ͽ����ϴ�: %s\n", errbuf);
		return RETURN_ERROR;
	}

	for (d = alldevs; d != NULL; d = d->next) {
		printf("\n%d)\n\t�̸�: %s\n", ++i, d->name);
		if (d->description) {
			printf("\t����: %s\n", d->description);
		}
		uint8_t d_mac[6];
		get_mac_address(d, d_mac);
		printf("\tMac: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X", d_mac[0], d_mac[1], d_mac[2], d_mac[3], d_mac[4], d_mac[5]);
	}

	if (i == 0) {
		puts("��밡���� �������̽� ����� �ҷ��� �� �����ϴ�!");
		puts("WinPcap�� ���������� ��ġ�Ǿ� �ִ��� Ȯ�����ּ���");
		return RETURN_ERROR;
	}

	pcap_freealldevs(alldevs);
	return RETURN_SUCCESS;
}