#include "settings.h"
#include "ui_settings.h"
#include <QMessageBox>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    // hiding elements
    ui->label_precision->hide();
    ui->precision->hide();
    ui->stohastic_parameters_box->hide();

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_rad1_rosenbrock_toggled(bool checked)
{
    if(checked) {
        ui->label_lb_z->show();
        ui->label_rb_z->show();
        ui->lb_z->show();
        ui->rb_z->show();
        ui->label_start_z->show();
        ui->start_z->show();
    }
    else {
        ui->label_lb_z->hide();
        ui->label_rb_z->hide();
        ui->lb_z->hide();
        ui->rb_z->hide();
        ui->label_start_z->hide();
        ui->start_z->hide();
    }
}


void Settings::on_rad2_it_num_toggled(bool checked)
{
    if(checked) {
        ui->label_precision->hide();
        ui->precision->hide();
    }
    else {
        ui->label_precision->show();
        ui->precision->show();
    }
}


void Settings::on_radioButton_2_toggled(bool checked)
{
    if(checked) {
        ui->stohastic_parameters_box->show();
    }
    else {
        ui->stohastic_parameters_box->hide();
    }
}

