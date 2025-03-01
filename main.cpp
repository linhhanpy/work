#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h> // 用于 SHGetFileInfo
#include <string>
#include <vector>

// 图标结构体
struct Icon {
    int x, y;              // 图标位置
    int width, height;     // 图标大小
    std::string name;      // 图标名称
    std::string path;      // 图标路径
    HICON hIcon;           // 图标句柄
};

// 全局变量
std::vector<Icon> icons;   // 图标列表
IMAGE backgroundImg;       // 背景图片

// 加载背景图片
void loadBackground() {
    // 直接指定一张背景图片路径
    loadimage(&backgroundImg, "123.jpg");
}

// 获取 .exe 文件的图标
HICON getExeIcon(const std::string& path) {
    SHFILEINFO shfi;
    if (SHGetFileInfo(path.c_str(), 0, &shfi, sizeof(shfi), SHGFI_ICON | SHGFI_LARGEICON)) {
        return shfi.hIcon;
    }
    return nullptr;
}

void DrawVectorText(HDC hdc, int x, int y, const std::string& text, const std::string& fontName, int fontSize, COLORREF color) {
    // 创建字体
    HFONT hFont = CreateFontA(
        fontSize,                // 字体高度
        0,                       // 字体宽度（0 表示自适应）
        0,                       // 文本倾斜角度
        0,                       // 字体倾斜角度
        FW_NORMAL,               // 字体粗细（FW_NORMAL 为正常）
        FALSE,                   // 是否斜体
        FALSE,                   // 是否下划线
        FALSE,                   // 是否删除线
        DEFAULT_CHARSET,         // 字符集
        OUT_OUTLINE_PRECIS,      // 输出精度
        CLIP_DEFAULT_PRECIS,     // 裁剪精度
        CLEARTYPE_QUALITY,       // 字体质量
        VARIABLE_PITCH,          // 字体间距
        fontName.c_str()         // 字体名称
    );

    // 选择字体
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    // 设置文本颜色
    SetTextColor(hdc, color);

    // 设置背景模式为透明
    SetBkMode(hdc, TRANSPARENT);

    // 绘制文本
    TextOutA(hdc, x, y, text.c_str(), text.length());

    // 恢复旧字体
    SelectObject(hdc, hOldFont);

    // 释放字体
    DeleteObject(hFont);
}


// 初始化系统图标
void loadSystemIcons() {
    // 清空图标列表
    icons.clear();

    // 添加系统图标
    icons.push_back({50, 50, 48, 48, "主文件夹", "explorer.exe", getExeIcon("explorer.exe")});
    icons.push_back({50, 150, 48, 48, " 终端", "linuxcmd.exe", getExeIcon("cmd.exe")});
    icons.push_back({50, 250, 48, 48, "浏览器", "microweb.exe", getExeIcon("microweb.exe")});
    icons.push_back({50, 350, 48, 48, "虚拟机", "VMwork.exe", getExeIcon("VMwork.exe")});
    icons.push_back({50, 450, 48, 48, "笔记本", "notes.exe", getExeIcon("notepad.exe")});
    icons.push_back({50, 550, 48, 48, "计算机", "calc.exe", getExeIcon("calc.exe")});
    icons.push_back({50, 650, 48, 48, " 游戏", "Gamesbox.exe", getExeIcon("Gamesbox.exe")});
    icons.push_back({50, 750, 48, 48, "渗透测试", "hacker.exe", getExeIcon("hacker.exe")});
    icons.push_back({50, 850, 48, 48, "后门程序", "Penetration_Testing.exe", getExeIcon("hacker.exe")});
    icons.push_back({150, 50, 48, 48, "木马控制", "Penetration_Testing2.exe", getExeIcon("hacker.exe")});
    icons.push_back({150, 150, 48, 48, "网络爬虫", "http.exe", getExeIcon("hacker.exe")});

}

// 绘制图标
void drawIcons() {
    settextstyle(20, 0, "宋体"); // 设置字体
    settextcolor(WHITE);         // 设置文字颜色
    setbkmode(TRANSPARENT);      // 设置文字背景透明

    for (const auto& icon : icons) {
        // 如果有图标句柄，绘制图标
        if (icon.hIcon) {
            // 直接绘制图标（支持透明背景）
            DrawIconEx(GetImageHDC(), icon.x, icon.y, icon.hIcon, icon.width, icon.height, 0, NULL, DI_NORMAL | DI_MASK);
        }

        // 绘制图标名称
        //outtextxy(icon.x - 5, icon.y + icon.height + 5, icon.name.c_str());
        HDC hdc = GetImageHDC();
        DrawVectorText(hdc, icon.x, icon.y + icon.height + 5, icon.name.c_str(), "微软雅黑", 20, RGB(255, 255, 255));
    }
}

// 检测图标点击
void checkIconClick(int x, int y) {
    for (const auto& icon : icons) {
        // 判断点击是否在图标区域内
        if (x >= icon.x && x <= icon.x + icon.width &&
            y >= icon.y && y <= icon.y + icon.height) {
            // 打开对应的文件或程序
            ShellExecute(NULL, "open", icon.path.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
    }
}

// 初始化窗口
void initWindow() {
    // 获取屏幕尺寸
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 创建窗口
    initgraph(screenWidth, screenHeight);
    HWND hwnd = GetHWnd(); // 获取窗口句柄

    // 设置窗口样式为无边框
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION & ~WS_THICKFRAME);

    // 获取任务栏高度
    RECT taskbarRect;
    HWND taskbarHwnd = FindWindow("Shell_TrayWnd", NULL);
    if (taskbarHwnd) {
        GetWindowRect(taskbarHwnd, &taskbarRect);
        int taskbarHeight = taskbarRect.bottom - taskbarRect.top;

        // 调整窗口大小和位置（不遮挡任务栏）
        SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight - taskbarHeight, SWP_SHOWWINDOW);
    } else {
        // 如果找不到任务栏，默认减去 50 像素
        SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight - 50, SWP_SHOWWINDOW);
    }
}

int main() {
    // 初始化窗口
    initWindow();

    // 加载背景图片
    loadBackground();

    // 加载系统图标
    loadSystemIcons();

    // 启用双缓冲
    BeginBatchDraw();

    // 主循环
    while (true) {
        // 绘制背景
        if (backgroundImg.getwidth() > 0) {
            putimage(0, 0, &backgroundImg);
        }

        // 绘制图标
        drawIcons();

        // 检测鼠标点击
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                checkIconClick(msg.x, msg.y);
            }
        }

        // 刷新画面
        FlushBatchDraw();
        Sleep(10); // 控制帧率
    }

    // 关闭图形窗口
    EndBatchDraw();
    closegraph();

    // 释放图标资源
    for (const auto& icon : icons) {
        if (icon.hIcon) {
            DestroyIcon(icon.hIcon);
        }
    }

    return 0;
}

