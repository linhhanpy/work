#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h> // ���� SHGetFileInfo
#include <string>
#include <vector>

// ͼ��ṹ��
struct Icon {
    int x, y;              // ͼ��λ��
    int width, height;     // ͼ���С
    std::string name;      // ͼ������
    std::string path;      // ͼ��·��
    HICON hIcon;           // ͼ����
};

// ȫ�ֱ���
std::vector<Icon> icons;   // ͼ���б�
IMAGE backgroundImg;       // ����ͼƬ

// ���ر���ͼƬ
void loadBackground() {
    // ֱ��ָ��һ�ű���ͼƬ·��
    loadimage(&backgroundImg, "123.jpg");
}

// ��ȡ .exe �ļ���ͼ��
HICON getExeIcon(const std::string& path) {
    SHFILEINFO shfi;
    if (SHGetFileInfo(path.c_str(), 0, &shfi, sizeof(shfi), SHGFI_ICON | SHGFI_LARGEICON)) {
        return shfi.hIcon;
    }
    return nullptr;
}

void DrawVectorText(HDC hdc, int x, int y, const std::string& text, const std::string& fontName, int fontSize, COLORREF color) {
    // ��������
    HFONT hFont = CreateFontA(
        fontSize,                // ����߶�
        0,                       // �����ȣ�0 ��ʾ����Ӧ��
        0,                       // �ı���б�Ƕ�
        0,                       // ������б�Ƕ�
        FW_NORMAL,               // �����ϸ��FW_NORMAL Ϊ������
        FALSE,                   // �Ƿ�б��
        FALSE,                   // �Ƿ��»���
        FALSE,                   // �Ƿ�ɾ����
        DEFAULT_CHARSET,         // �ַ���
        OUT_OUTLINE_PRECIS,      // �������
        CLIP_DEFAULT_PRECIS,     // �ü�����
        CLEARTYPE_QUALITY,       // ��������
        VARIABLE_PITCH,          // ������
        fontName.c_str()         // ��������
    );

    // ѡ������
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    // �����ı���ɫ
    SetTextColor(hdc, color);

    // ���ñ���ģʽΪ͸��
    SetBkMode(hdc, TRANSPARENT);

    // �����ı�
    TextOutA(hdc, x, y, text.c_str(), text.length());

    // �ָ�������
    SelectObject(hdc, hOldFont);

    // �ͷ�����
    DeleteObject(hFont);
}


// ��ʼ��ϵͳͼ��
void loadSystemIcons() {
    // ���ͼ���б�
    icons.clear();

    // ���ϵͳͼ��
    icons.push_back({50, 50, 48, 48, "���ļ���", "explorer.exe", getExeIcon("explorer.exe")});
    icons.push_back({50, 150, 48, 48, " �ն�", "linuxcmd.exe", getExeIcon("cmd.exe")});
    icons.push_back({50, 250, 48, 48, "�����", "microweb.exe", getExeIcon("microweb.exe")});
    icons.push_back({50, 350, 48, 48, "�����", "VMwork.exe", getExeIcon("VMwork.exe")});
    icons.push_back({50, 450, 48, 48, "�ʼǱ�", "notes.exe", getExeIcon("notepad.exe")});
    icons.push_back({50, 550, 48, 48, "�����", "calc.exe", getExeIcon("calc.exe")});
    icons.push_back({50, 650, 48, 48, " ��Ϸ", "Gamesbox.exe", getExeIcon("Gamesbox.exe")});
    icons.push_back({50, 750, 48, 48, "��͸����", "hacker.exe", getExeIcon("hacker.exe")});
    icons.push_back({50, 850, 48, 48, "���ų���", "Penetration_Testing.exe", getExeIcon("hacker.exe")});
    icons.push_back({150, 50, 48, 48, "ľ�����", "Penetration_Testing2.exe", getExeIcon("hacker.exe")});
    icons.push_back({150, 150, 48, 48, "��������", "http.exe", getExeIcon("hacker.exe")});

}

// ����ͼ��
void drawIcons() {
    settextstyle(20, 0, "����"); // ��������
    settextcolor(WHITE);         // ����������ɫ
    setbkmode(TRANSPARENT);      // �������ֱ���͸��

    for (const auto& icon : icons) {
        // �����ͼ����������ͼ��
        if (icon.hIcon) {
            // ֱ�ӻ���ͼ�֧꣨��͸��������
            DrawIconEx(GetImageHDC(), icon.x, icon.y, icon.hIcon, icon.width, icon.height, 0, NULL, DI_NORMAL | DI_MASK);
        }

        // ����ͼ������
        //outtextxy(icon.x - 5, icon.y + icon.height + 5, icon.name.c_str());
        HDC hdc = GetImageHDC();
        DrawVectorText(hdc, icon.x, icon.y + icon.height + 5, icon.name.c_str(), "΢���ź�", 20, RGB(255, 255, 255));
    }
}

// ���ͼ����
void checkIconClick(int x, int y) {
    for (const auto& icon : icons) {
        // �жϵ���Ƿ���ͼ��������
        if (x >= icon.x && x <= icon.x + icon.width &&
            y >= icon.y && y <= icon.y + icon.height) {
            // �򿪶�Ӧ���ļ������
            ShellExecute(NULL, "open", icon.path.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
    }
}

// ��ʼ������
void initWindow() {
    // ��ȡ��Ļ�ߴ�
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // ��������
    initgraph(screenWidth, screenHeight);
    HWND hwnd = GetHWnd(); // ��ȡ���ھ��

    // ���ô�����ʽΪ�ޱ߿�
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION & ~WS_THICKFRAME);

    // ��ȡ�������߶�
    RECT taskbarRect;
    HWND taskbarHwnd = FindWindow("Shell_TrayWnd", NULL);
    if (taskbarHwnd) {
        GetWindowRect(taskbarHwnd, &taskbarRect);
        int taskbarHeight = taskbarRect.bottom - taskbarRect.top;

        // �������ڴ�С��λ�ã����ڵ���������
        SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight - taskbarHeight, SWP_SHOWWINDOW);
    } else {
        // ����Ҳ�����������Ĭ�ϼ�ȥ 50 ����
        SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight - 50, SWP_SHOWWINDOW);
    }
}

int main() {
    // ��ʼ������
    initWindow();

    // ���ر���ͼƬ
    loadBackground();

    // ����ϵͳͼ��
    loadSystemIcons();

    // ����˫����
    BeginBatchDraw();

    // ��ѭ��
    while (true) {
        // ���Ʊ���
        if (backgroundImg.getwidth() > 0) {
            putimage(0, 0, &backgroundImg);
        }

        // ����ͼ��
        drawIcons();

        // ��������
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                checkIconClick(msg.x, msg.y);
            }
        }

        // ˢ�»���
        FlushBatchDraw();
        Sleep(10); // ����֡��
    }

    // �ر�ͼ�δ���
    EndBatchDraw();
    closegraph();

    // �ͷ�ͼ����Դ
    for (const auto& icon : icons) {
        if (icon.hIcon) {
            DestroyIcon(icon.hIcon);
        }
    }

    return 0;
}

