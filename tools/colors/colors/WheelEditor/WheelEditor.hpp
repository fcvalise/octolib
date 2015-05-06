#ifndef COLORWHEELEDITOR_HPP
#define COLORWHEELEDITOR_HPP

#include <QWidget>

class WheelModel;
class OffsetEditor;
class HueOffset;
class SpinBoxSlider;

class QTableView;
class QModelIndex;

class WheelEditor : public QWidget
{
    Q_OBJECT
public:
    explicit WheelEditor(QWidget *parent = 0);
    ~WheelEditor();

public slots:
    void    newWheel();
    void    saveWheel(QString const& filePath);
    void    openWheel(QString const& filePath);

    void    addOffset(quint16 offset = 0);
    void    addAnaloguous(QWidget* parent);
    void    addComplementaries(QWidget* parent);
    void    addTriad(QWidget* parent);
    void    addSquare(QWidget *parent);

    void    removeCurrent();
    void    removeAll();
    bool    hasSelection()const;
    bool    isEmpty()const;
private:
    void    setup();
private slots:
    void    onCurrentChanged(const QModelIndex& current, const QModelIndex&);
    void    onOffsetEdited(const HueOffset &offset);
signals:
    void    modified();
    void    selectionChanged();
private:
    WheelModel*     m_wheelModel;
    QTableView*     m_wheelView;
    OffsetEditor*   m_offsetEditor;
    SpinBoxSlider*  m_hue;
};

#endif // COLORWHEELEDITOR_HPP
