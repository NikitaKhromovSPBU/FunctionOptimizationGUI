#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "AbsoluteValueDifferenceSC.h"
#include "ExpModulatedSin.h"
#include "FletcherReevesOptimizer.h"
#include "HimmelblauFunction.h"
#include "IterationsNumberSC.h"
#include "LeviFunction.h"
#include "RectangularArea.h"
#include "RelativeDifferenceSC.h"
#include "RosenbrockFunction.h"
#include "StohasticOptimizer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;

    // Settings
    int function_id, method_id, criterion_id;
    size_t max_iterations;
    RectangularArea rect_area;
    GeneralFunction *function;
    GeneralOptimizer *optimizer;
    GeneralStopCriterion *stop_criterion;
};
#endif // MAINWINDOW_H
