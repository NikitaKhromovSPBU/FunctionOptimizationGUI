#include "mainwindow.h"
#include "settings.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), function_id(4), method_id(1), criterion_id(1), max_iterations(1000),
    sample_rate(1), precision(0.), p(0.), alpha(1.), delta(0.), starting_point({0, 0, 0}), rect_area(3)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
    Settings settings;
    settings.setModal(true);
    settings.set_function(function_id);
    settings.set_criterion(criterion_id);
    settings.set_method(method_id);
    settings.set_max_iterations(max_iterations);
    settings.set_sampling_rate(sample_rate);
    settings.set_precision(precision);
    settings.set_p(p);
    settings.set_alpha(alpha);
    settings.set_delta(delta);
    settings.set_area(rect_area);
    settings.set_starting_point(starting_point);
    if (settings.exec() == QDialog::Accepted) {
        function_id = settings.get_function();
        method_id = settings.get_method();
        criterion_id = settings.get_criterion();
        max_iterations = settings.get_max_iterations();
        sample_rate = settings.get_sampling_rate();
        precision = settings.get_precision();
        p = settings.get_p();
        alpha = settings.get_alpha();
        delta = settings.get_delta();
        rect_area.set_bounds(settings.get_area());
        starting_point = settings.get_starting_point();
    }
}

