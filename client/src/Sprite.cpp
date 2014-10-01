#include <GL/gl.h>
#include "Sprite.hpp"

Sprite::Sprite(Vector2d position, Vector2d vector, int life)
{
    _isAlive = true;
    _position = position;
    _vector = vector;
    _life = life;
}

void Sprite::Update()
{
    --_life;
    _position += _vector;
}

void Sprite::Draw()
{
    glPushMatrix();
        glTranslatef(_position.X(), _position.Y(), 0.0);
        glBegin(GL_POINTS);
            glVertex2f(0.0, 0.0);
        glEnd();
    glPopMatrix();
}
