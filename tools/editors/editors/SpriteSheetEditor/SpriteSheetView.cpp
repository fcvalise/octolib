#include "SpriteSheetView.hpp"
#include "SpriteSheetScene.hpp"
#include "RectangleModel.hpp"

#include <QGraphicsRectItem>
#include <QItemSelectionModel>

SpriteSheetView::SpriteSheetView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new SpriteSheetScene(this)),
    m_zoomFactor(1.0)
{
    setInteractive(true);
    setMouseTracking(true);
    setScene(m_scene);
    setupBackgroundBrush();
    connect(m_scene, SIGNAL(modified()), SIGNAL(modified()), Qt::DirectConnection);
    enableBackground(true);
}

SpriteSheetView::~SpriteSheetView()
{
}

void SpriteSheetView::enableBackground(bool enable)
{
    if (enable)
        m_scene->setBackgroundBrush(m_backgroundBrush);
    else
        m_scene->setBackgroundBrush(QBrush());
}

void SpriteSheetView::setTexturePixmap(const QPixmap &pixmap)
{
    m_scene->setTexturePixmap(pixmap);
}

void SpriteSheetView::clearTexturePixmap()
{
    m_scene->setTexturePixmap(QPixmap());
}

void SpriteSheetView::resetTiles(const QList<QPointF> &tilePosition, const QSizeF &tileSize)
{
    m_scene->resetRectangles(tilePosition, tileSize);
}

QSizeF SpriteSheetView::generateRectangles(int widthSubDiv, int heightSubDiv)
{
    QRectF          textureRect = textureRectangle();
    int             width = textureRect.width() / widthSubDiv;
    int             height = textureRect.height() / heightSubDiv;
    int             posX = 0;
    int             posY = 0;
    QList<QPointF>  positions;
    QSizeF          rectangleSize;

    for (int y = 0; y < heightSubDiv; ++y)
    {
        posX = 0;
        for (int x = 0; x < widthSubDiv; ++x)
        {
            positions.append(QPointF(posX, posY));
            posX += width;
        }
        posY += height;
    }
    rectangleSize = QSizeF(width, height);
    resetTiles(positions, rectangleSize);
    return (rectangleSize);
}

void SpriteSheetView::setTileSize(const QSizeF &size)
{
    m_scene->setRectangleSize(size);
}

void SpriteSheetView::removeRectangle(const QModelIndex &index)
{
    m_scene->removeRectangle(index);
}

void SpriteSheetView::removeAllRectangles()
{
    m_scene->removeAllRectangles();
}

void SpriteSheetView::sortRectangles()
{
    m_scene->sortRectangles();
}

void SpriteSheetView::zoomIn()
{
    setZoom(m_zoomFactor + 0.1);
    centerOnCurrent();
}

void SpriteSheetView::zoomOut()
{
    if (m_zoomFactor > 0.1)
    {
        setZoom(m_zoomFactor - 0.1);
        centerOnCurrent();
    }
}

void SpriteSheetView::zoomZero()
{
    setZoom(1.0);
}

void SpriteSheetView::zoomToFit()
{
    QRectF  viewRect = viewport()->rect().adjusted(2, 2, -2, -2);
    qreal   factorX = viewRect.width() / m_scene->textureWidth();
    qreal   factorY = viewRect.height() / m_scene->textureHeight();

    setZoom(std::min(factorX, factorY));
}

void SpriteSheetView::setZoom(qreal factor)
{
    m_zoomFactor = factor;
    setTransform(QTransform::fromScale(m_zoomFactor, m_zoomFactor), false);
}

RectangleModel *SpriteSheetView::rectangleModel() const
{
    return (m_scene->rectangleModel());
}

QItemSelectionModel *SpriteSheetView::selectionRectangleModel() const
{
    return (m_scene->selectionRectangleModel());
}

QList<QAction *> SpriteSheetView::commandActions() const
{
    return (m_scene->commandActions());
}

QSizeF SpriteSheetView::tileSize() const
{
    return (m_scene->rectangleModel()->size());
}

QList<QPointF> SpriteSheetView::tilePositions() const
{
    return (m_scene->rectangleModel()->positions());
}

QRectF SpriteSheetView::textureRectangle() const
{
    return (QRectF(0, 0, m_scene->textureWidth(), m_scene->textureHeight()));
}

QPixmap SpriteSheetView::texturePixmap() const
{
    return (m_scene->texturePixmap());
}

void SpriteSheetView::setupBackgroundBrush()
{
    static const QColor s_light = QColor(125, 125, 125);
    static const QColor s_dark = QColor(75, 75, 75);
    QPixmap             pixmap(16, 16);
    QPainter            painter(&pixmap);

    painter.fillRect(0, 0, 8, 8, s_light);
    painter.fillRect(8, 0, 8, 8, s_dark);
    painter.fillRect(0, 8, 8, 8, s_dark);
    painter.fillRect(8, 8, 8, 8, s_light);
    m_backgroundBrush = QBrush(pixmap);
}

void SpriteSheetView::centerOnCurrent()
{
    QModelIndex current = selectionRectangleModel()->currentIndex();

    if (current.isValid())
    {
        centerOn(rectangleModel()->rectangle(current).center());
    }
}
