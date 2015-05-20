#include "TilePreview.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>
#include <QAction>

class GraphicsMark : public QGraphicsLineItem
{
public:
    explicit GraphicsMark(Qt::Orientation orientation, QGraphicsItem* parent = nullptr) :
        QGraphicsLineItem(parent),
        m_orientation(orientation)
    {
        setPen(QPen(Qt::red, 0));
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
        setZValue(1);
    }

    void    setup(QGraphicsScene* scene)
    {
        QRectF  sceneRect = scene->sceneRect();
        QPointF center = sceneRect.center();

        switch (m_orientation)
        {
        case Qt::Horizontal:
            setLine(sceneRect.left(), center.y(), sceneRect.right(), center.y());
            break;
        case Qt::Vertical:
            setLine(center.x(), sceneRect.top(), center.x(), sceneRect.bottom());
            break;
        default:
            break;
        }
        scene->addItem(this);
    }

    virtual QRectF boundingRect() const
    {
        QRectF  rect = QGraphicsLineItem::boundingRect();

        return (rect.adjusted(-10, -10, 10, 10));
    }

    virtual QPainterPath shape() const
    {
        QPainterPath    path;

        path.addRect(boundingRect());
        return (path);
    }
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value)
    {
        QPointF     newPos;
        QVariant    result;

        if (change == ItemPositionChange && scene())
        {
            newPos = value.toPointF();
            switch (m_orientation)
            {
            case Qt::Horizontal:
                newPos.setX(pos().x());
                break;
            case Qt::Vertical:
                newPos.setY(pos().y());
                break;
            default:
                break;
            }
            result = qVariantFromValue(newPos);
        }
        else
        {
            result = QGraphicsLineItem::itemChange(change, value);
        }
        return (result);
    }
private:
    Qt::Orientation const   m_orientation;
};

TilePreview::TilePreview(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(nullptr),
    m_addVerticalMark(nullptr),
    m_addHorizontalMark(nullptr),
    m_clearMarks(nullptr)
{
    m_pixmapItem = m_scene->addPixmap(QPixmap());
    m_pixmapItem->setZValue(-1);
    setScene(m_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(true);
    setMouseTracking(true);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setupActions();
}

TilePreview::~TilePreview()
{
}

void TilePreview::setRectangleSize(const QSizeF &size)
{
    QRectF  rect(QPointF(0, 0), size);

    m_scene->setSceneRect(rect);
}

void TilePreview::setPixmap(const QPixmap &pixmap)
{
    m_pixmapItem->setPixmap(pixmap);
    fitInView(m_pixmapItem, Qt::KeepAspectRatio);
}

void TilePreview::setupActions()
{
    QAction*    separatorAction = new QAction(this);

    m_addVerticalMark = new QAction(tr("Add vertical mark"), this);
    m_addHorizontalMark  = new QAction(tr("Add horizontal mark"), this);
    m_clearMarks = new QAction(tr("Remove marks"), this);
    separatorAction->setSeparator(true);
    addAction(m_addVerticalMark);
    addAction(m_addHorizontalMark);
    addAction(separatorAction);
    addAction(m_clearMarks);
    connect(m_addVerticalMark, &QAction::triggered, this, &TilePreview::addVerticalMark);
    connect(m_addHorizontalMark, &QAction::triggered, this, &TilePreview::addHorizontalMark);
    connect(m_clearMarks, &QAction::triggered, this, &TilePreview::removeMarks);
}

void TilePreview::addVerticalMark()
{
    GraphicsMark*  newMark = new GraphicsMark(Qt::Vertical);

    newMark->setup(m_scene);
    m_marks.append(newMark);
}

void TilePreview::addHorizontalMark()
{
    GraphicsMark*  newMark = new GraphicsMark(Qt::Horizontal);

    newMark->setup(m_scene);
    m_marks.append(newMark);
}

void TilePreview::removeMarks()
{
    auto it = m_marks.begin();

    while (it != m_marks.end())
    {
        m_scene->removeItem(*it);
        delete *it;
        it = m_marks.erase(it);
    }
}

