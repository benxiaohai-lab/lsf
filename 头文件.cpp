// MineSweeper.h（头文件）
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <cstring>
namespace MineSweeperNS {

class MineSweeper {
private:
    int map[10][10];
    int show[10][10];
    int row;
    int column;
    int mineCount;
    bool isGameOver;
    bool isWin;

    int countSurroundMines(int x, int y);
    void dfsExpand(int x, int y);

public:
    MineSweeper();
    void initGame();
    void clickGrid(int x, int y);
    void showMap(); // 声明showMap
    bool getIsGameOver() const;
    bool getIsWin() const;
};

} // namespace MineSweeperNS

#endif // MINESWEEPER_H