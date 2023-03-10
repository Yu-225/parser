#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logparser.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Log File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("No file selected."));
        return;
    }

    LogParser logParser;
    QStringList errorLines = logParser.parseFile(filePath);

    ui->logListView->reset();

    // Create a model to store the error lines
    QStringListModel *model = new QStringListModel(errorLines, ui->logListView);

    // Set the model to the QListView
    ui->logListView->setModel(model);
}

void MainWindow::on_saveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save CSV File"), "", tr("CSV Files (*.csv);;All Files (*)"));

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("No file selected."));
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file for writing."));
        return;
    }

    QTextStream out(&file);

    LogParser logParser;
    QStringList errorLines = logParser.parseFile(filePath);

    // Write the contents of errorLines to the file
    foreach (const QString& line, errorLines) {
        out << line << "\n";
    }

    // Close the file
    file.close();

    QMessageBox::information(this, tr("Save CSV File"), tr("File saved successfully."));
}



