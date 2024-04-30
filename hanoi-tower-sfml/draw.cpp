#include "draw.h"


void draw(sf::RenderWindow& window, std::vector<std::stack<Disk>>& pegs, bool is_holding_disk, Disk& held_disk, bool show_menu, int num_disks, sf::Font font) {
    if (show_menu) {
        draw_menu(window, show_menu, num_disks, font);
    }
    else {
        add_game_buttons(window);

        sf::RectangleShape base(sf::Vector2f(410.f, 10.f));
        base.setFillColor(sf::Color::Black);
        base.setPosition(190.f, 350.f);
        window.draw(base);

        for (int i = 0; i < 3; ++i) {
            sf::RectangleShape peg(sf::Vector2f(10.f, 150.f));
            peg.setFillColor(sf::Color::Black);
            peg.setPosition(190.f + i * 200.f, 200.f);
            window.draw(peg);

            std::stack<Disk> temp_stack;
            while (!pegs[i].empty()) {
                temp_stack.push(pegs[i].top());
                pegs[i].pop();
            }

            int count = 0;
            while (!temp_stack.empty()) {
                Disk& d = temp_stack.top();
                d.rect.setPosition(195.f + i * 200.f, 340.f - count * 30.f);
                window.draw(d.rect);
                pegs[i].push(d);
                temp_stack.pop();
                count++;
            }
        }

        if (is_holding_disk) {
            held_disk.rect.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            window.draw(held_disk.rect);
        }
    }

}


void draw_menu(sf::RenderWindow& window, bool &show_menu, int &num_disks, sf::Font font) {
    if (!show_menu) return;

    sf::RectangleShape menu(sf::Vector2f(200.f, 250.f));
    menu.setPosition(300.f, 200.f);
    menu.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(menu);

    sf::RectangleShape disk_control_panel(sf::Vector2f(180.f, 100.f));
    disk_control_panel.setPosition(310.f, 310.f);
    disk_control_panel.setFillColor(sf::Color(100, 100, 100, 150));
    window.draw(disk_control_panel);

    std::string button_labels[] = { "Start", "Exit", "+ Disks", "- Disks" };
    for (int i = 0; i < 2; i++) {
        sf::Text text = create_text(button_labels[i], font, 20, 310.f, 210.f + i * 50);
        window.draw(text);
    }


    sf::Text plus_text = create_text("+ Disks", font, 20, 310.f, 360.f);
    sf::Text minus_text = create_text("- Disks", font, 20, 310.f, 410.f);
    window.draw(plus_text);
    window.draw(minus_text);


    sf::Text disk_count_text = create_text("Disks: " + std::to_string(num_disks), font, 20, 310.f, 310.f);
    window.draw(disk_count_text);
}

sf::Text create_text(const std::string& str, sf::Font font, int font_size, float x, float y) {
    sf::Text text(str, font, font_size);
    text.setPosition(x, y);
    return text;
}

void add_game_buttons(sf::RenderWindow& window, sf::Font font) {
    sf::RectangleShape menu(sf::Vector2f(213.f, 65.f));
    menu.setPosition(45.f, 445.f);
    menu.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(menu);

    std::string buttons[] = { "Auto (Console Output)", "Back" };
    for (int i = 0; i < 2; i++) {
        sf::Text text = create_text(buttons[i], font, 20, 50.f, 450.f + i * 30);
        window.draw(text);
    }
}