#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <lightwindow.h>
#include <materialwindow.h>
#include <serialwindow.h>
#include <transformationswindow.h>
#include <defines.h>
#include <QMessageBox>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class SerialData
{
public:
    char controle;
    char header;
    int dataI;
    double data;
};



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openSerialPort();
    void closeSerialPort();
    void setPreProcessFunc(void(*_preprocessfunc)(unsigned char,double&));

signals:
    void on_actionOpen3DModel(QString);
    void on_actionClose3DModel();
    void on_actionUseRadians(bool);
    void on_actionLight(float,float,float);
    void on_newSerialData(unsigned char,double);
    void rotateModel(unsigned char,double);

private slots:
    void on_actionOpen3DModel_triggered();
    void on_actionClose3DModel_triggered();
    void on_actionUse_Radians_triggered(bool checked);
    void on_actionLight_triggered();
    void on_actionMaterial_triggered();
    void on_actionTransformations_triggered();
    void on_actionAbout_triggered();
    void on_actionSerial_Port_triggered();
    void on_connectSerial(SerialWindow::Settings);
    void on_disconnectSerial();
    void readData();
    void newData(unsigned char header, double val);

private:
    Ui::MainWindow *ui;
    SerialWindow::Settings serialSettings;
    QSerialPort *serial;
    bool serialConnection;
    SerialData serialData;
    void(*preprocessfunc)(unsigned char,double&);
};

#endif // MAINWINDOW_H
