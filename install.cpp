#include <iostream>
#include <string>
#include <windows.h>
#include <unordered_set>
using namespace std;
int main()
{
    system("title ���Ժ� - CSimpleOS��װ����");
    cout << "���Ժ�" << endl;
    Sleep(20000);
    system("cls");
    system("title CSimpleOS - ��װ����");
    while (true)
    {
        cout << "��ӭʹ��CSimpleOS��װ��" << endl;
        cout << "��������Լ�����װ" << endl;
        cout << "����exit���˳���" << endl;
        string input_start;
        cin >> input_start;
        if (input_start == "����")
        {
            system("title CSimpleOS - ��װ���� - ��ӭ����");
            system("cls");
            break;
        }
        else if (input_start == "exit")
        {
            cout << "�������ٴδ򿪴����԰�װ" << endl;
            cout << "��л����ʹ��" << endl;
            return 0;
        }
        else if (input_start == "home")
        {
            system("start https://github.com/mtxgdn/CSimpleOS");
            return 0;
        }
        else
        {
            cout << "������Ч" << endl;
            system("cls");
            continue;
        }
    }
    cout << "�뼤��CSimpleOS" << endl;
    cout << "���к�:"<< endl;
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
            cout << "����ɹ�" << endl;
            system ("cls");
            break;
        }
        else
        {
            cout << "����ʧ��" << endl;
            cout << "�������������к�" << endl;
            cout << "�����֪�����к������з���Դ����" << endl;
        }
    }
    system("title CSimpleOS - ��װ���� - ѡ��װ��ʽ");
    cout << "��ѡ��CSimpleOS�İ�װ" << endl;
    cout << "1.�͵ذ�װ" << endl;
    cout << "2.ʹ���Խ�ѹ��������Զ��尲װ�����Ƽ���"<< endl;
    cout << "wget��������Դ��https://eternallybored.org/misc/wget/"<<endl;
    string Install_user_choose;
    cin>>Install_user_choose;
    if(Install_user_choose == "1"){
        system("wget https://github.com/CSimpleOS/CSimpleOS-Tool/releases/download/V0.0.1/notepad.exe");
    }
    if(Install_user_choose == "2"){
        cout<<"��δ���и���Դ"<<endl;
    }
    system("pause");
    return 0;
}
