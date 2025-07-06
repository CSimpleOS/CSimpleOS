#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>

using namespace std;

// 文本缓冲区
vector<string> lines;
string filename = "";
bool modified = false;
int currentLine = 0;
int currentPos = 0;

// 控制台文本颜色设置
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 清除屏幕
void clearScreen() {
    system("cls");
}

// 设置控制台标题
void setConsoleTitle(const string& title) {
    SetConsoleTitleA(title.c_str());
}

// 显示帮助信息
void showHelp() {
    clearScreen();
    setColor(11); // 青色
    cout << "===== 帮助信息 =====\n\n";
    cout << "编辑命令:\n";
    cout << "  方向键     : 移动光标\n";
    cout << "  Enter      : 插入新行\n";
    cout << "  Backspace  : 删除左侧字符\n";
    cout << "  Delete     : 删除右侧字符\n\n";
    
    cout << "快捷键:\n";
    cout << "  Ctrl+S     : 保存文件\n";
    cout << "  Ctrl+O     : 打开文件\n";
    cout << "  Ctrl+N     : 新建文件\n";
    cout << "  Ctrl+F     : 查找文本\n";
    cout << "  Ctrl+H     : 替换文本\n";
    cout << "  Ctrl+Q     : 退出程序\n";
    cout << "  ESC        : 退出编辑模式\n";
    cout << "  F1         : 显示帮助\n\n";
    
    cout << "主菜单命令:\n";
    cout << "  1-6        : 选择菜单项\n\n";
    
    setColor(14); // 黄色
    cout << "按任意键返回...";
    setColor(7); // 默认颜色
    _getch(); // 等待按键
}

// 显示文件内容（带行号）
void displayContent() {
    clearScreen();
    
    // 显示文件名和状态
    setColor(14);
    cout << "文件: " << (filename.empty() ? "[未命名]" : filename);
    if (modified) cout << " *已修改*";
    cout << "\n";
    
    // 显示分隔线
    setColor(8);
    cout << "--------------------------------------------------\n";
    setColor(7);
    
    // 显示带行号的文件内容
    for (int i = 0; i < lines.size(); i++) {
        // 高亮显示当前行
        if (i == currentLine) {
            setColor(15); // 高亮白色
        } else {
            setColor(7); // 默认颜色
        }
        
        // 显示行号
        cout << setw(3) << right << i + 1 << " | ";
        
        // 显示行内容
        cout << lines[i] << "\n";
    }
}

// 保存文件
bool saveFile() {
    if (filename.empty()) {
        setColor(14);
        cout << "输入文件名: ";
        setColor(7);
        getline(cin, filename);
    }

    ofstream file(filename);
    if (!file.is_open()) {
        setColor(12);
        cout << "无法保存文件!" << endl;
        setColor(7);
        return false;
    }

    for (const auto& line : lines) {
        file << line << "\n";
    }

    modified = false;
    setColor(10);
    cout << "文件已保存!" << endl;
    setColor(7);
    return true;
}

// 打开文件
void openFile() {
    string newFilename;
    setColor(14);
    cout << "输入要打开的文件名: ";
    setColor(7);
    getline(cin, newFilename);

    ifstream file(newFilename);
    if (!file.is_open()) {
        setColor(12);
        cout << "无法打开文件!" << endl;
        setColor(7);
        return;
    }

    lines.clear();
    string line;
    while (getline(file, line)) {
        // 移除Windows回车符
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    filename = newFilename;
    modified = false;
    currentLine = 0;
    currentPos = 0;
    
    setColor(10);
    cout << "文件已加载! 共 " << lines.size() << " 行" << endl;
    setColor(7);
}

// 查找文本
void findText() {
    if (lines.empty()) {
        setColor(12);
        cout << "文件为空!" << endl;
        setColor(7);
        return;
    }
    
    string searchTerm;
    setColor(14);
    cout << "输入要查找的文本: ";
    setColor(7);
    getline(cin, searchTerm);
    
    if (searchTerm.empty()) return;
    
    int startLine = currentLine;
    int startPos = currentPos + 1;
    bool found = false;
    int foundLine = -1;
    size_t foundPos = string::npos;
    
    // 从当前位置开始查找
    for (int i = startLine; i < lines.size(); i++) {
        size_t pos = (i == startLine) ? lines[i].find(searchTerm, startPos) : lines[i].find(searchTerm);
        
        if (pos != string::npos) {
            foundLine = i;
            foundPos = pos;
            found = true;
            break;
        }
    }
    
    // 如果没找到，从文件开头继续查找
    if (!found) {
        for (int i = 0; i <= startLine; i++) {
            size_t pos = lines[i].find(searchTerm, (i == startLine) ? 0 : startPos);
            
            if (pos != string::npos) {
                foundLine = i;
                foundPos = pos;
                found = true;
                break;
            }
        }
    }
    
    if (found) {
        currentLine = foundLine;
        currentPos = static_cast<int>(foundPos);
        setColor(10);
        cout << "已找到匹配文本! 位置: 行 " << foundLine + 1 << ", 列 " << foundPos + 1 << endl;
        setColor(7);
    } else {
        setColor(12);
        cout << "未找到匹配文本!" << endl;
        setColor(7);
    }
}

// 替换文本
void replaceText() {
    if (lines.empty()) {
        setColor(12);
        cout << "文件为空!" << endl;
        setColor(7);
        return;
    }
    
    string searchTerm, replaceTerm;
    setColor(14);
    cout << "输入要查找的文本: ";
    setColor(7);
    getline(cin, searchTerm);
    
    if (searchTerm.empty()) return;
    
    setColor(14);
    cout << "输入替换文本: ";
    setColor(7);
    getline(cin, replaceTerm);
    
    int replaceCount = 0;
    
    for (int i = 0; i < lines.size(); i++) {
        size_t pos = 0;
        while ((pos = lines[i].find(searchTerm, pos)) != string::npos) {
            lines[i].replace(pos, searchTerm.length(), replaceTerm);
            pos += replaceTerm.length();
            replaceCount++;
            modified = true;
        }
    }
    
    if (replaceCount > 0) {
        setColor(10);
        cout << "已替换 " << replaceCount << " 处匹配文本!" << endl;
        setColor(7);
    } else {
        setColor(12);
        cout << "未找到匹配文本!" << endl;
        setColor(7);
    }
}

// 删除行
void deleteLine() {
    if (lines.empty()) return;
    
    if (currentLine < lines.size()) {
        lines.erase(lines.begin() + currentLine);
        modified = true;
        
        // 调整光标位置
        if (currentLine >= lines.size() && !lines.empty()) {
            currentLine = static_cast<int>(lines.size()) - 1;
        }
        if (currentPos > lines[currentLine].size()) {
            currentPos = static_cast<int>(lines[currentLine].size());
        }
    }
}

// 编辑文本
void editText() {
    while (true) {
        displayContent();
        
        // 显示光标位置信息
        setColor(8);
        cout << "\n行: " << currentLine + 1 << "  列: " << currentPos + 1;
        cout << "  按F1查看帮助\n";
        setColor(7);

        // 设置光标位置
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorCoord;
        cursorCoord.X = min(currentPos, static_cast<int>(lines[currentLine].size())) + 7; // 7 = 行号宽度 + 分隔符
        cursorCoord.Y = currentLine + 3; // 偏移标题行
        SetConsoleCursorPosition(hConsole, cursorCoord);

        // 处理键盘输入
        int ch = _getch();
        
        // 功能键处理
        if (ch == 0 || ch == 0xE0) { // 扩展键
            int ext = _getch();
            
            // 方向键
            if (ext == 72 && currentLine > 0) currentLine--; // 上
            else if (ext == 80 && currentLine < lines.size() - 1) currentLine++; // 下
            else if (ext == 75 && currentPos > 0) currentPos--; // 左
            else if (ext == 77 && currentPos < lines[currentLine].size()) currentPos++; // 右
            
            // 处理行尾限制
            currentPos = min(currentPos, static_cast<int>(lines[currentLine].size()));
        }
        else if (ch == 224) { // 功能键 (F1-F12)
            int ext = _getch();
            if (ext == 59) { // F1
                showHelp();
            }
        }
        // Ctrl组合键
        else if (ch == 3) return;          // Ctrl+C
        else if (ch == 19) saveFile();     // Ctrl+S
        else if (ch == 15) openFile();     // Ctrl+O
        else if (ch == 14) {               // Ctrl+N
            lines.clear();
            lines.push_back("");
            filename = "";
            modified = false;
            currentLine = 0;
            currentPos = 0;
        }
        else if (ch == 6) findText();      // Ctrl+F
        else if (ch == 8) replaceText();    // Ctrl+H (H=8)
        else if (ch == 17) exit(0);        // Ctrl+Q
        else if (ch == 27) return;         // ESC
        // 普通字符
        else if (ch == 13) { // 回车
            string remainder = lines[currentLine].substr(currentPos);
            lines[currentLine] = lines[currentLine].substr(0, currentPos);
            lines.insert(lines.begin() + currentLine + 1, remainder);
            currentLine++;
            currentPos = 0;
            modified = true;
        }
        else if (ch == 8) { // 退格
            if (currentPos > 0) {
                lines[currentLine].erase(currentPos - 1, 1);
                currentPos--;
                modified = true;
            }
            else if (currentLine > 0) {
                currentPos = lines[currentLine - 1].size();
                lines[currentLine - 1] += lines[currentLine];
                lines.erase(lines.begin() + currentLine);
                currentLine--;
                modified = true;
            }
        }
        else if (ch == 83) { // Delete键
            if (currentPos < lines[currentLine].size()) {
                lines[currentLine].erase(currentPos, 1);
                modified = true;
            }
            else if (currentLine < lines.size() - 1) {
                lines[currentLine] += lines[currentLine + 1];
                lines.erase(lines.begin() + currentLine + 1);
                modified = true;
            }
        }
        else if (ch >= 32 && ch <= 126) { // 可打印字符
            lines[currentLine].insert(currentPos, 1, static_cast<char>(ch));
            currentPos++;
            modified = true;
        }
    }
}

// 显示主菜单
void showMainMenu() {
    clearScreen();
    
    setColor(14);
    cout << "===== 增强型控制台记事本 =====\n\n";
    setColor(7);
    
    cout << "1. 新建文件\n";
    cout << "2. 打开文件\n";
    cout << "3. 编辑当前文件\n";
    cout << "4. 保存文件\n";
    cout << "5. 查找文本\n";
    cout << "6. 替换文本\n";
    cout << "7. 删除当前行\n";
    cout << "8. 退出\n\n";
    
    setColor(8);
    cout << "当前文件: " << (filename.empty() ? "[未命名]" : filename);
    if (modified) cout << " *已修改*";
    cout << "\n";
    cout << "总行数: " << lines.size() << "\n\n";
    setColor(7);
}

int main() {
    // 设置控制台标题
    setConsoleTitle("增强型记事本");

    // 设置控制台窗口大小
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 79, 49}; // 80x50
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    
    // 设置缓冲区大小
    COORD bufferSize = {80, 50};
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // 初始化
    lines.push_back("");
    
    while (true) {
        showMainMenu();
        
        cout << "请选择操作: ";
        char choice;
        cin >> choice;
        cin.ignore(); // 清除输入缓冲区

        switch (choice) {
            case '1':
                lines.clear();
                lines.push_back("");
                filename = "";
                modified = false;
                currentLine = 0;
                currentPos = 0;
                setColor(10);
                cout << "已创建新文件!\n";
                setColor(7);
                break;
            case '2':
                openFile();
                break;
            case '3':
                if (lines.empty()) lines.push_back("");
                editText();
                break;
            case '4':
                saveFile();
                break;
            case '5':
                findText();
                break;
            case '6':
                replaceText();
                break;
            case '7':
                deleteLine();
                setColor(10);
                cout << "已删除当前行!\n";
                setColor(7);
                break;
            case '8':
                if (modified) {
                    setColor(12);
                    cout << "有未保存的修改，确定要退出吗? (y/n): ";
                    setColor(7);
                    char confirm = _getch();
                    if (tolower(confirm) != 'y') continue;
                }
                return 0;
            default:
                setColor(12);
                cout << "无效选择!\n";
                setColor(7);
        }
        
        cout << "\n按任意键继续...";
        _getch();
    }
}
