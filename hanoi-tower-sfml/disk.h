#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <random>

struct Disk {
    sf::RectangleShape rect;
    int size;
};

std::vector<std::stack<Disk>> initialize_pegs(int num_disks);
Disk create_disk(int size, std::mt19937& gen, std::uniform_int_distribution<>& distrib);
bool check_win_condition(const std::vector<std::stack<Disk>>& pegs, int num_disks);
