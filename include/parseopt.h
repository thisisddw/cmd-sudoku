struct Arguments {
    int number;
    int level;
    int r1, r2;
    char input_file[128];
    char output_file[128];
    int flags;
    
    enum {C_FLAG = 1, S_FLAG = 2, N_FLAG = 4, M_FLAG = 8, R_FLAG = 16, U_FLAG = 32, O_FLAG = 64, X_FLAG = 128};
};

extern Arguments arguments;

void parse_options(int argc, char *argv[]);