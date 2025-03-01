#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <fstream>
#include <direct.h>
#include <conio.h> // ��Ӵ�ͷ�ļ���ʹ�� _getch

// ���ÿ���̨�ı���ɫ
void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ��ӡ����ɫ���ı�
void printColoredText(const std::string& text, int color) {
    setConsoleColor(color);
    std::cout << text;
    setConsoleColor(7); // �ָ�Ĭ����ɫ
}

// ģ�� ls ����
void listDirectory(const std::string& path = ".") {
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile((path + "\\*").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printColoredText("����: �޷���Ŀ¼\n", 12); // ��ɫ
        return;
    }

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printColoredText(findData.cFileName, 9); // ��ɫ��Ŀ¼��
            } else {
                printColoredText(findData.cFileName, 10); // ��ɫ���ļ���
            }
            std::cout << "  ";
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
    std::cout << std::endl;
}

// ģ�� cd ����
bool changeDirectory(std::string& currentDir, const std::string& newDir) {
    if (SetCurrentDirectory(newDir.c_str())) {
        char buffer[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, buffer);
        currentDir = buffer;
        return true;
    } else {
        printColoredText("����: �޷��л�Ŀ¼\n", 12); // ��ɫ
        return false;
    }
}

// ģ�� pwd ����
void printWorkingDirectory(const std::string& currentDir) {
    printColoredText(currentDir + "\n", 14); // ��ɫ
}

// ģ�� mkdir ����
void makeDirectory(const std::string& dirName) {
    if (_mkdir(dirName.c_str()) != 0) {
        printColoredText("����: �޷�����Ŀ¼\n", 12); // ��ɫ
    }
}

// ģ�� rmdir ����
void removeDirectory(const std::string& dirName) {
    if (_rmdir(dirName.c_str()) != 0) {
        printColoredText("����: �޷�ɾ��Ŀ¼\n", 12); // ��ɫ
    }
}

// ģ�� touch ����
void createFile(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file) {
        printColoredText("����: �޷������ļ�\n", 12); // ��ɫ
    } else {
        file.close();
    }
}

// ģ�� cat ����
void displayFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        printColoredText("����: �޷����ļ�\n", 12); // ��ɫ
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

// ������ִ������
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
            printColoredText("����: ȱ��Ŀ¼����\n", 12); // ��ɫ
        }
    } else if (args[0] == "pwd") {
        printWorkingDirectory(currentDir);
    } else if (args[0] == "mkdir") {
        if (args.size() > 1) {
            makeDirectory(args[1]);
        } else {
            printColoredText("����: ȱ��Ŀ¼����\n", 12); // ��ɫ
        }
    } else if (args[0] == "rmdir") {
        if (args.size() > 1) {
            removeDirectory(args[1]);
        } else {
            printColoredText("����: ȱ��Ŀ¼����\n", 12); // ��ɫ
        }
    } else if (args[0] == "touch") {
        if (args.size() > 1) {
            createFile(args[1]);
        } else {
            printColoredText("����: ȱ���ļ�������\n", 12); // ��ɫ
        }
    } else if (args[0] == "cat") {
        if (args.size() > 1) {
            displayFile(args[1]);
        } else {
            printColoredText("����: ȱ���ļ�������\n", 12); // ��ɫ
        }
    } else if (args[0] == "exit") {
        exit(0);
    } else {
        // ����������������ͨ�� system ִ��
        system(command.c_str());
    }
}

// ��̬������������
std::string echoColoredInput(const std::string& currentDir) {
    std::string input;
    char ch;
    while (true) {
        ch = _getch(); // ��ȡ�����ַ�����

        if (ch == '\r') { // �س���
            std::cout << std::endl;
            break;
        } else if (ch == '\b') { // �˸��
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b"; // ɾ����һ���ַ�
            }
        } else {
            input.push_back(ch);
            std::cout << ch;
        }

        // ��̬�����������ݲ�������ɫ
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

        // ������������
        std::cout << "\r"; // �ص�����
        
        printColoredText("����", 1);
        printColoredText("$ ", 12); // ��ɫ

        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == " ") {
                std::cout << " ";
            } else if (i == 0 || args[i][0] == '-') {
                printColoredText(args[i], 11); // ǳ��ɫ
            } else {
                printColoredText(args[i], 10); // ǳ��ɫ
            }
        }
    }
    return input; // �����û����������
}

int main() {
    // ���ÿ���̨���ڱ���
    SetConsoleTitle("WorkOS������");

    // ��ȡ��ǰĿ¼
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    std::string currentDir = buffer;

    while (true) {
        // ��ӡ������ʾ��
        printColoredText("������(", 1);
        printColoredText("root@WorkOS", 4);
        printColoredText(")-[", 1);
        printColoredText("~\\home\\" + currentDir, 15);
        printColoredText("]\n����", 1);
        printColoredText("$ ", 12); // ��ɫ

        // ��ȡ�û����벢��̬����
        std::string command = echoColoredInput(currentDir);

        // ִ������
        executeCommand(command, currentDir);
    }

    return 0;
}

