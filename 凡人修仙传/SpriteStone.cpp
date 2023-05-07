#include "SpriteStone.h"
#include <sstream>
SpriteStone::SpriteStone(int count, SpriteStoneLevel level)
{
    this->count = count;
    this->level = level;
}

std::string SpriteStone::str() const
{
    std::stringstream ret;
    ret << count << "块";
    switch (level)
    {
    case SpriteStoneLevel::PRIMARY_LEVEL:
        ret << "初级灵石";
        break;
    case SpriteStoneLevel::MIDDLE_LEVEL:
        ret << "中阶灵石";
        break;
    case SpriteStoneLevel::ADVANCE_LEVEL:
        ret << "高阶灵石";
        break;
    default:
        ret << "未知灵石";
        break;
    }
    return ret.str();
}

// 重载+号,结果都用初阶灵石表示
SpriteStone SpriteStone::operator+(const SpriteStone &stone)
{
    int sum = 0;
    // 拿到+号前的初阶灵石个数
    if (stone.level == SpriteStoneLevel::PRIMARY_LEVEL)
    {
        sum = this->count;
        ;
    }
    else if (stone.level == SpriteStoneLevel::MIDDLE_LEVEL)
    {
        sum = this->count * 10;
    }
    else if (stone.level == SpriteStoneLevel::ADVANCE_LEVEL)
    {
        sum = this->count * 100;
    }
    // 加上+号的初阶灵石的个数
    if (stone.level == SpriteStoneLevel::PRIMARY_LEVEL)
    {
        sum += stone.count;
    }
    else if (stone.level == SpriteStoneLevel::MIDDLE_LEVEL)
    {
        sum += stone.count * 10;
    }
    else if (stone.level == SpriteStoneLevel::ADVANCE_LEVEL)
    {
        sum += stone.count * 100;
    }
    return SpriteStone(sum, SpriteStoneLevel::PRIMARY_LEVEL);
}
SpriteStone SpriteStone::operator-(const SpriteStone &stone)
{
    int sum = 0;
    // 拿到-号前的初阶灵石个数
    if (stone.level == SpriteStoneLevel::PRIMARY_LEVEL)
    {
        sum = this->count;
        ;
    }
    else if (stone.level == SpriteStoneLevel::MIDDLE_LEVEL)
    {
        sum = this->count * 10;
    }
    else if (stone.level == SpriteStoneLevel::ADVANCE_LEVEL)
    {
        sum = this->count * 100;
    }
    // 加上-号的初阶灵石的个数
    if (stone.level == SpriteStoneLevel::PRIMARY_LEVEL)
    {
        sum -= stone.count;
    }
    else if (stone.level == SpriteStoneLevel::MIDDLE_LEVEL)
    {
        sum -= stone.count * 10;
    }
    else if (stone.level == SpriteStoneLevel::ADVANCE_LEVEL)
    {
        sum -= stone.count * 100;
    }
    return SpriteStone(sum, SpriteStoneLevel::PRIMARY_LEVEL);
}
// 灵石价值的初阶灵石数>=妖兽价值的初阶灵石数
bool SpriteStone::operator>=(const SpriteStone &stone) const
{
    int sum1 = 0; // 灵石价值的初阶灵石数
    if (this->level == SpriteStoneLevel::PRIMARY_LEVEL)
    {
        sum1 = this->count;
    }
    else if (this->level == SpriteStoneLevel::MIDDLE_LEVEL)
    {
        sum1 = this->count * 10;
    }
    else if (this->level == SpriteStoneLevel::ADVANCE_LEVEL)
    {
        sum1 = this->count * 100;
    }
    int sum2 = 0; // 妖兽价值的初阶灵石数
    if (stone.level == SpriteStoneLevel::PRIMARY_LEVEL)
    {
        sum2 = stone.count;
    }
    else if (stone.level == SpriteStoneLevel::MIDDLE_LEVEL)
    {
        sum2 = stone.count * 10;
    }
    else if (stone.level == SpriteStoneLevel::ADVANCE_LEVEL)
    {
        sum2 = stone.count * 100;
    }
    return sum1 >= sum2;
}

int SpriteStone::getCount() const
{
    // std::cout << "SpriteStones.cpp中的getCount():" << this->count << std::endl;
    return this->count;
}

std::ostream &operator<<(std::ostream &os, const SpriteStone &stone)
{
    // TODO: 在此处插入 return 语句
    os << stone.str();
    return os;
}
