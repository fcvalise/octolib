#include "WheelEditor.hpp"
#include "OffsetEditor.hpp"
#include "AnaloguousOffsetDialog.hpp"
#include "ComplementaryOffsetDialog.hpp"
#include "TriadOffsetDialog.hpp"
#include "SquareOffsetDialog.hpp"

#include <SpinBoxSlider.hpp>
#include <ColorItemDelegate.hpp>
#include <WheelModel.hpp>

#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QFormLayout>

WheelEditor::WheelEditor(QWidget *parent) :
    QWidget(parent),
    m_wheelModel(new WheelModel(this)),
    m_wheelView(new QTableView),
    m_offsetEditor(new OffsetEditor),
    m_hue(new SpinBoxSlider(0, 359, this))
{
    setup();
}

WheelEditor::~WheelEditor()
{
}

void WheelEditor::newWheel()
{
    m_wheelModel->removeAll();
    m_wheelModel->setHue(0);
    m_offsetEditor->setEnabled(false);
}

void WheelEditor::saveWheel(const QString &filePath)
{
    m_wheelModel->saveToFile(filePath);
}

void WheelEditor::openWheel(const QString &filePath)
{
    m_wheelModel->loadFromFile(filePath);
    emit modified();
}

void WheelEditor::addOffset(quint16 offset)
{
    m_wheelModel->addOffset(offset);
    emit modified();
}

void WheelEditor::addAnaloguous(QWidget *parent)
{
    AnaloguousOffsetDialog  dialog(parent);

    if (dialog.exec() == QDialog::Accepted)
    {
        dialog.addOffsets(m_wheelModel);
        emit modified();
    }
}

void WheelEditor::addComplementaries(QWidget *parent)
{
    ComplementaryOffsetDialog  dialog(parent);

    if (dialog.exec() == QDialog::Accepted)
    {
        dialog.addOffsets(m_wheelModel);
        emit modified();
    }
}

void WheelEditor::addTriad(QWidget *parent)
{
    TriadOffsetDialog  dialog(parent);

    if (dialog.exec() == QDialog::Accepted)
    {
        dialog.addOffsets(m_wheelModel);
        emit modified();
    }
}

void WheelEditor::addSquare(QWidget* parent)
{
    SquareOffsetDialog  dialog(parent);

    if (dialog.exec() == QDialog::Accepted)
    {
        dialog.addOffsets(m_wheelModel);
        emit modified();
    }
}

void WheelEditor::removeCurrent()
{
    int currentRow = m_wheelView->currentIndex().row();

    m_wheelModel->removeOffset(m_wheelView->currentIndex());
    // Reselect current item
    if (currentRow >= m_wheelModel->rowCount(QModelIndex()))
        currentRow = m_wheelModel->rowCount(QModelIndex()) - 1;
    m_wheelView->setCurrentIndex(m_wheelModel->index(currentRow, 0));
    emit modified();
}

void WheelEditor::removeAll()
{
    m_wheelModel->removeAll();
    emit modified();
}

bool WheelEditor::hasSelection() const
{
    return (m_wheelView->currentIndex().isValid());
}

bool WheelEditor::isEmpty() const
{
    return (m_wheelModel->rowCount() > 0);
}

void WheelEditor::setup()
{
    QHBoxLayout*    layout = new QHBoxLayout(this);
    QFormLayout*    hueLayout = new QFormLayout;
    QVBoxLayout*    controlLayout = new QVBoxLayout;

    m_wheelView->setItemDelegateForColumn(WheelModel::ComputedColor, new ColorItemDelegate(this));
    m_wheelView->setModel(m_wheelModel);
    m_wheelView->horizontalHeader()->setStretchLastSection(true);
    m_wheelView->horizontalHeader()->hide();
    m_wheelView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_wheelView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(m_wheelView->selectionModel(), &QItemSelectionModel::currentChanged, this, &WheelEditor::onCurrentChanged);
    connect(m_offsetEditor, &OffsetEditor::offsetChanged, this, &WheelEditor::onOffsetEdited);
    connect(m_hue, &SpinBoxSlider::valueChanged, m_wheelModel, &WheelModel::setHue);
    connect(m_hue, &SpinBoxSlider::valueChanged, [this](int){emit modified();});
    layout->addWidget(m_wheelView, 2);
    layout->addLayout(controlLayout);
    hueLayout->addRow(tr("Hue:"), m_hue);
    controlLayout->addWidget(m_offsetEditor);
    controlLayout->addLayout(hueLayout);
    m_offsetEditor->setEnabled(false);
}

void WheelEditor::onCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    if (current.isValid())
    {
        m_offsetEditor->setEnabled(true);
        m_offsetEditor->setOffset(m_wheelModel->getOffset(current));
    }
    else
    {
        m_offsetEditor->setEnabled(false);
        m_offsetEditor->setOffset(HueOffset(0, 0, 0, 0));
    }
    emit selectionChanged();
}

void WheelEditor::onOffsetEdited(HueOffset const& offset)
{
    m_wheelModel->setOffset(m_wheelView->currentIndex(), offset);
    emit modified();
}
