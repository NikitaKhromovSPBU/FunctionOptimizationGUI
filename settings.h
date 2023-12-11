#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_rad1_rosenbrock_toggled(bool checked);

    void on_rad2_it_num_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
