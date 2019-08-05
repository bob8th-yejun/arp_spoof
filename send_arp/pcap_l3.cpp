#include "stdafx.h"
#include "header.h"

bool makeL3Arp(L3Arp* arp, uint16_t opCode, uint8_t* sMac, uint8_t* sIP, uint8_t* dMac, uint8_t* dIP) {
	arp->hwType = 0x0001;	// Ethernet
	arp->proType = 0x0800;	// IPv4
	arp->hwLen = 6;			// Mac size
	arp->proLen = 4;		// IPv4 size
	arp->opCode = opCode;
	memcpy(arp->sMac, sMac, sizeof(uint8_t) * 6);
	memcpy(arp->sIP, sIP, sizeof(uint8_t) * 4);
	memcpy(arp->dMac, dMac, sizeof(uint8_t) * 6);
	memcpy(arp->dIP, dIP, sizeof(uint8_t) * 4);
	return RETURN_SUCCESS;
}

bool parseL3Arp(L3Arp* arp, uint16_t opCode, uint8_t* sMac, uint8_t* sIP, uint8_t* dMac, uint8_t* dIP) {
	if (arp->hwType != 0x0001 || arp->proType != 0x0800 || arp->hwLen != 6 || arp->proLen != 4)
		return RETURN_ERROR;
	opCode = arp->opCode;
	memcpy(sMac, arp->sMac, sizeof(uint8_t) * 6);
	memcpy(sIP, arp->sIP, sizeof(uint8_t) * 4);
	memcpy(dMac, arp->dMac, sizeof(uint8_t) * 6);
	memcpy(dIP, arp->dIP, sizeof(uint8_t) * 4);
	return RETURN_SUCCESS;
}