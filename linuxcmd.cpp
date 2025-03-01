#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <fstream>
#include <direct.h>
#include <conio.h> // 添加此头文件以使用 _getch

// 设置控制台文本颜色
void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 打印带颜色的文本
void printColoredText(const std::string& text, int color) {
    setConsoleColor(color);
    std::cout << text;
    setConsoleColor(7); // 恢复默认颜色
}

// 模拟 ls 命令
void listDirectory(const std::string& path = ".") {
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile((path + "\\*").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printColoredText("错误: 无法打开目录\n", 12); // 红色
        return;
    }

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printColoredText(findData.cFileName, 9); // 蓝色（目录）
            } else {
                printColoredText(findData.cFileName, 10); // 绿色（文件）
            }
            std::cout << "  ";
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
    std::cout << std::endl;
}

// 模拟 cd 命令
bool changeDirectory(std::string& currentDir, const std::string& newDir) {
    if (SetCurrentDirectory(newDir.c_str())) {
        char buffer[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, buffer);
        currentDir = buffer;
        return true;
    } else {
        printColoredText("错误: 无法切换目录\n", 12); // 红色
        return false;
    }
}

// 模拟 pwd 命令
void printWorkingDirectory(const std::string& currentDir) {
    printColoredText(currentDir + "\n", 14); // 黄色
}

// 模拟 mkdir 命令
void makeDirectory(const std::string& dirName) {
    if (_mkdir(dirName.c_str()) != 0) {
        printColoredText("错误: 无法创建目录\n", 12); // 红色
    }
}

// 模拟 rmdir 命令
void removeDirectory(const std::string& dirName) {
    if (_rmdir(dirName.c_str()) != 0) {
        printColoredText("错误: 无法删除目录\n", 12); // 红色
    }
}

// 模拟 touch 命令
void createFile(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file) {
        printColoredText("错误: 无法创建文件\n", 12); // 红色
    } else {
        file.close();
    }
}

// 模拟 cat 命令
void displayFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        printColoredText("错误: 无法打开文件\n", 12); // 红色
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

// 解析并执行命令
void executeCommand(const std::string& command, std::string& currentDir) {
    std::vector<std::string> args;
    std::string arg;
    for (char ch : command) {
        if (ch == ' ') {
            if (!arg.empty()) {
                args.push_back(arg);
                arg.clear();
            }
        } else {
            arg += ch;
        }
    }
    if (!arg.empty()) {
        args.push_back(arg);
    }

    if (args.empty()) return;

    if (args[0] == "ls") {
        listDirectory(args.size() > 1 ? args[1] : currentDir);
    } else if (args[0] == "cd") {
        if (args.size() > 1) {
            changeDirectory(currentDir, args[1]);
        } else {
            printColoredText("错误: 缺少目录参数\n", 12); // 红色
        }
    } else if (args[0] == "pwd") {
        printWorkingDirectory(currentDir);
    } else if (args[0] == "mkdir") {
        if (args.size() > 1) {
            makeDirectory(args[1]);
        } else {
            printColoredText("错误: 缺少目录参数\n", 12); // 红色
        }
    } else if (args[0] == "rmdir") {
        if (args.size() > 1) {
            removeDirectory(args[1]);
        } else {
            printColoredText("错误: 缺少目录参数\n", 12); // 红色
        }
    } else if (args[0] == "touch") {
        if (args.size() > 1) {
            createFile(args[1]);
        } else {
            printColoredText("错误: 缺少文件名参数\n", 12); // 红色
        }
    } else if (args[0] == "cat") {
        if (args.size() > 1) {
            displayFile(args[1]);
        } else {
            printColoredText("错误: 缺少文件名参数\n", 12); // 红色
        }
    } else if (args[0] == "exit") {
        exit(0);
    } else {
        // 如果不是内置命令，则通过 system 执行
        system(command.c_str());
    }
}

// 动态回显输入内容
std::string echoColoredInput(const std::string& currentDir) {
    std::string input;
    char ch;
    while (true) {
        ch = _getch(); // 获取单个字符输入

        if (ch == '\r') { // 回车键
            std::cout << std::endl;
            break;
        } else if (ch == '\b') { // 退格键
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b"; // 删除上一个字符
            }
        } else {
            input.push_back(ch);
            std::cout << ch;
        }

        // 动态解析输入内容并设置颜色
        std::vector<std::string> args;
        std::string arg;
        for (char c : input) {
            if (c == ' ') {
            	std::cout << " ";
                if (!arg.empty()) {
                    args.push_back(arg);
                    arg.clear();
                }
                args.push_back(" ");
            } else {
                arg += c;
            }
        }
        if (!arg.empty()) {
            args.push_back(arg);
        }

        // 回显输入内容
        std::cout << "\r"; // 回到行首
        
        printColoredText("└─", 1);
        printColoredText("$ ", 12); // 红色

        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == " ") {
                std::cout << " ";
            } else if (i == 0 || args[i][0] == '-') {
                printColoredText(args[i], 11); // 浅蓝色
            } else {
                printColoredText(args[i], 10); // 浅绿色
            }
        }
    }
    return input; // 返回用户输入的内容
}

int main() {
    // 设置控制台窗口标题
    SetConsoleTitle("WorkOS命令行");

    // 获取当前目录
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    std::string currentDir = buffer;

    while (true) {
        // 打印命令提示符
        printColoredText("┌──(", 1);
        printColoredText("root@WorkOS", 4);
        printColoredText(")-[", 1);
        printColoredText("~\\home\\" + currentDir, 15);
        printColoredText("]\n└─", 1);
        printColoredText("$ ", 12); // 红色

        // 获取用户输入并动态回显
        std::string command = echoColoredInput(currentDir);

        // 执行命令
        executeCommand(command, currentDir);
    }

    return 0;
}

