#include "stdafx.h"
#include "header.h"

bool GetMac(char* adapter, uint8_t* mac) {
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		printf("인터페이스 목록을 불러오는 중 오류가 발생하였습니다: %s\n", errbuf);
		return RETURN_ERROR;
	}

	for (d = alldevs; d != NULL; d = d->next) {
		if (strcmp(d->name, adapter) == 0) {
			bool b = get_mac_address(d, mac);
			pcap_freealldevs(alldevs);
			if (b)
				return RETURN_ERROR;
			else
				return RETURN_SUCCESS;
		}
	}
}

bool ArpGetMac(pcap_t* handle, const uint8_t* myMac, const uint8_t* myIP, const uint8_t* ip, uint8_t* mac) {
	static const uint8_t broadMac[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	static const uint8_t nullMac[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t) * (SIZE_ETHERNET_HEADER + SIZE_ARP_HEADER));
	L2Ethernet* eth = (L2Ethernet*)packet;
	L3Arp* arp = (L3Arp*)(packet + SIZE_ETHERNET_HEADER);

	MakeL2Ethernet(eth, broadMac, myMac, ETH_TYPE_ARP);
	MakeL3Arp(arp, ARP_OPCODE_REQUEST, myMac, myIP, nullMac, ip);
	PcapSend(handle, packet, SIZE_ETHERNET_HEADER + SIZE_ARP_HEADER);
	PcapRecvArpReply(handle, ip, mac);

	return RETURN_SUCCESS;
}



// get_mac_address와 compare_guid는 WinPcap에서 선택한 어뎁터
// Mac Address를 얻어오기 위해 인터넷에서 가져온 코드
// 점점 달라지는 중?! 빨리 최적화하자!
// 출처: https://stackoverflow.com/questions/47748975/how-to-get-selected-adapters-mac-address-in-winpcap

int get_mac_address(pcap_if_t *d, u_char mac_addr[6]) {
	wchar_t* wszWideName = NULL;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	int nRVal = 0;
	unsigned int i;

	MIB_IFTABLE *pIfTable;
	MIB_IFROW *pIfRow;

	pIfTable = (MIB_IFTABLE *)malloc(sizeof(MIB_IFTABLE));
	if (pIfTable == NULL) {
		return 0;
	}
	dwSize = sizeof(MIB_IFTABLE);
	dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE);

	if (dwRetVal == ERROR_INSUFFICIENT_BUFFER) {
		free(pIfTable);
		pIfTable = (MIB_IFTABLE *)malloc(dwSize);
		if (pIfTable == NULL) {
			return 0;
		}

		dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE);
	}

	if (dwRetVal != NO_ERROR)
		goto done;

	{
		size_t stISize, stOSize;
		stISize = strlen(d->name) + 1;
		wszWideName = (wchar_t*)malloc(stISize * sizeof(wchar_t));

		if (!wszWideName)
			goto done;

		mbstowcs_s(&stOSize, wszWideName, stISize, d->name, stISize);
	}

	for (i = 0; i < pIfTable->dwNumEntries; i++) {
		pIfRow = (MIB_IFROW *)& pIfTable->table[i];

		if (!compare_guid(wszWideName, pIfRow->wszName)) {
			if (pIfRow->dwPhysAddrLen != 6)
				continue;

			memcpy(mac_addr, pIfRow->bPhysAddr, 6);
			nRVal = 1;
			break;
		}
	}

done:
	if (pIfTable != NULL)
		free(pIfTable);
	pIfTable = NULL;

	if (wszWideName != NULL)
		free(wszWideName);
	wszWideName = NULL;

	return nRVal;
}

int compare_guid(wchar_t *wszPcapName, wchar_t *wszIfName) {
	wchar_t *pc, *ic;

	for (pc = wszPcapName; ; ++pc) {
		if (!*pc)
			return -1;
		if (*pc == L'{') {
			pc++;
			break;
		}
	}

	for (ic = wszIfName; ; ++ic) {
		if (!*ic)
			return 1;

		if (*ic == L'{') {
			ic++;
			break;
		}
	}

	for (;; ++pc, ++ic) {
		if (!pc)
			return -1;
		if (!ic)
			return 1;
		if ((*pc == L'}') && (*ic == L'}'))
			return 0;
		if (*pc != *ic)
			return *ic - *pc;
	}
}