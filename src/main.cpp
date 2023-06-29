#include <stdio.h>
#include <time.h>
#include "parseopt.h"
#include "myio.h"

int main(int argc, char *argv[])
{
    extern Arguments arguments;
    parse_options(argc, argv);
    // printf("flags: %d\n", arguments.flags);

    srand(time(NULL));

    char out_file[128] = "../game.txt";
    if(arguments.flags & Arguments::O_FLAG)
    {
        memccpy(out_file, arguments.output_file, 0, sizeof(out_file));
        arguments.flags ^= Arguments::O_FLAG;
    }

    bool screen = 1;
    if(arguments.flags & Arguments::X_FLAG)
    {
        screen = 0;
        arguments.flags ^= Arguments::X_FLAG;
    }

    if(arguments.flags & Arguments::C_FLAG)
    {
        if (arguments.flags != Arguments::C_FLAG)
            goto ARG_ERR;

        auto list = generate_c(arguments.number);

        if(screen)
            to_screen(&list);
        
        to_file(&list, out_file);
    }
    else if(arguments.flags & Arguments::S_FLAG)
    {
        if(arguments.flags != Arguments::S_FLAG)
            goto ARG_ERR;

        if(std::freopen(arguments.input_file, "r", stdin)) 
        {
            Sudoku sudo;
            int sudo_num = 0;
            while (sudo.read_sudo())
            {
                sudo_num ++;
                auto solve_list = solve(sudo, 100);

                // print to screen
                if(screen)
                {
                    printf("the %dth game:\n", sudo_num);
                    for(const auto &s: solve_list)
                        printf("%s\n", s.to_pretty_string().c_str());
                    printf("\n\n");
                }
                // print to sudoku.txt
                char *out_file = new char[100];
                sprintf(out_file, "../sudoku%d.txt", sudo_num);
                if(std::freopen(out_file, "w", stdout))
                {
                    for(const auto &s: solve_list)
                        std::printf("%s\n", s.to_string().c_str());
                    std::fclose(stdout);
                    freopen("CON", "w", stdout);
                }
                else
                {
                    printf("print to file error!\n");
                }
            }
            std::fclose(stdin);
        }
        else
        {
            printf("open file error!\n");
        }
        
    }
    else if(arguments.flags & Arguments::N_FLAG)
    {
        if(arguments.flags == Arguments::N_FLAG)
        {
            auto list = generate_n(arguments.number);

            if(screen)
                to_screen(&list);
        
            to_file(&list, out_file);
        }
        else if(arguments.flags == (Arguments::M_FLAG | Arguments::N_FLAG))
        {
            if(arguments.level < 1 || arguments.level > 3)
                goto ARG_ERR;

            auto list = generate_m(arguments.number, arguments.level);

            if(screen)
                to_screen(&list);
        
            to_file(&list, out_file);
        }
        else if(arguments.flags == (Arguments::R_FLAG | Arguments::N_FLAG))
        {
            auto list = generate_r(arguments.number, arguments.r1, arguments.r2);

            if(screen)
                to_screen(&list);
        
            to_file(&list, out_file);
        }
        else if(arguments.flags == (Arguments::U_FLAG | Arguments::N_FLAG))
        {
            auto list = generate_u(arguments.number);

            if(screen)
                to_screen(&list);
        
            to_file(&list, out_file);
        }
        else
            goto ARG_ERR;
    }
    else
    {
        goto ARG_ERR;
    }

    return 0;

ARG_ERR:
    fprintf(stderr, "Wrong arguments\n");
    return -1;
}