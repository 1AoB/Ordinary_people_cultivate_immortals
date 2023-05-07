#include "Immortal.h"

#define IMMORTAL_LEVEL_FACTOR 1000 // 每个修仙者级别战斗力的差值
#define SPRITE_FACTOR 0.1          // 每个灵石战斗力的差值
#define MONSTER_FACTOR 0.1         // 妖兽和修仙者的配合程度

// 构造函数
Immortal::Immortal(const char *name, const char *menPai, ImmortalLevel level)
{
    this->name = name;
    this->menPai = menPai;
    this->level = level;
    this->alive = true;
}

void Immortal::mining()
{
    stones.push_back(SpriteStone(100,
                                 SpriteStoneLevel::PRIMARY_LEVEL));
    // std::cout << "mining之后,灵石个数:" << stones.size() << std::endl;
}

// 贸易:到市场售卖所有妖兽
bool Immortal::trade()
{
    if (!alive)
    {
        return false;
    }
    SpriteStone stone;
    for (int i = 0; i < monsters.size(); i++)
    {
        // 只重载了+,没有重载+=
        stone = stone + monsters[i].getValue();
    }
    // 灵石加入钱包
    stones.push_back(stone);
    // 灵兽清空
    monsters.erase(monsters.begin(), monsters.end());
    return true;
}
// 到市场售卖指定妖兽
bool Immortal::trade(const Monster &monster)
{
    if (!alive)
    {
        return false;
    }
    // check一下该修仙者有没有这个要妖兽
    if (!hadMonster(monster))
    {
        std::cout << this->name << "没有" << monster << std::endl;
        return false;
    }
    // 这个妖兽值多少钱
    SpriteStone stone = monster.getValue(); // getValue要加const,只读函数最好加上const,不然会出现报错
    this->stones.push_back(stone);
    // 移除指定妖兽
    removeMonster(monster);
    return true;
}
// 用自己的灵石,来购买 其他 指定的修仙者的 指定妖兽
bool Immortal::trade(Immortal &other, const Monster &monster)
{
    // 自己或者交易者有一人已经战死
    if (alive == false || other.alive == false)
    {
        return false;
    }
    // 交易者没有自己想要的妖兽
    if (!other.hadMonster(monster))
    {
        std::cout << other.name << "没有" << monster << std::endl;
    }
    // 计算当前所以灵石的总价
    SpriteStone stone;
    for (int i = 0; i < stones.size(); i++)
    {
        stone = stone + stones[i];
    }
    if (stone >= monster.getValue()) // 灵石价值的初阶灵石数>=妖兽价值的初阶灵石数
    {
        // 购买
        // 妖兽价值多少初阶灵石
        SpriteStone valueStone = monster.getValue();
        stone = stone - valueStone;         // 剩下的钱
        stones.clear();                     // 全部清空
        stones.push_back(stone);            // 把剩下的钱放进去
        monsters.push_back(monster);        // 把买到妖兽放入钱包
        other.removeMonster(monster);       // 交易者把妖兽拿出钱包
        other.stones.push_back(valueStone); // 交易者获得交易妖兽的初阶灵石
        return true;
    }
    else
    {
        std::cout << "抱歉!" << this->name << "的灵石不够买"
                  << other.name << "的" << monster << std::endl;
        return false;
    }
}
// 用自己指定的妖兽,来换其他修仙者的指定妖兽
bool Immortal::trade(const Monster &monsterSource, Immortal &other, const Monster &monsterDest)
{
    // 自己或者交易者有一人已经战死
    if (alive == false || other.alive == false)
    {
        cout << "自己或者交易者有一人已经战死" << endl;
        return false;
    }
    if (monsterSource == monsterDest ||                       // 妖兽相同
        !hadMonster(monsterSource) ||                         // 自己没有这个妖兽
        !other.hadMonster(monsterDest) ||                     // 对方没有那个妖兽
        (monsterDest.getValue() >= monsterSource.getValue())) // 对方妖兽价值>=自己的妖兽价值
    {
        return false; // 不愿意换
    }

    removeMonster(monsterSource);            // 自己拿出
    other.removeMonster(monsterDest);        // 对方拿出
    monsters.push_back(monsterDest);         // 自己收下对方的
    other.monsters.push_back(monsterSource); // 对方收下自己的

    return true;
}
// 把自己的妖兽售卖给其他修仙者,以换取灵石
bool Immortal::trade(const Monster &monster, Immortal &other)
{
    // 自己或者交易者有一人已经战死
    if (alive == false || other.alive == false)
    {
        return false;
    }
    if (!hadMonster(monster)) // 自己没有这个妖兽
    {
        std::cout << "抱歉!" << this->name << "没有" << monster << std::endl;
        return false; // 不愿意换
    }
    // 计算一下对方的总财富
    SpriteStone otherStone;
    for (int i = 0; i < other.stones.size(); ++i)
    {
        otherStone = otherStone + other.stones[i];
    }
    if (!(otherStone >= monster.getValue())) // 对方钱不够
    {
        std::cout << "抱歉!" << other.name << "钱不够" << std::endl;
        return false; // 不愿意换
    }
    // 交换
    // 对方付钱
    otherStone = otherStone - monster.getValue();
    other.stones.clear();
    other.stones.push_back(otherStone);

    // 自己交出妖兽,对方拿到妖兽,自己拿到钱
    removeMonster(monster);
    other.monsters.push_back(monster);
    stones.push_back(monster.getValue());

    return true;
}
// 获取修仙者自己的战斗力=修仙者等级+灵石+妖兽的综合战力
int Immortal::getPower() const
{
    // 计算该修仙者的级别
    int ret = ((int)level + 1) * IMMORTAL_LEVEL_FACTOR;
    // 计算灵石助攻的战斗力
    SpriteStone stone;
    for (int i = 0; i < this->stones.size(); i++)
    {
        stone = stone + this->stones[i]; // 所有灵石都会转换成初级灵石
    }
    ret += stone.getCount() * SPRITE_FACTOR;
    // 计算所有妖兽的助攻的战斗力
    for (int i = 0; i < monsters.size(); i++)
    {
        ret += monsters[i].getPower() * MONSTER_FACTOR;
    }
    return ret;
}
// 捕获妖兽
void Immortal::fight(const Monster &monster)
{
    // 根据战斗力谁强谁弱确定,是否可以捕获妖兽
    int selfPower = this->getPower();
    int monsterPower = monster.getPower();
    if (selfPower > monsterPower)
    {
        monsters.push_back(monster);
    }
    else if (selfPower < monsterPower)
    {
        // 战死
        dead();
    }
    else
    {
        // 平局
    }
}
// 修仙者战死
void Immortal::dead()
{
    // 改状态
    alive = false;
    // 灵石清空
    stones.erase(stones.begin(), stones.end());
    // 妖兽清空
    monsters.erase(monsters.begin(), monsters.end());
}
// 调试用,没有意义
int Immortal::getStonesSize() const
{
    // std::cout << "Immortal.cpp中的getStonesSize:" << stones.size() << std::endl;
    return this->stones.size();
}
bool Immortal::fightPeo(Immortal &other)
{
    // 先判断自己和对方，是否是存活状态
    if (alive == false || other.alive == false)
        return false;

    int selfPower = getPower();
    int otherPower = other.getPower();

    // 计算当前自己的所有灵石总价
    SpriteStone stone;
    for (int i = 0; i < stones.size(); i++)
    {
        stone = stone + stones[i];
    }
    // 计算对方有多少灵石
    SpriteStone otherstone;
    for (int i = 0; i < other.stones.size(); i++)
    {
        otherstone = otherstone + other.stones[i];
    }
    cout << "自身战力:" << selfPower << ",对方战力:" << otherPower << endl;
    // 开始PK
    if (selfPower > otherPower) // 我赢了
    {
        cout << "胜利者是：" << this->name << endl;
        // 夺取对方灵石
        stone = stone + otherstone;
        stones.clear();
        stones.push_back(stone);
        // 夺取对方妖兽
        for (int i = 0; i < other.monsters.size(); i++)
        {
            // 把other妖兽，放进 自己背包
            monsters.push_back(other.monsters[i]);
        }
        // 对方阵亡
        other.dead();
        return true;
    }
    else
    {
        cout << "胜利者是" << other.name << endl; // 对方赢了
        // 对方夺取自己的灵石
        otherstone = otherstone + stone;
        other.stones.clear();
        other.stones.push_back(otherstone);
        // 对方夺取自己的妖兽
        for (int i = 0; i < monsters.size(); i++)
        {
            // 把妖兽给对方
            other.monsters.push_back(monsters[i]);
        }
        // 死亡
        dead();
        return true;
    }
}
// 渡劫升级
bool Immortal::getUp()
{
    // 先判断，角色是否 存活
    if (!alive)
        return false;

    // 计算角色，当前等级战力+身上灵石战力
    int selfPower = this->getPower();
    cout << "自身战力:" << selfPower << ",渡劫需要的战力 : " << (((int)level + 1) * IMMORTAL_LEVEL_FACTOR * 1.5) << endl;
    // 自身战力+灵石战力 > 下一等级战力 * 1.5 ，则渡劫成功
    if (selfPower > (((int)level + 1) * IMMORTAL_LEVEL_FACTOR * 1.5))
    {
        // 渡劫成功，等级+1
        // level = level + 1;
        if (this->level < ImmortalLevel::DU_JIE)
        {
            this->level = (ImmortalLevel)((int)level + 1);
            cout << "武道漫漫其修远，天地同寿有可期。渡劫成功！"
                 << "当前等级:" << this->level << endl;
        }
        else // 已经过了渡劫期(天下第一,独断万古)了,无法在升级了
        {
            cout << "天下第一,独断万古,不灭之体，天罚奈何？\n";
        }

        return true;
    }
    else
    {
        cout << "渡劫失败，身消命陨。\n";
        dead();
        return true;
    }
}
// 判断该修仙者有没有这个妖兽
bool Immortal::hadMonster(const Monster &monster)
{
    for (int i = 0; i < this->monsters.size(); ++i)
    {
        if (monster == this->monsters[i])
        {
            return true;
        }
    }
    return false;
}
// 该修仙者移除指定妖兽
bool Immortal::removeMonster(const Monster &monster)
{
    // vector<>移除某个元素的小技巧
    std::vector<Monster>::iterator it = this->monsters.begin();
    while (it != monsters.end())
    {
        if (monster == (*it))
        {
            it = this->monsters.erase(it);
            return true;
        }
        else
        {
            it++;
        }
    }
    return false;
}

// 打印修仙者的信息
std::ostream &operator<<(std::ostream &os, const Immortal &immortal)
{
    os << "[修仙者]:" << immortal.name
       << (immortal.alive ? "[在修]" : "[已亡]")
       << "\t门派:" << immortal.menPai
       << "\t级别:" << immortal.level;
    SpriteStone stone;
    // std::cout << " 输出时的灵石组数:" << immortal.stones.size() << std::endl;
    for (int i = 0; i < immortal.stones.size(); i++)
    {
        // std::cout << "第" << i << "组的灵石数:" << immortal.stones[i] << std::endl;
        stone = stone + immortal.stones[i];
    }
    os << "\t灵石:折合" << stone;

    os << "\t妖兽:";
    if (immortal.monsters.size() == 0)
    {
        os << "无";
    }
    else
    {
        for (int i = 0; i < immortal.monsters.size(); i++)
        {
            os << immortal.monsters[i]
               << " ";
        }
    }
    return os;
}
// 重载<<,输出修仙级别
std::ostream &operator<<(std::ostream &os, const ImmortalLevel &level)
{
    switch (level)
    {
    case ImmortalLevel::LIAN_QI:
        os << "练气期";
        break;
    case ImmortalLevel::ZHU_JI:
        os << "筑基期";
        break;
    case ImmortalLevel::JIE_DAN:
        os << "结丹期";
        break;
    case ImmortalLevel::YUAN_YING:
        os << "元婴期";
        break;
    case ImmortalLevel::HUA_SHENG:
        os << "化神期";
        break;
    case ImmortalLevel::LIAN_XU:
        os << "炼虚期";
        break;
    case ImmortalLevel::HE_TI:
        os << "合体期";
        break;
    case ImmortalLevel::DA_CHENG:
        os << "大乘期";
        break;
    case ImmortalLevel::DU_JIE:
        os << "渡劫期";
        break;
    }
    return os;
}
