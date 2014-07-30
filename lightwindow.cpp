#include "lightwindow.h"
#include "ui_lightwindow.h"

LightWindow::LightWindow(QWidget *parent,QWidget *glview) :
    QDialog(parent),
    ui(new Ui::LightWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(on_LightPosition(float,float,float)),glview,SLOT(setLightPosition(float,float,float)));
    connect(this,SIGNAL(on_LightADS(float,float,float)),glview,SLOT(setLightADS(float,float,float)));
}
LightWindow::~LightWindow()
{
    delete ui;
}
void LightWindow::setLightPositionValues(float x,float y,float z)
{
    lpx=oldlpx=x;
    lpy=oldlpy=y;
    lpz=oldlpz=z;
    ui->doubleSpinBoxPositionX->setValue(lpx);
    ui->doubleSpinBoxPositionY->setValue(lpy);
    ui->doubleSpinBoxPositionZ->setValue(lpz);
}
void LightWindow::setLightADSValues(float ambient,float diffuse,float specular)
{
    lambient=ambient;
    ldiffuse=diffuse;
    lspecular=specular;
    ui->spinBoxAmbient->setValue(lambient);
    ui->spinBoxDiffuse->setValue(ldiffuse);
    ui->spinBoxSpecular->setValue(lspecular);
}
void LightWindow::on_buttonBox_accepted()
{
    emit on_LightPosition(ui->doubleSpinBoxPositionX->value(),ui->doubleSpinBoxPositionY->value(),ui->doubleSpinBoxPositionZ->value());
}
void LightWindow::on_buttonBox_rejected()
{
    emit on_LightPosition(oldlpx,oldlpy,oldlpz);
}
void LightWindow::on_doubleSpinBoxPositionZ_valueChanged(double arg1)
{
    emit on_LightPosition(ui->doubleSpinBoxPositionX->value(),ui->doubleSpinBoxPositionY->value(),ui->doubleSpinBoxPositionZ->value());
}
void LightWindow::on_doubleSpinBoxPositionY_valueChanged(double arg1)
{
    emit on_LightPosition(ui->doubleSpinBoxPositionX->value(),ui->doubleSpinBoxPositionY->value(),ui->doubleSpinBoxPositionZ->value());
}
void LightWindow::on_doubleSpinBoxPositionX_valueChanged(double arg1)
{
    emit on_LightPosition(ui->doubleSpinBoxPositionX->value(),ui->doubleSpinBoxPositionY->value(),ui->doubleSpinBoxPositionZ->value());
}
void LightWindow::on_spinBoxDiffuse_valueChanged(int arg1)
{
    emit on_LightADS(ui->spinBoxAmbient->value(),ui->spinBoxDiffuse->value(),ui->spinBoxSpecular->value());
}
void LightWindow::on_spinBoxAmbient_valueChanged(int arg1)
{
    emit on_LightADS(ui->spinBoxAmbient->value(),ui->spinBoxDiffuse->value(),ui->spinBoxSpecular->value());
}
void LightWindow::on_spinBoxSpecular_valueChanged(int arg1)
{
    emit on_LightADS(ui->spinBoxAmbient->value(),ui->spinBoxDiffuse->value(),ui->spinBoxSpecular->value());
}
