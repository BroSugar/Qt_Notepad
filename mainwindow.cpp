#include "mainwindow.h"
#include <QMessageBox>
#include <string.h>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    text1 = new QTextEdit;
    QFont f;
    f.setPixelSize(30);
    text1->setFont(f);//设置text1字体的大小为30
    this->setCentralWidget(text1);


    file=this->menuBar()->addMenu("文件");//在菜单栏加入一个菜单项
    edu=this->menuBar()->addMenu("菜单");
    goujian=this->menuBar()->addMenu("构建");
    help=this->menuBar()->addMenu("帮助");


    file_open=new QAction("打开", this);//建立一个action
    file_open->setShortcut(tr("Ctrl+o"));//设置快捷键
    file->addAction(file_open);//将下拉菜单加入到文件

    file_exit=new QAction("关闭",this);
    file_exit->setShortcut(tr("Alt+F4"));
    file->addAction(file_exit);

    file->addSeparator();//加入分割符

    file_save=new QAction("保存",this);
    file_save->setShortcut(tr("Ctrl+s"));
    file->addAction(file_save);

    select_all=new QAction("全选",this);
    select_all->setShortcut(tr("Ctrl+a"));
    edu->addAction(select_all);//放到edu选项卡中

    copy=new QAction("复制",this);
    copy->setShortcut(tr("Ctrl+c"));
    edu->addAction(copy);

    edt_paste=new QAction("粘贴",this);
    edt_paste->setShortcut(tr("Ctrl+v"));
    edu->addAction(edt_paste);

    edt_cut=new QAction("剪切",this);
    edt_cut->setShortcut(tr("Ctrl+x"));
    edu->addAction(edt_cut);

    bianyi=new QAction("编译",this);
    bianyi->setShortcut(tr("Ctrl+r"));
    goujian->addAction(bianyi);

    yunxing=new QAction("运行",this);
    yunxing->setShortcut(tr("Ctrl+F5"));
    goujian->addAction(yunxing);

    help_about=new QAction("关于",this);
    help_about->setShortcut(tr("Ctrl+h"));
    help->addAction(help_about);


    connect(file_open,SIGNAL(triggered()),this,SLOT(on_open()));
            //第一个参数是出发事件控件，第二个参数是对于action来说固定写SIGNAL(tirggered())
            //第三个参数是固定写this
            //第四个参数是指定触发的函数
    connect(help_about,SIGNAL(triggered()),this,SLOT(on_help()));//关于
    connect(file_exit,SIGNAL(triggered()),this,SLOT(on_exit()));//退出
    connect(copy,SIGNAL(triggered()),this,SLOT(on_copy()));//复制
    connect(edt_paste,SIGNAL(triggered()),this,SLOT(paste()));
    connect(edt_cut,SIGNAL(triggered()),this,SLOT(cut()));
    connect(select_all,SIGNAL(triggered()),this,SLOT(sel_all()));
    connect(file_save,SIGNAL(triggered()),this,SLOT(on_save()));
    connect(bianyi,SIGNAL(triggered()),this,SLOT(on_bianyi()));



}

MainWindow::~MainWindow()
{
    delete text1;

}

void MainWindow::on_open()
{
    filename=QFileDialog::getOpenFileName();
    if(filename.isEmpty())
    {
        return;
    }
    //filename.toStdString().data();//将QString 原封不动的转换为const char *
    QString connent;//是qt定义的字符串类
    FILE *p=fopen(filename.toStdString().data(),"r");
    if(p==NULL)
    {
        QMessageBox::information(this,"错误","文件打开失败");
    }else
    {
        while(!feof(p))
        {
            char buf[1024]={0};
            fgets(buf,sizeof(buf),p);
            connent+=buf;
        }
        fclose(p);
        text1->setText(connent);
    }
}

void MainWindow::on_help()
{
    QMessageBox::information(this,"版权所有","辣酱2018,Qt记事本1.0，可编写程序");
}

void MainWindow::on_exit()
{
    exit(0);
}

void MainWindow::on_copy()
{
    text1->copy();
}

void MainWindow::paste()
{
    text1->paste();
}

void MainWindow::cut()
{
    text1->cut();
}

void MainWindow::sel_all()
{
    text1->selectAll();
}

void MainWindow::on_save()
{
    filename=QFileDialog::getSaveFileName();
    if(filename.isEmpty())
    {
        return;
    }
    FILE *p=fopen(filename.toStdString().data(),"w");
    if(p==NULL)
    {
        QMessageBox::information(this,"错误","打开文件失败");

    }else
    {
        fputs(text1->toPlainText().toStdString().data(),p);//将用户在text1中输入的字符串转换为const char *
        fclose(p);
    }
}

void MainWindow::on_bianyi()
{


    //中文编程
    QString conect;
    FILE *p=fopen(filename.toStdString().data(),"r");
    if(p==NULL)
        return;
    while(!feof(p))
    {
        char buf[1024]={0};
        fgets(buf,sizeof(buf),p);
        conect+=buf;
    }
    fclose(p);
    conect.replace("整数","int").replace("主函数","main").replace("开始","{").replace("打印","printf").replace("结束","}").replace("返回","return").replace("输入输出头文件","#include <stdio.h>");

    QString destname=filename;
    destname.replace(".e",".c");
    p=fopen(destname.toStdString().data(),"w");
    fputs(conect.toStdString().data(),p);
    fclose(p);
    QString srcname=destname;
    srcname=srcname.replace(".c","");//将filename中的.c的字符串替换
    QString command="gcc -o "+srcname+" "+destname;
    system(command.toStdString().data());
}

void MainWindow::on_yunxing()
{

    QString destname=filename;
    destname=destname.replace(".c","");//将filename中的.c的字符串替换
    system(destname.toStdString().data());

}
