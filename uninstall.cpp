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
    cout << "正在卸载CSimpleOS..." << endl;
    // 检查是否以管理员权限运行
    if (!IsUserAnAdmin()) {
        cout << "请以管理员权限运行此程序！" << endl;
        return 1;
    }
    //
    // 删除注册表项
    system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\CSimpleOS");
    // 删除文件
    system("del ./install.exe");
    system("del ./wget.exe");
    system("del ./tools/notepad.exe");
    system("del ./main.exe");
    // 删除源代码
    system("del ./main.cpp");
    system("del ./install.cpp");
    system("del ./uninstall.cpp");
    system("del ./tools/notepad.cpp");
    system("del ./LICENSE");
    system("del ./README.md");
    // 删除目录
    system("rmdir /S /Q ./tools");
    // 删除卸载程序
    system("del ./uninstall.exe");
}