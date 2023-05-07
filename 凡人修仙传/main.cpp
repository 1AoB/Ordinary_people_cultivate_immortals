#include "SpriteStone.h"
#include "Monster.h"
#include "Immortal.h"
#include <iostream>

using namespace std;

void testSpriteStone()
{
    SpriteStone stone(100, SpriteStoneLevel::MIDDLE_LEVEL);
    cout << stone << endl;
}

void testMonster()
{
    Monster monster(5, "蛟龙");
    cout << monster << endl;
}

void testImmortal()
{
    Immortal wxn("Wxn", "c++", ImmortalLevel::LIAN_QI);
    std::cout << wxn << endl;
    // std::cout << "挖矿前:" << wxn.getStonesSize() << "块灵石===========================" << endl;
    //  挖矿
    for (int i = 0; i < 50; i++) // 50*100
    {
        wxn.mining();
    }
    std::cout << wxn << endl;
    // std::cout << "挖矿后:" << wxn.getStonesSize() << "块灵石===========================" << endl;

    Monster monster(1, "蛟龙");
    wxn.fight(monster);
    std::cout << "捕获" << monster << "之后:" << endl;
    std::cout << wxn << endl;
    Monster monster2(1, "蜘蛛");
    wxn.fight(monster2);
    std::cout << "捕获" << monster2 << "之后:" << endl;
    std::cout << wxn << endl;
    Monster monster3(1, "壁虎");
    wxn.fight(monster3);
    std::cout << "捕获" << monster3 << "之后:" << endl;
    std::cout << wxn << endl;

    // 贸易
    wxn.trade(monster2); // 注:1级妖兽100块初阶灵石
    std::cout << "售卖" << monster2 << "之后:" << endl;
    std::cout << wxn << endl;
    // std::cout << "售卖后:" << wxn.getStonesSize() << "块灵石===========================" << endl;
    //  售卖所有妖兽
    wxn.trade();
    std::cout << "售卖所有妖兽之后:" << endl;
    std::cout << wxn << endl;
    // std::cout << "售卖后:" << wxn.getStonesSize() << "块灵石" << endl;

    // 向指定修仙者购买妖兽
    Immortal hanli("韩立", "黄枫谷", ImmortalLevel::JIE_DAN);
    std::cout << hanli << std::endl;
    Monster monster4(2, "青龙");
    hanli.fight(monster4);
    std::cout << hanli << std::endl;

    wxn.trade(hanli, monster4); // wxn向韩立买青龙妖兽
    std::cout << "wxn向韩立买青龙妖兽后" << std::endl;
    std::cout << wxn << std::endl;
    std::cout << hanli << std::endl;

    std::cout << "--------------------------" << std::endl;
    // 用自己指定的妖兽,来换其他修仙者的指定妖兽
    Monster monster5(1, "天蚕");
    hanli.fight(monster5);
    std::cout << "韩立捕获" << monster5 << std::endl;
    std::cout << hanli << std::endl;

    bool flag = wxn.trade(monster4, hanli, monster5); // wxn用自己的青龙妖兽和韩立换天蚕妖兽
    std::cout << "wxn用自己的青龙妖兽和韩立换天蚕妖兽:" << (flag == true ? "交换成功" : "交换失败") << std::endl;
    std::cout << wxn << std::endl;
    std::cout << hanli << std::endl;
    // 把自己的妖兽售卖给其他修仙者,以换取灵石bool trade(const Monster &monster, Immortal &other);
    flag = hanli.trade(monster4, wxn); // 韩立又把青龙妖兽卖给wxn
    std::cout << "韩立又把青龙妖兽卖给wxn:" << (flag == true ? "交换成功" : "交换失败") << std::endl;
    std::cout << wxn << std::endl;
    std::cout << hanli << std::endl;
    std::cout << "-------渡劫升级-------------" << std::endl;
    // bool Immortal::getUp();
    wxn.getUp();

    cout << "wxn去挖矿,为下一次渡劫做准备..." << endl;
    for (int i = 0; i < 50; i++) // 50*100
    {
        wxn.mining();
    }
    std::cout << wxn << endl;
    wxn.getUp();
    std::cout << "-------生死斗-------------" << std::endl;
    // 生死斗:修仙者之间进行比武  +夺取对方灵石 + 夺取对方妖兽
    // bool fightPeo(Immortal &other);
    wxn.fightPeo(hanli);
    std::cout << wxn << std::endl;
    std::cout << hanli << std::endl;

    cout << "wxn去挖矿,闭关修炼..." << endl;
    for (int i = 0; i < 5000; i++) // 50*100
    {
        wxn.mining();
    }
    std::cout << wxn << endl;
    for (int i = 0; i < 7; i++)
    {
        wxn.getUp();
    }
}
int main()
{
    testSpriteStone();
    testMonster();
    testImmortal();
    return 0;
}
// 编译的bash命令:
//  g++ -std=c++11 main.cpp SpriteStone.cpp Monster.cpp Immortal.cpp