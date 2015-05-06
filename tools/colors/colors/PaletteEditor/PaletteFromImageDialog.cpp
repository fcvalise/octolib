#include "PaletteFromImageDialog.hpp"
#include "ui_PaletteFromImageDialog.h"

#include <ColorItemDelegate.hpp>
#include <PaletteModel.hpp>
#include <QFileDialog>
#include <QImageReader>

PaletteFromImageDialog::PaletteFromImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaletteFromImageDialog)
{
    ui->setupUi(this);

    ui->listView->setModel(ui->graphicsView->paletteModel());
    ui->listView->setItemDelegate(new ColorItemDelegate(this));
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    ui->colorsCountSpinBox->setDisabled(true);
    connect(ui->colorsCountSpinBox, SIGNAL(valueChanged(int)), SLOT(setColorCount(int)));
}

PaletteFromImageDialog::~PaletteFromImageDialog()
{
    delete ui;
}

void PaletteFromImageDialog::addColors(PaletteModel *model)
{
    PaletteModel*   paletteModel = ui->graphicsView->paletteModel();

    for (int i = 0; i < paletteModel->rowCount(); ++i)
    {
        model->addColor(paletteModel->getColor(paletteModel->index(i)));
    }
}

void PaletteFromImageDialog::loadImage()
{
    QString         filePath = QFileDialog::getOpenFileName(this, tr("Choose an image"), "", tr("Images (*.png *.jpg *.jpeg)"));
    QPixmap         pixmap;

    ui->colorsCountSpinBox->setDisabled(true);
    if (filePath.isEmpty())
        return;
    if (pixmap.load(filePath) == false)
        return;
    ui->graphicsView->setImage(pixmap);
    ui->colorsCountSpinBox->setEnabled(true);
}

void PaletteFromImageDialog::setColorCount(int count)
{
    ui->graphicsView->setColorCount(count);
}

int PaletteFromImageDialog::exec()
{
    show();
    loadImage();
    return (QDialog::exec());
}
