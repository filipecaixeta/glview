#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <lightwindow.h>
#include <materialwindow.h>
#include <transformationswindow.h>
#include <defines.h>
 #include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void on_actionOpen3DModel(QString);
    void on_actionClose3DModel();
    void on_actionUseRadians(bool);
    void on_actionLight(float,float,float);

private slots:
    void on_actionOpen3DModel_triggered();
    void on_actionClose3DModel_triggered();
    void on_actionUse_Radians_triggered(bool checked);
    void on_actionLight_triggered();
    void on_actionMaterial_triggered();
    void on_actionTransformations_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
