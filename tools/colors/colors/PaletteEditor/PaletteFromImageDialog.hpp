#ifndef PALETTEFROMIMAGEDIALOG_HPP
#define PALETTEFROMIMAGEDIALOG_HPP

#include <QDialog>

namespace Ui
{
    class PaletteFromImageDialog;
}

class PaletteModel;

class PaletteFromImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaletteFromImageDialog(QWidget *parent = 0);
    ~PaletteFromImageDialog();

    void    addColors(PaletteModel* model);
public slots:
    virtual int exec();
private slots:
    void    loadImage();
    void    setColorCount(int count);
private:
    Ui::PaletteFromImageDialog *ui;
};



#endif // PALETTEFROMIMAGEDIALOG_HPP
