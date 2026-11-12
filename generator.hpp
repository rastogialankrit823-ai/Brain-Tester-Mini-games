#pragma once
#include "solver.hpp"
#include <random>
#include <chrono>
#include <mutex>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum Difficulty { EASY = 1, MEDIUM = 2, HARD = 3 };

class RandomGen {
    std::mt19937 rng;
    std::mutex mtx;
public:
    RandomGen() {
        rng.seed(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    }
    int nextInt(int low, int high) {
        std::lock_guard<std::mutex> lk(mtx);
        std::uniform_int_distribution<int> dist(low, high);
        return dist(rng);
    }
    std::mt19937& engine() { return rng; }
    std::mutex& getMutex() { return mtx; }
};

struct KeyHunterPuzzle {
    int R, C, K;
    std::vector<std::string> grid;
    int optimalSteps;
};

struct DungeonPuzzle {
    int R, C;
    std::vector<std::vector<int>> grid;
    int optimalMinHP;
};

struct DualRobotPuzzle {
    int R, C;
    std::vector<std::vector<int>> grid;
    int optimalLoot;
};

struct CherryPuzzle {
    int N;
    std::vector<std::vector<int>> grid;
    int optimalCherries;
};

struct PermutationPuzzle {
    int N;
    std::vector<std::vector<int>> board;
    int optimalMoves;
};

struct SudokuPuzzle {
    std::vector<std::vector<int>> puzzle;
    std::vector<std::vector<int>> solution;
};

class Generator {
    RandomGen randGen;
    Solver solver;
public:
    KeyHunterPuzzle generateKeyHunter(Difficulty diff) {
        int R = (diff == EASY) ? 3 : (diff == MEDIUM ? 4 : 5);
        int C = (diff == EASY) ? 4 : (diff == MEDIUM ? 5 : 6);
        int K = (diff == EASY) ? 2 : (diff == MEDIUM ? 3 : 4);
        while (true) {
            std::vector<std::string> grid(R, std::string(C, '.'));
            grid[0][0] = '@';
            int walls = (R * C) / 5;
            for (int i = 0; i < walls; i++) {
                int r = randGen.nextInt(0, R - 1);
                int c = randGen.nextInt(0, C - 1);
                if (grid[r][c] == '.') grid[r][c] = '#';
            }
            for (int k = 0; k < K; k++) {
                while (true) {
                    int r = randGen.nextInt(0, R - 1);
                    int c = randGen.nextInt(0, C - 1);
                    if (grid[r][c] == '.') {
                        grid[r][c] = 'a' + k;
                        break;
                    }
                }
                while (true) {
                    int r = randGen.nextInt(0, R - 1);
                    int c = randGen.nextInt(0, C - 1);
                    if (grid[r][c] == '.') {
                        grid[r][c] = 'A' + k;
                        break;
                    }
                }
            }
            int opt = solver.solveKeyHunter(grid, K);
            if (opt != -1) return {R, C, K, grid, opt};
        }
    }

    DungeonPuzzle generateDungeon(Difficulty diff) {
        int R = (diff == EASY) ? 4 : (diff == MEDIUM ? 5 : 6);
        int C = R;
        std::vector<std::vector<int>> grid(R, std::vector<int>(C));
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (randGen.nextInt(1, 100) <= 65)
                    grid[r][c] = -randGen.nextInt(2, 15);
                else
                    grid[r][c] = randGen.nextInt(2, 10);
            }
        }
        grid[0][0] = -randGen.nextInt(1, 5);
        grid[R - 1][C - 1] = -randGen.nextInt(5, 15);
        return {R, C, grid, solver.solveDungeonSurvival(grid)};
    }

    DualRobotPuzzle generateDualRobot(Difficulty diff) {
        int R = (diff == EASY) ? 4 : (diff == MEDIUM ? 5 : 6);
        int C = R;
        std::vector<std::vector<int>> grid(R, std::vector<int>(C));
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                grid[r][c] = randGen.nextInt(1, 20);
            }
        }
        return {R, C, grid, solver.solveDualRobot(grid)};
    }

    CherryPuzzle generateCherryExpedition(Difficulty diff) {
        int N = (diff == EASY) ? 4 : (diff == MEDIUM ? 5 : 6);
        while (true) {
            std::vector<std::vector<int>> grid(N, std::vector<int>(N, 0));
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    int roll = randGen.nextInt(1, 100);
                    if (roll <= 20) grid[r][c] = -1;
                    else if (roll <= 65) grid[r][c] = 1;
                    else grid[r][c] = 0;
                }
            }
            grid[0][0] = 0;
            grid[N - 1][N - 1] = 0;
            int opt = solver.solveCherryExpedition(grid);
            if (opt > 0) return {N, grid, opt};
        }
    }

    PermutationPuzzle generatePermutationPuzzle(Difficulty diff) {
        int N = (diff == EASY) ? 4 : (diff == MEDIUM ? 6 : 8);
        std::vector<std::vector<int>> board(N, std::vector<int>(N));
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                board[r][c] = (r + c) % 2;
            }
        }
        for (int k = 0; k < N * 2; k++) {
            int i = randGen.nextInt(0, N - 1);
            int j = randGen.nextInt(0, N - 1);
            std::swap(board[i], board[j]);
            int c1 = randGen.nextInt(0, N - 1);
            int c2 = randGen.nextInt(0, N - 1);
            for (int r = 0; r < N; r++) std::swap(board[r][c1], board[r][c2]);
        }
        int opt = solver.solveMovesToChessboard(board);
        return {N, board, opt};
    }

    SudokuPuzzle generateSudoku(Difficulty diff) {
        std::vector<std::vector<int>> sol(9, std::vector<int>(9, 0));
        std::function<bool(std::vector<std::vector<int>>&, int, int)> fillBoard = [&](std::vector<std::vector<int>>& b, int r, int c) -> bool {
            if (r == 9) return true;
            if (c == 9) return fillBoard(b, r + 1, 0);
            if (b[r][c] != 0) return fillBoard(b, r, c + 1);
            
            std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            {
                std::lock_guard<std::mutex> lk(randGen.getMutex());
                std::shuffle(nums.begin(), nums.end(), randGen.engine());
            }
            
            for (int num : nums) {
                bool safe = true;
                for (int i = 0; i < 9; i++) {
                    if (b[r][i] == num || b[i][c] == num) {
                        safe = false;
                        break;
                    }
                }
                
                if (safe) {
                    int sr = (r / 3) * 3;
                    int sc = (c / 3) * 3;
                    for (int i = 0; i < 3 && safe; i++) {
                        for (int j = 0; j < 3 && safe; j++) {
                            if (b[sr + i][sc + j] == num) {
                                safe = false;
                            }
                        }
                    }
                }
                
                if (safe) {
                    b[r][c] = num;
                    if (fillBoard(b, r, c + 1)) return true;
                    b[r][c] = 0;
                }
            }
            return false;
        };
        
        fillBoard(sol, 0, 0);
        std::vector<std::vector<int>> puz = sol;
        int removeCount = (diff == EASY) ? 33 : (diff == MEDIUM ? 45 : 54);
        
        while (removeCount > 0) {
            int r = randGen.nextInt(0, 8);
            int c = randGen.nextInt(0, 8);
            if (puz[r][c] != 0) {
                puz[r][c] = 0;
                removeCount--;
            }
        }
        return {puz, sol};
    }

    RandomGen& getRandomGen() { return randGen; }
    Solver& getSolver() { return solver; }
};

inline Generator generator;
inline KeyHunterPuzzle generateKeyHunter(Difficulty diff) { return generator.generateKeyHunter(diff); }
inline DungeonPuzzle generateDungeon(Difficulty diff) { return generator.generateDungeon(diff); }
inline DualRobotPuzzle generateDualRobot(Difficulty diff) { return generator.generateDualRobot(diff); }
inline CherryPuzzle generateCherryExpedition(Difficulty diff) { return generator.generateCherryExpedition(diff); }
inline PermutationPuzzle generatePermutationPuzzle(Difficulty diff) { return generator.generatePermutationPuzzle(diff); }
inline SudokuPuzzle generateSudoku(Difficulty diff) { return generator.generateSudoku(diff); }