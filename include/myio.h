#include <stdio.h>
#include <vector>
#include "sudoku.h"

/**
 * @brief 输出到屏幕
 * @param list 需要输出的数独列表
 */
void to_screen(const std::vector<Sudoku> *list);

/**
 * @brief 输出到文件
 * @param list 需要输出的数独列表
 * @param file 目标文件
 */
void to_file(const std::vector<Sudoku> *list, const char *file);