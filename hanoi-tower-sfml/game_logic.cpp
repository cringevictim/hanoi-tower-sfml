#include "game_logic.h"
#include "draw.h"
#include <iostream>

void reset_game(std::vector<std::stack<Disk>> &pegs, bool &is_holding_disk, int &num_disks, std::mt19937& gen, std::uniform_int_distribution<>& distrib) {
    pegs = std::vector<std::stack<Disk>>(3);
    for (int i = num_disks; i > 0; --i) {
        pegs[0].push(create_disk(i, gen, distrib));
    }
    is_holding_disk = false;
}

bool check_win_condition(std::vector<std::stack<Disk>>& pegs, int& num_disks) {
    return pegs[0].empty() && pegs[1].empty() && pegs[2].size() == num_disks;
}


void moveDisk(int n, int from_peg, int to_peg, int aux_peg, std::vector<std::stack<Disk>>& pegs_local) {
    if (n == 1) {
        std::cout << "Move disk 1 from peg " << from_peg << " to peg " << to_peg << std::endl;
        pegs_local[to_peg].push(pegs_local[from_peg].top());
        pegs_local[from_peg].pop();
        return;
    }
    moveDisk(n - 1, from_peg, aux_peg, to_peg, pegs_local);
    std::cout << "Move disk " << n << " from peg " << from_peg << " to peg " << to_peg << std::endl;
    pegs_local[to_peg].push(pegs_local[from_peg].top());
    pegs_local[from_peg].pop();
    moveDisk(n - 1, aux_peg, to_peg, from_peg, pegs_local);
}

void autoSolve(std::vector<std::stack<Disk>>& pegs, int& num_disks) {
    std::vector<std::stack<Disk>> pegs_local = pegs;
    moveDisk(num_disks, 0, 2, 1, pegs_local);
}




