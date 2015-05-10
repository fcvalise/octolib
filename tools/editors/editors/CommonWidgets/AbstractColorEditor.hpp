#ifndef ABSTRACTCOLOREDITOR_HPP
#define ABSTRACTCOLOREDITOR_HPP

#include <QWidget>

class AbstractColorEditor : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractColorEditor(QWidget *parent = 0);
    ~AbstractColorEditor();

    virtual void    setColor(QColor color) = 0;
    virtual QColor  getColor()const = 0;
signals:
    void            colorChanged(QColor color);
};

#endif // ABSTRACTCOLOREDITOR_HPP
