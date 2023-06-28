#include "sudoku.h"
#include <assert.h>
#include <algorithm>

using std::vector;

int Sudoku::count() const
{
    int cnt = 0;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(data[i][j])
                cnt++;
    return cnt;
}

bool Sudoku::is_full() const
{
    return count() == 81;
}

static bool row[9][10], col[9][10], block[3][3][10];
bool Sudoku::is_valid() const
{
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(block, 0, sizeof(block));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            if(!data[i][j]) continue;
            if(row[i][data[i][j]]) return false;
            if(col[j][data[i][j]]) return false;
            if(block[i / 3][j / 3][data[i][j]]) return false;
            row[i][data[i][j]] = true;
            col[j][data[i][j]] = true;
            block[i / 3][j / 3][data[i][j]] = true;
        }
    return true;
}

std::string Sudoku::to_string() const
{
    char buf[81 + 9 + 1] = {};
    int ptr = 0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            buf[ptr++] = data[i][j] ? '0' + data[i][j] : '$';
        buf[ptr++] = '\n';
    }
    return std::string(buf);
}

std::string Sudoku::to_pretty_string() const
{
    char buf[800];
    int ptr = 0;
    sprintf(buf + ptr, "    1   2   3   4   5   6   7   8   9  \n"); ptr += 40;
    for(int i = 0; i < 9; i++)
    {
        sprintf(buf + ptr, "  +---+---+---+---+---+---+---+---+---+"); ptr += 39;
        sprintf(buf + ptr, "\n%d |", i + 1); ptr += 4;
        for(int j = 0; j < 9; j++)
            sprintf(buf + ptr, " %c |", data[i][j] ? '0' + data[i][j] : ' '), ptr += 4;
        buf[ptr++] = '\n';
    }
    sprintf(buf + ptr, "  +---+---+---+---+---+---+---+---+---+");
    return std::string(buf);
}

bool Sudoku::read_sudo()
{
    char sudo_char;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            sudo_char = std::getchar();
            if((sudo_char <= '9' && sudo_char >= '1') || sudo_char == '$')
            {
                if(sudo_char == '$')
                    data[i][j] = 0;
                else
                    data[i][j] = sudo_char - '0';
                
            }
            else
                return 0;
        }
        std::getchar();
    }
    std::getchar();
    return 1;
}

void get_stats(const Sudoku &s)
{
    if(!s.is_valid())
    {    
        printf("invalid:\n%s", s.to_string().c_str());
        assert(0);
    }
}
vector<int> get_candidates(const Sudoku &s, int x, int y)
{
    assert(!s[x][y]);
    get_stats(s);
    bool invalid[10] = {};
    for(int i = 1; i <= 9; i++)
        invalid[i] = row[x][i] || col[y][i] || block[x/3][y/3][i];
    vector<int> ret;
    for(int i = 1; i <= 9; i++)
        if(!invalid[i])
            ret.push_back(i);
    return ret;
}

vector<Sudoku> solve(const Sudoku &s, int n)
{
    assert(n > 0);

    if(s.is_full())
        return vector<Sudoku>({s});
    
    int x = -1, y = -1;
    vector<int> candidates;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            if(s[i][j]) continue;
            vector<int> ret = get_candidates(s, i, j);
            if(x == -1 || candidates.size() > ret.size())
                x = i, y = j, candidates = ret;
        }
    
    vector<Sudoku> ans_list;
    std::random_shuffle(candidates.begin(), candidates.end());
    for(int val: candidates)
    {
        if(!n) break;

        Sudoku tmp = s;
        tmp.set(x, y, val);
        auto ret = solve(tmp, n);
        n -= ret.size();
        ans_list.insert(ans_list.end(), ret.begin(), ret.end());
    }
    return ans_list;
}

/**
 * @brief 从s上挖r个空
*/
Sudoku drop_r(Sudoku s, int r)
{
    assert(r <= s.count());

    std::vector<int> pos_list;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(s[i][j])
                pos_list.push_back(i*9 + j);
    
    std::random_shuffle(pos_list.begin(), pos_list.end());
    for(int i = 0; i < r; i++)
        s.set(pos_list[i] / 9, pos_list[i] % 9, 0);
    
    return s;
}

vector<Sudoku> generate_c(int n)
{
    vector<Sudoku> ans;
    while(n--) ans.push_back(solve(Sudoku()).back());
    return ans;
}

vector<Sudoku> generate_n(int n)
{
    return generate_r(n, 20, 50);
}

vector<Sudoku> generate_m(int n, int m)
{
    vector<Sudoku> list;
    switch (m)
    {
    case 1:
        list = generate_r(n, 1, 20);
        break;
    case 2:
        list = generate_r(n, 21, 40);
        break;
    case 3:
        list = generate_r(n, 41, 60);
        break;
    default:
        break;
    }
    return list;
}

vector<Sudoku> generate_r(int n, int r1, int r2)
{
    assert(r1 <= r2);

    auto s_list = generate_c(n);
    for(int i = 0; i < n; i++)
        s_list[i] = drop_r(s_list[i], r1 + rand() % (r2 - r1 + 1));
    return s_list;
}

vector<Sudoku> generate_u(int n)
{
    vector<Sudoku> uniq_sudokus;
    for(int i = 0; i < n; i++)
    {
        int drops = 54;
        auto list = generate_r(1, drops, drops + 10);
        auto s_list = solve(list[0], 2);
        while (s_list.size() > 1)
        {
            drops = std::max(drops - 2, 12);
            list = generate_r(1, drops, drops + 10);
            s_list = solve(list[0], 2);
        }
        uniq_sudokus.push_back(list[0]);
    }
    return uniq_sudokus;
}