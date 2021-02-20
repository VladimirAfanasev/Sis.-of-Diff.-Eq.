#include "mainwindow.h"
#include "ui_mainwindow.h"

#include  <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    on_PloatButton_clicked();
}

MainWindow::~MainWindow()
{

    delete ui;
}




void MainWindow::on_PloatButton_clicked()
{
    QVector<QVector<double>> U;

    double a=0,b=2;
    double one=30.0;
    double zoom=ui->doubleSpinBox->value();
    QVector <double> x;
    int N=ui->Knots->value();
    for (int i=0;i<N+1;i++){
        x.push_back(a+i*abs(b-a)/N);
    }
    double h=(abs(b-a)/N);

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    QPen pen(Qt::magenta);
    scene->addLine(-zoom*100*b,0,zoom*100*b,0,pen);//x
    scene->addLine(0,-80*zoom,0,zoom*80,pen);//y
    scene->addLine(one*zoom,5,zoom*one,-5,pen);
    scene->addLine(-5,-one*zoom,5,-one*zoom,pen);

    QPen pen1(Qt::darkRed);
    QPen pen2(Qt::darkBlue);
    if (ui->Function->checkState()){
    for (int i =0; i<50*b*zoom;i++){
        scene->addLine(i,-fi1(i/one/zoom)*one*zoom,(i+1),-fi1((i+1)/one/zoom)*one*zoom,pen1);
        scene->addLine(i,-fi2(i/one/zoom)*one*zoom,(i+1),-fi2((i+1)/one/zoom)*one*zoom,pen2);
        }
    for (int i =0; i>-50*b*zoom;i--){
       scene->addLine(i,-fi1(i/one/zoom)*one*zoom,(i+1),-fi1((i+1)/one/zoom)*one*zoom,pen1);
       scene->addLine(i,-fi2(i/one/zoom)*one*zoom,(i+1),-fi2((i+1)/one/zoom)*one*zoom,pen2);

        }
    }


    QPen Rpen1(Qt::green);
    QPen Rpen2(Qt::darkGreen);
    if (ui->RungeBox->checkState()){
       U=Runge(x,h);

       for(int i=0;i<N;i++){
           scene->addLine(zoom*one*x[i],-zoom*one*U[0][i],zoom*one*x[i+1],-zoom*one*U[0][i+1],Rpen1);
           scene->addLine(zoom*one*x[i],-zoom*one*U[1][i],zoom*one*x[i+1],-zoom*one*U[1][i+1],Rpen2);
       }
    }

    QPen Epen1(Qt::cyan);
    QPen Epen2(Qt::darkCyan);
    if (ui->EylerBox->checkState()){
       U=Eyler(x,h);

       for(int i=0;i<N;i++){
           scene->addLine(zoom*one*x[i],-zoom*one*U[0][i],zoom*one*x[i+1],-zoom*one*U[0][i+1],Epen1);
           scene->addLine(zoom*one*x[i],-zoom*one*U[1][i],zoom*one*x[i+1],-zoom*one*U[1][i+1],Epen2);
       }
    }


    ui->graphicsView->setScene(scene);

}

void MainWindow::on_ConvergenceButton_clicked()
{

    double a=0,b=2,n1,max1,max2;
    double one=5.0;
    double zoom=ui->doubleSpinBox->value();

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsConvergence);
    std::cout<< "hey \n";
    QPen pen1(Qt::magenta);
    scene->addLine(0,0,zoom*100,0,pen1);//N
    scene->addLine(0,-80*zoom,0,0,pen1);//MAX
    scene->addLine(one*zoom,5,zoom*one,-5,pen1);
    scene->addLine(-5,-one*zoom,5,-one*zoom,pen1);

    QPen Rpen1(Qt::green);
    QPen Rpen2(Qt::darkGreen);
    if (ui->RungeBox->checkState()){
         std::cout<<"__________RUNGE_________\n";


        QVector<QVector<double>> U;
        QVector <double>x,MaxError1,MaxError2,N;
        n1=5;


        for (int j=0;j<n1+1;j++){
            x.push_back(a+j*abs(b-a)/n1);
        }

        U=Runge(x,abs(b-a)/n1);

        max1=abs(U[0][0]-fi1(x[0]));
        max2=abs(U[1][0]-fi2(x[0]));

        for (int j=0;j<U[0].length();j++){
            if (max1<abs(U[0][j]-fi1(x[j]))){
                    max1=abs(U[0][j]-fi1(x[j]));
            }
        }
        for (int j=0;j<U[1].length();j++){
            if (max2<abs(U[1][j]-fi2(x[j]))){
                    max2=abs(U[1][j]-fi2(x[j]));
            }
        }

        for (int i=0;i<10;i++){
            std::cout<< n1<<"  ---  ";
            N.append(n1);

            n1=n1*2;
            x.clear();
            for (int j=0;j<n1+1;j++){
                x.push_back(a+j*abs(b-a)/n1);
            }
            U=Runge(x,abs(b-a)/n1);
            double MAX1=abs(U[0][0]-fi1(x[0]));
            double MAX2=abs(U[1][0]-fi2(x[0]));

            for (int j=0;j<U[0].length();j++){
                if (MAX1<abs(U[0][j]-fi1(x[j]))){
                        MAX1=abs(U[0][j]-fi1(x[j]));
                }
            }
            for (int j=0;j<U[1].length();j++){
                if (MAX2<abs(U[1][j]-fi2(x[j]))){
                        MAX2=abs(U[1][j]-fi2(x[j]));
                }
            }

            x.clear();

            std::cout<<"\n" <<" u: ";
            std::cout<< max1<<" / "<< MAX1<< " = "<<max1/MAX1<<"\n";

            std::cout<< " v: ";
            std::cout<< max2<<" / "<< MAX2<< " = "<<max2/MAX2<<"\n";

            MaxError1.push_back(max1/MAX1);
            MaxError2.push_back(max2/MAX2);
            max1=MAX1;
            max2=MAX2;
            }

        for(int i=0;i<N.length()-1;i++){
            scene->addLine(zoom*one*N[i],-zoom*one*MaxError1[i],zoom*one*N[i+1],-zoom*one*MaxError1[i+1],Rpen1);
            scene->addLine(zoom*one*N[i],-zoom*one*MaxError2[i],zoom*one*N[i+1],-zoom*one*MaxError2[i+1],Rpen2);
        }
        N.clear();
        MaxError1.clear();
        MaxError2.clear();



    }

    QPen Epen1(Qt::cyan);
    QPen Epen2(Qt::darkCyan);

    if (ui->EylerBox->checkState()){
         std::cout<<"__________EYLER_________\n";
        QVector<QVector<double>> U;
        QVector <double>x,MaxError1,MaxError2,N;
        n1=5;
        for (int j=0;j<n1+1;j++){
            x.push_back(a+j*abs(b-a)/n1);
        }
        U=Eyler(x,abs(b-a)/n1);

        max1=abs(U[0][0]-fi1(x[0]));
        max2=abs(U[1][0]-fi2(x[0]));

        for (int j=0;j<U[0].length();j++){
            if (max1<abs(U[0][j]-fi1(x[j]))){
                    max1=abs(U[0][j]-fi1(x[j]));
            }
        }
        for (int j=0;j<U[1].length();j++){
            if (max2<abs(U[1][j]-fi2(x[j]))){
                    max2=abs(U[1][j]-fi2(x[j]));
            }
        }

        for (int i=0;i<10;i++){
            std::cout<< n1<<"  ---  ";
            N.append(n1);

            n1=n1*2;
            x.clear();
            for (int j=0;j<n1+1;j++){
                x.push_back(a+j*abs(b-a)/n1);
            }
            U=Eyler(x,abs(b-a)/n1);
            double MAX1=abs(U[0][0]-fi1(x[0]));
            double MAX2=abs(U[1][0]-fi2(x[0]));

            for (int j=0;j<U[0].length();j++){
                if (MAX1<abs(U[0][j]-fi1(x[j]))){
                        MAX1=abs(U[0][j]-fi1(x[j]));
                }
            }
            for (int j=0;j<U[1].length();j++){
                if (MAX2<abs(U[1][j]-fi2(x[j]))){
                        MAX2=abs(U[1][j]-fi2(x[j]));
                }
            }

            x.clear();

            std::cout<<"\n" <<" u: ";
            std::cout<< max1<<" / "<< MAX1<< " = "<<max1/MAX1<<"\n";

            std::cout<< " v: ";
            std::cout<< max2<<" / "<< MAX2<< " = "<<max2/MAX2<<"\n";

            MaxError1.push_back(max1/MAX1);
            MaxError2.push_back(max2/MAX2);
            max1=MAX1;
            max2=MAX2;
            }

        for(int i=0;i<N.length()-1;i++){
            scene->addLine(zoom*one*N[i],-zoom*one*MaxError1[i],zoom*one*N[i+1],-zoom*one*MaxError1[i+1],Epen1);
            scene->addLine(zoom*one*N[i],-zoom*one*MaxError2[i],zoom*one*N[i+1],-zoom*one*MaxError2[i+1],Epen2);
        }
        N.clear();
        MaxError1.clear();
        MaxError2.clear();



    }



    ui->graphicsConvergence->setScene(scene);
}

