#include "myio.h"
#include <assert.h>
#include <algorithm>

void to_screen(std::vector<Sudoku> *list)
{
    // print to screen
    for(const auto &s: *list)
        printf("%s\n", s.to_pretty_string().c_str());
}

void to_file(std::vector<Sudoku> *list, const char *file)
{
    // print to game.txt
    if(std::freopen(file, "w", stdout)) 
    {
        for(const auto &s: *list)
            std::printf("%s\n", s.to_string().c_str());
        std::fclose(stdout);
    }
    else
    {
        printf("print to file error!\n");
    }
}