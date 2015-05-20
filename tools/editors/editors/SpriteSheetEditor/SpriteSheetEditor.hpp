#ifndef SPRITESHEETEDITOR_HPP
#define SPRITESHEETEDITOR_HPP

#include <QWidget>
#include <ByteArray.hpp>

class SpriteSheetView;
class RectangleModel;
class RectangleListView;
class TileControlWidget;
class TilePreview;

class QPixmap;
class QListView;
class QModelIndex;

class SpriteSheetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteSheetEditor(QWidget *parent = 0);
    ~SpriteSheetEditor();

    void            newSpriteSheet(QString const& textureFilePath);
    bool            openSpriteSheet(QString const& filePath);
    bool            saveSpriteSheet(QString const& filePath) const;

    void            deleteCurrentRectangle();
    void            deleteAllRectangles();
    void            sortRectangles();
    void            generateRectangles(QWidget* parent);

    void            zoomIn();
    void            zoomOut();
    void            zoomZero();
    void            zoomToFit();

    bool            hasSelection()const;
    QList<QAction*> commandActions()const;
signals:
    void            selectionChanged();
    void            modified();
private slots:
    void            onCurrentChanged(const QModelIndex&, const QModelIndex&);
    void            updateTilePreview();
private:
    void            setup();
private:
    SpriteSheetView*    m_spriteSheetView;
    RectangleListView*  m_rectangleView;
    TileControlWidget*  m_tileControl;
    TilePreview*        m_tilePreview;

    octo::ByteArray     m_textureBytes; // Hold raw datas of the texture for saving
};

#endif // SPRITESHEETEDITOR_HPP
