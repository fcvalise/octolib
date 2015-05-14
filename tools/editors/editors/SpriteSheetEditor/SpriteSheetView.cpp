#include "SpriteSheetView.hpp"
#include "SpriteSheetScene.hpp"

SpriteSheetView::SpriteSheetView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new SpriteSheetScene(this))
{
    setScene(m_scene);
}

SpriteSheetView::~SpriteSheetView()
{

}

void SpriteSheetView::newSpriteSheet(const QPixmap &pixmap)
{
    m_scene->setTexture(pixmap);
}

