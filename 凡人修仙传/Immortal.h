#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SpriteStone.h"
#include "Monster.h"

class SpriteStone;
class Monster;

// c++11枚举类型 级别
enum class ImmortalLevel
{
    LIAN_QI,   // 炼气期
    ZHU_JI,    // 筑基期
    JIE_DAN,   // 结丹期
    YUAN_YING, // 元婴期
    HUA_SHENG, // 化神期
    LIAN_XU,   // 炼虚期
    HE_TI,     // 合体期
    DA_CHENG,  // 大乘期
    DU_JIE     // 渡劫期
};

// 修仙者类
class Immortal
{
public:
    // 构造函数
    Immortal(const char *name, const char *menPai,
             ImmortalLevel level);

    // 挖矿一次,增加100块初阶灵石
    void mining();
    // 贸易:到市场售卖所有妖兽
    bool trade();
    // 到市场售卖指定妖兽
    bool trade(const Monster &monster);
    // 用自己的灵石,来购买其他修仙者的指定妖兽
    bool trade(Immortal &other, const Monster &monster);
    // 用自己指定的妖兽,来换其他修仙者的指定妖兽
    bool trade(const Monster &monsterSource,
               Immortal &other, const Monster &monsterDest);
    // 把自己的妖兽售卖给其他修仙者,以换取灵石
    bool trade(const Monster &monster, Immortal &other);
    // 获取修仙者自己的战斗力
    int getPower() const;
    // 捕获妖兽
    void fight(const Monster &monster);
    // 运算符重载
    friend std::ostream &operator<<(std::ostream &os,
                                    const Immortal &immortal);
    friend std::ostream &operator<<(std::ostream &os,
                                    const ImmortalLevel &level);
    // 修仙者战死
    void dead();

    // 获取修仙者灵石的个数
    int getStonesSize() const;

    // 生死斗:修仙者之间进行比武  +夺取对方灵石 + 夺取对方妖兽
    bool fightPeo(Immortal &other);

    // 渡劫升级
    bool getUp();

private:
    std::string name;                // 修仙者名字:韩立
    std::string menPai;              // 门派
    ImmortalLevel level;             // 修仙者的级别
    std::vector<SpriteStone> stones; // 灵石资产
    std::vector<Monster> monsters;   // 妖兽资产
    bool alive;                      // 生死状态
    // 判断该修仙者有没有这个妖兽
    bool hadMonster(const Monster &monster);
    // 移除指定妖兽
    bool removeMonster(const Monster &monster);
};
// 重载<<,输出修仙的基础信息
std::ostream &operator<<(std::ostream &os, const Immortal &immortal);
// 重载<<,输出修仙级别
std::ostream &operator<<(std::ostream &os,
                         const ImmortalLevel &level);
