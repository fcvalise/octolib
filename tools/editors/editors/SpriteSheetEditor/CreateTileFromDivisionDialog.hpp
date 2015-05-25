#ifndef CREATETILEFROMDIVISIONDIALOG_HPP
#define CREATETILEFROMDIVISIONDIALOG_HPP

#include <QDialog>

class QSpinBox;
class QFormLayout;

class SpriteSheetView;
class SpriteSheetModel;

class CreateTileFromDivisionDialog : public QDialog
{
    Q_OBJECT
public:
    CreateTileFromDivisionDialog(SpriteSheetModel const* sourceModel, QWidget* parent = nullptr);
    ~CreateTileFromDivisionDialog();

    QList<QPoint>   positions()const;

protected:
    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent *);
private:
    QSpinBox*       createSpinBox(QString const& label, int min, int max, int current, QFormLayout *layout);
private slots:
    void            updateTiles();
private:
    QRect               m_textureRect;
    SpriteSheetView*    m_view;
    SpriteSheetModel*   m_model;
    QSpinBox*           m_widthDivision;
    QSpinBox*           m_heightDivision;
    QSpinBox*           m_widthOffset;
    QSpinBox*           m_heightOffset;
    QSpinBox*           m_widthInterval;
    QSpinBox*           m_heightInterval;
};

#endif // CREATETILEFROMDIVISIONDIALOG_HPP
