#include "PaletteEditor.hpp"
#include "PaletteFromImageDialog.hpp"

#include <ColorEditor.hpp>
#include <ColorItemDelegate.hpp>
#include <PaletteModel.hpp>

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
    m_colorEditor(new ColorEditor)

{
    setup();
    emit selectionChanged();
}

PaletteEditor::~PaletteEditor()
{
}

void PaletteEditor::newPalette()
{
    m_paletteModel->removeAll();
}

void PaletteEditor::setup()
{
    QHBoxLayout*    layout = new QHBoxLayout(this);

    m_paletteView->setItemDelegate(new ColorItemDelegate(this));
    m_paletteView->setModel(m_paletteModel);
    m_paletteView->horizontalHeader()->setStretchLastSection(true);
    m_paletteView->horizontalHeader()->hide();
    m_paletteView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_paletteView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_colorEditor->setEnabled(false);
    connect(m_paletteView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
    connect(m_colorEditor, SIGNAL(colorChanged(QColor)), SLOT(onColorEdited(QColor)));
    layout->addWidget(m_paletteView, 2);
    layout->addWidget(m_colorEditor);
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
    emit modified();
}

void PaletteEditor::addColorFromImage(QWidget *parent)
{
    PaletteFromImageDialog    dialog(parent);

    if (dialog.exec() == QDialog::Accepted)
    {
        dialog.addColors(m_paletteModel);
    }
}

void PaletteEditor::removeCurrent()
{
    int currentRow = m_paletteView->currentIndex().row();

    m_paletteModel->removeColor(m_paletteView->currentIndex());
    // Reselect current item
    if (currentRow >= m_paletteModel->rowCount(QModelIndex()))
        currentRow = m_paletteModel->rowCount(QModelIndex()) - 1;
    m_paletteView->setCurrentIndex(m_paletteModel->index(currentRow));
    emit modified();

}

void PaletteEditor::removeAll()
{
    m_paletteModel->removeAll();
    emit modified();
}

bool PaletteEditor::hasSelection() const
{
    return (m_paletteView->currentIndex().isValid());
}

bool PaletteEditor::isEmpty() const
{
    return (m_paletteModel->rowCount() > 0);
}

void PaletteEditor::onCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    if (current.isValid())
    {
        m_colorEditor->setEnabled(true);
        m_colorEditor->setColor(m_paletteModel->getColor(current));
    }
    else
    {
        m_colorEditor->setEnabled(false);
        m_colorEditor->setColor(QColor(0, 0, 0, 0));
    }
    emit selectionChanged();
}

void PaletteEditor::onColorEdited(QColor color)
{
    m_paletteModel->setColor(m_paletteView->currentIndex(), color);
    emit modified();
}

void PaletteEditor::savePalette(QString const& filePath)
{
    m_paletteModel->saveToFile(filePath);
}

void PaletteEditor::openPalette(const QString &filePath)
{
    m_paletteModel->loadFromFile(filePath);
    emit modified();
}
