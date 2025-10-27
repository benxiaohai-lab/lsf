#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <cstring>

// 命名空间：避免与其他模块命名冲突
namespace MineSweeperNS 
{

class MineSweeper 
{
private:
    // 私有属性：游戏核心数据（仅类内部可访问，隐藏实现细节）
    int map[10][10];       // 雷区地图：0=无雷，1=有雷
    int show[10][10];      // 显示状态：0=未显示，1~8=周围雷数，9=已显示空白
    int row;               // 雷区行数（固定10）
    int column;            // 雷区列数（固定10）
    int mineCount;         // 总雷数（固定10）
    bool isGameOver;       // 游戏是否结束
    bool isWin;            // 游戏是否胜利

    // 私有方法：内部辅助逻辑（仅类内部调用）
    // 计算指定坐标周围的雷数
    int countSurroundMines(int x, int y);
    // 深度优先展开空白区域
    void dfsExpand(int x, int y);

public:
    // 公有接口：外部可调用的核心功能
    // 构造函数：初始化游戏默认参数
    MineSweeper();
    // 初始化游戏（重置地图、雷分布、游戏状态）
    void initGame();
    // 点击指定坐标（处理玩家操作）
    void clickGrid(int x, int y);
    // 显示当前雷区状态
    void showMap();
    // 获取游戏结束状态
    bool getIsGameOver() const;
    // 获取游戏胜利状态
    bool getIsWin() const;
};

} // namespace MineSweeperNS

#endif // MINESWEEPER_H
#include "MineSweeper.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;
using namespace MineSweeperNS;

// 构造函数：初始化雷区尺寸、雷数及默认状态
MineSweeper::MineSweeper() 
{
    row = 10;
    column = 10;
    mineCount = 10;
    isGameOver = false;
    isWin = false;
    // 初始化地图数组（避免随机值干扰）
    memset(map, 0, sizeof(map));
    memset(show, 0, sizeof(show));
}

// 初始化游戏：重置状态+随机生成雷区
void MineSweeper::initGame() 
{
    isGameOver = false;
    isWin = false;
    memset(map, 0, sizeof(map));
    memset(show, 0, sizeof(show));

    // 随机分布雷（确保雷不重复）
    srand(static_cast<unsigned int>(time(NULL)));
    int placedMines = 0;
    while (placedMines < mineCount) 
	{
        int x = rand() % row;    // 0~9行（对应玩家输入1~10）
        int y = rand() % column; // 0~9列（对应玩家输入1~10）
        if (map[x][y] != 1) 
		{    
		// 该位置无雷时才放置
            map[x][y] = 1;
            placedMines++;
        }
    }
}

// 私有方法：计算(x,y)周围8个方向的雷数
int MineSweeper::countSurroundMines(int x, int y) 
{
    int count = 0;
    // 遍历周围8个方向（行偏移-1~1，列偏移-1~1）
    for (int i = -1; i <= 1; i++) 
	{
        for (int j = -1; j <= 1; j++) 
		{
            int nx = x + i; // 新行坐标
            int ny = y + j; // 新列坐标
            // 确保坐标在雷区范围内
            if (nx >= 0 && nx < row && ny >= 0 && ny < column)
			{
                count += map[nx][ny]; // 累加雷数（1=有雷，0=无雷）
            }
        }
    }
    return count;
}

// 私有方法：DFS展开空白区域（周围无雷时递归展开）
void MineSweeper::dfsExpand(int x, int y) 
{
    // 终止条件：坐标越界 或 已显示 或 是雷（避免重复处理）
    if (x < 0 || x >= row || y < 0 || y >= column || show[x][y] != 0)
	{
        return;
    }

    int surroundMines = countSurroundMines(x, y);
    show[x][y] = surroundMines + 1; // 1~8=雷数，9=空白（surroundMines=0时+1=1？此处保持原逻辑）

    // 周围无雷时，递归展开所有相邻格子
    if (surroundMines == 0) 
	{
        for (int i = -1; i <= 1; i++) 
		{
            for (int j = -1; j <= 1; j++) 
			{
                dfsExpand(x + i, y + j);
            }
        }
    }
}

// 公有方法：处理玩家点击坐标（x,y为玩家输入的1~10）
void MineSweeper::clickGrid(int x, int y) 
{
    // 转换为代码中的0~9索引
    x--;
    y--;

    // 合法性校验：坐标越界
    if (x < 0 || x >= row || y < 0 || y >= column) 
	{
        cout << "坐标错误！请输入1~10的整数。" << endl;
        return;
    }

    // 合法性校验：坐标已显示
    if (show[x][y] != 0) {
        cout << "该坐标已显示，请重新选择！" << endl;
        return;
    }

    // 游戏失败：点击到雷
    if (map[x][y] == 1) {
        cout << "游戏失败！你踩到雷了！" << endl;
        isGameOver = true;
        return;
    }

    // 正常点击：展开空白区域
    dfsExpand(x, y);

    // 判断游戏胜利：已显示区域 = 总区域 - 雷数
    int shownCount = 0;
    for (int i = 0; i < row; i++) 
	{
        for (int j = 0; j < column; j++) 
		{
            if (show[i][j] != 0) 
			{
                shownCount++;
            }
        }
    }
    if (shownCount == row * column - mineCount) 
	{
        cout << "游戏胜利！你成功排除所有雷！" << endl;
        isWin = true;
        isGameOver = true;
    }
}
// 公有方法：获取游戏结束状态（只读）
bool MineSweeper::getIsGameOver() const 
{
    return isGameOver;
}

// 公有方法：获取游戏胜利状态（只读）
bool MineSweeper::getIsWin() const 
{
    return isWin;
}
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