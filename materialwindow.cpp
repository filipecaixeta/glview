#include "materialwindow.h"
#include "ui_materialwindow.h"

MaterialWindow::MaterialWindow(QWidget *parent,QWidget *glview) :
    QDialog(parent),
    ui(new Ui::MaterialWindow)
{
    ui->setupUi(this);
    ui->comboBoxMaterial->addItem("");
    ui->comboBoxMaterial->addItem("Gold");
    ui->comboBoxMaterial->addItem("Bonze");
    ui->comboBoxMaterial->addItem("Silver");
    ui->comboBoxMaterial->addItem("Red Plastic");
    connect(this,SIGNAL(on_comboBoxMaterial(unsigned int)),glview,SLOT(setMaterial(unsigned int)));
    connect(this,SIGNAL(on_doubleSpinBoxShininess(float)),glview,SLOT(setShininess(float)));
}

void MaterialWindow::setShininess(double s)
{
    oldshininess=shininess=s;
    ui->doubleSpinBoxShininess->setValue(shininess);
}

MaterialWindow::~MaterialWindow()
{
    emit on_doubleSpinBoxShininess(oldshininess);
    delete ui;
}

void MaterialWindow::on_comboBoxMaterial_currentIndexChanged(int index)
{
    if (index!=0)
        emit on_comboBoxMaterial(index);
}

void MaterialWindow::on_doubleSpinBoxShininess_valueChanged(double arg1)
{
    shininess=arg1/100;
    emit on_doubleSpinBoxShininess(shininess);
}

void MaterialWindow::on_buttonBox_accepted()
{
    emit on_doubleSpinBoxShininess(shininess);
}

void MaterialWindow::on_buttonBox_rejected()
{
    emit on_doubleSpinBoxShininess(oldshininess);
}
