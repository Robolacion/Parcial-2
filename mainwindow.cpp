#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  f_b=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_2.dat","r");
  //  f_c=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_3.dat","r");
  //  f_d=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_4.dat","r");
  //  f_e=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_5.dat","r");
  connect(ui->run_plot,SIGNAL(clicked()),this,SLOT(plot()));
    connect(ui->File_selection,SIGNAL(valueChanged(int)),this,SLOT(choose_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot(){
    load_data();
    double vrms=rms(f_tension),Irms=rms(f_corriente);
    P=vrms*Irms*cos(desfase);
    ui->Vrms->display(vrms);
    ui->Potencia->display(P);
    ui->Irms->display(Irms);
    ui->plotter->addGraph();
    ui->plotter->setInteractions(QCP::iRangeZoom| QCP::iRangeDrag);
    ui->plotter->graph(0)->setData(f_corriente.x,f_corriente.y);
     ui->plotter->graph(0)->setPen(QPen(QColor(255,200,50,155)));
    ui->plotter->addGraph();
    ui->plotter->graph(1)->setData(f_tension.x,f_tension.y);
     ui->plotter->graph(1)->setPen(QPen(QColor(0,200,50,155)));
    ui->plotter->replot();
     count=0;
}
void MainWindow::choose_file(){
    if(ui->File_selection->value()==1){
        f_a=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_1.dat","rb"); //abro archivo
        std::cout<<"archivo abierto con exito"<<std::endl;
        read_file();
    }
    if(ui->File_selection->value()==2){
        f_a=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_2.dat","rb"); //abro archivo
        std::cout<<"archivo abierto con exito";
        read_file();
    }
    if(ui->File_selection->value()==3){
        f_a=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_3.dat","rb"); //abro archivo
        std::cout<<"archivo abierto con exito";
        read_file();
    }
    if(ui->File_selection->value()==4){
        f_a=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_4.dat","rb"); //abro archivo
        std::cout<<"archivo abierto con exito";
        read_file();
    }
    if(ui->File_selection->value()==5){
        f_a=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 - 2024\\vi_5.dat","rb"); //abro archivo
        std::cout<<"archivo abierto con exito";
        read_file();
    }
}
void MainWindow:: read_file(){
     fseek(f_a,0,SEEK_END);//voy al ultimo dato
     FileLenght=ftell(f_a)/(3*sizeof(double));//guardo numero de datos
     std::cout<<"numero de datos:["<<FileLenght<<"]"<<std::endl;
     fseek(f_a,0,SEEK_SET);//vuelvo al inicio
     Time=new double[FileLenght];
     I=new double[FileLenght];
     V=new double[FileLenght];
     for (int i = 0; i < FileLenght; ++i) {

         fread(&Time[i],sizeof(double),1,f_a);
         fread(&V[i],sizeof(double),1,f_a);
         fread(&I[i],sizeof(double),1,f_a);

     }
     fclose(f_a);
}
void MainWindow::load_data(){
    f_corriente.y.resize(FileLenght);
    f_corriente.x.resize(FileLenght);
    f_tension.y.resize(FileLenght);
    f_tension.x.resize(FileLenght);
    for (int i = 0; i < FileLenght; i++) {
        f_corriente.x[i]=Time[i];
        f_tension.x[i]=Time[i];
        f_corriente.y[i]=I[i];
        f_tension.y[i]=V[i];

        if(i<FileLenght-1){
          if (((f_corriente.y[i])*(f_corriente.y[i+1]))<0 && count==0){ //esta linea crashea el codigo
            desfase=calc_desfase(i);
            count++;}
        else{
            desfase=0;
            count++;
        }
        }
        std::cout<<"T:["<<Time[i]<<"],V:["<<V[i]<<"],I["<<I[i]<<"]"<<std::endl;

    }

}
double MainWindow:: rms(Plotter_Casero function){
    /*double res,aux;
    aux=(1/(final-inicial))*((final-final)-(inicial*inicial));
    res=sqrt(aux);
    return res;
    */
    return function.calc_area();
    std::cout<<"calculo valor efectivo realizado"<<std::endl;
}
double MainWindow:: calc_desfase(int k){
    double angle,value;
    value=((0-f_corriente.y[k])/(f_corriente.y[k+1]-f_corriente.y[k])*(f_corriente.x[k+1]-f_corriente.x[k])+f_corriente.x[k]);
    if(value!=0)
    angle=180/(0.01*value);
    else{
        angle=0;
    }
    std::cout<<"desfase:["<<angle<<"]"<<std::endl;
    return angle;
}

