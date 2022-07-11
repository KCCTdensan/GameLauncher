#include "UUIDGenerator.h"

#pragma comment(lib, "rpcrt4.lib")

std::string UUIDGenerator::GetGUID()
{
    if (S_OK != ::CoCreateGuid(&tGUID)) {
        MessageBox(NULL, "GUIDの生成に失敗しました。", "", MB_OK);
        return "";
    }
    else {

        // GUIDを文字列へ変換
        std::string oGuidString = GuidToString(&tGUID);

        return oGuidString;
    }
    
}

std::string UUIDGenerator::GuidToString(GUID* _GUID)
{
    std::string oGuidString;
    RPC_CSTR cString;

    // GUIDを文字列へ変換する
    if (RPC_S_OK == ::UuidToString(_GUID, &cString)) {

        // GUIDを結果にセット
        oGuidString = (CHAR*)cString;

        // GUID文字列の破棄
        ::RpcStringFree(&cString);
    }

    // GUIDを返す
    return oGuidString;
}