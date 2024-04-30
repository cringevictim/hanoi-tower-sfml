/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <vector>
#include <random>

#include "utility.h"
#include "disk.h"
#include "draw.h"
#include "game_logic.h"
#include "handle.h"
#include "global.h"

std::vector<std::stack<Disk>> pegs(3);

sf::Font font;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 255);


int num_disks = 4;
int selected_peg = -1;

bool is_holding_disk = false;
bool game_won = false;
bool show_menu = true;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower of Hanoi");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    reset_game(pegs, is_holding_disk, num_disks);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (show_menu) {
                    handle_menu_clicks(window, event, pegs, num_disks, show_menu, game_won, is_holding_disk);
                }
                else {
                    handle_game_button_clicks(window, event, pegs, is_holding_disk, num_disks, show_menu, game_won);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !game_won && !show_menu && event.mouseButton.y < 400) {
                    int x = event.mouseButton.x;
                    int peg_index = (x - 150) / 200;
                    if (peg_index >= 0 && peg_index < 3) {
                        if (!is_holding_disk && !pegs[peg_index].empty()) {
                            held_disk = pegs[peg_index].top();
                            pegs[peg_index].pop();
                            is_holding_disk = true;
                            log_num("Disk was picked up from peg ", peg_index);
                            selected_peg = peg_index;
                        }
                        else if (is_holding_disk) {
                            if (pegs[peg_index].empty() || held_disk.size < pegs[peg_index].top().size) {
                                pegs[peg_index].push(held_disk);
                                log_num("Disk was putt down on peg ", peg_index);
                                is_holding_disk = false;
                                if (check_win_condition(pegs, num_disks)) {
                                    reset_game(pegs, is_holding_disk, num_disks);
                                    game_won = true;
                                    show_menu = true;
                                }
                            }
                            else {
                                pegs[selected_peg].push(held_disk);
                                is_holding_disk = false;
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        draw(window, pegs, is_holding_disk, held_disk, show_menu, num_disks);
        window.display();
    }

    return 0;
}*/