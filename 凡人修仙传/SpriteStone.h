#pragma once
#include <string>
#include <iostream>
// c++11 的新标准
enum class SpriteStoneLevel
{
    PRIMARY_LEVEL = 0,
    MIDDLE_LEVEL = 1,
    ADVANCE_LEVEL = 2,
    SPRITE_STONE_LEVEL_COUNT = 3
};

// 灵石类
class SpriteStone
{
public:
    SpriteStone(int count = 0,
                SpriteStoneLevel level = SpriteStoneLevel::PRIMARY_LEVEL);
    // 输出
    std::string str() const;
    friend std::ostream &operator<<(std::ostream &os,
                                    const SpriteStone &stone);
    SpriteStone operator+(const SpriteStone &stone);
    SpriteStone operator-(const SpriteStone &stone);
    // 灵石价值的初阶灵石数>=妖兽价值的初阶灵石数
    bool operator>=(const SpriteStone &stone) const;
    // 灵石有多少块
    int getCount() const;

private:
    // 灵石的数量:xx块
    int count;
    // 灵石等级
    SpriteStoneLevel level;
};

std::ostream &operator<<(std::ostream &os,
                         const SpriteStone &stone);