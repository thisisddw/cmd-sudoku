#include <stdio.h>
#include <time.h>
#include "parseopt.h"
#include "myio.h"
#include <gtest/gtest.h>

int sudoku_main(int argc, char *argv[])
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
    exit(-1);
}

extern int optind;

namespace {
    TEST(SUDOKU_TEST, GENERATE_C)
    {
        auto sudoku_list = generate_c(10);
        for(const auto &s: sudoku_list)
            EXPECT_TRUE(s.is_valid() && s.is_full());
    }
    TEST(SUDOKU_TEST, GENERATE_N)
    {
        auto sudoku_list = generate_n(10);
        for(const auto &s: sudoku_list)
            EXPECT_TRUE(s.is_valid() && !s.is_full());
    }
    TEST(SUDOKU_TEST, GENERATE_R)
    {
        auto sudoku_list = generate_r(10, 30, 60);
        for(const auto &s: sudoku_list)
            EXPECT_TRUE(s.is_valid() && (81 - s.count()) >= 30 && (81 - s.count()) <= 60);
    }
    TEST(SUDOKU_TEST, GENERATE_U)
    {
        auto sudoku_list = generate_u(10);
        for(const auto &s: sudoku_list)
            EXPECT_TRUE(s.is_valid() && solve(s, 2).size() == 1);
    }
    TEST(SUDOKU_TEST, SOLVE)
    {
        auto sudoku_list = generate_n(10);
        for(const auto &s: sudoku_list)
        {
            auto t = solve(s, 1).back();
            EXPECT_TRUE(s.is_valid() && t.is_full() && t.is_valid());
        }
    }

    TEST(ARGUMENTS_TEST, GENERATE)
    {
        char *arg1[] = { (char *)"shudu", (char *)"-c", (char *)"100" };
        optind = 1;
        parse_options(3, arg1);
        EXPECT_TRUE(arguments.flags == Arguments::C_FLAG && arguments.number == 100);

        char *arg2[] = { (char *)"shudu", (char *)"-n", (char *)"10", (char *)"-u" };
        optind = 1;
        parse_options(4, arg2);
        EXPECT_TRUE((arguments.flags == (Arguments::N_FLAG | Arguments::U_FLAG)) && arguments.number == 10);
        
        char *arg3[] = { (char *)"shudu", (char *)"-n", (char *)"1", (char *)"-r", (char *)"12~34" };
        optind = 1;
        parse_options(5, arg3);
        EXPECT_TRUE((arguments.flags == (Arguments::N_FLAG | Arguments::R_FLAG)) && arguments.number == 1 &&
            arguments.r1 == 12 && arguments.r2 == 34);
    }
    TEST(ARGUMENTS_TEST, SOLVE)
    {
        char *arg1[] = { (char *)"shudu", (char *)"-s", (char *)"file_name" };
        optind = 1;
        parse_options(3, arg1);
        EXPECT_TRUE(arguments.flags == Arguments::S_FLAG && !strcmp(arguments.input_file, "file_name"));
    }

    TEST(ARGUMENTS_TEST, MISSING_ARG)
    {
        char *arg1[] = { (char *)"shudu", (char *)"-c" };
        optind = 1;
        EXPECT_EXIT(parse_options(2, arg1), ::testing::ExitedWithCode(-1), ".*");
    }
    TEST(ARGUMENTS_TEST, EXTRA_ARG)
    {
        char *arg1[] = { (char *)"shudu", (char *)"-c", (char *)"10", (char *)"extra_arg" };
        optind = 1;
        EXPECT_EXIT(parse_options(4, arg1), ::testing::ExitedWithCode(-1), ".*");
    }
    TEST(ARGUMENTS_TEST, BAD_COMBO1)
    {
        char *arg1[] = { (char *)"shudu", (char *)"-c", (char *)"10", (char *)"-u" };
        optind = 1;
        EXPECT_EXIT(sudoku_main(4, arg1), ::testing::ExitedWithCode(-1), ".*");
    }
    TEST(ARGUMENTS_TEST, BAD_COMBO2)
    {
        char *arg1[] = { (char *)"shudu", (char *)"-n", (char *)"10", (char *)"-m", (char *)"1", (char *)"-u" };
        optind = 1;
        EXPECT_EXIT(sudoku_main(6, arg1), ::testing::ExitedWithCode(-1), ".*");
    }
}