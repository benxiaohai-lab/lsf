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