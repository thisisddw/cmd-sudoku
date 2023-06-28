#include "parseopt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Arguments arguments;

void parse_options(int argc, char *argv[])
{
    extern char *optarg;
    extern int optind;
    char opt;
    memset(&arguments, 0, sizeof(Arguments));

    while((opt = getopt(argc, argv, "c:s:n:m:r:u")) != -1)
    {
        switch (opt)
        {
        case 'c':
            arguments.flags |= Arguments::C_FLAG;
            sscanf(optarg, "%d", &arguments.number);
            break;
        case 's':
            arguments.flags |= Arguments::S_FLAG;
            sscanf(optarg, "%s", arguments.input_file);
            break;
        case 'n':
            arguments.flags |= Arguments::N_FLAG;
            sscanf(optarg, "%d", &arguments.number);
            break;
        case 'm':
            arguments.flags |= Arguments::M_FLAG;
            sscanf(optarg, "%d", &arguments.level);
            break;
        case 'r':
            arguments.flags |= Arguments::R_FLAG;
            sscanf(optarg, "%d~%d", &arguments.r1, &arguments.r2);
            break;
        case 'u':
            arguments.flags |= Arguments::U_FLAG;
            break;
        case '?':
        default:
            exit(-1);
            break;
        }
    }
    
    if (optind < argc)
    {
        fprintf(stderr, "unknown argument: %s\n", argv[optind]);
        exit(-1);
    }
}