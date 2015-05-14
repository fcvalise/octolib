#ifndef SPRITESHEETSCENE_HPP
#define SPRITESHEETSCENE_HPP
#include <QGraphicsScene>

class QGraphicsPixmapItem;

class SpriteSheetScene : public QGraphicsScene
{
public:
    SpriteSheetScene(QObject* parent = nullptr);
    ~SpriteSheetScene();

    void    setTexture(QPixmap const& pixmap);
private:
    QGraphicsPixmapItem*    m_texture;
};

#endif // SPRITESHEETSCENE_HPP
