#include "transformationswindow.h"
#include "ui_transformationswindow.h"

TransformationsWindow::TransformationsWindow(QWidget *parent,QWidget *glview) :
    QDialog(parent),
    ui(new Ui::TransformationsWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(on_doubleSpinBoxRotate(double,double,double)),glview,SLOT(setRotation(double,double,double)));
    connect(this,SIGNAL(on_doubleSpinBoxTranslate(float,float,float)),glview,SLOT(setTranslation(float,float,float)));
    connect(this,SIGNAL(on_doubleSpinBoxScale(double)),glview,SLOT(setScale(double)));
}

TransformationsWindow::~TransformationsWindow()
{
    emit on_doubleSpinBoxRotate(oldrx,oldry,oldrz);
    emit on_doubleSpinBoxTranslate(oldtx,oldty,oldtz);
    emit on_doubleSpinBoxScale(oldscale);
    delete ui;
}

void TransformationsWindow::setRotationValues(double x,double y,double z)
{
    oldrx=rx=x;
    oldry=ry=y;
    oldrz=rz=z;
    ui->doubleSpinBoxRotateX->setValue(rx);
    ui->doubleSpinBoxRotateY->setValue(ry);
    ui->doubleSpinBoxRotateZ->setValue(rz);
}

void TransformationsWindow::setTranslationValues(float x,float y,float z)
{
    oldtx=tx=x;
    oldty=ty=y;
    oldtz=tz=z;
    ui->doubleSpinBoxTranslateX->setValue(rx);
    ui->doubleSpinBoxTranslateY->setValue(ry);
    ui->doubleSpinBoxTranslateZ->setValue(rz);
}

void TransformationsWindow::setScaleValue(double s)
{
    oldscale=scale=s;
    ui->doubleSpinBoxScale->setValue(scale);
}

void TransformationsWindow::on_doubleSpinBoxTranslateX_valueChanged(double arg1)
{
    tx=arg1;
    emit on_doubleSpinBoxTranslate(tx,ty,tz);
}

void TransformationsWindow::on_doubleSpinBoxTranslateY_valueChanged(double arg1)
{
    ty=arg1;
    emit on_doubleSpinBoxTranslate(tx,ty,tz);
}

void TransformationsWindow::on_doubleSpinBoxTranslateZ_valueChanged(double arg1)
{
    tz=arg1;
    emit on_doubleSpinBoxTranslate(tx,ty,tz);
}

void TransformationsWindow::on_doubleSpinBoxRotateX_valueChanged(double arg1)
{
    rx=arg1;
    emit on_doubleSpinBoxRotate(rx,ry,rz);
}

void TransformationsWindow::on_doubleSpinBoxRotateY_valueChanged(double arg1)
{
    ry=arg1;
    emit on_doubleSpinBoxRotate(rx,ry,rz);
}

void TransformationsWindow::on_doubleSpinBoxRotateZ_valueChanged(double arg1)
{
    rz=arg1;
    emit on_doubleSpinBoxRotate(rx,ry,rz);
}

void TransformationsWindow::on_doubleSpinBoxScale_valueChanged(double arg1)
{
    scale=arg1;
    emit on_doubleSpinBoxScale(scale);
}

void TransformationsWindow::on_buttonBox_accepted()
{
    emit on_doubleSpinBoxRotate(rx,ry,rz);
    emit on_doubleSpinBoxTranslate(tx,ty,tz);
    emit on_doubleSpinBoxScale(scale);
}

void TransformationsWindow::on_buttonBox_rejected()
{
    emit on_doubleSpinBoxRotate(oldrx,oldry,oldrz);
    emit on_doubleSpinBoxTranslate(oldtx,oldty,oldtz);
    emit on_doubleSpinBoxScale(oldscale);
}
