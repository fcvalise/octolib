#ifndef SPINBOXSLIDER_HPP
#define SPINBOXSLIDER_HPP

#include <QWidget>

class QLabel;
class QSlider;
class QSpinBox;
class QDoubleSpinBox;

class SpinBoxSlider : public QWidget
{
    Q_OBJECT
public:
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER true)

    explicit SpinBoxSlider(QWidget *parent = 0);
    SpinBoxSlider(int min, int max, QWidget *parent = 0);
    ~SpinBoxSlider();

    int     value()const;
signals:
    void    valueChanged(int value);
public slots:
    void    setValue(int value);
    void    setMinimum(int value);
    void    setMaximum(int value);
private slots:
    void    onSliderChanged(int value);
    void    onSpinBoxChanged(int value);
private:
    QLabel*     m_label;
    QSlider*    m_slider;
    QSpinBox*   m_spinBox;
    int         m_value;
    int         m_min;
    int         m_max;
};


#endif // SPINBOXSLIDER_HPP
