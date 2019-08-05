#include "stdafx.h"
#include "header.h"

bool PcapRecv(pcap_t* handle) {
	while (true) {
		struct pcap_pkthdr* header = nullptr;
		const u_char* packet = nullptr;
		int res = pcap_next_ex(handle, &header, &packet);
		if (res == 0) continue;
		if (res == -1 || res == -2) break;

		printf("%u bytes captured\n", header->caplen);
	}
	return RETURN_SUCCESS;
}

bool PcapRecvArpReply(pcap_t* handle, const uint8_t* ip, uint8_t* mac) {
	uint16_t ethType, arpOpCode;
	uint8_t arpIP[4], arpMac[6];
	// 패킷 3000개 안에 REPLY가 오지 않으면 실패 (무한 루프 가능성 때문에)
	for (int i = 0; i < 3000; i++) {
		struct pcap_pkthdr* header = nullptr;
		const u_char* packet = nullptr;
		int res = pcap_next_ex(handle, &header, &packet);
		if (res == 0) continue;
		if (res == -1 || res == -2) break;

		ParseL2EthernetType((L2Ethernet*)packet, &ethType);
		//printf("ethType = %d\n", ethType);
		if (ethType == ETH_TYPE_ARP) {
			ParseL3ArpReply((L3Arp*)(packet + SIZE_ETHERNET_HEADER), &arpOpCode, arpIP, arpMac);
			if (arpOpCode == ARP_OPCODE_REPLY && memcmp(ip, arpIP, sizeof(uint8_t) * 4) == 0) {
				memcpy(mac, arpMac, sizeof(uint8_t) * 6);
				return RETURN_SUCCESS;
			}
		}
	}
	return RETURN_ERROR;
}