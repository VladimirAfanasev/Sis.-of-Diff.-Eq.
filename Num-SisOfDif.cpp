#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include  <iostream>


double MainWindow::fi1(double x){
    return pow(x,5);
    //return sin(3.14*x);
}

double MainWindow:: dfi1(double x){
    return 5*pow(x,4);
    //return 3.14*cos(3.14*x);
}
double MainWindow::fi2(double x){
    return sin(3.14*x);
}

double MainWindow:: dfi2(double x){
    return 3.14*cos(3.14*x);
}

QVector<double> MainWindow::Function(double x,double u,double v){
    QVector<double> F;
    double A[2][2]={{3,2},{1,4}};
    //double A[2][2]={{1,4},{4,80}};


    F.push_back(dfi1(x)+A[0][0]*fi1(x)+A[0][1]*fi2(x)-A[0][0]*u-A[0][1]*v);
    F.push_back(dfi2(x)+A[1][0]*fi1(x)+A[1][1]*fi2(x)-A[1][0]*u-A[1][1]*v);
    return F;
}

QVector<QVector<double>> MainWindow::Runge(QVector<double> x,double h){
QVector<double> k1,k2,k3,k4;

    QVector<QVector<double>> U;

    U.push_back({0});
    U.push_back({0});

   for (int i=0; i<x.length()-1;i++){
       k1=Function(x[i],U[0][i],U[1][i]);
       k1[0]=k1[0]*h;
       k1[1]=k1[1]*h;


       k2=Function(x[i]+h/2,U[0][i]+k1[0]/2,U[1][i]+k1[1]/2);
       k2[0]=k2[0]*h;
       k2[1]=k2[1]*h;


       k3=Function(x[i]+h/2,U[0][i]+k2[0]/2,U[1][i]+k2[1]/2);
       k3[0]=k3[0]*h;
       k3[1]=k3[1]*h;

       k4=Function(x[i]+h,U[0][i]+k3[0],U[1][i]+k3[1]);
       k4[0]=k4[0]*h;
       k4[1]=k4[1]*h;

       U[0].push_back(U[0][i]+(k1[0]+2*k2[0]+2*k3[0]+k4[0])/6);
       U[1].push_back(U[1][i]+(k1[1]+2*k2[1]+2*k3[1]+k4[1])/6);


   }

   return U;
}




QVector<double>  MainWindow::FEyler(double x, QVector<double> U0, QVector<double> U1,double h){//u0->u1
    double Fe0=U1[0]-U0[0]-h*Function(x,U1[0],U1[1])[0];
    double Fe1=U1[1]-U0[1]-h*Function(x,U1[0],U1[1])[1];


    return {Fe0,Fe1};
}

QVector<double>  MainWindow::dFEyler(double x, QVector<double> U1,double h){
        double A[2][2]={{3,2},{1,4}};
        //double A[2][2]={{1,4},{4,80}};
    double Dfe1=1-h*(-A[0][0]+A[0][1]*0);
    double Dfe2=1-h*(0*A[1][0]-A[1][1]);
    return {Dfe1,Dfe2};


}


QVector<double> MainWindow:: Newton(double x, double u0,double v0,double h){
    double epsilon =0.00000001;
    double u,u1=0;
    double v,v1=0;
    u=u1-FEyler(x,{u0,v0},{u1,v1},h)[0]/dFEyler(x,{u1,v1},h)[0];
    v=v1-FEyler(x,{u0,v0},{u1,v1},h)[1]/dFEyler(x,{u1,v1},h)[1];

    while ((abs(u-u1)>epsilon && abs(u-u1)<1000) ||(abs(v-v1)>epsilon && abs(v-v1)<1000)){
        u1=u;
        u=u1-FEyler(x,{u0,v0},{u1,v1},h)[0]/dFEyler(x,{u1,v1},h)[0];
        v1=v;
        v=v1-FEyler(x,{u0,v0},{u1,v1},h)[1]/dFEyler(x,{u1,v1},h)[1];
    }


    QVector<double> U;
    U.push_back(u);
    U.push_back(v);

    return U;
}
QVector<QVector<double>> MainWindow::Eyler(QVector<double> x,double h){

QVector<QVector<double>> U;

    U.push_back({0});
    U.push_back({0});
    for (int i=1;i<x.length();i++){
        U[0].push_back(Newton(x[i],U[0][i-1],U[1][i-1],h)[0]);
        U[1].push_back(Newton(x[i],U[0][i-1],U[1][i-1],h)[1]);

    }
    return U;

}

