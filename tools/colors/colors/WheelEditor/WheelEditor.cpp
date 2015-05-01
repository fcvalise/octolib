#include "WheelEditor.hpp"
#include "WheelModel.hpp"

#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <ColorItemDelegate.hpp>

WheelEditor::WheelEditor(QWidget *parent) :
    QWidget(parent),
    m_wheelModel(new WheelModel(this)),
    m_wheelView(new QTableView)
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

void WheelEditor::addOffsets(quint16 initial, qint16 interval, int count)
{
    qint16  current = initial;

    for (int i = 0; i < count; ++i)
    {
        if (current > -360 && current < 360)
        {
            addOffset(current);
        }
        current += interval;
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

    m_wheelView->setItemDelegateForColumn(WheelModel::ComputedColor, new ColorItemDelegate(this));
    m_wheelView->setModel(m_wheelModel);
    m_wheelView->horizontalHeader()->setStretchLastSection(true);
    m_wheelView->horizontalHeader()->hide();
    m_wheelView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_wheelView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(m_wheelView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
    layout->addWidget(m_wheelView, 2);
}

void WheelEditor::onCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    /*if (current.isValid())
    {
        m_colorEditor->setEnabled(true);
        m_colorEditor->setColor(m_paletteModel->getColor(current));
    }
    else
    {
        m_colorEditor->setEnabled(false);
        m_colorEditor->setColor(QColor(0, 0, 0, 0));
    }*/
    emit selectionChanged();
}

