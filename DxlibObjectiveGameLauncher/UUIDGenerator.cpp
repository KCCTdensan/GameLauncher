#include "UUIDGenerator.h"

#pragma comment(lib, "rpcrt4.lib")

std::string UUIDGenerator::GetGUID()
{
    if (S_OK != ::CoCreateGuid(&tGUID)) {
        MessageBox(NULL, "GUID�̐����Ɏ��s���܂����B", "", MB_OK);
        return "";
    }
    else {

        // GUID�𕶎���֕ϊ�
        std::string oGuidString = GuidToString(&tGUID);

        return oGuidString;
    }
    
}

std::string UUIDGenerator::GuidToString(GUID* _GUID)
{
    std::string oGuidString;
    RPC_CSTR cString;

    // GUID�𕶎���֕ϊ�����
    if (RPC_S_OK == ::UuidToString(_GUID, &cString)) {

        // GUID�����ʂɃZ�b�g
        oGuidString = (CHAR*)cString;

        // GUID������̔j��
        ::RpcStringFree(&cString);
    }

    // GUID��Ԃ�
    return oGuidString;
}