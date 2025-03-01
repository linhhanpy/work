#include <winsock2.h>
#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <string>


#pragma comment(lib, "gdiplus.lib")

#pragma comment(lib, "ws2_32.lib")
#define IDC_BUTTON1 1001
#define IDC_EDIT1 1002
#define IDC_EDIT_IP 1003
#define IDC_EDIT_PORT 1004
#define IDC_EDIT_MESSAGE 1005
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

// 修改后的 trojan_horse 函数，接收 hWnd 作为参数
void trojan_horse(HWND hWnd, std::string ip, int port, std::string cmd) {
    if (cmd == "exit") {
        return;
    }
    std::string result = sendCommandAndReceive(ip.c_str(), port, cmd);
    MessageBox(hWnd, result.c_str(), "return", MB_OK);
    std::cout << "Return: " << result << std::endl;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0)); // RGB(0, 0, 0) 表示黑色

    RegisterClass(&wc);

    // 创建窗口
    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (hWnd == nullptr)
    {
        return 0;
    }

    // 创建静态文本控件：IP
    HWND hStaticTextIP = CreateWindow(
        "STATIC",
        "IP:",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        50, 50, 200, 25,
        hWnd,
        nullptr,
        hInstance,
        nullptr);

    // 创建输入框：IP
    HWND hEditIP = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
        100, 50, 100, 25,
        hWnd,
        (HMENU)IDC_EDIT_IP,
        hInstance,
        nullptr);

    // 创建静态文本控件：PORT
    HWND hStaticTextPort = CreateWindow(
        "STATIC",
        "PORT:",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        50, 80, 200, 25,
        hWnd,
        nullptr,
        hInstance,
        nullptr);

    // 创建输入框：PORT
    HWND hEditPort = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
        100, 80, 100, 25,
        hWnd,
        (HMENU)IDC_EDIT_PORT,
        hInstance,
        nullptr);

    // 创建静态文本控件：Command
    HWND hStaticTextCommand = CreateWindow(
        "STATIC",
        "CMD:",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        50, 110, 200, 25,
        hWnd,
        nullptr,
        hInstance,
        nullptr);

    // 创建输入框：MESSAGE
    HWND hEditMessage = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
        100, 110, 100, 25,
        hWnd,
        (HMENU)IDC_EDIT_MESSAGE,
        hInstance,
        nullptr);

    // 创建按钮
    HWND hButton = CreateWindow(
        "BUTTON",
        "Send",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 140, 100, 25,
        hWnd,
        (HMENU)IDC_BUTTON1,
        hInstance,
        nullptr);

    // 创建静态文本控件显示一段文字
    HWND hStaticTextInfo = CreateWindow(
        "STATIC",
        "Enter the things.",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        50, 170, 200, 25,
        hWnd,
        nullptr,
        hInstance,
        nullptr);


    ShowWindow(hWnd, nCmdShow);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1)
        {
            // 处理按钮点击事件
            char bufferIP[256];
            char bufferPort[256];
            char bufferMessage[256];
            GetDlgItemText(hWnd, IDC_EDIT_IP, bufferIP, sizeof(bufferIP));
            GetDlgItemText(hWnd, IDC_EDIT_PORT, bufferPort, sizeof(bufferPort));
            GetDlgItemText(hWnd, IDC_EDIT_MESSAGE, bufferMessage, sizeof(bufferMessage));
            MessageBox(hWnd, bufferMessage, bufferIP, MB_OK);
            int portNumber = atoi(bufferPort);
            trojan_horse(hWnd, bufferIP, portNumber, bufferMessage);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}