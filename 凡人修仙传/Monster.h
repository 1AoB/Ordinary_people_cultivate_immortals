#pragma once
#include <string>
#include "SpriteStone.h"

#include <iostream>
using namespace std;

class SpriteStone;

// 妖兽类
class Monster
{

public:
    // 构造函数
    Monster(int level = 1, const std::string &category = "未知类型");
    SpriteStone getValue() const;
    // 获取该妖兽的战斗力
    int getPower() const;
    friend std::ostream &operator<<(std::ostream &os,
                                    const Monster &monster);
    friend bool operator==(const Monster &one,
                           const Monster other);

private:
    std::string category; // 妖兽的种类
    int level;            // 1~9级
};

std::ostream &operator<<(std::ostream &os, const Monster &monster);
// 重载==
bool operator==(const Monster &one,
                const Monster other);