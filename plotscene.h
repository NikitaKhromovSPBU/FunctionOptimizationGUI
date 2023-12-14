#ifndef PLOTSCENE_H
#define PLOTSCENE_H

#include <QGraphicsScene>
#include <QResizeEvent>

class PlotScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PlotScene(QObject *parent = nullptr) : QGraphicsScene(parent) {};
    ~PlotScene() override {};

signals:
    void sceneClicked(QPointF point);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // PLOTSCENE_H
