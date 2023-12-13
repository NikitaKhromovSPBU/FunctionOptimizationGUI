#pragma once
#include "mainwindow.h"
#include "settings.h"
#include "ui_mainwindow.h"
#include "plotscene.h"
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

    delete function;
    delete stop_criterion;
    delete optimizer;

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

    double grid_step_x = (rect_area[1] - rect_area[0]) / grid_width;
    double grid_step_y = (rect_area[3] - rect_area[2]) / grid_height;

    std::vector<std::vector<double>> grid(grid_height, std::vector<double>(grid_width));
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
    PlotScene *scene = new PlotScene(ui->function_plot);
    connect(scene, &PlotScene::sceneClicked, this, &MainWindow::on_scene_clicked);
    double scene_height = ui->function_plot->height();

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

    double max_value_trunc = fmin(max_value, min_value + 255);

    double lower_interval_length = max_value_trunc - min_value;
    double upper_interval_length = max_value - max_value_trunc;

    for (unsigned i{}; i < grid.size(); ++i) {
        for (unsigned j{}; j < grid[0].size(); ++j) {
            int green_shade{}, blue_shade{};
            if (grid[i][j] < max_value_trunc){
                double proportion = (grid[i][j] - min_value) / lower_interval_length;
                blue_shade = 255 * proportion;
            }
            else {
                double proportion = (max_value - grid[i][j]) / upper_interval_length;
                green_shade = 255 * (1 - proportion);
                blue_shade = 255 * proportion;
            }
            QPen pen(QColor(0, green_shade, blue_shade));
            QBrush brush(QColor(0, green_shade, blue_shade));

            scene->addRect(j * sample_rate, scene_height - i * sample_rate, sample_rate, sample_rate, pen, brush);
        }
    }
    plot_trajectory(optimizer->get_trajectory(), scene);

    ui->function_plot->setScene(scene);
}

void MainWindow::on_scene_clicked(QPointF point) {
    if (!settings_set || function_id == 4)
        return;

    int plot_width = ui->function_plot->frameGeometry().width();
    int plot_height = ui->function_plot->frameGeometry().height();

    double grid_step_x = (rect_area[1] - rect_area[0]) / plot_width;
    double grid_step_y = (rect_area[3] - rect_area[2]) / plot_height;

    double x = rect_area[0] + grid_step_x * point.x();
    double y = rect_area[3] - grid_step_y * point.y();

    if(rect_area.contains(std::vector{x, y})){
        starting_point = std::vector<double>{x, y};
        ui->x_start->setText(QString::number(starting_point[0], 'g', 2));
        ui->y_start->setText(QString::number(starting_point[1], 'g', 2));
        on_actionOptimize_triggered();
    }
}

void MainWindow::plot_trajectory(const std::vector<std::vector<double>>& trajectory, PlotScene* scene) {
    int plot_width = ui->function_plot->frameGeometry().width();
    int plot_height = ui->function_plot->height();
    double area_width = rect_area[1] - rect_area[0];
    double area_height = rect_area[3] - rect_area[2];

    QPen red_pen(QColor(255, 0, 0));
    double last_point_x = (trajectory[0][0] - rect_area[0]) * plot_width / area_width;
    double last_point_y = (rect_area[3] - trajectory[0][1]) * plot_height / area_height;
    double new_point_x{}, new_point_y{};
    for (auto& point : trajectory) {
        new_point_x = (point[0] - rect_area[0]) * plot_width / area_width;
        new_point_y = (rect_area[3] - point[1]) * plot_height / area_height;
        scene->addLine(last_point_x, last_point_y, new_point_x, new_point_y, red_pen);
        last_point_x = new_point_x;
        last_point_y = new_point_y;
    }
}

