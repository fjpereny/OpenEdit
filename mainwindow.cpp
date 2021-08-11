#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file_name = "New Document";
    file_path = "";
    unsaved_title_active = false;
    user_name = getlogin();

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
    QString user_dir = QString::fromStdString("/home/" + user_name);
    QString new_file_path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                user_dir,
                "All Files (*.*);;"
                "Text Files (*.txt, *.md, *.doc, *.log"
                );
    file_path = new_file_path;


    // Get file name from full file path
    if(file_path != QString(""))
        {
            std::ifstream file_stream;
            file_stream.open(file_path.toStdString());
            if(file_stream.is_open())
            {
                std::string data;
                std::string line;
                while(std::getline(file_stream, line))
                {
                    data += line + '\n';
                }
                file_stream.close();

                QString new_text = QString::fromStdString(data);
                ui->mainTextEdit->clear();
                ui->mainTextEdit->insertPlainText(new_text);
                window()->setWindowTitle(get_file_name() + " - OpenEdit");
                unsaved_title_active = false;
            }
            else {
                QMessageBox *err_msg = new QMessageBox(this);
                err_msg->setText("Could not open the specified file.");
                err_msg->setWindowTitle("File Read Error");
                err_msg->show();
            }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(file_path == "")
    {
        on_actionSave_As_triggered();
    }
    else {
            std::ofstream output_file;
            std::string output_file_path = file_path.toStdString();
            output_file.open(output_file_path);
            if(output_file.is_open())
            {
                std::string data = ui->mainTextEdit->toPlainText().toStdString();
                output_file << data;
                output_file.close();
                window()->setWindowTitle(get_file_name() + " - OpenEdit");
                unsaved_title_active = false;
            }
            else
            {
                QMessageBox *err_msg = new QMessageBox(this);
                err_msg->setText("Could not save the specified file.");
                err_msg->setWindowTitle("File Save Error");
                err_msg->show();
            }
    }


}

void MainWindow::on_actionSave_As_triggered()
{
    QString user_dir = QString::fromStdString("/home/" + user_name);
    QString new_file_path = QFileDialog::getSaveFileName(
                this,
                "Save File",
                user_dir,
                "All Files (*.*, *);;"
                "Text Files (*.txt, *.md, *.doc, *.log"
                );
    if(new_file_path.toStdString() != "")
    {
        file_path = new_file_path;

        std::ofstream output_file;
        std::string output_file_path = file_path.toStdString();
        output_file.open(output_file_path);
        if(output_file.is_open())
        {
            std::string data = ui->mainTextEdit->toPlainText().toStdString();
            output_file << data;
            output_file.close();
            window()->setWindowTitle(get_file_name() + " - OpenEdit");
            unsaved_title_active = false;
        }
        else {
            QMessageBox *err_msg = new QMessageBox(this);
            err_msg->setText("Could not save the specified file.");
            err_msg->setWindowTitle("File Save Error");
            err_msg->show();
        }
    }
}

QString MainWindow::get_file_name()
{
    std::stringstream *stream = new std::stringstream();
    *stream << file_path.toStdString();
    std::string segment;
    std::vector<std::string> segment_list;
    while(std::getline(*stream, segment, '/'))
    {
        segment_list.push_back(segment);
    }
    delete stream;
    std::string fname = segment_list.back();
    QString file_name = QString::fromStdString(fname);
    return file_name;
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow *newWindow = new MainWindow();
    newWindow->show();
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_mainTextEdit_textChanged()
{
    if(!unsaved_title_active)
        setWindowTitle("*Unsaved Changes* - " + windowTitle());
    unsaved_title_active = true;
}
