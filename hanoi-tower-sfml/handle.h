#pragma once
#include "utility.h"
#include "game_logic.h"
#include "disk.h"

void handle_game_button_clicks(sf::RenderWindow& window, const sf::Event& event, std::vector<std::stack<Disk>>& pegs, bool& is_holding_disk, int& num_disks, bool& show_menu, bool& game_won);
void handle_menu_clicks(sf::RenderWindow& window, const sf::Event& event, std::vector<std::stack<Disk>>& pegs, int& num_disks, bool& show_menu, bool& game_won, bool& is_holding_disk);
