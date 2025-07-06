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

// �ı�������
vector<string> lines;
string filename = "";
bool modified = false;
int currentLine = 0;
int currentPos = 0;

// ����̨�ı���ɫ����
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// �����Ļ
void clearScreen() {
    system("cls");
}

// ���ÿ���̨����
void setConsoleTitle(const string& title) {
    SetConsoleTitleA(title.c_str());
}

// ��ʾ������Ϣ
void showHelp() {
    clearScreen();
    setColor(11); // ��ɫ
    cout << "===== ������Ϣ =====\n\n";
    cout << "�༭����:\n";
    cout << "  �����     : �ƶ����\n";
    cout << "  Enter      : ��������\n";
    cout << "  Backspace  : ɾ������ַ�\n";
    cout << "  Delete     : ɾ���Ҳ��ַ�\n\n";
    
    cout << "��ݼ�:\n";
    cout << "  Ctrl+S     : �����ļ�\n";
    cout << "  Ctrl+O     : ���ļ�\n";
    cout << "  Ctrl+N     : �½��ļ�\n";
    cout << "  Ctrl+F     : �����ı�\n";
    cout << "  Ctrl+H     : �滻�ı�\n";
    cout << "  Ctrl+Q     : �˳�����\n";
    cout << "  ESC        : �˳��༭ģʽ\n";
    cout << "  F1         : ��ʾ����\n\n";
    
    cout << "���˵�����:\n";
    cout << "  1-6        : ѡ��˵���\n\n";
    
    setColor(14); // ��ɫ
    cout << "�����������...";
    setColor(7); // Ĭ����ɫ
    _getch(); // �ȴ�����
}

// ��ʾ�ļ����ݣ����кţ�
void displayContent() {
    clearScreen();
    
    // ��ʾ�ļ�����״̬
    setColor(14);
    cout << "�ļ�: " << (filename.empty() ? "[δ����]" : filename);
    if (modified) cout << " *���޸�*";
    cout << "\n";
    
    // ��ʾ�ָ���
    setColor(8);
    cout << "--------------------------------------------------\n";
    setColor(7);
    
    // ��ʾ���кŵ��ļ�����
    for (int i = 0; i < lines.size(); i++) {
        // ������ʾ��ǰ��
        if (i == currentLine) {
            setColor(15); // ������ɫ
        } else {
            setColor(7); // Ĭ����ɫ
        }
        
        // ��ʾ�к�
        cout << setw(3) << right << i + 1 << " | ";
        
        // ��ʾ������
        cout << lines[i] << "\n";
    }
}

// �����ļ�
bool saveFile() {
    if (filename.empty()) {
        setColor(14);
        cout << "�����ļ���: ";
        setColor(7);
        getline(cin, filename);
    }

    ofstream file(filename);
    if (!file.is_open()) {
        setColor(12);
        cout << "�޷������ļ�!" << endl;
        setColor(7);
        return false;
    }

    for (const auto& line : lines) {
        file << line << "\n";
    }

    modified = false;
    setColor(10);
    cout << "�ļ��ѱ���!" << endl;
    setColor(7);
    return true;
}

// ���ļ�
void openFile() {
    string newFilename;
    setColor(14);
    cout << "����Ҫ�򿪵��ļ���: ";
    setColor(7);
    getline(cin, newFilename);

    ifstream file(newFilename);
    if (!file.is_open()) {
        setColor(12);
        cout << "�޷����ļ�!" << endl;
        setColor(7);
        return;
    }

    lines.clear();
    string line;
    while (getline(file, line)) {
        // �Ƴ�Windows�س���
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
    cout << "�ļ��Ѽ���! �� " << lines.size() << " ��" << endl;
    setColor(7);
}

// �����ı�
void findText() {
    if (lines.empty()) {
        setColor(12);
        cout << "�ļ�Ϊ��!" << endl;
        setColor(7);
        return;
    }
    
    string searchTerm;
    setColor(14);
    cout << "����Ҫ���ҵ��ı�: ";
    setColor(7);
    getline(cin, searchTerm);
    
    if (searchTerm.empty()) return;
    
    int startLine = currentLine;
    int startPos = currentPos + 1;
    bool found = false;
    int foundLine = -1;
    size_t foundPos = string::npos;
    
    // �ӵ�ǰλ�ÿ�ʼ����
    for (int i = startLine; i < lines.size(); i++) {
        size_t pos = (i == startLine) ? lines[i].find(searchTerm, startPos) : lines[i].find(searchTerm);
        
        if (pos != string::npos) {
            foundLine = i;
            foundPos = pos;
            found = true;
            break;
        }
    }
    
    // ���û�ҵ������ļ���ͷ��������
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
        cout << "���ҵ�ƥ���ı�! λ��: �� " << foundLine + 1 << ", �� " << foundPos + 1 << endl;
        setColor(7);
    } else {
        setColor(12);
        cout << "δ�ҵ�ƥ���ı�!" << endl;
        setColor(7);
    }
}

// �滻�ı�
void replaceText() {
    if (lines.empty()) {
        setColor(12);
        cout << "�ļ�Ϊ��!" << endl;
        setColor(7);
        return;
    }
    
    string searchTerm, replaceTerm;
    setColor(14);
    cout << "����Ҫ���ҵ��ı�: ";
    setColor(7);
    getline(cin, searchTerm);
    
    if (searchTerm.empty()) return;
    
    setColor(14);
    cout << "�����滻�ı�: ";
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
        cout << "���滻 " << replaceCount << " ��ƥ���ı�!" << endl;
        setColor(7);
    } else {
        setColor(12);
        cout << "δ�ҵ�ƥ���ı�!" << endl;
        setColor(7);
    }
}

// ɾ����
void deleteLine() {
    if (lines.empty()) return;
    
    if (currentLine < lines.size()) {
        lines.erase(lines.begin() + currentLine);
        modified = true;
        
        // �������λ��
        if (currentLine >= lines.size() && !lines.empty()) {
            currentLine = static_cast<int>(lines.size()) - 1;
        }
        if (currentPos > lines[currentLine].size()) {
            currentPos = static_cast<int>(lines[currentLine].size());
        }
    }
}

// �༭�ı�
void editText() {
    while (true) {
        displayContent();
        
        // ��ʾ���λ����Ϣ
        setColor(8);
        cout << "\n��: " << currentLine + 1 << "  ��: " << currentPos + 1;
        cout << "  ��F1�鿴����\n";
        setColor(7);

        // ���ù��λ��
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorCoord;
        cursorCoord.X = min(currentPos, static_cast<int>(lines[currentLine].size())) + 7; // 7 = �кſ�� + �ָ���
        cursorCoord.Y = currentLine + 3; // ƫ�Ʊ�����
        SetConsoleCursorPosition(hConsole, cursorCoord);

        // �����������
        int ch = _getch();
        
        // ���ܼ�����
        if (ch == 0 || ch == 0xE0) { // ��չ��
            int ext = _getch();
            
            // �����
            if (ext == 72 && currentLine > 0) currentLine--; // ��
            else if (ext == 80 && currentLine < lines.size() - 1) currentLine++; // ��
            else if (ext == 75 && currentPos > 0) currentPos--; // ��
            else if (ext == 77 && currentPos < lines[currentLine].size()) currentPos++; // ��
            
            // ������β����
            currentPos = min(currentPos, static_cast<int>(lines[currentLine].size()));
        }
        else if (ch == 224) { // ���ܼ� (F1-F12)
            int ext = _getch();
            if (ext == 59) { // F1
                showHelp();
            }
        }
        // Ctrl��ϼ�
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
        // ��ͨ�ַ�
        else if (ch == 13) { // �س�
            string remainder = lines[currentLine].substr(currentPos);
            lines[currentLine] = lines[currentLine].substr(0, currentPos);
            lines.insert(lines.begin() + currentLine + 1, remainder);
            currentLine++;
            currentPos = 0;
            modified = true;
        }
        else if (ch == 8) { // �˸�
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
        else if (ch == 83) { // Delete��
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
        else if (ch >= 32 && ch <= 126) { // �ɴ�ӡ�ַ�
            lines[currentLine].insert(currentPos, 1, static_cast<char>(ch));
            currentPos++;
            modified = true;
        }
    }
}

// ��ʾ���˵�
void showMainMenu() {
    clearScreen();
    
    setColor(14);
    cout << "===== ��ǿ�Ϳ���̨���±� =====\n\n";
    setColor(7);
    
    cout << "1. �½��ļ�\n";
    cout << "2. ���ļ�\n";
    cout << "3. �༭��ǰ�ļ�\n";
    cout << "4. �����ļ�\n";
    cout << "5. �����ı�\n";
    cout << "6. �滻�ı�\n";
    cout << "7. ɾ����ǰ��\n";
    cout << "8. �˳�\n\n";
    
    setColor(8);
    cout << "��ǰ�ļ�: " << (filename.empty() ? "[δ����]" : filename);
    if (modified) cout << " *���޸�*";
    cout << "\n";
    cout << "������: " << lines.size() << "\n\n";
    setColor(7);
}

int main() {
    // ���ÿ���̨����
    setConsoleTitle("��ǿ�ͼ��±�");

    // ���ÿ���̨���ڴ�С
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 79, 49}; // 80x50
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    
    // ���û�������С
    COORD bufferSize = {80, 50};
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // ��ʼ��
    lines.push_back("");
    
    while (true) {
        showMainMenu();
        
        cout << "��ѡ�����: ";
        char choice;
        cin >> choice;
        cin.ignore(); // ������뻺����

        switch (choice) {
            case '1':
                lines.clear();
                lines.push_back("");
                filename = "";
                modified = false;
                currentLine = 0;
                currentPos = 0;
                setColor(10);
                cout << "�Ѵ������ļ�!\n";
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
                cout << "��ɾ����ǰ��!\n";
                setColor(7);
                break;
            case '8':
                if (modified) {
                    setColor(12);
                    cout << "��δ������޸ģ�ȷ��Ҫ�˳���? (y/n): ";
                    setColor(7);
                    char confirm = _getch();
                    if (tolower(confirm) != 'y') continue;
                }
                return 0;
            default:
                setColor(12);
                cout << "��Чѡ��!\n";
                setColor(7);
        }
        
        cout << "\n�����������...";
        _getch();
    }
}
