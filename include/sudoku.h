#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <vector>

class Sudoku {
    int data[9][9];

    static inline void check_val(int val) { assert(val >= 0 && val <= 9); } 
    static inline void check_range(int x, int y)
    {
        assert(x >= 0 && x < 9 && y >= 0 && y < 9);
    }

public:
    Sudoku()
    {
        memset(data, 0, sizeof(data));
    }
    int *operator [](const int row) const { return (int *)data[row]; }
    int get(int x, int y) const { check_range(x, y); return data[x][y]; }
    void set(int x, int y, int val) { check_range(x, y); check_val(val); data[x][y] = val; }
    bool read_sudo();

    bool is_valid() const;
    int count() const;
    bool is_full() const;
    std::string to_string() const;
    std::string to_pretty_string() const;
};

/**
 * @brief 求解数独
 * @param s 要求解的数独
 * @param n 最多返回多少个解
*/
std::vector<Sudoku> solve(const Sudoku &s, int n = 1);

/**
 * @brief 生成n个满的数独
*/
std::vector<Sudoku> generate_c(int n);

/**
 * @brief 生成n个有空缺的数独
*/
std::vector<Sudoku> generate_n(int n);

/**
 * @brief 生成n个难度等级为m的数独
*/
std::vector<Sudoku> generate_m(int n, int m);

/**
 * @brief 生成n个有空缺的数独
 * @param r1 最小空缺数
 * @param r2 最大空缺数
*/
std::vector<Sudoku> generate_r(int n, int r1, int r2);

/**
 * @brief 生成n个解唯一的数独
*/
std::vector<Sudoku> generate_u(int n);
