#include "mainwindow.h"
#include "settings.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), function_id(4), method_id(1), criterion_id(1), rect_area(3)
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
    if (settings.exec() == QDialog::Accepted) {
        function_id = settings.get_function();
        method_id = settings.get_method();
        criterion_id = settings.get_criterion();
    }
}

