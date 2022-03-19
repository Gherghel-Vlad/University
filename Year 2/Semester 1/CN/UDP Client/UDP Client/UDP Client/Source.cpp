#include <winsock.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <time.h> 
#include <Windows.h>

#pragma comment(lib,"WS2_32")


int main() {
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0) {
		perror("Couldnt create socket.");
		exit(-1);
	}

	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	 
	struct hostent*hp;
	hp = gethostbyname("192.168.0.155");

	if (hp == 0) {
		perror("Couldnt get addr from host name");
		exit(-2);
	}

	memcpy((char*)&server.sin_addr, (char*)hp->h_addr, hp->h_length);

	const char message[] = "asgfsgfdsgdf\0";


	int n = sendto(sock, message, sizeof(message)+1, 0, (struct sockaddr*)&server, sizeof(struct sockaddr_in));

	if (n < 0) {
		perror("Couldnt sent the data to the server");
		exit(-3);
	}

	return 0;
}