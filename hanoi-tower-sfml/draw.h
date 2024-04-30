#pragma once
#include <SFML\Graphics.hpp>
#include "disk.h"


void draw(sf::RenderWindow& window, std::vector<std::stack<Disk>>& pegs, bool is_holding_disk, Disk& held_disk, bool show_menu, int num_disks, sf::Font font);
void draw_menu(sf::RenderWindow& window, bool& show_menu, int& num_disks, sf::Font font);
void add_game_buttons(sf::RenderWindow& window);
sf::Text create_text(const std::string& str, sf::Font font, int font_size, float x, float y);