#include "SpriteSheetEditor.hpp"
#include "SpriteSheetView.hpp"
#include "RectangleModel.hpp"
#include "RectangleListView.hpp"
#include "TileControlWidget.hpp"
#include "GenerateRectangleDialog.hpp"
#include "TilePreview.hpp"

#include <QGridLayout>
#include <QListView>

#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>

#include <fstream>

SpriteSheetEditor::SpriteSheetEditor(QWidget *parent) :
    QWidget(parent),
    m_spriteSheetView(new SpriteSheetView),
    m_rectangleView(new RectangleListView),
    m_tileControl(new TileControlWidget),
    m_tilePreview(new TilePreview)
{
    setup();
}

SpriteSheetEditor::~SpriteSheetEditor()
{
}

void SpriteSheetEditor::newSpriteSheet(const QString &textureFilePath)
{
    QPixmap         pixmap;
    std::fstream    file;

    file.open(textureFilePath.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open())
    {
        pixmap.load(textureFilePath);
        m_spriteSheetView->removeAllRectangles();
        m_spriteSheetView->setTexturePixmap(pixmap);
        m_spriteSheetView->setTileSize(QSizeF(16, 16));
        m_tileControl->setTileSize(QSizeF(16, 16));
        m_tilePreview->setRectangleSize(QSizeF(16, 16));
        m_tilePreview->removeMarks();
        m_textureBytes.read(file);
    }
}

bool SpriteSheetEditor::openSpriteSheet(const QString &filePath)
{
    QPixmap                 pixmap;
    octo::ByteArray         buffer;
    octo::BinaryInputStream is(buffer);
    std::fstream            file;
    quint32                 textureByteCount = 0u;
    quint32                 tileWidth = 0u;
    quint32                 tileHeight = 0u;
    quint32                 tileCount = 0u;
    quint32                 x = 0u;
    quint32                 y = 0u;
    QList<QPointF>          tilePositions;
    QSizeF                  tileSize;

    file.open(filePath.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open() == false)
        return (false);
    if (buffer.read(file) == false)
        return (false);
    is.read(textureByteCount);
    if (pixmap.loadFromData(reinterpret_cast<uchar const*>(buffer.bytes() + is.getPosition()), textureByteCount) == false)
        return (false);
    m_textureBytes.assign(buffer.bytes() + is.getPosition(), textureByteCount);
    is.skip(textureByteCount);
    is.read(tileWidth, tileHeight, tileCount);
    for (quint32 i = 0u; i < tileCount; ++i)
    {
        is.read(x, y);
        tilePositions.append(QPointF(x, y));
    }
    tileSize = QSizeF(tileWidth, tileHeight);
    m_tileControl->setTileSize(tileSize);
    m_tilePreview->setRectangleSize(tileSize);
    m_tilePreview->removeMarks();
    m_spriteSheetView->resetTiles(tilePositions, tileSize);
    m_spriteSheetView->setTexturePixmap(pixmap);
    return (true);
}

bool SpriteSheetEditor::saveSpriteSheet(const QString &filePath)const
{
    octo::ByteArray             buffer;
    octo::BinaryOutputStream    os(buffer);
    std::fstream                file;
    quint32                     textureByteCount = m_textureBytes.size();
    QSizeF                      tileSize = m_spriteSheetView->tileSize();
    QList<QPointF>              tilePositions = m_spriteSheetView->tilePositions();

    file.open(filePath.toStdString(), std::ios_base::out | std::ios_base::binary);
    if (file.is_open() == false)
        return (false);
    os.write(textureByteCount);
    os.write(m_textureBytes.bytes(), m_textureBytes.size());
    os.write<quint32>(tileSize.width());
    os.write<quint32>(tileSize.height());
    os.write<quint32>(tilePositions.size());
    for (int i = 0; i < tilePositions.size(); ++i)
    {
        os.write<quint32>(tilePositions.at(i).x());
        os.write<quint32>(tilePositions.at(i).y());
    }
    buffer.write(file);
    return (true);
}

void SpriteSheetEditor::deleteCurrentRectangle()
{
    QModelIndex current = m_rectangleView->currentIndex();

    m_spriteSheetView->removeRectangle(current);
    emit modified();
}

void SpriteSheetEditor::deleteAllRectangles()
{
    m_spriteSheetView->removeAllRectangles();
    emit modified();
}

void SpriteSheetEditor::sortRectangles()
{
    m_spriteSheetView->sortRectangles();
    emit modified();
}

void SpriteSheetEditor::generateRectangles(QWidget *parent)
{
    GenerateRectangleDialog dialog(m_spriteSheetView->texturePixmap(), parent);
    QSizeF                  rectangleSize;

    if (dialog.exec() == QDialog::Accepted)
    {
        rectangleSize = m_spriteSheetView->generateRectangles(dialog.widthSubDivCount(), dialog.heightSubDivCount());
        m_tileControl->setTileSize(rectangleSize);
        m_tilePreview->setRectangleSize(rectangleSize);
        m_spriteSheetView->setTileSize(rectangleSize);
    }
}

void SpriteSheetEditor::zoomIn()
{
    m_spriteSheetView->zoomIn();
}

void SpriteSheetEditor::zoomOut()
{
    m_spriteSheetView->zoomOut();
}

void SpriteSheetEditor::zoomZero()
{
    m_spriteSheetView->zoomZero();
}

void SpriteSheetEditor::zoomToFit()
{
    m_spriteSheetView->zoomToFit();
}

bool SpriteSheetEditor::hasSelection() const
{
    return (m_rectangleView->currentIndex().isValid());
}

QList<QAction *> SpriteSheetEditor::commandActions() const
{
    return (m_spriteSheetView->commandActions());
}

void SpriteSheetEditor::onCurrentChanged(const QModelIndex &, const QModelIndex &)
{
    updateTilePreview();
    emit selectionChanged();
}

void SpriteSheetEditor::setup()
{
    QGridLayout*    layout = new QGridLayout(this);

    m_rectangleView->setModel(m_spriteSheetView->rectangleModel());
    m_rectangleView->setSelectionModel(m_spriteSheetView->selectionRectangleModel());
    layout->addWidget(m_spriteSheetView, 0, 0, 0, 1);
    layout->addWidget(m_tileControl, 0, 1);
    layout->addWidget(m_rectangleView, 1, 1);
    layout->addWidget(m_tilePreview, 2, 1);
    layout->setColumnStretch(0, 4);
    connect(m_spriteSheetView->selectionRectangleModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
    connect(m_spriteSheetView, SIGNAL(modified()), SIGNAL(modified()), Qt::DirectConnection);
    connect(m_spriteSheetView, SIGNAL(modified()), SLOT(updateTilePreview()));
    connect(m_tileControl, &TileControlWidget::tileSizeChanged, [this](QSizeF const& size){m_spriteSheetView->setTileSize(size);});
    connect(m_tileControl, &TileControlWidget::tileSizeChanged, [this](QSizeF const& size){m_tilePreview->setRectangleSize(size);});
}

void SpriteSheetEditor::updateTilePreview()
{
    QModelIndex current = m_rectangleView->currentIndex();
    QPixmap     pixmap(m_spriteSheetView->tileSize().toSize());
    QPainter    painter(&pixmap);
    QRectF      subRect;

    if (m_spriteSheetView->tileSize().isEmpty())
        return;
    painter.fillRect(pixmap.rect(), Qt::white);
    if (current.isValid())
    {
        subRect = m_spriteSheetView->rectangleModel()->rectangle(current);
        painter.drawPixmap(pixmap.rect(), m_spriteSheetView->texturePixmap(), subRect);
    }
    m_tilePreview->setPixmap(pixmap);
}
