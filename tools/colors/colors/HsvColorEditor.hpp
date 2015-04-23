#ifndef HSVCOLOREDITOR_HPP
#define HSVCOLOREDITOR_HPP

#include "AbstractColorEditor.hpp"

class SpinBoxSlider;

class HsvColorEditor : public AbstractColorEditor
{
    Q_OBJECT
public:
    HsvColorEditor(QWidget* parent= nullptr);
    ~HsvColorEditor();

    virtual void setColor(QColor color);
    virtual QColor getColor() const;
private:
    void    setup();
private slots:
    void    emitColorChanged();
private:
    SpinBoxSlider*   m_hue;
    SpinBoxSlider*   m_saturation;
    SpinBoxSlider*   m_value;
    SpinBoxSlider*   m_alpha;
};

#endif // HSVCOLOREDITOR_HPP
