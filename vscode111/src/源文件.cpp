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