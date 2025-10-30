// 源文件（包含实现和main）
#include "MineSweeper.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace MineSweeperNS;

// MineSweeper类方法实现
MineSweeper::MineSweeper() {
    row = 10;
    column = 10;
    mineCount = 10;
    isGameOver = false;
    isWin = false;
    memset(map, 0, sizeof(map));
    memset(show, 0, sizeof(show));
}

void MineSweeper::initGame() {
    isGameOver = false;
    isWin = false;
    memset(map, 0, sizeof(map));
    memset(show, 0, sizeof(show));

    srand(static_cast<unsigned int>(time(NULL)));
    int placedMines = 0;
    while (placedMines < mineCount) {
        int x = rand() % row;
        int y = rand() % column;
        if (map[x][y] != 1) {
            map[x][y] = 1;
            placedMines++;
        }
    }
}

int MineSweeper::countSurroundMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < row && ny >= 0 && ny < column) {
                count += map[nx][ny];
            }
        }
    }
    return count;
}

void MineSweeper::dfsExpand(int x, int y) {
    if (x < 0 || x >= row || y < 0 || y >= column || show[x][y] != 0) {
        return;
    }

    int surroundMines = countSurroundMines(x, y);
    show[x][y] = surroundMines + 1;

    if (surroundMines == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                dfsExpand(x + i, y + j);
            }
        }
    }
}

void MineSweeper::clickGrid(int x, int y) {
    x--;
    y--;

    if (x < 0 || x >= row || y < 0 || y >= column) {
        std::cout << "坐标错误！请输入1~10的整数。" << std::endl
        return;
    }

    if (show[x][y] != 0) {
        std::cout << "该坐标已显示，请重新选择！" << std::endl
        return;
    }

    if (map[x][y] == 1) {
        std::cout << "游戏失败！你踩到雷了！" << std::endl
        isGameOver = true;
        return;
    }

    dfsExpand(x, y);

    int shownCount = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (show[i][j] != 0) {
                shownCount++;
            }
        }
    }
    if (shownCount == row * column - mineCount) {
        std::cout << "游戏胜利！你成功排除所有雷！" << std::endl
        isWin = true;
        isGameOver = true;
    }
}

void MineSweeper::showMap() { // 实现showMap
    std::cout << "  ";
    for (int j = 0; j < column; j++) {
        std::cout << j + 1 << " ";
    }
    std::cout << std::endl

    for (int i = 0; i < row; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < column; j++) {
            if (show[i][j] == 0) {
                std::cout << "* ";
            } else if (show[i][j] == 9) {
                std::cout << "  ";
            } else {
                std::cout << show[i][j] - 1 << " ";
            }
        }
        std::cout << std::endl
    }
}

bool MineSweeper::getIsGameOver() const {
    return isGameOver;
}

bool MineSweeper::getIsWin() const {
    return isWin;
}

// main函数
int main() {
    MineSweeper game;
    int choice;

    std::cout << "===== 扫雷游戏 =====" << std::endl
    while (true) {
        std::cout << "1. 开始游戏" << std::endl
        std::cout << "2. 退出游戏" << std::endl
        std::cout << "请选择（1/2）：";

        while (!(std::cin >> choice)) {
            std::cout << "输入错误！请输入1或2：";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice == 2) {
            break;
        } else if (choice == 1) {
            game.initGame();
            while (!game.getIsGameOver()) {
                game.showMap();
                int x, y;
                std::cout << "请输入坐标（x  y，空格分隔）：";

                while (!(std::cin >> x >> y)) {
                    std::cout << "输入错误！请输入两个整数（1~10）：";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                game.clickGrid(x, y);
            }

            game.showMap();

            if (game.getIsWin()) {
                std::cout << "是否再次尝试？（1.是  2.否）：";
                std::cin >> choice;
                if (choice == 2) {
                    break;
                }
            }
        } else {
            std::cout << "输入错误！请重新选择1或2。" << std::endl
        }
    }

    std::cout << "游戏结束，感谢游玩！" << std::endl
    return 0;
}