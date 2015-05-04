#ifndef SQUAREOFFSETDIALOG_HPP
#define SQUAREOFFSETDIALOG_HPP

#include <QDialog>

namespace Ui
{
    class SquareOffsetDialog;
}

class WheelModel;
class PaletteModel;

class SquareOffsetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SquareOffsetDialog(QWidget *parent = 0);
    ~SquareOffsetDialog();

    void    addOffsets(WheelModel* model);
    void    addColors(PaletteModel *model);
private slots:
    void    setHue(int hue);
    void    updateModel();
private:
    Ui::SquareOffsetDialog  *ui;
    WheelModel*             m_model;
};

#endif // SQUAREOFFSETDIALOG_HPP
