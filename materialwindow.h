#ifndef MATERIALWINDOW_H
#define MATERIALWINDOW_H

#include <QDialog>
#include <defines.h>
#include <QtSerialPort/QSerialPort>

namespace Ui {
class MaterialWindow;
}

class MaterialWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialWindow(QWidget *parent = 0,QWidget *glview = 0);
    void setShininess(double s);
    ~MaterialWindow();

signals:
    void on_comboBoxMaterial(unsigned int);
    void on_doubleSpinBoxShininess(float);

private slots:
    void on_comboBoxMaterial_currentIndexChanged(int index);
    void on_doubleSpinBoxShininess_valueChanged(double arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MaterialWindow *ui;
    double oldshininess,shininess;
};

#endif // MATERIALWINDOW_H
