#ifndef ANALOGUOUSOFFSETDIALOG_HPP
#define ANALOGUOUSOFFSETDIALOG_HPP

#include <QDialog>

namespace Ui
{
    class AnaloguousOffsetDialog;
}

class WheelModel;
class PaletteModel;

class AnaloguousOffsetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AnaloguousOffsetDialog(QWidget *parent = 0);
    ~AnaloguousOffsetDialog();

    void    addOffsets(WheelModel* model);
    void    addColors(PaletteModel* model);
private slots:
    void    setHue(int hue);
    void    updateModel();
private:
    Ui::AnaloguousOffsetDialog  *ui;
    WheelModel*                 m_model;
};

#endif // ANALOGUOUSOFFSETDIALOG_HPP
