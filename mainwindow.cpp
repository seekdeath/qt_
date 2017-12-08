#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "netcacha.h"

#define netcmdmax 256
#define netcmdcountmax 16
extern char netqueue[netcmdcountmax][netcmdmax];//命令队列
extern unsigned char queuehead;//队列头
extern unsigned char queueend;//队尾
extern unsigned char netcmdcount;//当前命令计数
extern unsigned char countflag ;//命令队列头尾交叉标志
extern char nettemp[256] ;//命令拆分临时空间
extern unsigned char frameflag ;//数据帧标志
extern unsigned char netququefull ;//queue full state


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str ;
    QByteArray qb;
     char * p;
     unsigned char n;
    ui->textEdit->setText(0);
    str = ui->lineEdit->text();
    qb = str.toLatin1();
//    a = qb.data();
    p = qb.data();
    splitnetcmd(p);
    netcmdcount = getnetcmdcount();
    n = netcmdcount;
    ui->label->setText(QString::number(netcmdcount));
    while(netcmdcount != 0)
    {
        char *temp ;
        temp = popnetqueue();
        ui->textEdit->append(temp);
        netcmdcount = getnetcmdcount();
    }
}
//void cheacknetcmd(char* netcmd)
//{
//    unsigned int num = 0;
//    num = strlen(netcmd);
//    if(num < 10)
//    {
//        return 1;//异常
//    }
//    else if(num > netcmdmax)
//    {
//        return 1;//超限
//    }

//}
