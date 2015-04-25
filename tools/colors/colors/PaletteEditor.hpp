#ifndef PALETTEEDITOR_HPP
#define PALETTEEDITOR_HPP

#include <QWidget>

class PaletteModel;
class ColorEditor;

class QTableView;
class QFrame;
class QModelIndex;

class PaletteEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PaletteEditor(QWidget *parent = 0);
    ~PaletteEditor();
public slots:
    void    newPalette();
    void    savePalette();
    void    loadPalette();
private:
    void    setup();
    void    setupControls();
private slots:
    void    addColor();
    void    removeCurrent();
    void    onCurrentChanged(const QModelIndex& current, const QModelIndex&);
    void    onColorEdited(QColor color);
private:
    PaletteModel*   m_paletteModel;
    QTableView*     m_paletteView;
    QFrame*         m_controlFrame;
    ColorEditor*    m_colorEditor;
};

#endif // PALETTEEDITOR_HPP
