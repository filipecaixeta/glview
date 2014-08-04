#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <math.h>

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

    connect(this,SIGNAL(on_newSerialData(unsigned char,double)),this,SLOT(newData(unsigned char,double)));
    connect(this,SIGNAL(rotateModel(unsigned char,double)),ui->glView,SLOT(rotate(unsigned char,double)));

    preprocessfunc=NULL;

    serialConnection=false;
    serial = new QSerialPort(this);
    serialData.controle=11;
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

MainWindow::~MainWindow()
{
    try
    {
        serial->close();
    }
    catch (std::exception e)
    {}
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

void MainWindow::on_actionSerial_Port_triggered()
{
    SerialWindow *w=new SerialWindow(this,ui->glView);
    w->setConnected(serialConnection);
    w->show();
}

void MainWindow::on_connectSerial(SerialWindow::Settings _settings)
{
    serialSettings=_settings;
    serial->setPortName(serialSettings.name);
    serial->setBaudRate(serialSettings.baudRate);
    serial->setDataBits(serialSettings.dataBits);
    serial->setParity(serialSettings.parity);
    serial->setStopBits(serialSettings.stopBits);
    serial->setFlowControl(serialSettings.flowControl);
    if (serial->open(QIODevice::ReadWrite))
    {
        serialConnection=true;
        ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                        .arg(serialSettings.name).arg(serialSettings.stringBaudRate)
                        .arg(serialSettings.stringDataBits).arg(serialSettings.stringParity)
                        .arg(serialSettings.stringStopBits).arg(serialSettings.stringFlowControl));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        ui->statusBar->showMessage(tr("Open error"));
    }
}

void MainWindow::on_disconnectSerial()
{
    serial->close();
    serialConnection=false;
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    foreach (unsigned char c, data)
    {
        if (c=='*' && serialData.controle>6)
            serialData.controle=0;
        else if (c=='\n' && serialData.controle==6)
        {
            emit on_newSerialData(serialData.header,serialData.data);
            serialData.controle=7;
        }
        else
        {
            serialData.controle++;
            switch (serialData.controle)
            {
            case 1:
                serialData.header=c;
                break;
            case 2:
                serialData.dataI=c<<24;
                break;
            case 3:
                serialData.dataI+=c<<16;
                break;
            case 4:
                serialData.dataI+=c<<8;
                break;
            case 5:
                serialData.dataI+=c;
                break;
            case 6:
                serialData.data=serialData.dataI*pow(10,c>127?c-256:c);
                break;
            default:
                break;
            }
        }
    }
}

void MainWindow::newData(unsigned char header,double val)
{
    if (preprocessfunc!=NULL)
        preprocessfunc(header,val);
    if (header==AXIS_X || header==AXIS_Y || header==AXIS_Z)
        emit rotateModel(header,val);
    else
        std::cout << "treta\n";
}

void MainWindow::setPreProcessFunc(void(*_preprocessfunc)(unsigned char,double&))
{
    preprocessfunc=_preprocessfunc;
}
