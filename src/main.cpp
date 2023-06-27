#include <stdio.h>
#include "sudoku.h"

int main()
{
    auto list = generate_n(1);
    for(const auto &s: list)
        printf("%s\n", s.to_pretty_string().c_str());

    return 0;
}