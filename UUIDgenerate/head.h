#pragma once

#include <sstream>
#include <random>
#include <stdint.h>
#include <array>

/**
 * UUID(GUID)��\���N���X
 */
class Uuid
{
public:

    Uuid() = default;
    ~Uuid() = default;
    Uuid(const Uuid&) = default;
    Uuid& operator=(const Uuid&) = default;
    Uuid(Uuid&&) = default;
    Uuid& operator=(Uuid&&) = default;

    // �V����UUID�𐶐�����
    static Uuid newUuid();
    // �f�[�^�𕶎���Ƃ��Ď��o���B"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"�`��
    std::string toString();
    // �f�[�^��16�o�C�g�̃X�g���[���Ƃ��Ď��o��
    std::array<unsigned char, 16> toByte();

    // ��r���Z�q
    bool operator==(const Uuid& a);
    bool operator!=(const Uuid& a);

private:

    // �f�[�^�Ǘ��p�̃R���e�i
    union _TempU64
    {
        uint64_t      a;
        uint32_t      b[2];
        uint16_t      c[4];
        unsigned char d[8];
    };

    // ��Ӑ������m�ۂ��邽�߃C���X�^���X�͑S�����L
    static bool isInit;
    static std::mt19937 mt;
    static std::uniform_int_distribution<uint64_t> range;

    // C#��GUID�Ɠ����f�[�^�\�������
    uint32_t a;
    uint16_t b;
    uint16_t c;
    unsigned char d[8];

    // UIntSplit�𗐐��Ŗ��߂ĕԂ�
    static _TempU64 gen();

    // 16�i�ϊ� + ��ʕs�������[������
    template<typename CNT>
    static std::string toHex(CNT value);
    static std::string toHex(unsigned char value[]);
};

template<typename CNT>
inline std::string Uuid::toHex(CNT value)
{
    int size = sizeof(value);

    std::stringstream ss;
    ss << std::hex << (int)value;
    std::string str = ss.str();

    std::string temp = "";
    if (str.length() < size)
    {
        for (int i = 0; i < size - str.length(); i++)
        {
            temp.append("0");
        }
    }

    return temp + str;
}#pragma once
