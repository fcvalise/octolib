#include "SpriteSheetModel.hpp"
#include "TilePreview.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>
#include <QAction>
#include <QItemSelectionModel>

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
    m_model(nullptr),
    m_selectionModel(nullptr),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(nullptr),
    m_addVerticalMark(nullptr),
    m_addHorizontalMark(nullptr),
    m_clearMarks(nullptr)
{
    m_pixmapItem = m_scene->addPixmap(QPixmap());
    m_pixmapItem->setZValue(-1);
    m_borderItem = m_scene->addRect(0, 0, 0, 0, QPen(Qt::black, 0, Qt::DotLine));
    m_borderItem->setZValue(0);
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

void TilePreview::setModel(SpriteSheetModel *model)
{
    if (m_model)
    {
        disconnect(m_model, SIGNAL(textureChanged(QPixmap)), this, SLOT(updateTilePreview));
        disconnect(m_model, SIGNAL(tileSizeChanged(QSize)), this, SLOT(updateTilePreview));
        disconnect(m_model, &SpriteSheetModel::dataChanged, this, &TilePreview::updateTilePreview);
        m_selectionModel = nullptr;
    }
    m_model = model;
    if (m_model)
    {
        connect(m_model, &SpriteSheetModel::textureChanged, this, &TilePreview::updateTilePreview);
        connect(m_model, &SpriteSheetModel::tileSizeChanged, this, &TilePreview::updateTilePreview);
        connect(m_model, &SpriteSheetModel::dataChanged, this, &TilePreview::updateTilePreview);
        setSelectionModel(new QItemSelectionModel(m_model, this));
    }
}

void TilePreview::setSelectionModel(QItemSelectionModel *model)
{
    if (m_selectionModel)
    {
        disconnect(m_selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(updateTilePreview()));
    }
    m_selectionModel = model;
    if (m_selectionModel)
    {
        connect(m_selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(updateTilePreview()));
    }
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

void TilePreview::updateTilePreview()
{
    if (m_model == nullptr || m_selectionModel == nullptr)
        return;
    QList<QModelIndex>  selection = m_selectionModel->selectedIndexes();
    QModelIndex         current = m_selectionModel->currentIndex();
    QPixmap             pixmap(m_model->tileSize());
    QPainter            painter(&pixmap);
    QRectF              subRect;

    if (current.isValid() == false && selection.size() > 1)
        current = selection.first();
    if (m_model->tileSize().isEmpty())
        return;
    painter.fillRect(pixmap.rect(), Qt::white);
    if (current.isValid())
    {
        subRect = m_model->tile(current);
        painter.drawPixmap(pixmap.rect(), m_model->texture(), subRect);
    }
    m_pixmapItem->setPixmap(pixmap);
    m_borderItem->setRect(m_pixmapItem->boundingRect());
    fitInView(m_pixmapItem, Qt::KeepAspectRatio);
}

