#ifndef SPRITESHEETVIEW_HPP
#define SPRITESHEETVIEW_HPP
#include <QGraphicsView>

class SpriteSheetScene;

class SpriteSheetView : public QGraphicsView
{
public:
    SpriteSheetView(QWidget* parent = nullptr);
    ~SpriteSheetView();

    void    newSpriteSheet(QPixmap const& pixmap);
private:
    SpriteSheetScene*   m_scene;
};

#endif // SPRITESHEETVIEW_HPP
