#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#define IDC_EDIT_URL 1001
#define IDC_BUTTON_CRAWL 1002

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "URL HTML Crawler",
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

    // 创建输入框：URL
    HWND hEditURL = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
        50, 50, 200, 25,
        hWnd,
        (HMENU)IDC_EDIT_URL,
        hInstance,
        nullptr);

    // 创建按钮：Crawl
    HWND hButtonCrawl = CreateWindow(
        "BUTTON",
        "Crawl",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 100, 100, 25,
        hWnd,
        (HMENU)IDC_BUTTON_CRAWL,
        hInstance,
        nullptr);

    ShowWindow(hWnd, nCmdShow);

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
        if (LOWORD(wParam) == IDC_BUTTON_CRAWL)
        {
            char bufferURL[256];
            GetDlgItemText(hWnd, IDC_EDIT_URL, bufferURL, sizeof(bufferURL));

            HINTERNET hInternet = InternetOpen("MyApp", INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
            if (hInternet)
            {
                HINTERNET hConnect = InternetConnect(hInternet, bufferURL, INTERNET_DEFAULT_HTTP_PORT, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0);
                if (hConnect)
                {
                    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", nullptr, nullptr, nullptr, nullptr, INTERNET_FLAG_RELOAD, 0);
                    if (hRequest)
                    {
                        if (HttpSendRequest(hRequest, nullptr, 0, nullptr, 0))
                        {
                            std::stringstream ss;
                            char buffer[1024];
                            DWORD bytesRead;
                            while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
                            {
                                ss.write(buffer, bytesRead);
                            }

                            std::string htmlContent = ss.str();

                            // 将 HTML 内容写入文件
                            std::ofstream outFile("html.html");
                            if (outFile.is_open())
                            {
                                outFile << htmlContent;
                                outFile.close();
                                std::cout << "HTML content saved to html.html\n";
                            }
                            else
                            {
                                std::cerr << "Failed to open html.html for writing.\n";
                            }
                        }
                        InternetCloseHandle(hRequest);
                    }
                    InternetCloseHandle(hConnect);
                }
                InternetCloseHandle(hInternet);
            }
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