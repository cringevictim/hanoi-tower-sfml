#pragma once
#include <SFML/Graphics.hpp>
#include "disk.h"

Disk held_disk;

void reset_game(std::vector<std::stack<Disk>>& pegs, bool& is_holding_disk, int& num_disks);
bool check_win_condition(std::vector<std::stack<Disk>>& pegs, int& num_disks);

void moveDisk(int n, int from_peg, int to_peg, int aux_peg, std::vector<std::stack<Disk>>& pegs_local);
void autoSolve(std::vector<std::stack<Disk>>& pegs, int& num_disks);


