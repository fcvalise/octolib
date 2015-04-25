#include "PaletteEditor.hpp"
#include "ColorEditor.hpp"
#include "PaletteModel.hpp"
#include "ColorItemDelegate.hpp"

#include <QTableView>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QHeaderView>
#include <QFileDialog>

PaletteEditor::PaletteEditor(QWidget *parent) :
    QWidget(parent),
    m_paletteModel(new PaletteModel(this)),
    m_paletteView(new QTableView),
    m_controlFrame(new QFrame),
    m_colorEditor(new ColorEditor)

{
    setup();
    setupControls();
}

PaletteEditor::~PaletteEditor()
{
}

void PaletteEditor::newPalette()
{
    m_paletteModel->clear();
}

void PaletteEditor::setup()
{
    QHBoxLayout*    layout = new QHBoxLayout(this);

    m_paletteView->setItemDelegate(new ColorItemDelegate(this));
    m_paletteView->setModel(m_paletteModel);
    m_paletteView->horizontalHeader()->setStretchLastSection(true);
    m_paletteView->horizontalHeader()->hide();
    connect(m_paletteView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
    connect(m_colorEditor, SIGNAL(colorChanged(QColor)), SLOT(onColorEdited(QColor)));
    layout->addWidget(m_paletteView, 2);
    layout->addWidget(m_controlFrame);
    layout->addWidget(m_colorEditor, 2);
}

void PaletteEditor::setupControls()
{
    QVBoxLayout*    layout = new QVBoxLayout(m_controlFrame);
    QPushButton*    addColor = new QPushButton(tr("Add color"));
    QPushButton*    removeColor = new QPushButton(tr("Remove color"));
    QPushButton*    savePalette = new QPushButton(tr("Save palette..."));
    QPushButton*    loadPalette = new QPushButton(tr("Load palette..."));

    connect(addColor, SIGNAL(clicked()), this, SLOT(addColor()));
    connect(removeColor, SIGNAL(clicked()), this, SLOT(removeCurrent()));
    connect(savePalette, SIGNAL(clicked()), this, SLOT(savePalette()));
    connect(loadPalette, SIGNAL(clicked()), this, SLOT(loadPalette()));
    layout->addWidget(addColor);
    layout->addWidget(removeColor);
    layout->addWidget(savePalette);
    layout->addWidget(loadPalette);
    layout->setSpacing(3);
    layout->addStretch(500);
}

void PaletteEditor::addColor()
{
    static int  s_hue = 0;
    QModelIndex index = m_paletteModel->addColor(QColor::fromHsv(s_hue, 255, 255));

    // Generate a color
    m_paletteView->setCurrentIndex(index);
    s_hue += 20;
    if (s_hue >= 360)
        s_hue -= 360;
}

void PaletteEditor::removeCurrent()
{
    int currentRow = m_paletteView->currentIndex().row();

    m_paletteModel->removeColor(m_paletteView->currentIndex());
    // Reselect current item
    if (currentRow >= m_paletteModel->rowCount(QModelIndex()))
        currentRow = m_paletteModel->rowCount(QModelIndex()) - 1;
    m_paletteView->setCurrentIndex(m_paletteModel->index(currentRow));
}

void PaletteEditor::onCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    m_colorEditor->setColor(m_paletteModel->getColor(current));
}

void PaletteEditor::onColorEdited(QColor color)
{
    m_paletteModel->setColor(m_paletteView->currentIndex(), color);
}

void PaletteEditor::savePalette()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save palette"), "", "Palette (*.opa)");

    if (path.isEmpty() == false)
    {
        m_paletteModel->saveToFile(path);
    }
}

void PaletteEditor::loadPalette()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open palette"), "", "Palette (*.opa)");

    if (path.isEmpty() == false)
    {
        m_paletteModel->loadFromFile(path);
    }
}
