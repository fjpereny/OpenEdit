#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>

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

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->mainTextEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->mainTextEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->mainTextEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->mainTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->mainTextEdit->paste();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->mainTextEdit->selectAll();
}

void MainWindow::on_actionZoom_In_triggered()
{
    ui->mainTextEdit->zoomIn();
}

void MainWindow::on_actionZoom_Out_triggered()
{
    ui->mainTextEdit->zoomOut();
}

void MainWindow::on_actionWord_Wrap_triggered()
{
    if(ui->actionWord_Wrap->isChecked())
        ui->mainTextEdit->setWordWrapMode(QTextOption::WrapMode::WordWrap);
    else {
        ui->mainTextEdit->setWordWrapMode(QTextOption::WrapMode::NoWrap);
    }
}
