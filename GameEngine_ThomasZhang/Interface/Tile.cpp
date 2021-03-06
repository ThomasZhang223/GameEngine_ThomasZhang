#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, bool colliding)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setPosition(x * gridSizeF, y * gridSizeF);
    this->colliding = colliding;
}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(shape);

}

const bool& Tile::getCollision() const
{
    return this->colliding;
}

const sf::Vector2f& Tile::getPosition() const
{
    return this->shape.getPosition();
}

std::string Tile::toString()
{
    std::stringstream stringForm;
    stringForm << this->colliding << " ";
    return stringForm.str();
}
