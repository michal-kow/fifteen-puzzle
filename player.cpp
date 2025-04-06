#include "player.h"

Player::Player(const QString& name, QObject *parent)
    : QObject(parent), name(name)
{
}

QString Player::getName() const {
    return name;
}
