#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QFileDialog>
#include <sstream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file_name = "New Document";
    file_path = "";

    window()->setWindowTitle(file_name + " - OpenEdit");
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

void MainWindow::on_actionOpen_triggered()
{
    QString new_file_path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "/home/",
                "All Files (*.*);;"
                "Text Files (*.txt, *.md, *.doc, *.log"
                );
    file_path = new_file_path;

    // Get file name from full file path
    std::stringstream *stream = new std::stringstream();
    *stream << file_path.toStdString();
    std::string segment;
    std::vector<std::string> segment_list;
    while(std::getline(*stream, segment, '/'))
    {
        segment_list.push_back(segment);
    }
    std::string fname = segment_list.back();
    QString file_name = QString::fromStdString(fname);

    window()->setWindowTitle(file_name + " - OpenEdit");
}
