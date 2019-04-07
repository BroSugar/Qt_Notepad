#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString filename;

    QTextEdit *text1;
    QMenu *file;
    QMenu *edu;
    QMenu *goujian;
    QMenu *help;

    QAction *file_open;
    QAction *file_exit;
    QAction *help_about;
    QAction *copy;
    QAction *edt_paste;
    QAction *edt_cut;
    QAction *select_all;
    QAction *file_save;
    QAction *bianyi;
    QAction *yunxing;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_open();
    void on_help();
    void on_exit();
    void on_copy();
    void paste();
    void cut();
    void sel_all();//全选
    void on_save();
    void on_bianyi();
    void on_yunxing();
};

#endif // MAINWINDOW_H
