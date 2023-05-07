#include "Monster.h"

#define MONSTER_LEVEL_FACTOR 1000

Monster::Monster(int level, const std::string &category)
{
    this->level = level;
    this->category = category;
}
// 转换成初级灵石的个数
SpriteStone Monster::getValue() const
{
    int stoneCount[] = {100, 200, 500, 1000, 2000,
                        5000, 10000, 20000, 100000};
    int count = stoneCount[this->level - 1];
    return SpriteStone(count, SpriteStoneLevel::PRIMARY_LEVEL);
}

int Monster::getPower() const
{
    // 不同级别的妖兽的战斗力不同
    int ret = this->level * MONSTER_LEVEL_FACTOR;
    return ret;
}

std::ostream &operator<<(std::ostream &os, const Monster &monster)
{
    // TODO: 在此处插入 return 语句
    os << monster.level << "级" << monster.category << "妖兽";
    return os;
}
// 重载==
bool operator==(const Monster &one, const Monster other)
{
    if (one.category == other.category &&
        one.level == other.level)
    {
        return true;
    }
    else
    {
        return false;
    }
}
