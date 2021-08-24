#pragma once

#include <sstream>
#include <random>
#include <stdint.h>
#include <array>

/**
 * UUID(GUID)を表すクラス
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

    // 新しいUUIDを生成する
    static Uuid newUuid();
    // データを文字列として取り出す。"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"形式
    std::string toString();
    // データを16バイトのストリームとして取り出す
    std::array<unsigned char, 16> toByte();

    // 比較演算子
    bool operator==(const Uuid& a);
    bool operator!=(const Uuid& a);

private:

    // データ管理用のコンテナ
    union _TempU64
    {
        uint64_t      a;
        uint32_t      b[2];
        uint16_t      c[4];
        unsigned char d[8];
    };

    // 一意正性を確保するためインスタンスは全部共有
    static bool isInit;
    static std::mt19937 mt;
    static std::uniform_int_distribution<uint64_t> range;

    // C#のGUIDと同じデータ構造を取る
    uint32_t a;
    uint16_t b;
    uint16_t c;
    unsigned char d[8];

    // UIntSplitを乱数で埋めて返す
    static _TempU64 gen();

    // 16進変換 + 上位不足桁をゼロ埋め
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
