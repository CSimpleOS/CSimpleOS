#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <windows.h>
using namespace std;
int main()
{
    system("title CSimpleOS - 主程序 - 检测激活状态");
    const char *subKey = "SOFTWARE\\CSimpleOS\\CSimpleOS\\License";
    const char *valueName = "SerialNumber";

    std::vector<string> validSerialNumbers = {
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

    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
    {
        exit(1);
    }

    DWORD dataType;
    char data[256];
    DWORD dataSize = sizeof(data);
    if (RegQueryValueExA(hKey, valueName, 0, &dataType, (LPBYTE)data, &dataSize) != ERROR_SUCCESS ||
        dataType != REG_SZ)
    {
        RegCloseKey(hKey);
        exit(1);
    }

    RegCloseKey(hKey);

    std::string serialNumber(data);
    bool isValid = false;
    for (const auto &valid : validSerialNumbers)
    {
        if (serialNumber == valid)
        {
            isValid = true;
            break;
        }
    }

    if (!isValid)
    {
        exit(1);
    }

    return 0;

    // 主程序

    system("cls");
    system("title CSimpleOS - 主程序 - 欢迎界面");
    cout << "欢迎使用CSimpleOS" << endl;
    
    

}