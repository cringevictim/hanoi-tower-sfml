#include "handle.h"

void handle_game_button_clicks(sf::RenderWindow& window, const sf::Event& event, std::vector<std::stack<Disk>>& pegs, bool &is_holding_disk, int &num_disks, bool &show_menu, bool &game_won) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    if (mouse_pos.x >= 45 && mouse_pos.x <= 260) {
        if (mouse_pos.y >= 450 && mouse_pos.y <= 470) { // "Tip"
            log("[Auto] button was triggered");
            if (!is_holding_disk && pegs[0].size() == num_disks) autoSolve(pegs, num_disks);
        }
        else if (mouse_pos.y >= 480 && mouse_pos.y <= 500) { // "Auto"
            log("[Back] button was triggered");
            show_menu = true;
            game_won = false;
            reset_game(pegs, is_holding_disk, num_disks);
        }
    }
}

void handle_menu_clicks(sf::RenderWindow& window, const sf::Event& event, std::vector<std::stack<Disk>>& pegs, int& num_disks, bool& show_menu, bool& game_won, bool &is_holding_disk) {
    if (!show_menu) return;

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int start_x = 310, start_y = 210;
    int height = 50;
    for (int i = 0; i < 2; ++i) {
        if (mouse_pos.x >= start_x && mouse_pos.x <= start_x + 180 &&
            mouse_pos.y >= start_y + i * height && mouse_pos.y <= start_y + (i + 1) * height) {
            switch (i) {
            case 0: // Start
                log("[Start] button was triggered");
                game_won = false;
                show_menu = false;
                reset_game(pegs, is_holding_disk, num_disks);
                break;
            case 1: // Exit
                log("[Exit] button was triggered");
                window.close();
                break;
            }
        }
    }


    if (mouse_pos.x >= start_x && mouse_pos.x <= start_x + 180) {
        if (mouse_pos.y >= 360 && mouse_pos.y <= 410) { // "+ Disks"
            if (num_disks < 6) num_disks++;
            log("[+ Disks] button was triggered");
        }
        else if (mouse_pos.y >= 410 && mouse_pos.y <= 460) { // "- Disks"
            if (num_disks > 3) num_disks--;
            log("[- Disks] button was triggered");
        }
    }
}