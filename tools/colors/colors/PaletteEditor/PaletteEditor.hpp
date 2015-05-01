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
    void    savePalette(QString const& filePath);
    void    openPalette(QString const& filePath);

    void    addColor();
    void    removeCurrent();
    void    removeAll();
    bool    hasSelection()const;
    bool    isEmpty()const;
private:
    void    setup();
private slots:
    void    onCurrentChanged(const QModelIndex& current, const QModelIndex&);
    void    onColorEdited(QColor color);
signals:
    void    modified();
    void    selectionChanged();
private:
    PaletteModel*   m_paletteModel;
    QTableView*     m_paletteView;
    ColorEditor*    m_colorEditor;
};

#endif // PALETTEEDITOR_HPP
