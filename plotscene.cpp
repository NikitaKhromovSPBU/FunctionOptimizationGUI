#include "plotscene.h"
#include <QGraphicsSceneMouseEvent>

void PlotScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    emit sceneClicked(mouseEvent->scenePos());
}
