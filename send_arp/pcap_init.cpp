#include "stdafx.h"
#include "header.h"

pcap_t* PcapInit(char* adapter) {
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	handle = pcap_open_live(adapter, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		printf("\'%s\'을(를) 열지 못했습니다: %s\n", adapter, errbuf);
		puts("\n아래 인터페이스 목록을 확인하고 다시 실행해주세요");
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
		printf("인터페이스 목록을 불러오는 중 오류가 발생하였습니다: %s\n", errbuf);
		return RETURN_ERROR;
	}

	for (d = alldevs; d != NULL; d = d->next) {
		printf("\n%d)\n\t이름: %s\n", ++i, d->name);
		if (d->description) {
			printf("\t설명: %s\n", d->description);
		}
		uint8_t d_mac[6];
		get_mac_address(d, d_mac);
		printf("\tMac: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X", d_mac[0], d_mac[1], d_mac[2], d_mac[3], d_mac[4], d_mac[5]);
	}

	if (i == 0) {
		puts("사용가능한 인터페이스 목록을 불러올 수 없습니다!");
		puts("WinPcap이 정상적으로 설치되어 있는지 확인해주세요");
		return RETURN_ERROR;
	}

	pcap_freealldevs(alldevs);
	return RETURN_SUCCESS;
}