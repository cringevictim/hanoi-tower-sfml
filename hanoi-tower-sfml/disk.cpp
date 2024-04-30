#include "disk.h"

std::vector<std::stack<Disk>> initialize_pegs(int num_disks, std::mt19937& gen, std::uniform_int_distribution<>& distrib) {
    std::vector<std::stack<Disk>> pegs(3);
    for (int i = num_disks; i > 0; --i) {
        pegs[0].push(create_disk(i, gen, distrib));
    }
    return pegs;
}

Disk create_disk(int size, std::mt19937& gen, std::uniform_int_distribution<>& distrib) {
    Disk d;
    d.size = size;
    d.rect.setSize(sf::Vector2f(20.f * size, 20.f));
    d.rect.setFillColor(sf::Color(distrib(gen), distrib(gen), distrib(gen)));
    d.rect.setOrigin(d.rect.getSize().x / 2, d.rect.getSize().y / 2);
    return d;
}

bool check_win_condition(const std::vector<std::stack<Disk>>& pegs, int num_disks) {
    return pegs[0].empty() && pegs[1].empty() && pegs[2].size() == num_disks;
}
