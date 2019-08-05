#include "stdafx.h"
#include "header.h"

bool MakeL3Arp(L3Arp* arp, const uint16_t opCode, const uint8_t* sMac, const uint8_t* sIP, const uint8_t* dMac, const uint8_t* dIP) {
	arp->hwType = htons(0x0001);	// Ethernet
	arp->proType = htons(0x0800);	// IPv4
	arp->hwLen = 6;					// Mac size
	arp->proLen = 4;				// IPv4 size
	arp->opCode = htons(opCode);
	memcpy(arp->sMac, sMac, sizeof(uint8_t) * 6);
	memcpy(arp->sIP, sIP, sizeof(uint8_t) * 4);
	memcpy(arp->dMac, dMac, sizeof(uint8_t) * 6);
	memcpy(arp->dIP, dIP, sizeof(uint8_t) * 4);
	return RETURN_SUCCESS;
}

bool ParseL3Arp(const L3Arp* arp, uint16_t opCode, uint8_t* sMac, uint8_t* sIP, uint8_t* dMac, uint8_t* dIP) {
	if (ntohs(arp->hwType) != 0x0001 || ntohs(arp->proType) != 0x0800 || arp->hwLen != 6 || arp->proLen != 4)
		return RETURN_ERROR;
	opCode = ntohs(arp->opCode);
	memcpy(sMac, arp->sMac, sizeof(uint8_t) * 6);
	memcpy(sIP, arp->sIP, sizeof(uint8_t) * 4);
	memcpy(dMac, arp->dMac, sizeof(uint8_t) * 6);
	memcpy(dIP, arp->dIP, sizeof(uint8_t) * 4);
	return RETURN_SUCCESS;
}

bool ParseL3ArpReply(const L3Arp* arp, uint16_t* opCode, uint8_t* sIP, uint8_t* sMac) {
	if (ntohs(arp->hwType) != 0x0001 || ntohs(arp->proType) != 0x0800 || arp->hwLen != 6 || arp->proLen != 4)
		return RETURN_ERROR;
	*opCode = ntohs(arp->opCode);
	memcpy(sMac, arp->sMac, sizeof(uint8_t) * 6);
	memcpy(sIP, arp->sIP, sizeof(uint8_t) * 4);
	return RETURN_SUCCESS;
}