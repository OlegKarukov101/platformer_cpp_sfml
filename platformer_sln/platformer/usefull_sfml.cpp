#pragma once
#include "usefull_sfml.h"

RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position) {
    RectangleShape shape(size);
    shape.setFillColor(color);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(position);
    return shape;
}
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position, float OutlineThikness, Color ColorOutlineThikness) {
    RectangleShape shape(size);
    shape.setFillColor(color);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(position);
    shape.setOutlineThickness(OutlineThikness);
    shape.setOutlineColor(ColorOutlineThikness);
    return shape;
}
CircleShape InitialCircleShape(float radius, Color color, Vector2f position) {
    CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    return shape;
}
CircleShape InitialCircleShape(float radius, Color color, Vector2f position, float OutlineThikness, Color ColorOutlineThikness) {
    CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setOutlineThickness(OutlineThikness);
    shape.setOutlineColor(ColorOutlineThikness);
    return shape;
}
Text InitialText(Text text, Vector2f position, Color TextColor, float OutlineThikness, Color OutlineColor) {
    Text text_(text);
    text_.setPosition(position);
    text_.setFillColor(TextColor);
    text_.setOutlineThickness(OutlineThikness);
    text_.setOutlineColor(OutlineColor);
    return text_;
}