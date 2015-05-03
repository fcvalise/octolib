#ifndef COMPLEMENTARYOFFSETDIALOG_HPP
#define COMPLEMENTARYOFFSETDIALOG_HPP

#include <QDialog>

namespace Ui
{
    class ComplementaryOffsetDialog;
}

class WheelModel;

class ComplementaryOffsetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComplementaryOffsetDialog(QWidget *parent = 0);
    ~ComplementaryOffsetDialog();

    void    addOffsets(WheelModel* model);
private slots:
    void    setHue(int hue);
    void    updateModel();
private:
    Ui::ComplementaryOffsetDialog   *ui;
    WheelModel*                     m_model;
};

#endif // COMPLEMENTARYOFFSETDIALOG_HPP
