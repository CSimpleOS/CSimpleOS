#include <iostream>
#include <string>
#include <windows.h>
#include <unordered_set>
using namespace std;
int main()
{
    system("title 请稍后 - CSimpleOS安装程序");
    cout << "请稍后" << endl;
    Sleep(20000);
    system("cls");
    system("title CSimpleOS - 安装程序");
    while (true)
    {
        cout << "欢迎使用CSimpleOS安装向导" << endl;
        cout << "输入继续以继续安装" << endl;
        cout << "输入exit以退出向导" << endl;
        string input_start;
        cin >> input_start;
        if (input_start == "继续")
        {
            system("title CSimpleOS - 安装程序 - 欢迎界面");
            system("cls");
            break;
        }
        else if (input_start == "exit")
        {
            cout << "您可以再次打开此向导以安装" << endl;
            cout << "感谢您的使用" << endl;
            return 0;
        }
        else if (input_start == "home")
        {
            system("start https://github.com/mtxgdn/CSimpleOS");
            return 0;
        }
        else
        {
            cout << "输入无效" << endl;
            system("cls");
            continue;
        }
    }
    cout << "请激活CSimpleOS" << endl;
    cout << "序列号:"<< endl;
    string activate_UUID;
    while (true)
    {
        cin >> activate_UUID;
        std::unordered_set<std::string> valid_UUIDs = {
            "2c4e5485-346c-4a9c-b85d-dd8ebdbf5e10",
            "80feeffe-80bb-4f89-a736-7b89eb657e8a",
            "56b3c0aa-1a79-4f7d-975f-34abfa7981b4",
            "52705f84-72d8-4e00-a636-eda0c1451f5c",
            "7dc04382-d82f-4d2d-b9e4-3f928e38a4d9",
            "a1cd370a-1cea-4c60-aa9c-c1de29c067d7",
            "36cf910b-e5a0-436d-88b0-de70281cb2fb",
            "d5e33f68-6411-4fb3-a285-9409d1178567",
            "2a1cd846-315c-4ab6-94fb-a6d6d1ace4bb",
            "1aa8f1d1-6355-4bb4-8af7-5835f8c8e2e0"};
        if (valid_UUIDs.find(activate_UUID) != valid_UUIDs.end())
        {
            cout << "激活成功" << endl;
            system ("cls");
            break;
        }
        else
        {
            cout << "激活失败" << endl;
            cout << "请重新输入序列号" << endl;
            cout << "如果不知道序列号请自行翻找源代码" << endl;
        }
    }
    system("cls");
    system("title CSimpleOS - 安装程序 - 签署协议");
    // 签署协议界面
    cout<<"签署协议"<<endl;
    cout<<"请阅读以下协议"<<endl;
   // 协议标题与版权信息
    cout << "===================== CSimpleOS用户协议 =====================" << endl;
    cout << "GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007" << endl;
    cout << "Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>" << endl;
    cout << "? 2025 CSimpleOS Development Team. All rights reserved." << endl;
    cout << "=================================================================" << endl << endl;

    // 协议前言 - 自由软件声明
    cout << "1. 本软件遵循GNU GPLv3开源协议，保障您自由分享、修改和传播的权利。" << endl;
    cout << "2. 您有权获取软件源代码，修改后版本需继续遵守本协议并标注修改信息。" << endl;
    cout << "3. CSimpleOS是模拟操作系统环境的教学软件，非实际功能操作系统。" << endl << endl;

    // 核心条款 - 基于GPLv3简化
    cout << "===================== GNU GPLv3核心条款 =====================" << endl;
    cout << "4. 源代码获取：您可从官方渠道获取完整源代码，二进制文件需附带源码或提供获取方式。" << endl;
    cout << "5. 传播要求：分享软件时需保留所有版权声明、协议条款及免责声明。" << endl;
    cout << "6. 修改限制：修改后的版本需明确标注'已修改'及日期，且必须整体遵循本协议。" << endl;
    cout << "7. 专利许可：本软件贡献者授予您免版税的专利许可，允许正常使用和传播。" << endl;
    cout << "8. 免责声明：软件按'现状'提供，不保证适销性或特定用途适用性，使用风险自担。" << endl;
    cout << "9. 责任限制：开发者不对因使用软件导致的数据丢失、系统故障等损失承担责任。" << endl << endl;

    // CSimpleOS特殊声明
    cout << "===================== CSimpleOS附加声明 =====================" << endl;
    cout << "10. 非实际操作系统：本软件仅用于教学演示，不具备真实操作系统功能，不影响实际系统。" << endl;
    cout << "11. 无技术支持：软件免费提供，不包含技术支持、更新或维护服务。" << endl;
    cout << "12. 数据安全：使用前请备份重要数据，开发者不对数据损失负责。" << endl;
    cout << "13. 禁止篡改：请从官方渠道获取软件，勿使用修改或篡改版本。" << endl;
    cout << "14. 适用场景：本软件不适合生产环境或关键任务场景。" << endl << endl;

    // 协议接受确认
    cout << "=================================================================" << endl;
    cout << "使用本软件即表示您已阅读、理解并同意上述所有条款。" << endl;
    cout << "如不同意本协议，请立即停止使用CSimpleOS。" << endl;
    cout << "===================== CSimpleOS开发团队 ======================" << endl;
    string agreement_choice;
    cout << "请输入'同意'以接受协议，或输入'不同意'以退出安装程序：" << endl;
    cin >> agreement_choice;
    if (agreement_choice == "同意")
    {
        cout << "感谢您接受CSimpleOS用户协议！" << endl;
        system("cls");
    }
    else if (agreement_choice == "不同意")
    {
        cout << "您已选择不同意协议，安装程序将退出。" << endl;
        return 0;
    }
    else
    {
        cout << "输入无效，请重新运行安装程序。" << endl;
        return 0;
    }
    system("title CSimpleOS - 安装程序 - 选择安装方式");
    cout << "请选择CSimpleOS的安装" << endl;
    cout << "1.就地安装" << endl;
    cout << "2.使用自解压程序进行自定义安装（不推荐）"<< endl;
    cout << "wget的下载来源：https://eternallybored.org/misc/wget/"<<endl;
    string Install_user_choose;
    cin>>Install_user_choose;
    if(Install_user_choose == "1"){
        system("wget -P ./tools https://github.com/CSimpleOS/CSimpleOS-Tool/releases/download/V0.0.1/notepad.exe");
    }
    else if(Install_user_choose == "2"){
        cout<<"暂未发行该资源"<<endl;
    }
    system("pause");
    system("cls");
    system("title CSimpleOS - 安装程序 - 安装中");
    cout << "正在安装CSimpleOS" << endl;
    cout << "请稍后" << endl;

    return 0;
}
