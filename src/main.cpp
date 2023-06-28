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

        // print to screen
        for(const auto &s: list)
            printf("%s\n", s.to_pretty_string().c_str());
        // print to ending.txt
        if(std::freopen("../ending.txt", "w", stdout)) 
        {
            for(const auto &s: list)
                std::printf("%s\n", s.to_string().c_str());
            std::fclose(stdout);
        }
        else
        {
            printf("print to file error!\n");
        }
    }
    if(arguments.flags & Arguments::S_FLAG)
    {
        if(arguments.flags != Arguments::S_FLAG)
            goto ARG_ERR;

        
    }
    if(arguments.flags & Arguments::N_FLAG)
    {
        if(arguments.flags == Arguments::N_FLAG)
        {
            auto list = generate_n(arguments.number);

            // print to screen
            for(const auto &s: list)
                printf("%s\n", s.to_pretty_string().c_str());
            
            // print to game.txt
            if(std::freopen("../game.txt", "w", stdout)) 
            {
                for(const auto &s: list)
                    std::printf("%s\n", s.to_string().c_str());
                std::fclose(stdout);
            }
            else
            {
                printf("print to file error!\n");
            }
        }
    }


    return 0;

ARG_ERR:
    fprintf(stderr, "Wrong arguments\n");
    return -1;
}