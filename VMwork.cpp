#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <string>
#include <map>
#include <shlwapi.h>

using namespace std;

#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

void VM(const string& file);

void ShowErrorDialog(const string& message) {
    MessageBox(GetHWnd(), message.c_str(), "VMwork ����", MB_ICONERROR | MB_OK);
}


string GetCurrentDirectoryPath() {
    char buffer[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}


// ��������ýṹ��
struct VMConfig {
    string name;
    string filePath;  // ͳһ�ļ�·���ֶ�
    string fileType;  // "ASM" �� "IMG"
};

// ȫ�����ô洢
map<string, VMConfig> vmConfigs;
const char* CONFIG_FILE = "vm.dll";

// ͼ�ν���ߴ����
const int WIDTH = 800;
const int HEIGHT = 600;
const int BTN_WIDTH = 200;
const int BTN_HEIGHT = 40;

// ��ǰ����״̬
enum class AppState {
    MAIN_MENU,
    CREATE_VM,
    OPEN_VM,
    SETTINGS
};
AppState currentState = AppState::MAIN_MENU;

char vmNameInput[64] = {0};
char asmPathInput[256] = {0};

void InitGUI() {
    initgraph(WIDTH, HEIGHT);
    HWND hWnd = GetHWnd();
    SetWindowText(hWnd, "VMwork �����");
    ShowWindow(hWnd, SW_SHOWNORMAL);
    setbkcolor(WHITE);
    cleardevice();
    settextcolor(BLACK);
    settextstyle(30, 0, "����");
}

void SaveConfig() {
    ofstream fout(CONFIG_FILE);
    for (auto& entry : vmConfigs) {
        auto& name = entry.first;
        auto& config = entry.second;
        fout << name << endl;
        fout << config.filePath << endl;
        fout << config.fileType << endl;
    }
    fout.close();
}

void LoadConfig() {
    vmConfigs.clear();
    ifstream fin(CONFIG_FILE);
    string name, path, type;
    while (getline(fin, name) && 
           getline(fin, path) && 
           getline(fin, type)) {
        vmConfigs[name] = {name, path, type};
    }
    fin.close();
}

void DrawMainMenu() {
    cleardevice();
    setbkcolor(WHITE);
    settextcolor(BLUE);
    settextstyle(30, 0, "����");
    outtextxy(100, 50, "VMwork �����");

    setfillcolor(LIGHTGRAY);
    fillroundrect(300, 150, 300 + BTN_WIDTH, 150 + BTN_HEIGHT, 5, 5);
    outtextxy(330, 155, "�½������");

    fillroundrect(300, 250, 300 + BTN_WIDTH, 250 + BTN_HEIGHT, 5, 5);
    outtextxy(330, 255, "�������");

    fillroundrect(300, 350, 300 + BTN_WIDTH, 350 + BTN_HEIGHT, 5, 5);
    outtextxy(350, 355, "����");
}

string SelectFile() {
    OPENFILENAMEA ofn;
    char szFile[260] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "IMG Files (*.img)\0*.img\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        return szFile;
    }
    return "";
}


bool InputBox(const char* title, char* buffer, int bufferSize) {
    char prompt[10] = "";
    return InputBox(buffer, bufferSize, prompt, title); 
}

void CreateVMProcess() {
    int fileType = MessageBox(GetHWnd(), "�Ƿ����ö�ȡnasm�﷨?\n[��]����img���̶�ȡ", "VMwork", MB_YESNO | MB_ICONQUESTION);
    bool isASM = (fileType == IDYES);

    OPENFILENAMEA ofn;
    char szFile[260] = {0};
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = isASM ? 
        "ASM Files (*.asm)\0*.asm\0All Files (*.*)\0*.*\0" :
        "IMG Files (*.img)\0*.img\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (!GetOpenFileNameA(&ofn)) return;

    if (!InputBox("�������������", vmNameInput, sizeof(vmNameInput))) return;

    vmConfigs[vmNameInput] = {
        vmNameInput, 
        szFile, 
        isASM ? "ASM" : "IMG"
    };
    SaveConfig();
}

void DisassembleImg(const string& imgPath, const string& asmPath) {
    string cmd = "cmd /c \"\"" + GetCurrentDirectoryPath() + "\\ndisasm.exe\" \"" 
               + imgPath + "\" > \"" + asmPath + "\"\"";
    WinExec(cmd.c_str(), SW_HIDE);
}

void ProcessAsm(const string& asmPath, const string& finalAsmPath) {
    string cmd = "cmd /c \"\"" + GetCurrentDirectoryPath() + "\\toasm.exe\" \"" 
               + asmPath + "\" \"" + finalAsmPath + "\"\"";
    WinExec(cmd.c_str(), SW_HIDE);
}

void OpenVMProcess() {
    LoadConfig();
    cleardevice();
    settextcolor(BLACK);
    outtextxy(50, 50, "ѡ�������:");

    int y = 100;
    for (auto& entry : vmConfigs) {
        std::string text = entry.first + " (" + entry.second.filePath + ")";
        outtextxy(100, y, const_cast<char*>(text.c_str()));
        y += 50;
    }

    int choice = 0;
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int clickY = msg.y;
                int index = 0;
                for (auto& entry : vmConfigs) {
                    int itemTop = 100 + index * 40;
                    if (clickY > itemTop && clickY < itemTop + 50) {
                        choice = index + 1;
                        break;
                    }
                    index++;
                }
            }
        }
        if (choice!= 0) break;
    }

    if (choice > 0 && choice <= vmConfigs.size()) {
        auto it = vmConfigs.begin();
        advance(it, choice - 1);
        string selectedPath = it->second.filePath;

        string tempAsmPath = "temp.asm";
        string finalAsmPath = "final.asm";
        if (it->second.fileType == "IMG") {
            DisassembleImg(selectedPath, tempAsmPath);
            ProcessAsm(tempAsmPath, finalAsmPath);
        }
        else {
            finalAsmPath = selectedPath;
        }

        VM(finalAsmPath);
    }
}

void SetVMProcess() {
    LoadConfig();
    cleardevice();
    settextcolor(BLACK);
    outtextxy(30, 50, "�����");
    outtextxy(50, 90, "������  : 1");
    outtextxy(50, 130, "�ڴ�    : 64KB");
    outtextxy(50, 170, "������ʽ: ����(��������)");
    outtextxy(50, 210, "����    : ��");
    outtextxy(50, 250, "BIOS    : VMwork");
    outtextxy(50, 290, "��ʽ    : .IMG/.ASM");
    while (1) {}
}


void MainLoop() {
	AppState prevState = AppState::MAIN_MENU; 
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                // �����水ť����
                if (currentState == AppState::MAIN_MENU) {
                    if (msg.x > 300 && msg.x < 300 + BTN_WIDTH) {
                        if (msg.y > 150 && msg.y < 150 + BTN_HEIGHT) {
                            CreateVMProcess();
                        } else if (msg.y > 250 && msg.y < 250 + BTN_HEIGHT) {
                            OpenVMProcess();
                        } else if (msg.y > 350 && msg.y < 350 + BTN_HEIGHT) {
                            SetVMProcess(); 
                        }
                    }
                }
            }
        }
 
        switch (currentState) {
            case AppState::MAIN_MENU:
                if (prevState!= AppState::MAIN_MENU) {
                    //cleardevice();
                }
                DrawMainMenu();
                break;
            case AppState::CREATE_VM:
                if (prevState!= AppState::CREATE_VM) {
                    //cleardevice();
                }
                DrawMainMenu();
                break;
            case AppState::OPEN_VM:
                if (prevState!= AppState::OPEN_VM) {
                    //cleardevice();
                }
                DrawMainMenu();
                break;
            case AppState::SETTINGS:
                if (prevState!= AppState::SETTINGS) {
                    //cleardevice();
                }
                DrawMainMenu();
                break;
        }
 
        prevState = currentState;
 
        Sleep(30);
    }
}

// �Ĵ�������
unsigned char al = 0, ah = 0, bl = 0, bh = 0, cl = 0, ch = 0, dl = 0, dh = 0, si = 0;
unsigned short ax = 0, bx = 0, cx = 0, dx = 0, sp = 0x8000, bp = 0;
unsigned int org = 0, end_times = 0, end_AA55 = 0;
bool ZF = false, CF = false, SF = false;

unordered_map<string, size_t> labels;
size_t current_line = 0;
size_t new_current_line;
vector<string> program_lines;

vector<unsigned char> memory(0x10000, 0);

mutex fileMutex;

int textX = 0;
int textY = 48;
const int CHAR_WIDTH = 8;
const int LINE_HEIGHT = 16;
bool graphicsInitialized = false;

enum class InstructionError {
    INVALID_OPCODE,
    INVALID_OPERAND,
    LABEL_NOT_FOUND,
    UNKNOWN_INTERRUPT,
    OTHER_ERROR
};

void printError(const InstructionError& error, const string& details = "") {
    //cerr << "ERROR: ";
    switch (error) {
    case InstructionError::INVALID_OPCODE: MessageBox(GetHWnd(), "��Ч�Ĳ�����", "����ʱ����", MB_ICONERROR); break;
    case InstructionError::INVALID_OPERAND: MessageBox(GetHWnd(), "��Ч�Ĳ�����", "����ʱ����", MB_ICONERROR); break;
    case InstructionError::LABEL_NOT_FOUND: MessageBox(GetHWnd(), "��ǩδ�ҵ�", "����ʱ����", MB_ICONERROR); break;
    case InstructionError::UNKNOWN_INTERRUPT: MessageBox(GetHWnd(), "δ֪���жϺ�", "����ʱ����", MB_ICONERROR); break;
    case InstructionError::OTHER_ERROR: MessageBox(GetHWnd(), "δ֪����", "����ʱ����", MB_ICONERROR); break;
    }
    if (!details.empty()) cerr << " - " << details;
    cerr << endl;
}

int parseImmediate(const string& immediateStr) {
    string result;
    bool inQuote = false;
    char quoteChar = '\0';

    for (size_t i = 0; i < immediateStr.size(); ++i) {
        char c = immediateStr[i];
        if (c == '\'' || c == '"') {
            if (!inQuote) {
                inQuote = true;
                quoteChar = c;
            } else if (c == quoteChar) {
                inQuote = false;
            }
        } else if (!inQuote && isspace(c)) {
            continue;
        }
        result += c;
    }

    if (result.empty()) return 0;
    if (result.length() == 3 && result[0] == '\'' && result[2] == '\'') {
        return static_cast<int>(result[1]);
    }
    else if (result.find("0x") == 0) {
        return stoi(result.substr(2), nullptr, 16);
    }
    else if (result.back() == 'h') {
        return stoi(result.substr(0, result.length() - 1), nullptr, 16);
    }
    else {
        return stoi(result);
    }
}

int parseImmediate1(const string& immediateStr) {
    string processed = immediateStr;

    // �Ƴ���ת���η���near/short/far��
    vector<string> modifiers = {"near ", "short ", "far "};
    for (const auto& mod : modifiers) {
        size_t pos = processed.find(mod);
        if (pos != string::npos) {
            processed.erase(pos, mod.length());
            break;
        }
    }

    // �����:ƫ�Ƹ�ʽ����ȡƫ�Ʋ��֣�
    size_t colon = processed.find(':');
    if (colon != string::npos) {
        processed = processed.substr(colon + 1);
    }

    // ������ָ�����������ret 4 -> ����4��
    size_t space = processed.find(' ');
    if (space != string::npos) {
        processed = processed.substr(0, space);
    }

    // ���������ַ���'A' -> 65��
    if (processed.length() == 3 && processed[0] == '\'' && processed[2] == '\'') {
        return static_cast<int>(processed[1]);
    }

    // ����ʮ�����Ƹ�ʽ
    if (processed.find("0x") == 0) {
        return stoi(processed.substr(2), nullptr, 16);
    }

    // ����h��β��ʮ������
    if (!processed.empty() && processed.back() == 'h') {
        return stoi(processed.substr(0, processed.length()-1), nullptr, 16);
    }

    // ��������Ƹ�ʽ������֧�֣�
    if (processed.find("0b") == 0) {
        return stoi(processed.substr(2), nullptr, 2);
    }

    // ������ţ�+/-��
    bool negative = false;
    if (!processed.empty()) {
        if (processed[0] == '+') {
            processed = processed.substr(1);
        } else if (processed[0] == '-') {
            negative = true;
            processed = processed.substr(1);
        }
    }

    // ������ֵת��
    try {
        int value = stoi(processed);
        return negative ? -value : value;
    } catch (...) {
        //throw invalid_argument("�޷�������������: " + immediateStr);
        MessageBox(GetHWnd(), ("�޷�������������: " + immediateStr).c_str(), "����ʱ����", MB_ICONERROR);
    }
}

unordered_map<string, unsigned char*> createRegister8BitMap() {
    return {
        {"al", &al}, {"ah", &ah}, {"bl", &bl}, {"bh", &bh},
        {"cl", &cl}, {"ch", &ch}, {"dl", &dl}, {"dh", &dh},
        {"si", &si}
    };
}

unordered_map<string, unsigned short*> createRegister16BitMap() {
    return {
        {"ax", &ax}, {"bx", &bx}, {"cx", &cx}, {"dx", &dx},
        {"sp", &sp}, {"bp", &bp}
    };
}

void UpdateTextPosition() {
    textX += CHAR_WIDTH;
    if (textX > 620) {
        textX = 0;
        textY += LINE_HEIGHT;
    }
    if (textY + LINE_HEIGHT > 480) {
        cleardevice();
        textX = 0;
        textY = 0;
    }
}

void MovInstruction(const string& line) {
    string processedLine = line;
    replace(processedLine.begin(), processedLine.end(), ',', ' ');
    istringstream iss(processedLine);
    string opcode, dest, src;
    iss >> opcode >> dest >> src;

    auto reg8 = createRegister8BitMap();
    auto reg16 = createRegister16BitMap();

    auto parseOperand = [&](const string& op) -> int {
        if (reg8.count(op)) return *reg8[op];
        if (reg16.count(op)) return *reg16[op];
        return parseImmediate(op);
    };

    int value = parseOperand(src);

    if (reg8.count(dest)) {
        *reg8[dest] = static_cast<unsigned char>(value);
    }
    else if (reg16.count(dest)) {
        *reg16[dest] = static_cast<unsigned short>(value);
    }
}

void AddInstruction(const string& line) {
    string processedLine = line;
    replace(processedLine.begin(), processedLine.end(), ',', ' ');
    istringstream iss(processedLine);
    string opcode, dest, src;
    iss >> opcode >> dest >> src;

    auto reg8 = createRegister8BitMap();
    auto reg16 = createRegister16BitMap();

    auto parseOperand = [&](const string& op) -> int {
        if (reg8.count(op)) return *reg8[op];
        if (reg16.count(op)) return *reg16[op];
        return parseImmediate(op);
    };

    int val1 = parseOperand(dest);
    int val2 = parseOperand(src);
    int result = val1 + val2;

    if (reg8.count(dest)) {
        *reg8[dest] = static_cast<unsigned char>(result);
    }
    else if (reg16.count(dest)) {
        *reg16[dest] = static_cast<unsigned short>(result);
    }

    ZF = (result == 0);
    SF = (result < 0);
    CF = (static_cast<unsigned>(result) < static_cast<unsigned>(val1));
}

void SubInstruction(const string& line) {
    string processedLine = line;
    replace(processedLine.begin(), processedLine.end(), ',', ' ');
    istringstream iss(processedLine);
    string opcode, dest, src;
    iss >> opcode >> dest >> src;

    auto reg8 = createRegister8BitMap();
    auto reg16 = createRegister16BitMap();

    auto parseOperand = [&](const string& op) -> int {
        if (reg8.count(op)) return *reg8[op];
        if (reg16.count(op)) return *reg16[op];
        return parseImmediate(op);
    };

    int val1 = parseOperand(dest);
    int val2 = parseOperand(src);
    int result = val1 - val2;

    if (reg8.count(dest)) {
        *reg8[dest] = static_cast<unsigned char>(result);
    }
    else if (reg16.count(dest)) {
        *reg16[dest] = static_cast<unsigned short>(result);
    }

    ZF = (result == 0);
    SF = (result < 0);
    CF = (static_cast<unsigned>(val1) < static_cast<unsigned>(val2));
}

void IncInstruction(const string& line) {
    istringstream iss(line);
    string opcode, operand;
    iss >> opcode >> operand;

    auto reg8 = createRegister8BitMap();
    auto reg16 = createRegister16BitMap();

    if (reg8.count(operand)) {
        *reg8[operand] += 1;
        ZF = (*reg8[operand] == 0);
        SF = (*reg8[operand] < 0);
    }
    else if (reg16.count(operand)) {
        *reg16[operand] += 1;
        ZF = (*reg16[operand] == 0);
        SF = (*reg16[operand] < 0);
    }
}

void CmpInstruction(const string& line) {
    string processedLine = line;
    replace(processedLine.begin(), processedLine.end(), ',', ' ');
    istringstream iss(processedLine);
    string opcode, op1, op2;
    iss >> opcode >> op1 >> op2;

    auto reg8 = createRegister8BitMap();
    auto reg16 = createRegister16BitMap();

    auto parseOperand = [&](const string& op) -> int {
        if (reg8.count(op)) return *reg8[op];
        if (reg16.count(op)) return *reg16[op];
        return parseImmediate(op);
    };

    int val1 = parseOperand(op1);
    int val2 = parseOperand(op2);
    int result = val1 - val2;

    ZF = (result == 0);
    SF = (result < 0);
    CF = (static_cast<unsigned>(val1) < static_cast<unsigned>(val2));
}

void JmpInstruction(const string& line) {
    istringstream iss(line);
    string opcode, modifier, operand;
    iss >> opcode >> modifier;

    // ������ת���η���short/near��
    if (modifier == "short" || modifier == "near" || modifier == "nearptr") {
        iss >> operand;
    } else {
        operand = modifier;
    }

    // ���ȳ��Ա�ǩ��ת
    if (labels.count(operand)) {
        new_current_line = labels[operand];
        return;
    }

    // ���Խ���Ϊ��ֵ��ת
    try {
        int offset = parseImmediate(operand);
        // �����������һ��ָ���ƫ��
        new_current_line = current_line + 1 + offset;
    } catch (...) {
        printError(InstructionError::LABEL_NOT_FOUND, "JMPָ���е�Ŀ��δ�ҵ�: " + operand);
    }
}

void JeInstruction(const string& line) {
    istringstream iss(line);
    string opcode, modifier, operand;
    iss >> opcode >> modifier;

    if (modifier == "short" || modifier == "near" || modifier == "nearptr") {
        iss >> operand;
    } else {
        operand = modifier;
    }

    if (ZF) {
        if (labels.count(operand)) {
            new_current_line = labels[operand];
        } else {
            try {
                int offset = parseImmediate(operand);
                new_current_line = current_line + 1 + offset;
            } catch (...) {
                printError(InstructionError::LABEL_NOT_FOUND, "JEָ���е�Ŀ��δ�ҵ�: " + operand);
            }
        }
    } else {
        new_current_line = current_line + 1;
    }
}

void JneInstruction(const string& line) {
    istringstream iss(line);
    string opcode, modifier, operand;
    iss >> opcode >> modifier;

    if (modifier == "short" || modifier == "near" || modifier == "nearptr") {
        iss >> operand;
    } else {
        operand = modifier;
    }

    if (!ZF) {
        if (labels.count(operand)) {
            new_current_line = labels[operand];
        } else {
            try {
                int offset = parseImmediate(operand);
                new_current_line = current_line + 1 + offset;
            } catch (...) {
                printError(InstructionError::LABEL_NOT_FOUND, "JNEָ���е�Ŀ��δ�ҵ�: " + operand);
            }
        }
    } else {
        new_current_line = current_line + 1;
    }
}

void CallInstruction(const string& line) {
    istringstream iss(line);
    string opcode, modifier, operand;
    iss >> opcode;  // ��ȡcall
    
    // ��ȡʣ�ಿ����Ϊ������
    getline(iss, operand);
    operand = operand.substr(operand.find_first_not_of(" \t"), operand.find_last_not_of(" \t")+1);

    // �������η�����far��
    size_t space = operand.find(' ');
    if (space != string::npos) {
        operand = operand.substr(space+1);
    }

    // ѹ�뷵�ص�ַ
    sp -= 2;
    memory[sp] = (current_line + 1) & 0xFF;
    memory[sp + 1] = ((current_line + 1) >> 8) & 0xFF;

    try {
        int offset = parseImmediate1(operand);
        new_current_line = current_line + 1 + offset;
    } catch (...) {
        if (labels.count(operand)) {
            new_current_line = labels[operand];  // ����ƴд����
        } else {
            // ʹ��ͼ�ν�����ʾ����
            MessageBox(GetHWnd(), ("CALLĿ��δ�ҵ�: " + operand).c_str(), "VM����", MB_ICONERROR);
        }
    }
}

// ����retָ�֧��������������
void RetInstruction(const string& line) {
    istringstream iss(line);
    string opcode, operand;
    iss >> opcode;  // ��ȡret
    
    // ��ȡ���ص�ַ
    unsigned short return_addr = memory[sp] | (memory[sp + 1] << 8);
    sp += 2;

    // �����������ret��ret 4��
    if (iss >> operand) {
        int adjust = parseImmediate1(operand);
        sp += adjust;
    }

    new_current_line = return_addr;
}

void PushInstruction(const std::string& line) {
    std::istringstream iss(line);
    std::string opcode, src;
    iss >> opcode >> src;

    auto reg16 = createRegister16BitMap(); 
    unsigned short value = reg16.count(src)? *reg16[src] : parseImmediate(src);

    sp -= 2;
    memory[sp] = value & 0xFF;
    memory[sp + 1] = (value >> 8) & 0xFF;
}

void PopInstruction(const std::string& line) {
    std::istringstream iss(line);
    std::string opcode, dest;
    iss >> opcode >> dest;

    auto reg16 = createRegister16BitMap(); 
    if (reg16.count(dest)) {
        *reg16[dest] = memory[sp] | (memory[sp + 1] << 8);
        sp += 2;
    }
}

void XorInstruction(const std::string& line) {
    std::string processedLine = line;
    std::replace(processedLine.begin(), processedLine.end(), ',', ' ');
    std::istringstream iss(processedLine);
    std::string opcode, dest, src;
    iss >> opcode >> dest >> src;

    auto reg8 = createRegister8BitMap(); 
    auto reg16 = createRegister16BitMap(); 

    auto parseOperand = [&](const std::string& op) -> int {
        if (reg8.count(op)) return *reg8[op];
        if (reg16.count(op)) return *reg16[op];
        return parseImmediate(op);
    };

    int val1 = parseOperand(dest);
    int val2 = parseOperand(src);
    int result = val1 ^ val2;

    if (reg8.count(dest)) {
        *reg8[dest] = static_cast<unsigned char>(result);
    }
    else if (reg16.count(dest)) {
        *reg16[dest] = static_cast<unsigned short>(result);
    }

    ZF = (result == 0);
    SF = (result < 0);
    CF = false;
}

void PreprocessLabels() {
    for (size_t i = 0; i < program_lines.size(); ++i) {
        std::string line = program_lines[i];
        std::istringstream iss(line);
        std::string address;
        if (iss >> address) {
            // ȥ����ַ�е�ð��
            address.erase(std::remove(address.begin(), address.end(), ':'), address.end());
            labels[address] = i;
        }

        size_t colonPos = line.find(':');
        if (colonPos!= std::string::npos) {
            std::string label = line.substr(0, colonPos);
            labels[label] = i;
            program_lines[i] = line.substr(colonPos + 1);
            //std::cout << "Label found: " << label << " at line " << i << std::endl;
        }
    }
}

void IntInstruction(const std::string& line) {
    std::string processedLine = line;
    std::replace(processedLine.begin(), processedLine.end(), ',', ' ');
    std::istringstream iss(processedLine);
    std::string opcode, interrupt;
    iss >> opcode >> interrupt;
    BYTE keyState[256];

    if (interrupt == "0x10" || interrupt == "10h") {

        if (ah == 0x0E) {
            if (!graphicsInitialized) {
                initgraph(640, 480);
                HWND hwnd = GetHWnd();
				SetWindowPos(hwnd, HWND_TOP, 100, 100, 0, 0, SWP_NOSIZE);
                setbkcolor(BLACK);
                cleardevice();
                settextcolor(CYAN);
                settextstyle(16, 0, _T("Courier New Bold"));
                graphicsInitialized = true;
                outtextxy(textX, 0, "  VMwork BIOS (PCI)");
                outtextxy(textX, 16, "  This VGA/VBE BIOS is released under the GNU LGPL");
                settextcolor(RGB(192, 192, 192));
            }

            // ���������ַ�
            if (al == 0x0D) {
                outtextxy(textX, textY, " ");
                textY += LINE_HEIGHT;
            }
            else if (al == 0x0A) {
                outtextxy(textX, textY, " ");
                textX = 0;
            }
            else {
                char str[2] = { static_cast<char>(al) };

                outtextxy(textX, textY, " ");
                outtextxy(textX, textY, str);
                UpdateTextPosition();
                outtextxy(textX, textY, "|");
            }
        }
        
        if (ah == 0x02 && bh == 0) {
            textX = 0;
            textY = 0;
        }
        if (ax == 0x0600 && bx == 0x0700 && cx == 0 && dx == 0x184f) {
        	
            setfillcolor(BLACK);
			bar(0, 0, 640, 480);
        	
        }
    }
    else if (interrupt == "0x16" || interrupt == "16h") {
    if (ah == 0) {
    	bool consoleAllocated = false;
        if (!consoleAllocated) {  // ȷ��ֻ����һ�ο���̨
            AllocConsole();
            freopen("CONIN$", "r", stdin);
            freopen("CONOUT$", "w", stdout);
			system("title VMwork���ƺ͵����ն�(�ڴ���������¼�):");
            consoleAllocated = true;
        }
        INPUT_RECORD inputRec;
        DWORD eventsRead;
        while (true) {
            if (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRec, 1, &eventsRead)) {
                if (inputRec.EventType == KEY_EVENT && 
                    inputRec.Event.KeyEvent.bKeyDown) {
                    
                    // ʹ��ϵͳAPIת���ַ�
                    BYTE keyState[256];
                    GetKeyboardState(keyState);
                    WORD charCode = 0;
                    ToAscii(
                        inputRec.Event.KeyEvent.wVirtualKeyCode,
                        inputRec.Event.KeyEvent.wVirtualScanCode,
                        keyState,
                        &charCode,
                        0
                    );

                    al = LOBYTE(charCode);  // ���ֽ���ASCII��
                    if (LOBYTE(charCode) == '\n') {
                    	al = 0x0D;
					}
                    break;
                }
            }
            Sleep(10);
        }
    }
}
    else {
        printError(InstructionError::UNKNOWN_INTERRUPT, "����:δ֪���жϺ�: " + interrupt);
    }
}


void OrgInstruction(const std::string& line) {
    std::string processedLine = line;
    std::replace(processedLine.begin(), processedLine.end(), ',', ' ');
    std::istringstream iss(processedLine);
    std::string opcode, interrupt;
    iss >> opcode >> interrupt;

    if (interrupt == "0x7c00" || interrupt == "0x7C00") {
        org = 0x7c00;
    } else {
        printError(InstructionError::INVALID_OPERAND, "ORGָ��Ĳ�������Ч: " + interrupt);
    }
}

void TimesInstruction(const std::string& line) {
    std::string processedLine = line;
    std::replace(processedLine.begin(), processedLine.end(), ',', ' ');
    std::istringstream iss(processedLine);
    std::string opcode, interrupt;
    iss >> opcode >> interrupt;

    if (interrupt == "510-($-$$) db 0" || interrupt == "510-($-$$)") {
        end_times = 1;
    } else {
        printError(InstructionError::INVALID_OPERAND, "TIMESָ��Ĳ�������Ч: " + interrupt);
    }
}

void DwInstruction(const std::string& line) {
    std::string processedLine = line;
    std::replace(processedLine.begin(), processedLine.end(), ',', ' ');
    std::istringstream iss(processedLine);
    std::string opcode, interrupt;
    iss >> opcode >> interrupt;

    if (interrupt == "0xAA55" || interrupt == "0xaa55") {
        end_AA55 = 1;
    } else {
        printError(InstructionError::INVALID_OPERAND, "DWָ��Ĳ�������Ч: " + interrupt);
    }
}

void VM(const std::string& asmPath) {
	HWND hWnd = initgraph(640, 480, SHOWCONSOLE);
    SetWindowText(hWnd, "VMwork �����������");
    setbkcolor(BLACK);
    cleardevice();
    
    // ��ʾ���ض���
    settextcolor(WHITE);
    settextstyle(24, 0, "����");
    outtextxy(50, 200, "�������������...");
    
    for (int i = 0; i < 10; ++i) {
        setfillcolor(HSVtoRGB(i*36, 1, 1));
        solidcircle(100 + i*50, 300, 15);
        Sleep(100);
    }
    cleardevice();

    std::ifstream file(asmPath);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << asmPath << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        size_t commentPos = line.find(';');
        if (commentPos!= std::string::npos) {
            line = line.substr(0, commentPos);
        }
        // ȥ������β�Ŀհ��ַ�
        while (!line.empty() && std::isspace(line.front())) {
            line.erase(line.begin());
        }
        while (!line.empty() && std::isspace(line.back())) {
            line.erase(line.length() - 1);
        }
        if (!line.empty()) {
            program_lines.push_back(line);
        }
    }
    file.close();

    for (auto& progLine : program_lines) {
        for (size_t i = 0; i < progLine.size(); ++i) {
            if (i < progLine.size() - 2 && progLine[i] == '\'' && progLine[i + 1] ==' ' && progLine[i + 2] == '\'') {
                progLine[i] = static_cast<char>(0x20);
                progLine.erase(i + 1, 2);  // �Ƴ�����Ŀո�͵�����
            }
            if (i < progLine.size() - 2 && progLine[i] == '\'' && progLine[i + 1] ==':' && progLine[i + 2] == '\'') {
                progLine[i] = '3';
                progLine[i + 1] = 'A';
                progLine[i + 2] = 'h';
            }
            if (i < progLine.size() - 2 && progLine[i] == '\'' && progLine[i + 1] ==',' && progLine[i + 2] == '\'') {
                progLine[i] = '2';
                progLine[i + 1] = 'C';
                progLine[i + 2] = 'h';
            }
            if (i < progLine.size() - 2 && progLine[i] == '\'' && progLine[i + 1] =='_' && progLine[i + 2] == '\'') {
                progLine[i] = '5';
                progLine[i + 1] = 'F';
                progLine[i + 2] = 'h';
            }
        }
    }

    PreprocessLabels();

    // ����ָ��ָ����µ�ָ��ָ��
    new_current_line = current_line;
    while (current_line < program_lines.size()) {
        std::istringstream iss(program_lines[current_line]);
        std::string opcode;
        iss >> opcode;
        if (opcode == "mov") MovInstruction(program_lines[current_line]);
        else if (opcode == "int") IntInstruction(program_lines[current_line]);
        else if (opcode == "org") OrgInstruction(program_lines[current_line]);
        else if (opcode == "times") TimesInstruction(program_lines[current_line]);
        else if (opcode == "dw") DwInstruction(program_lines[current_line]);
        else if (opcode == "cmp") CmpInstruction(program_lines[current_line]);
        else if (opcode == "jmp") {
            std::string label;
            iss >> label;
            // ���������ת��ַ��ʾ������������������ת������ڵ�ǰ�кţ�����ʵ�����������
            if (label.find("0x") == 0) {
                try {
                    size_t targetAddress = std::stoi(label.substr(2), nullptr, 16);
                    // ����ҵ���ַ��ǩ�����µ�ǰ�к�
                    if (labels.count(label)) {
                        new_current_line = labels[label];
                    } else {
                        // ������Ե�ַ
                        size_t relativeAddress = targetAddress - (current_line - labels.begin()->second);
                        new_current_line = current_line + relativeAddress;
                    }
                } catch (const std::invalid_argument& e) {
                    printError(InstructionError::LABEL_NOT_FOUND, "JMPָ���еķǷ���ַ��ǩ: " + label);
                } catch (const std::out_of_range& e) {
                    printError(InstructionError::LABEL_NOT_FOUND, "JMPָ���еĵ�ַ��ǩ������Χ: " + label);
                }
            } else {
                JmpInstruction(program_lines[current_line]);
            }
        }
        else if (opcode == "je" || opcode == "jz") JeInstruction(program_lines[current_line]);
        else if (opcode == "jne" || opcode == "jnz") JneInstruction(program_lines[current_line]);
        else if (opcode == "push") PushInstruction(program_lines[current_line]);
        else if (opcode == "pop") PopInstruction(program_lines[current_line]);
        else if (opcode == "xor") XorInstruction(program_lines[current_line]);
        else if (opcode == "call") CallInstruction(program_lines[current_line]);
        else if (opcode == "add") AddInstruction(program_lines[current_line]);
        else if (opcode == "sub") SubInstruction(program_lines[current_line]);
        else if (opcode == "inc") IncInstruction(program_lines[current_line]);
        else if (opcode == "hlt") break;

        if (opcode == "jmp" || opcode == "je" || opcode == "jne") {
            current_line = new_current_line;
        }
        else {
            current_line++;
        }

        new_current_line = current_line + 1; 
    }
    if (graphicsInitialized) {
        _getch();
        //closegraph();
    }
    settextcolor(LIGHTGRAY);
    outtextxy(100, 200, "������Ѱ�ȫֹͣ");
    outtextxy(100, 240, "�����������ع�����");
    FlushMouseMsgBuffer();
    while (!MouseHit()) Sleep(100);
    closegraph();
}


int main() {
	if (GetSystemMetrics(SM_CLEANBOOT) != 0) {
        MessageBox(NULL, "ϵͳ���ڰ�ȫģʽ���޷����������", "��������", MB_ICONSTOP);
        return 1;
    }

    // ���õ�ǰĿ¼
    if (!SetCurrentDirectoryA(GetCurrentDirectoryPath().c_str())) {
        MessageBox(NULL, "�޷����ù���Ŀ¼", "·������", MB_ICONERROR);
        return 1;
    }
    // ���õ�ǰ����Ŀ¼
    SetCurrentDirectoryA(GetCurrentDirectoryPath().c_str());

    // ��ʼ��ͼ�ν��棨ֱ�ӳ�ʼ����
    initgraph(WIDTH, HEIGHT);
    HWND hWnd = GetHWnd();
    SetWindowText(hWnd, "VMwork �����������");
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // ����Ҫ���
    if (!PathFileExistsA("ndisasm.exe") || !PathFileExistsA("toasm.exe")) {
        MessageBox(hWnd, "ȱ�ٱ�Ҫ�����ndisasm.exe �� toasm.exe", "��������", MB_ICONERROR);
        return 1;
    }

    // ��������
    try {
        LoadConfig();
    } catch (...) {
        ShowErrorDialog("�����ļ�����ʧ��");
    }

    // ��ѭ��
    MainLoop();
    
    // ��������
    SaveConfig();
    closegraph();
    return 0;
}


