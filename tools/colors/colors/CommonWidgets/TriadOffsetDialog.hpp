#ifndef TRIADOFFSETDIALOG_HPP
#define TRIADOFFSETDIALOG_HPP

#include <QDialog>

namespace Ui
{
    class TriadOffsetDialog;
}

class WheelModel;
class PaletteModel;

class TriadOffsetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TriadOffsetDialog(QWidget *parent = 0);
    ~TriadOffsetDialog();

    void    addOffsets(WheelModel* model);
    void    addColors(PaletteModel *model);
private slots:
    void    setHue(int hue);
    void    updateModel();
private:
    Ui::TriadOffsetDialog   *ui;
    WheelModel*             m_model;
};

#endif // TRIADOFFSETDIALOG_HPP
