#include "SpriteSheetScene.hpp"

#include <QGraphicsPixmapItem>

SpriteSheetScene::SpriteSheetScene(QObject *parent) :
    QGraphicsScene(parent),
    m_texture(nullptr)
{
    m_texture = addPixmap(QPixmap());
}

SpriteSheetScene::~SpriteSheetScene()
{
}

void SpriteSheetScene::setTexture(const QPixmap &pixmap)
{
    m_texture->setPixmap(pixmap);
}

