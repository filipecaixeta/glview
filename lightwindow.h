#ifndef LIGHTWINDOW_H
#define LIGHTWINDOW_H

#include <QDialog>
#include <defines.h>

namespace Ui {
class LightWindow;
}

class LightWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LightWindow(QWidget *parent = 0,QWidget *glview = 0);
    ~LightWindow();
    void setLightPositionValues(float x,float y,float z);
    void setLightADSValues(float ambient,float diffuse,float specular);

signals:
    void on_LightPosition(float,float,float);
    void on_LightADS(float,float,float);

private slots:
    void on_buttonBox_accepted();
    void on_doubleSpinBoxPositionZ_valueChanged(double arg1);
    void on_doubleSpinBoxPositionY_valueChanged(double arg1);
    void on_doubleSpinBoxPositionX_valueChanged(double arg1);
    void on_buttonBox_rejected();
    void on_spinBoxDiffuse_valueChanged(int arg1);
    void on_spinBoxAmbient_valueChanged(int arg1);
    void on_spinBoxSpecular_valueChanged(int arg1);

private:
    Ui::LightWindow *ui;
    float lpx,lpy,lpz;
    float oldlpx,oldlpy,oldlpz;
    float lambient,ldiffuse,lspecular;
    float oldlambient,oldldiffuse,oldlspecular;
};

#endif // LIGHTWINDOW_H
