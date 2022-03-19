#include <winsock.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <time.h> 
#include <Windows.h>
int main() {
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}



	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		perror("could not create socket");
		return -1;
	}

	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(9090);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.0.155"); //79.117.61.232

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("Couldnt connect to server");
		return -1;
	}

	printf("Connected \n");
	srand(time(NULL) + rand());
	INT32 a = rand();
	INT32 b = a;
	a = htonl(a);
	int nr_bytes = send(sock, (char*)&a, sizeof(a), 0);

	

	printf("Number %d was sent succefull.\n", b);



	return 0;
}