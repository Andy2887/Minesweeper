//
// Created by yuanliheng on 4/12/24.
//

#include "textObject.h"
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

sf::Text createTextObject(sf::Font font, string content, int size, sf::Color color, bool isBold,
                          bool isUnderlined){
    sf::Text result;
    result.setFont(font);
    result.setString(content);
    result.setCharacterSize(size);
    result.setFillColor(color);
    if (isBold){
        result.setStyle(sf::Text::Bold);
    }
    if (isUnderlined){
        result.setStyle(sf::Text::Underlined);
    }
    return result;
}

