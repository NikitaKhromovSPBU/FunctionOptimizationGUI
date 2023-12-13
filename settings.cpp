#include "settings.h"
#include "ui_settings.h"
#include <QMessageBox>
#include <QButtonGroup>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings), functions(this), methods(this), criteria(this),
    bounds_validator(new QRegularExpressionValidator(QRegularExpression("(^([+-]?(?:[0-9]+[.]?|[0-9]*[.][0-9]+))(?:[Ee][+-]?[0-9]+)?$)"), 0)),
    precision_validator(new QRegularExpressionValidator(QRegularExpression("(^([+]?(?:[0-9]+[.]?|[0-9]*[.][0-9]+))(?:[Ee][+-]?[0-9]+)?$)"), 0))
{
    ui->setupUi(this);

    // hiding elements
    ui->label_precision->hide();
    ui->precision->hide();
    ui->stohastic_parameters_box->hide();
    ui->start_z->hide();
    ui->label_start_z->hide();
    ui->lb_z->hide();
    ui->rb_z->hide();
    ui->label_lb_z->hide();
    ui->label_rb_z->hide();

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

void Settings::accept() {
    RectangularArea area(get_area());
    if(!area.is_valid()) {
        QMessageBox::warning(this, "Incorrect bounds", "Left bounds must be less than right bounds for area");
        return;
    }

    std::vector<double> starting_point = get_starting_point();

    if (!area.contains(starting_point)) {
        QMessageBox::warning(this, "Incorrect starting point", "Starting point must be within the area");
        return;
    }

    double delta = get_delta(),
        p = get_p(), e = get_precision();


    if (p > 0 && delta == 0) {
        QMessageBox::warning(this, "Incorrect radius delta", "Radius delta must be positive if p > 0");
        return;
    }

    if (criteria.checkedId() != 1 && e == 0) {
        QMessageBox::warning(this, "Incorrect precision value", "Precision must be positive");
        return;
    }

    QDialog::accept();
}

// getters/setters

int Settings::get_function() {
    return functions.checkedId();
}

QString Settings::get_function_name() {
    return functions.checkedButton()->text();
}

int Settings::get_method() {
    return methods.checkedId();
}

int Settings::get_criterion() {
    return criteria.checkedId();
}

size_t Settings::get_max_iterations() {
    return ui->max_iter->value();
}

size_t Settings::get_sampling_rate() {
    return ui->sampling_rate->value();
}

double Settings::get_precision() {
    return ui->precision->text().toDouble();
}

double Settings::get_p() {
    return ui->p_spin->value();
}

double Settings::get_delta() {
    return ui->delta->text().toDouble();
}

double Settings::get_alpha() {
    return ui->alpha_spin->value();
}

std::vector<double> Settings::get_area() {
    std::vector<double> result(4);

    result[0] = ui->lb_x->text().toDouble();
    result[1] = ui->rb_x->text().toDouble();

    result[2] = ui->lb_y->text().toDouble();
    result[3] = ui->rb_y->text().toDouble();

    if (functions.checkedId() == 4) {
        result.push_back(ui->lb_z->text().toDouble());
        result.push_back(ui->rb_z->text().toDouble());
    }

    return result;
}

std::vector<double> Settings::get_starting_point() {
    std::vector<double> result(2);

    result[0] = ui->start_x->text().toDouble();
    result[1] = ui->start_y->text().toDouble();
    if (functions.checkedId() == 4) {
        result.push_back(ui->start_z->text().toDouble());
    }

    return result;
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

void Settings::set_max_iterations(size_t n) {
    ui->max_iter->setValue(static_cast<int>(n));
}

void Settings::set_sampling_rate(size_t sr) {
    ui->sampling_rate->setValue(static_cast<int>(sr));
}

void Settings::set_precision(double e) {
    ui->precision->setText(QString::number(e, 'g', 16));
}

void Settings::set_p(double p) {
    ui->p_spin->setValue(p);
}

void Settings::set_delta(double d) {
    ui->delta->setText(QString::number(d, 'g', 16));
}

void Settings::set_alpha(double a) {
    ui->alpha_spin->setValue(a);
}


void Settings::set_area(const RectangularArea &rect) {
    ui->lb_x->setText(QString::number(rect[0], 'g', 16));
    ui->rb_x->setText(QString::number(rect[1], 'g', 16));
    ui->lb_y->setText(QString::number(rect[2], 'g', 16));
    ui->rb_y->setText(QString::number(rect[3], 'g', 16));

    if (functions.checkedId() == 4) {
        ui->lb_z->setText(QString::number(rect[4], 'g', 16));
        ui->rb_z->setText(QString::number(rect[5], 'g', 16));
    }
    else {
        ui->lb_z->setText(QString::number(0));
        ui->rb_z->setText(QString::number(0));
    }
}

void Settings::set_starting_point(const std::vector<double> &x) {
    ui->start_x->setText(QString::number(x[0], 'g', 16));
    ui->start_y->setText(QString::number(x[1], 'g', 16));

    if (functions.checkedId() == 4) {
        ui->start_z->setText(QString::number(x[2], 'g', 16));
    }
    else {
        ui->start_z->setText(QString::number(0));
    }
}
