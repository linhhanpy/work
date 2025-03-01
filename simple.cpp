
#include "simple.h"

int main(int argc, char* argv[]) {
    if (argc!= 4) {
        std::cerr << "用法：程序名 输入文件路径 模式 输出文件路径" << std::endl;
        system("pause");
        return 1;
    }

    std::unordered_set<std::string> processedFiles;

    if (!fileExists(argv[1])) {
        std::cerr << "输入文件不存在。" << std::endl;
        return 1;
    }
    std::string mode(argv[2]);
    if (mode == "-a") {
        clearFileContent(argv[3]);
        convertToAsm(argv[1], argv[3], processedFiles);
    } else if (mode == "-o") {
        std::string asmFileName = "a.asm";
        clearFileContent(asmFileName);
        clearFileContent(argv[3]);
        convertToAsm(argv[1], argv[3], processedFiles);
        runSasm(argv[3], asmFileName);
        std::remove(asmFileName.c_str());
    } else if (mode == "-e") {
        std::string asmFileName = "a.asm";
        std::string objFileName = "a.obj";
        clearFileContent(asmFileName);
        clearFileContent(objFileName);
        clearFileContent(argv[3]);
        convertToAsm(argv[1], asmFileName, processedFiles);
        runSasm(objFileName, asmFileName);
        runGcc(objFileName, argv[3]);
        std::remove(asmFileName.c_str());
        std::remove(objFileName.c_str());
    } else {
        std::cerr << "无效的模式参数。" << std::endl;
        return 1;
    }

    return 0;
}
