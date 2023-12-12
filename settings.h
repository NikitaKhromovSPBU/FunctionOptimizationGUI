#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QButtonGroup>
#include <QRegularExpressionValidator>

#include "RectangularArea.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    // getters/setters
    int get_function();

    int get_method();

    int get_criterion();

    size_t get_max_iterations();

    size_t get_sampling_rate();

    double get_precision();

    double get_p();

    double get_delta();

    double get_alpha();

    std::vector<double> get_area();

    std::vector<double> get_starting_point();

    void set_function(int id);

    void set_method(int id);

    void set_criterion(int id);

    void set_max_iterations(size_t n);

    void set_sampling_rate(size_t sr);

    void set_precision(double e);

    void set_p(double p);

    void set_delta(double d);

    void set_alpha(double a);

    void set_area(const RectangularArea &rect);

    void set_starting_point(const std::vector<double> &x);

private slots:
    void on_rad1_rosenbrock_toggled(bool checked);

    void on_rad2_it_num_toggled(bool checked);

    void on_p_slider_valueChanged(int value);

    void on_p_spin_valueChanged(double arg1);

    void on_alpha_slider_valueChanged(int value);

    void on_alpha_spin_valueChanged(double arg1);

    void on_stohastic_method_toggled(bool checked);

    void accept();

private:
    Ui::Settings *ui;
    QButtonGroup functions;
    QButtonGroup methods;
    QButtonGroup criteria;

    QRegularExpressionValidator *bounds_validator, *precision_validator;
};

#endif // SETTINGS_H
