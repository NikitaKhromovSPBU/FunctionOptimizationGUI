#include "settings.h"
#include "ui_settings.h"
#include <QMessageBox>
#include <QButtonGroup>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings), functions(this), methods(this), criteria(this),
    bounds_validator(new QRegularExpressionValidator(QRegularExpression("[-,+]{0,1}[0-9]+[.][0-9]+"), 0)),
    precision_validator(new QRegularExpressionValidator(QRegularExpression("[+]{0,1}[0-9]+[.][0-9]+"), 0))
{
    ui->setupUi(this);

    // hiding elements
    ui->label_precision->hide();
    ui->precision->hide();
    ui->stohastic_parameters_box->hide();

    // creating radio buttons groups
    functions.addButton(ui->rad1_exp_sin, 1);
    functions.addButton(ui->rad1_himmelblau, 2);
    functions.addButton(ui->rad1_levi, 3);
    functions.addButton(ui->rad1_rosenbrock, 4);

    methods.addButton(ui->fr_method, 1);
    methods.addButton(ui->stohastic_method, 2);

    criteria.addButton(ui->rad2_it_num, 1);
    criteria.addButton(ui->rad2_abs_diff, 2);
    criteria.addButton(ui->rad2_rel_diff, 3);

    // forbid user from inputing letters in numbers-only fields
    ui->precision->setValidator(precision_validator);
    ui->delta->setValidator(precision_validator);
    ui->lb_x->setValidator(bounds_validator);
    ui->rb_x->setValidator(bounds_validator);
    ui->lb_y->setValidator(bounds_validator);
    ui->rb_y->setValidator(bounds_validator);
    ui->lb_z->setValidator(bounds_validator);
    ui->rb_z->setValidator(bounds_validator);
    ui->start_x->setValidator(bounds_validator);
    ui->start_y->setValidator(bounds_validator);
    ui->start_z->setValidator(bounds_validator);
}

Settings::~Settings()
{
    delete bounds_validator;
    delete precision_validator;
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


void Settings::on_p_slider_valueChanged(int value)
{
    ui->p_spin->setValue(value / 100.);
}


void Settings::on_p_spin_valueChanged(double arg1)
{
    ui->p_slider->setValue(static_cast<int>(arg1 * 100));
}


void Settings::on_alpha_slider_valueChanged(int value)
{
    ui->alpha_spin->setValue(value / 100.);
}


void Settings::on_alpha_spin_valueChanged(double arg1)
{
    ui->alpha_slider->setValue(static_cast<int>(arg1 * 100));
}

void Settings::on_stohastic_method_toggled(bool checked)
{
    if(checked) {
        ui->stohastic_parameters_box->show();
    }
    else {
        ui->stohastic_parameters_box->hide();
    }
}

void Settings::on_buttonBox_accepted()
{

}

int Settings::get_function() {
    return functions.checkedId();
}

int Settings::get_method() {
    return methods.checkedId();
}

int Settings::get_criterion() {
    return criteria.checkedId();
}

void Settings::set_function(int id) {
    if (functions.button(id)) {
        functions.button(id)->toggle();
    }
}

void Settings::set_method(int id) {
    if (methods.button(id)) {
        methods.button(id)->toggle();
    }
}

void Settings::set_criterion(int id) {
    if (criteria.button(id)) {
        criteria.button(id)->toggle();
    }
}


