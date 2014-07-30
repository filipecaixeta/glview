#ifndef TRANSFORMATIONSWINDOW_H
#define TRANSFORMATIONSWINDOW_H

#include <QDialog>

namespace Ui {
class TransformationsWindow;
}

class TransformationsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransformationsWindow(QWidget *parent = 0,QWidget *glview = 0);
    ~TransformationsWindow();
    void setRotationValues(double x,double y,double z);
    void setTranslationValues(float x,float y,float z);
    void setScaleValue(double s);

signals:
    void on_doubleSpinBoxTranslate(float,float,float);
    void on_doubleSpinBoxRotate(double,double,double);
    void on_doubleSpinBoxScale(double);

private slots:
    void on_doubleSpinBoxTranslateX_valueChanged(double arg1);
    void on_doubleSpinBoxTranslateY_valueChanged(double arg1);
    void on_doubleSpinBoxTranslateZ_valueChanged(double arg1);
    void on_doubleSpinBoxRotateX_valueChanged(double arg1);
    void on_doubleSpinBoxRotateY_valueChanged(double arg1);
    void on_doubleSpinBoxRotateZ_valueChanged(double arg1);
    void on_doubleSpinBoxScale_valueChanged(double arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    double rx,ry,rz;
    double oldrx,oldry,oldrz;
    float tx,ty,tz;
    float oldtx,oldty,oldtz;
    double scale,oldscale;
    Ui::TransformationsWindow *ui;
};

#endif // TRANSFORMATIONSWINDOW_H
