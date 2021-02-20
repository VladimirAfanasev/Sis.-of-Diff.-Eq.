#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void Drow(double zoom);

private slots:
    double fi1(double x);
    double dfi1(double x);
    double fi2(double x);
    double dfi2(double x);
    QVector<double> Function(double x,double u,double v);

    QVector<QVector<double>> Runge(QVector<double> x, double h);
    QVector<QVector<double>> Eyler(QVector<double> x,double h);
    QVector<double>Newton(double x, double u0,double v0,double h);
    QVector<double>FEyler(double x, QVector<double> U0, QVector<double> U1,double h);
    QVector<double>dFEyler(double x,QVector<double> U1,double h);


    void on_PloatButton_clicked();

    void on_ConvergenceButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
