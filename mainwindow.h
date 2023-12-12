#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

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

    void plot_graph(const std::vector<std::vector<double>>& grid);

private slots:
    void on_actionSettings_triggered();

    void on_actionOptimize_triggered();

private:
    Ui::MainWindow *ui;

    // Settings
    bool settings_set;
    int function_id, method_id, criterion_id;
    size_t max_iterations, sample_rate;
    double precision, p, alpha, delta;
    std::vector<double> starting_point;
    RectangularArea rect_area;
    GeneralFunction *function;
    GeneralOptimizer *optimizer;
    GeneralStopCriterion *stop_criterion;
};
#endif // MAINWINDOW_H
