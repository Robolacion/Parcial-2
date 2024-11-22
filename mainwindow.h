#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotter_casero.h"
#include <QDebug>
//#include "qcustomplot.h"
//#include "muParser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void read_file();
    void load_data();
    double calc_desfase(int i);
    double rms(Plotter_Casero function);
private:
    Ui::MainWindow *ui;
    mu::Parser parser;
    Plotter_Casero f_corriente,f_tension;
    FILE *f_a;
    double *Time,*V,*I,desfase=0,P=0;
    int FileLenght,count=0;
public slots:
    void plot();
    void choose_file();

};
#endif // MAINWINDOW_H
