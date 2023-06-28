#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "parseopt.h"

int main(int argc, char *argv[])
{
    extern Arguments arguments;
    parse_options(argc, argv);
    // printf("flags: %d\n", arguments.flags);

    srand(time(NULL));

    if(arguments.flags & Arguments::C_FLAG)
    {
        if (arguments.flags != Arguments::C_FLAG)
            goto ARG_ERR;

        auto list = generate_c(arguments.number);
        for(const auto &s: list)
            printf("%s\n", s.to_pretty_string().c_str());
    }


    return 0;

ARG_ERR:
    fprintf(stderr, "Wrong arguments\n");
    return -1;
}