#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->doubleSpinBox_Eixo_X,SIGNAL(valueChanged(double)),ui->glView,SLOT(rotateX(double)));
    connect(ui->doubleSpinBox_Eixo_Y,SIGNAL(valueChanged(double)),ui->glView,SLOT(rotateY(double)));
    connect(ui->doubleSpinBox_Eixo_Z,SIGNAL(valueChanged(double)),ui->glView,SLOT(rotateZ(double)));

    connect(this,SIGNAL(on_actionOpen3DModel(QString)),ui->glView,SLOT(open3DModel(QString)));
    connect(this,SIGNAL(on_actionClose3DModel()),ui->glView,SLOT(close3DModel()));

    connect(this,SIGNAL(on_actionUseRadians(bool)),ui->glView,SLOT(setRad(bool)));
    connect(this,SIGNAL(on_actionLight(float,float,float)),ui->glView,SLOT(setLightPosition(float,float,float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen3DModel_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.obj)"));
    emit on_actionOpen3DModel(fileName);
}

void MainWindow::on_actionClose3DModel_triggered()
{
    emit on_actionClose3DModel();
}

void MainWindow::on_actionUse_Radians_triggered(bool checked)
{
    emit on_actionUseRadians(checked);
    if (checked==true)
    {
        ui->doubleSpinBox_Eixo_X->setMaximum(6.28);
        ui->doubleSpinBox_Eixo_X->setMinimum(-6.28);
        ui->doubleSpinBox_Eixo_X->setDecimals(4);
        ui->doubleSpinBox_Eixo_Y->setMaximum(6.28);
        ui->doubleSpinBox_Eixo_Y->setMinimum(-6.28);
        ui->doubleSpinBox_Eixo_Y->setDecimals(4);
        ui->doubleSpinBox_Eixo_Z->setMaximum(6.28);
        ui->doubleSpinBox_Eixo_Z->setMinimum(-6.28);
        ui->doubleSpinBox_Eixo_Z->setDecimals(4);
    }
    else
    {
        ui->doubleSpinBox_Eixo_X->setMaximum(360);
        ui->doubleSpinBox_Eixo_X->setMinimum(-360);
        ui->doubleSpinBox_Eixo_X->setDecimals(2);
        ui->doubleSpinBox_Eixo_Y->setMaximum(360);
        ui->doubleSpinBox_Eixo_Y->setMinimum(-360);
        ui->doubleSpinBox_Eixo_Y->setDecimals(2);
        ui->doubleSpinBox_Eixo_Z->setMaximum(360);
        ui->doubleSpinBox_Eixo_Z->setMinimum(-360);
        ui->doubleSpinBox_Eixo_Z->setDecimals(2);
    }
}

void MainWindow::on_actionLight_triggered()
{
    LightWindow *w=new LightWindow(this,ui->glView);
    w->setLightPositionValues(ui->glView->lpx,ui->glView->lpy,ui->glView->lpz);
    w->setLightADSValues(ui->glView->lambient,ui->glView->ldiffuse,ui->glView->lspecular);
    w->show();
}

void MainWindow::on_actionMaterial_triggered()
{
    MaterialWindow *w=new MaterialWindow(this,ui->glView);
    w->setShininess(ui->glView->shininess);
    w->show();
}

void MainWindow::on_actionTransformations_triggered()
{
    TransformationsWindow *w=new TransformationsWindow(this,ui->glView);
    w->setRotationValues(ui->glView->rax,ui->glView->ray,ui->glView->raz);
    w->setTranslationValues(ui->glView->tx,ui->glView->ty,ui->glView->tz);
    w->setScaleValue(ui->glView->scale);
    w->show();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("<p><b>Desined by:</b> Filipe A. Caixeta</p>"
                   "<p><b>License:</b> MIT <br><br>"
                   "Permission is hereby granted,free of charge, to any person obtaining a copy of this software "
                   "and associated documentation files (the \"Software\"), to deal in the Software without restriction"
                   ", including without limitation the rights to use, copy, modify, merge, publish, distribute, "
                   "sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is "
                   "furnished to do so, subject to the following conditions:<br><br>The above copyright notice and "
                   "this permission notice shall be included in all copies or substantial portions of the Software."
                   "<br><br>THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, "
                   "INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE "
                   "AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, "
                   "DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT "
                   "OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.</p>");
    msgBox.exec();
}
