

#ifndef MINESWEEPER_TEXTOBJECT_H
#define MINESWEEPER_TEXTOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

void setText(sf::Text &text, float x, float y);
sf::Text createTextObject(sf::Font font, string content, int size, sf::Color color, bool isBold,
                          bool isUnderlined);


#endif //MINESWEEPER_TEXTOBJECT_H
