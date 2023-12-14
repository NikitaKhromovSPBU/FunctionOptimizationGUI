#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>

class PlotView : public QGraphicsView
{
    Q_OBJECT
public:
    PlotView() : QGraphicsView() {};
    PlotView(QWidget *parent = nullptr) : QGraphicsView(parent) {};
    PlotView(QGraphicsScene *scene, QWidget *parent = nullptr) : QGraphicsView(scene, parent) {};
    ~PlotView() override {};

signals:
    void viewResized();

protected:
    void resizeEvent(QResizeEvent *) override {
        emit viewResized();
    }
};

#endif // PLOTVIEW_H
