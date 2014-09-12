#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poppyupper.h"

//! MainWindow class from Qt template

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
