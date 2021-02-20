#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
double MainWindow::dfi(double x){
    if (ui->comboBox->currentText()== "sin(x)"){
        return(3.14*cos(3.14*x));
    }
    else if (ui->comboBox->currentText()=="ln(x)") {
            return(1/(x+1));
        }
    else return -2*x*x*x+3*x*x+1;
}


double MainWindow::fi(double x){
    if (ui->comboBox->currentText()== "sin(x)"){
        return(sin(3.14*x));
    }
    else if (ui->comboBox->currentText()=="ln(x)") {
        return(log(x+1));
        }
    else return -0.5*x*x*x*x+x*x*x+x;
}



double MainWindow::f(double x,double u){
    double p=ui->ParametrP->value();
    return dfi(x)+p*pow((u-fi(x)),3);
}

QVector<double> MainWindow:: Runge(QVector<double> x, double h){
    double k1,k2,k3,k4;
    QVector<double> u;
    u.push_back(0);
    for (int i =0;i<x.length()-1;i++){
        k1=h*f(x[i],u[i]);
        k2=h*f(x[i]+h/2,u[i]+k1/2);
        k3=h*f(x[i]+h/2,u[i]+k2/2);
        k4=h*f(x[i]+h,u[i]+k3);
        u.push_back(u[i]+(k1+2*k2+2*k3+k4)/6);
    }
    return u;
}
QVector<double> MainWindow:: Adams(QVector<double> x,double h){
    QVector<double> u;
    u.push_back(x[0]);
    u.push_back(x[1]);
    u.push_back(x[2]);
    u.push_back(x[3]);
    u=Runge(u,h);
    for (int i=0;i<x.length()-4;i++){
        u.push_back(u[i+3]+(h/24)*(55*f(x[i+3],u[i+3])-59*f(x[i+2],u[i+2])+37*f(x[i+1],u[i+1])-9*f(x[i],u[i])));
    }

    return u;
}


double MainWindow::FEyler(double x,double u0,double u1,double h){//u0->u1
    return u1-u0-h*f(x,u1);

}
double MainWindow::dFEyler(double x,double u1,double h){//d /du1
    double p=ui->ParametrP->value();
    return 1-3*h*(p*pow((u1-fi(x)),2));

}

double MainWindow:: Newton(double x,double u0,double h){

    double epsilon =0.0000001;
    double u,u1=0;
    u=u1-FEyler(x,u0,u1,h)/dFEyler(x,u1,h);
    int count =0;

    while (abs(u-u1)>epsilon && abs(u-u1)<1000){
        u1=u;
        u=u1-FEyler(x,u0,u1,h)/dFEyler(x,u1,h);
        count+=1;
        if (x==0.5){
         std::cout<<u<<" "<<u1<<" "<<u-u1<<"\n";
        std::cout<<"u - fi(x) = "<<u-fi(x)<<"\n";}



    }

    if (x==0.5){
    std::cout<<count<<"\n";
    }







    return u;

}
QVector<double>MainWindow:: Eyler(QVector<double> x, double h){
    QVector<double> u;
    u.push_back(0);
    for (int i=1;i<x.length();i++){
        u.push_back(Newton(x[i],u[i-1],h));
    }
    return u;


}








