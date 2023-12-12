#pragma once
#include "mainwindow.h"
#include "settings.h"
#include "ui_mainwindow.h"
#include "AbsoluteValueDifferenceSC.h"
#include "ExpModulatedSin.h"
#include "FletcherReevesOptimizer.h"
#include "HimmelblauFunction.h"
#include "IterationsNumberSC.h"
#include "LeviFunction.h"
#include "RelativeDifferenceSC.h"
#include "RosenbrockFunction.h"
#include "StohasticOptimizer.h"

#include <limits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), settings_set(false), function_id(4), method_id(1), criterion_id(1), max_iterations(1000),
    sample_rate(10), precision(0.), p(0.), alpha(1.), delta(0.), starting_point({0, 0, 0}), rect_area(3),
    function(nullptr), optimizer(nullptr), stop_criterion(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete function;
    delete stop_criterion;
    delete optimizer;
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
        settings_set = true;

        ui->x_start->setText(QString::number(starting_point[0], 'g', 2));
        ui->y_start->setText(QString::number(starting_point[1], 'g', 2));
        if (function_id == 4) {
            ui->z_start->show();
            ui->z_start_label->show();
            ui->z_end->show();
            ui->z_end_label->show();
            ui->z_start->setText(QString::number(starting_point[2], 'g', 2));
        }
        else {
            ui->z_start->hide();
            ui->z_start_label->hide();
            ui->z_end->hide();
            ui->z_end_label->hide();
        }

        ui->func_name->setText(settings.get_function_name());

        ui->max_iterations->setText(QString::number(max_iterations));
    }
}


void MainWindow::on_actionOptimize_triggered()
{
    if (!settings_set)
        on_actionSettings_triggered();

    if (!settings_set)
        return;

    switch(function_id) {
    case 1:
        function = new ExpModulatedSin();
        break;
    case 2:
        function = new HimmelblauFunction();
        break;
    case 3:
        function = new LeviFunction();
        break;
    case 4:
        function = new RosenbrockFunction();
        break;
    default:
        throw std::invalid_argument("Undefuned function ID encountered");
    }

    switch(criterion_id) {
    case 1:
        stop_criterion = new IterationsNumberSC(max_iterations);
        break;
    case 2:
        stop_criterion = new AbsoluteValueDifferenceSC(max_iterations, precision);
        break;
    case 3:
        stop_criterion = new RelativeDifferenceSC(max_iterations, precision);
        break;
    default:
        throw std::invalid_argument("Undefuned stopping criterion ID encountered");
    }

    switch(method_id) {
    case 1:
        optimizer = new FletcherReevesOptimizer(function, starting_point, rect_area, stop_criterion);
        break;
    case 2:
        optimizer = new StohasticOptimizer(function, starting_point, rect_area, stop_criterion, p, delta, alpha);
        break;
    default:
        throw std::invalid_argument("Undefuned optimization method ID encountered");
    }

    optimizer->optimize();

    std::vector<double> end_point = optimizer->get_optimizing_point();
    double last_function_value = optimizer->get_optimized_value();
    size_t iterations_number = optimizer->trajectory_size();

    ui->x_end->setText(QString::number(end_point[0], 'g', 2));
    ui->y_end->setText(QString::number(end_point[1], 'g', 2));
    if (end_point.size() == 3){
        ui->z_end->setText(QString::number(end_point[2], 'g', 2));
    }

    ui->iter_number->setText(QString::number(iterations_number));

    ui->end_func_value->setText(QString::number(last_function_value, 'g', 8));

    if (function->get_dimensions() == 2){
        std::vector<std::vector<double>> grid(make_grid());

        plot_graph(grid);
    }
}

std::vector<std::vector<double>> MainWindow::make_grid() {
    int plot_width = ui->function_plot->frameGeometry().width();
    int plot_height = ui->function_plot->frameGeometry().height();
    int grid_width = plot_width / static_cast<int>(sample_rate);
    int grid_height = plot_height / static_cast<int>(sample_rate);

    std::vector<std::vector<double>> grid(grid_height, std::vector<double>(grid_width));

    double grid_step_x = (rect_area[1] - rect_area[0]) / grid_width;
    double grid_step_y = (rect_area[3] - rect_area[2]) / grid_height;

    std::vector<double> point{rect_area[0], rect_area[2]};

    for (int i{}; i < grid_height; ++i) {
        for (int j{}; j < grid_width; ++j) {
            grid[i][j] = function->evaluate(point);

            point[0] += grid_step_x;
        }
        point[0] = rect_area[0];
        point[1] += grid_step_y;
    }

    return grid;
}

void MainWindow::plot_graph(const std::vector<std::vector<double>>& grid) {
    QGraphicsScene *scene = new QGraphicsScene(ui->function_plot);

    double max_value = -std::numeric_limits<double>::infinity();
    double min_value = std::numeric_limits<double>::infinity();

    for(size_t i{}; i < grid.size(); ++i) {
        for(size_t j{}; j < grid[0].size(); ++j) {
            if (grid[i][j] > max_value)
                max_value = grid[i][j];
            if (grid[i][j] < min_value)
                min_value = grid[i][j];
        }
    }



    double interval_length = max_value - min_value;

    for (unsigned i{}; i < grid.size(); ++i) {
        for (unsigned j{}; j < grid[0].size(); ++j) {
            double proportion = (grid[i][j] - min_value) / interval_length;
            int blue_shade = 255 * proportion;
            int green_shade = 255 * (1 - proportion);
            QPen pen(QColor(0, green_shade, blue_shade));
            QBrush brush(QColor(0, green_shade, blue_shade));

            scene->addRect(rect_area[0] + j * sample_rate, rect_area[3] - i * sample_rate, sample_rate, sample_rate, pen, brush);
        }
    }

    ui->function_plot->setScene(scene);
}

