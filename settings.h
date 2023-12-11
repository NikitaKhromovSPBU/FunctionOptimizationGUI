#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QButtonGroup>
#include <QRegularExpressionValidator>

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

    void set_function(int id);

    void set_method(int id);

    void set_criterion(int id);

private slots:
    void on_rad1_rosenbrock_toggled(bool checked);

    void on_rad2_it_num_toggled(bool checked);

    void on_p_slider_valueChanged(int value);

    void on_p_spin_valueChanged(double arg1);

    void on_alpha_slider_valueChanged(int value);

    void on_alpha_spin_valueChanged(double arg1);

    void on_buttonBox_accepted();

    void on_stohastic_method_toggled(bool checked);

private:
    Ui::Settings *ui;
    QButtonGroup functions;
    QButtonGroup methods;
    QButtonGroup criteria;

    QRegularExpressionValidator *bounds_validator, *precision_validator;
};

#endif // SETTINGS_H
