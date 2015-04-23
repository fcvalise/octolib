#ifndef RGBACOLOREDITOR_HPP
#define RGBACOLOREDITOR_HPP

#include "AbstractColorEditor.hpp"
#include "SpinBoxSlider.hpp"

class RgbaColorEditor : public AbstractColorEditor
{
    Q_OBJECT
public:
    explicit RgbaColorEditor(QWidget *parent);
    ~RgbaColorEditor();

    virtual void    setColor(QColor color);
    virtual QColor  getColor() const;
private:
    void    setup();
private slots:
    void    emitColorChanged();
private:
    SpinBoxSlider*   m_red;
    SpinBoxSlider*   m_green;
    SpinBoxSlider*   m_blue;
    SpinBoxSlider*   m_alpha;
};

#endif // RGBACOLOREDITOR_HPP
