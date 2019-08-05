#include "stdafx.h"
#include "header.h"

bool PcapSend(pcap_t* handle, uint8_t* packet, int len) {
	for (int i = 0; i < len; i++) {
		if (i == 0);
		else if (i % 16 == 0) printf("\n");
		else if (i % 8 == 0) printf("   ");
		printf("%.2X ", packet[i]);
	}
	printf("\n\n\n");
	if (pcap_sendpacket(handle , packet, len) != 0) {
		printf("패킷 발송 실패: %s\n", pcap_geterr(handle));
		return RETURN_ERROR;
	}
	if (pcap_sendpacket(handle, packet, len) != 0) {
		printf("패킷 발송 실패: %s\n", pcap_geterr(handle));
		return RETURN_ERROR;
	}
	return RETURN_SUCCESS;
}