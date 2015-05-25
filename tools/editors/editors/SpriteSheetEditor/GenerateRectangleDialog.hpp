#ifndef GENERATERECTANGLEDIALOG_HPP
#define GENERATERECTANGLEDIALOG_HPP

#include <QDialog>

class SpriteSheetView;

class QSpinBox;

class GenerateRectangleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GenerateRectangleDialog(const QPixmap &texture, QWidget* parent = nullptr);
    ~GenerateRectangleDialog();

    int     widthSubDivCount()const;
    int     heightSubDivCount()const;
protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void showEvent(QShowEvent *);
private slots:
    void    regenerate();
private:
    SpriteSheetView*    m_view;
    QSpinBox*           m_widthSubDiv;
    QSpinBox*           m_heightSubDiv;
};

#endif // GENERATERECTANGLEDIALOG_HPP
