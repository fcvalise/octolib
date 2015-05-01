#ifndef OFFSETEDITOR_HPP
#define OFFSETEDITOR_HPP

#include <QWidget>

#include "HueOffset.hpp"

class QDataWidgetMapper;
class SpinBoxSlider;

class OffsetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit OffsetEditor(QWidget *parent = 0);
    ~OffsetEditor();

    HueOffset   getOffset()const;
public slots:
    void        setOffset(HueOffset const& offset);
private slots:
    void        emitOffsetChanged();
signals:
    void        offsetChanged(HueOffset const&);
private:
    QDataWidgetMapper*  m_mapper;
    SpinBoxSlider*      m_offset;
    SpinBoxSlider*      m_saturation;
    SpinBoxSlider*      m_value;
    SpinBoxSlider*      m_alpha;
};

#endif // OFFSETEDITOR_HPP
