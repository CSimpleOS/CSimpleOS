#include<iostream>
#include<string>
#include<windows.h>
#include<filesystem>
#include<Shellapi.h>
#include<fstream>
#include<vector>
#pragma comment(lib, "Shell32.lib")
using namespace std;
bool IsUserAnAdmin() {
    BOOL isAdmin = FALSE;
    PSID administratorsGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&ntAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &administratorsGroup)) {
        CheckTokenMembership(NULL, administratorsGroup, &isAdmin);
        FreeSid(administratorsGroup);
    }
    return isAdmin == TRUE;
}
int main(){
    cout << "����ж��CSimpleOS..." << endl;
    // ����Ƿ��Թ���ԱȨ������
    if (!IsUserAnAdmin()) {
        cout << "���Թ���ԱȨ�����д˳���" << endl;
        return 1;
    }
    //
    // ɾ��ע�����
    system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\CSimpleOS");
    // ɾ���ļ�
    system("del ./install.exe");
    system("del ./wget.exe");
    system("del ./tools/notepad.exe");
    system("del ./main.exe");
    // ɾ��Դ����
    system("del ./main.cpp");
    system("del ./install.cpp");
    system("del ./uninstall.cpp");
    system("del ./tools/notepad.cpp");
    system("del ./LICENSE");
    system("del ./README.md");
    // ɾ��Ŀ¼
    system("rmdir /S /Q ./tools");
    // ɾ��ж�س���
    system("del ./uninstall.exe");
}