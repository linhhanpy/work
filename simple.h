#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

void convertToAsm(const std::string& inputFilePath, const std::string& outputFilePath, std::unordered_set<std::string>& processedFiles);

// ��������������Ψһ�ı�ǩ
std::string generateLabel(const std::string& prefix) {
    static size_t labelCounter = 0;
    return prefix + "_" + std::to_string(labelCounter++);
}

// ���������������������ʽ
void processCondition(const std::string& condition, std::ostream& output, const std::string& trueLabel, const std::string& endLabel) {
    size_t comparisonOpPos = 0;
    if ((comparisonOpPos = condition.find("==")) != std::string::npos) {
        std::string leftOperand = condition.substr(0, comparisonOpPos);
        std::string rightOperand = condition.substr(comparisonOpPos + 2);
        output << "    mov rax, " << leftOperand << "\n";
        output << "    cmp rax, " << rightOperand << "\n";
        output << "    je " << trueLabel << "\n";
    } else if ((comparisonOpPos = condition.find("!=")) != std::string::npos) {
        std::string leftOperand = condition.substr(0, comparisonOpPos);
        std::string rightOperand = condition.substr(comparisonOpPos + 2);
        output << "    mov rax, " << leftOperand << "\n";
        output << "    cmp rax, " << rightOperand << "\n";
        output << "    jne " << trueLabel << "\n";
    } else if ((comparisonOpPos = condition.find("<=")) != std::string::npos) {
        std::string leftOperand = condition.substr(0, comparisonOpPos);
        std::string rightOperand = condition.substr(comparisonOpPos + 2);
        output << "    mov rax, " << leftOperand << "\n";
        output << "    cmp rax, " << rightOperand << "\n";
        output << "    jle " << trueLabel << "\n";
    } else if ((comparisonOpPos = condition.find(">=")) != std::string::npos) {
        std::string leftOperand = condition.substr(0, comparisonOpPos);
        std::string rightOperand = condition.substr(comparisonOpPos + 2);
        output << "    mov rax, " << leftOperand << "\n";
        output << "    cmp rax, " << rightOperand << "\n";
        output << "    jge " << trueLabel << "\n";
    } else if ((comparisonOpPos = condition.find("<")) != std::string::npos) {
        std::string leftOperand = condition.substr(0, comparisonOpPos);
        std::string rightOperand = condition.substr(comparisonOpPos + 1);
        output << "    mov rax, " << leftOperand << "\n";
        output << "    cmp rax, " << rightOperand << "\n";
        output << "    jl " << trueLabel << "\n";
    } else if ((comparisonOpPos = condition.find(">")) != std::string::npos) {
        std::string leftOperand = condition.substr(0, comparisonOpPos);
        std::string rightOperand = condition.substr(comparisonOpPos + 1);
        output << "    mov rax, " << leftOperand << "\n";
        output << "    cmp rax, " << rightOperand << "\n";
        output << "    jg " << trueLabel << "\n";
    } else {
        std::cerr << "������������ʽ��" << condition << std::endl;
    }
}

void processBlock(std::istream& input, std::ostream& output, const std::string& outputFilePath, std::unordered_set<std::string>& processedFiles) {
    std::string line;
    int braceLevel = 1; // ���ٴ����Ų㼶
    while (std::getline(input, line)) {
        std::string trimmedLine = line;
        trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t"));

        if (trimmedLine.empty()) continue;

        // ��������
        if (trimmedLine.find("}") != std::string::npos) {
            braceLevel--;
            if (braceLevel == 0) return; // �����
        }

        // ����鿪ʼ
        if (trimmedLine.find("{") != std::string::npos) {
            braceLevel++;
        }

        // �ݹ鴦��Ƕ�׽ṹ
        convertToAsm(line, outputFilePath, processedFiles);
    }
}

void runSasm(const std::string& objFileName, const std::string& asmFilePath) {
    std::string command1 = "sasm -f win64 -o " + objFileName + " " + asmFilePath;
    int result1 = system(command1.c_str());
    if (result1!= 0) {
        std::string command2 = ".\\sasm -f win64 -o " + objFileName + " " + asmFilePath;
        int result2 = system(command2.c_str());
        if (result2!= 0) {
            std::cerr << "SASM ����ʧ�ܡ�" << std::endl;
        }
    }
}

void runGcc(const std::string& objFileName, const std::string& exeFileName) {
    std::string command1 = "gcc " + objFileName + " -o " + exeFileName;
    int result1 = system(command1.c_str());
    if (result1!= 0) {
        std::string command2 = ".\\gcc " + objFileName + " -o " + exeFileName;
        int result2 = system(command2.c_str());
        if (result2!= 0) {
            std::cerr << "GCC ����ʧ�ܡ�" << std::endl;
        }
    }
}

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}


void clearFileContent(const std::string& filePath) {
    std::ofstream file(filePath, std::ofstream::out | std::ofstream::trunc);
    if (!file) {
        std::cerr << "�޷����ļ�������ղ�����" << filePath << std::endl;
    }
    file.close();
}

void copyFileContent(const std::string& sourceFilePath, const std::string& destinationFilePath) {
    std::ifstream sourceFile(sourceFilePath);
    if (!sourceFile) {
        std::cerr << "�޷���Դ�ļ���" << sourceFilePath << std::endl;
        return;
    }

    std::ofstream destinationFile(destinationFilePath, std::ios_base::app);
    if (!destinationFile) {
        std::cerr << "�޷���Ŀ���ļ���" << destinationFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(sourceFile, line)) {
        destinationFile << line << std::endl;
    }

    sourceFile.close();
    destinationFile.close();
}

void convertToAsm(const std::string& inputFilePath, const std::string& outputFilePath, std::unordered_set<std::string>& processedFiles) {
    std::ifstream inputFile(inputFilePath);
    if (!inputFile) {
        std::cerr << "�޷��������ļ���" << inputFilePath << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilePath, std::ios_base::app);
    if (!outputFile) {
        std::cerr << "�޷���������ļ���" << outputFilePath << std::endl;
        return;
    }

    std::string line;
    bool inBlockComment = false;
    bool inNasmBlock = false;
    std::string nasmContent;
    std::vector<std::string> ifBlockLines;
    bool inIfBlock = false;
    std::string ifCondition;
    size_t comparisonOpPos;
    std::string labelTrue;
    std::string labelEnd;

    while (std::getline(inputFile, line)) {
        std::string trimmedLine = line;
        while (!trimmedLine.empty() && (trimmedLine[0] == ' ' || trimmedLine[0] == '\t')) {
            trimmedLine.erase(0, 1);
        }
        if (trimmedLine.empty()) continue;
        if (trimmedLine.find("//") == 0) continue;
        if (trimmedLine.find("/*")!= std::string::npos) {
            inBlockComment = true;
        }
        if (inBlockComment) {
            if (trimmedLine.find("*/")!= std::string::npos) {
                inBlockComment = false;
            }
            continue;
        }
        if (line.find("main()")!= std::string::npos) {
            outputFile << "main:\n    push rbp\n    mov rbp, rsp\n";
        } else if (line.find("print(")!= std::string::npos) {
            std::string content = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            outputFile << "    sub rsp, 20h\n";
            outputFile << "    mov rcx, " << content << "\n";
            outputFile << "    call printf\n";
            outputFile << "    add rsp, 20h\n";
        } else if (line.find("return")!= std::string::npos) {
            std::string content = line.substr(line.find("return") + 6, line.find("\n") - line.find("return") - 6);
            outputFile << "    mov eax," << content << "\n";
            outputFile << "    pop rbp\n    ret\n";
        } else if (line.find("str ")!= std::string::npos) {
            size_t spacePos = line.find(" ");
            size_t equalPos = line.find("=");
            if (spacePos == std::string::npos || equalPos == std::string::npos) {
                std::cerr << "������ַ��������ʽ��" << line << std::endl;
                continue;
            }
            std::string content1 = line.substr(spacePos + 1, equalPos - spacePos - 1);
            std::string content2 = line.substr(equalPos + 1);
            outputFile << "jmp " << content1 << "_end\n" << content1 << " db " << content2 << ",0\n" << content1 << "_end:\n";
        } else if (line.find("#NASM")!= std::string::npos) {
            size_t endPos = line.find("}#NASM_END");
            if (endPos == std::string::npos) {
                std::cerr << "δ�ҵ� #NASM_END ��" << line << std::endl;
                continue;
            }
            std::string content = line.substr(line.find("#NASM{") + 6, endPos - line.find("#NASM{") - 6);
            outputFile << content << std::endl;
        } else if (line.find("int ")!= std::string::npos) {
            size_t spacePos = line.find(" ");
            size_t equalPos = line.find("=");
            if (spacePos == std::string::npos || equalPos == std::string::npos) {
                std::cerr << "��������������ʽ��" << line << std::endl;
                continue;
            }
            std::string content1 = line.substr(spacePos + 1, equalPos - spacePos - 1);
            std::string content2 = line.substr(equalPos + 1);
            outputFile << "jmp " << content1 << "_end\n" << content1 << " db " << content2 << "\n" << content1 << "_end:\n";
        } else if (line.find("input(")!= std::string::npos) {
            std::string content = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            outputFile << "    " << content << "1 resb 50\n";
            outputFile << "    sub rsp, 20h\n";
            outputFile << "    lea rdx, [" << content << "1]\n";
            outputFile << "    lea rcx, [aS]\n";
            outputFile << "    call scanf\n";
            outputFile << "    add rsp, 20h\n";
            outputFile << "    " << content << " db " << content << "1,0\n";
        } else if (line.find("system(")!= std::string::npos) {
            std::string content = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            outputFile << "    sub rsp, 20h\n";
            outputFile << "    lea rcx, [" << content << "]\n";
            outputFile << "    call system\n";
            outputFile << "    add rsp, 20h\n";
        } else if (line.find("#include")!= std::string::npos) {
            size_t startQuote = line.find('"');
            size_t endQuote = line.rfind('"');
            if (startQuote!= std::string::npos && endQuote!= std::string::npos && startQuote < endQuote) {
                std::string includeFileName = line.substr(startQuote + 1, endQuote - startQuote - 1);
                if (processedFiles.find(includeFileName) == processedFiles.end()) {
                    processedFiles.insert(includeFileName);
                    copyFileContent(includeFileName, outputFilePath);
                }
            }
        } else if (line.find("MessageBoxA(")!= std::string::npos) {
            size_t start = line.find("(");
            size_t mid = line.find(",");
            size_t end = line.find(")");
            std::string content1 = line.substr(start + 1, mid - start - 1);
            std::string content2 = line.substr(mid + 1, end - mid - 1);
            outputFile << "    sub rsp, 20h\n    mov r9d, 0\n    lea r8, [" << content1 << "]\n";
            outputFile << "    lea rdx, [" << content2 << "]\n" << "    mov rcx, 0\n    mov rax, [__imp_MessageBoxA]\n    call rax\n    add rsp, 20h\n";
        } else if (trimmedLine.find("if(") == 0) {
            size_t condStart = trimmedLine.find('(');
            size_t condEnd = trimmedLine.find(')');
            std::string condition = trimmedLine.substr(condStart + 1, condEnd - condStart - 1);

            std::string trueLabel = generateLabel("IF_TRUE");
            std::string endLabel = generateLabel("IF_END");

            // ����������ת
            processCondition(condition, outputFile, trueLabel, endLabel);
            outputFile << "    jmp " << endLabel << "\n";
            outputFile << trueLabel << ":\n";

            // ���� if ��
            processBlock(inputFile, outputFile, outputFilePath, processedFiles);

            outputFile << endLabel << ":\n";
        }
        // ���� for ѭ��
        else if (trimmedLine.find("for(") == 0) {
            size_t parenStart = trimmedLine.find('(');
            size_t parenEnd = trimmedLine.find(')');
            std::string parts = trimmedLine.substr(parenStart + 1, parenEnd - parenStart - 1);

            std::istringstream partStream(parts);
            std::string init, cond, iter;
            std::getline(partStream, init, ';');
            std::getline(partStream, cond, ';');
            std::getline(partStream, iter, ';');

            std::string loopStart = generateLabel("FOR_LOOP");
            std::string condCheck = generateLabel("FOR_COND");
            std::string endLabel = generateLabel("FOR_END");

            // ��ʼ��
            outputFile << "    ; ��ʼ��: " << init << "\n";
            outputFile << init << "\n";

            // ��ת���������
            outputFile << "    jmp " << condCheck << "\n";
            outputFile << loopStart << ":\n";

            // ����ѭ����
            processBlock(inputFile, outputFile, outputFilePath, processedFiles);

            // ����
            outputFile << "    ; ����: " << iter << "\n";
            outputFile << iter << "\n";

            // �������
            outputFile << condCheck << ":\n";
            processCondition(cond, outputFile, loopStart, endLabel);
            outputFile << endLabel << ":\n";
        }
        // ���� while ѭ��
        else if (trimmedLine.find("while(") == 0) {
            size_t condStart = trimmedLine.find('(');
            size_t condEnd = trimmedLine.find(')');
            std::string condition = trimmedLine.substr(condStart + 1, condEnd - condStart - 1);

            std::string loopStart = generateLabel("WHILE_LOOP");
            std::string condCheck = generateLabel("WHILE_COND");
            std::string endLabel = generateLabel("WHILE_END");

            outputFile << condCheck << ":\n";
            processCondition(condition, outputFile, loopStart, endLabel);
            outputFile << "    jmp " << endLabel << "\n";

            outputFile << loopStart << ":\n";
            processBlock(inputFile, outputFile, outputFilePath, processedFiles);
            outputFile << "    jmp " << condCheck << "\n";
            outputFile << endLabel << ":\n";
        } else if (inIfBlock &&!line.find("}")) {
            ifBlockLines.push_back(line);
        } else if (inIfBlock && line.find("}")) {
            inIfBlock = false;
            outputFile << labelTrue << ":\n";
            for (const std::string& ifLine : ifBlockLines) {
                convertToAsm(ifLine, outputFilePath, processedFiles);
            }
            ifBlockLines.clear();
            outputFile << "    jmp " << labelEnd << "\n";
            outputFile << labelEnd << ":\n";
        
        } else if (line.find("func")!= std::string::npos) {
        	
            size_t start = line.find("(");
            size_t func = line.find("func");
            std::string content1 = line.substr(func + 1, start - func - 1);
            outputFile << content1 << ":\n    push rbp\n    mov rbp, rsp\n";
        } else if (line.find("use")!= std::string::npos) {
            size_t start = line.find("()");
            size_t func = line.find("use");
            std::string content1 = line.substr(func + 1, start - func - 1);
            outputFile << "call" << content1 << "\n";
        }
    }

    inputFile.close();
    outputFile.close();
}

