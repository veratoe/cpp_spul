#include "slider.h"
#include <iostream>

Slider::Slider(int x, int y, int width, int height, 
    guiStyle containerBaseStyle, guiStyle containerHoverStyle, 
    guiStyle dialBaseStyle, guiStyle dialHoverStyle, function< void(float) > onChange
    ) {

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->baseElement = new sf::RectangleShape(sf::Vector2f(width, height));
    this->baseElement->setPosition(x, y);

    this->dial = new sf::RectangleShape(sf::Vector2f((width - 2 * containerBaseStyle.thickness) / 2, height - 2 * containerBaseStyle.thickness));
    this->dial->setPosition(x + containerBaseStyle.thickness, y + containerBaseStyle.thickness);

    this->containerBaseStyle = containerBaseStyle;
    this->containerHoverStyle = containerHoverStyle;
    this->dialBaseStyle = dialBaseStyle;
    this->dialHoverStyle = dialHoverStyle;
    this->text = text;

    this->onChange = onChange;

    applyBaseStyle();
}

Slider::~Slider() {
}

void Slider::applyBaseStyle() {

    this->baseElement->setFillColor(sf::Color(containerBaseStyle.fillColor));
    this->baseElement->setOutlineColor(sf::Color(containerBaseStyle.outlineColor));
    this->baseElement->setOutlineThickness(containerBaseStyle.thickness);

    this->dial->setFillColor(sf::Color(dialBaseStyle.fillColor));
    this->dial->setOutlineColor(sf::Color(dialBaseStyle.outlineColor));
    this->dial->setOutlineThickness(dialBaseStyle.thickness);
}

void Slider::applyHoverStyle() {
    this->baseElement->setFillColor(sf::Color(containerHoverStyle.fillColor));
    this->baseElement->setOutlineColor(sf::Color(containerHoverStyle.outlineColor));
    this->baseElement->setOutlineThickness(containerHoverStyle.thickness);

    this->dial->setFillColor(sf::Color(dialHoverStyle.fillColor));
    this->dial->setOutlineColor(sf::Color(dialHoverStyle.outlineColor));
    this->dial->setOutlineThickness(dialHoverStyle.thickness);
}

void Slider::set(float value) {
    setDial(value * width);
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(*baseElement);
    window.draw(*dial);
}

void Slider::setDial(int value) {
    if (value < 0) value = 0;
    if (value > width) value = width;
    dial->setSize(sf::Vector2f( value, height - 2 * containerBaseStyle.thickness));
    onChange((float) value / width);
}

void Slider::onClick(sf::Event& event) {
    int value = event.mouseButton.x - baseElement->getGlobalBounds().left;
    setDial(value);
}

void Slider::onDrag(sf::Event& event) {
    int value = event.mouseMove.x - baseElement->getGlobalBounds().left;
    setDial(value);
}
