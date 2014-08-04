#ifndef SERIALWINDOW_H
#define SERIALWINDOW_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>

namespace Ui {
class SerialWindow;
}

class SerialWindow : public QDialog
{
    Q_OBJECT
public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    explicit SerialWindow(QWidget *parent = 0,QWidget *glview=0);
    void setConnected(bool _connected);
    ~SerialWindow();

    Settings settings() const;

signals:
    void on_connect(SerialWindow::Settings);
    void on_disconnect();

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SerialWindow *ui;
    Settings currentSettings;
    QIntValidator *intValidator;
    bool connected;
};

#endif // SERIALWINDOW_H
