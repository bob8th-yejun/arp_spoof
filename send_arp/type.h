#pragma once

typedef struct L2Ethernet {
	uint8_t dMac[6];
	uint8_t sMac[6];
	uint16_t ethType;	// L3 Code (ARP = 0x0806)
} L2Ethernet;

typedef struct L3Arp {
	uint16_t hwType;	// ����: �̴���
	uint16_t proType;	// ����: IPv4
	uint8_t hwLen;		// ����: 6byte (mac size)
	uint8_t proLen;		// ����: 4byte (ip  size)
	uint16_t opCode;	// 0 = request, 1 = reply
	uint8_t sMac[6];	
	uint8_t sIP[4];
	uint8_t dMac[6];
	uint8_t dIP[4];
} L3Arp;