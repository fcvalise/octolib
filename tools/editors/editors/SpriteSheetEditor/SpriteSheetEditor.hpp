#ifndef SPRITESHEETEDITOR_HPP
#define SPRITESHEETEDITOR_HPP

#include <QWidget>

class SpriteSheetView;

class QPixmap;

class SpriteSheetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteSheetEditor(QWidget *parent = 0);
    ~SpriteSheetEditor();

    void    newSpriteSheet(const QPixmap &pixmap);
    void    openSpriteSheet(QString const& filePath);
    void    saveSpriteSheet(QString const& filePath);

signals:
    void    selectionChanged();
    void    modified();
private:
    SpriteSheetView*    m_spriteSheetView;
};

#endif // SPRITESHEETEDITOR_HPP
