#include <iostream>
#include <limits>
#include "MineSweeper.h"

using namespace std;
using namespace MineSweeperNS;

int main() 
{
    MineSweeper game; // 创建扫雷游戏对象
    int choice;       // 用户选择（开始/退出/重新游玩）
    cout << "===== 扫雷游戏 =====" << endl;
    while (true) 
	{
        // 主菜单
        cout << "1. 开始游戏" << endl;
        cout << "2. 退出游戏" << endl;
        cout << "请选择（1/2）：";

        // 输入合法性校验：确保输入是整数
        while (!(cin >> choice)) 
		{
            cout << "输入错误！请输入1或2：";
            cin.clear(); // 清除错误状态
            // 忽略缓冲区所有无效字符
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // 处理用户选择
        if (choice == 2) 
		{
            // 退出游戏
            break;
        } else if (choice == 1) 
		{
            // 开始游戏：初始化->循环点击->显示结果
            game.initGame();
            while (!game.getIsGameOver()) 
			{
                game.showMap(); // 显示当前地图
                int x, y;
                cout << "请输入坐标（x  y，空格分隔）：";

                // 坐标输入合法性校验：确保输入是整数
                while (!(cin >> x >> y)) 
				{
                    cout << "输入错误！请输入两个整数（1~10）：";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                game.clickGrid(x, y); // 处理坐标点击
            }

            // 游戏结束：显示最终地图
            game.showMap();

            // 胜利后询问是否重新游玩
            if (game.getIsWin()) 
			{
                cout << "是否再次尝试？（1.是  2.否）：";
                cin >> choice;
                if (choice == 2) 
				{
                    break;
                }
            }
        } else {
            // 选择错误：提示重新输入
            cout << "输入错误！请重新选择1或2。" << endl;
        }
    }

    cout << "游戏结束，感谢游玩！" << endl;
    return 0;
}