#ifndef ADDTILECOMMAND_HPP
#define ADDTILECOMMAND_HPP
#include <AbstractCommand.hpp>

class QAction;
class QGraphicsRectItem;

class AddTileCommand : public QObject, public AbstractCommand
{
    Q_OBJECT

    static QPen const       GhostRectanglePen;
    static QBrush const     GhostRectangleBrush;
public:
    explicit AddTileCommand(SpriteSheetModel* model, QItemSelectionModel* selection);
    ~AddTileCommand();

    virtual QAction *action() const;
    virtual QCursor cursor() const;
    virtual void    mousePressEvent(QGraphicsSceneMouseEvent *);
    virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void    mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    virtual void    keyPressEvent(QKeyEvent *);
    virtual void    keyReleaseEvent(QKeyEvent *);
    virtual void    onStarted(QGraphicsScene *scene);
    virtual void    onStopped(QGraphicsScene* scene);
private slots:
    void            onTileSizeChanged(QSize const& size);
private:
    QPoint              m_previous;
    QAction*            m_action;
    QGraphicsRectItem*  m_ghost;
};

#endif // ADDTILECOMMAND_HPP
