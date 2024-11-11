using namespace std;

bool warn_connect(const string& ip){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return false;
    }

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Socket creation error\n";
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);

    if (inet_pton(AF_INET, ip.c_str(), &serverAddress.sin_addr) <= 0) {
        cout << "[FAILED] Connect failed\n";
        cout << "[WARNING] This IP address is not supported!\n";
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        cout << "[FAILED] Cannot connect to the Internet!\n";
        cout << "[WARNING] This project supports only eth0 or wlan0!\n";
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    const char* message = "Hello, server!";
    if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        cout << "Message sending failed\n";
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    else {
        cout << "[OK] Internet connected\n";
        cout << "[OK] Loading packet manager...\n";
    }
    closesocket(clientSocket);
    WSACleanup();
    return true;
}

int system_load(){
    const string IP = "104.26.14.72";
	cout << "[PROCCESS] Loading system...\n";
	bool load = warn_connect(IP);
	if(load == false){
       cout << "[CRITICAL ERROR] Cannot load system!\n";
       cout << "Rebooting!\n";
       exit(0);
	}
	else {
		cout << "[OK] System loaded\n";
	}
	return 0;
}
