#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openFile1_lineEdit->setEnabled(false);
    ui->openFile2_lineEdit->setEnabled(false);
    ui->dataOut_plainTextEdit->setReadOnly(true);
    QString str = tr("Data separator. You can use 'endl' for line wrap while saving");
    ui->separator_lineEdit->setToolTip(str);
    setWindowTitle("Text Compare v.1.0.0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile1_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File 1"), "", tr("Text files (*.txt *.csv)"));

    if (fileName == "") return;

    fileName1 = fileName;

    QFileInfo fInfo(fileName);
    ui->openFile1_lineEdit->setText(fInfo.fileName());
}

void MainWindow::on_openFile2_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File 2"), "", tr("Text files (*.txt *.csv)"));

    if (fileName == "") return;

    fileName2 = fileName;

    QFileInfo fInfo(fileName);
    ui->openFile2_lineEdit->setText(fInfo.fileName());
}

void MainWindow::on_run_pushButton_clicked()
{
    ui->dataOut_plainTextEdit->clear();
    dataOut.clear();
    QString separtor(ui->separator_lineEdit->text());
    if (separtor.contains(str_endl))
            separtor.remove(str_endl);
    if (fileParse(fileName1, separtor, data1) && fileParse(fileName2, separtor, data2)){
        for(auto &d: data1){
            if (data2.find(d) != data2.end()){
                dataOut.push_back(d);
            }
        }

        for(auto &d: dataOut){
            ui->dataOut_plainTextEdit->appendPlainText(d);
        }
    }
}

void MainWindow::on_save_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text files (*.txt *.csv)"));

    if (fileName == "") return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ui->dataOut_plainTextEdit->appendPlainText(str_EOpenFile);
        return;
    }

    QTextStream out(&file);

    QString separtor(ui->separator_lineEdit->text());
    if (separtor.contains(str_endl)){
        separtor.remove(str_endl);
        for (auto &d:dataOut)
            out << d << separtor << endl;
    } else {
        for (auto &d:dataOut)
            out << d << separtor;
    }

    file.close();
}

bool MainWindow::fileParse(const QString &fileName, const QString &separator, QSet<QString> &data)
{
    if (fileName.isEmpty()){
        ui->dataOut_plainTextEdit->appendPlainText(str_EFileNameMiss);
        return false;
    }
    QFile file(fileName);
    if (!file.exists()){
        ui->dataOut_plainTextEdit->appendPlainText(str_EFileExists  + ":  " + fileName);
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->dataOut_plainTextEdit->appendPlainText(str_EOpenFile  + ":  " + fileName);
        return false;
    }

    data.clear();
    QStringList list;
    QString str;
    while (!file.atEnd()) {
        str = file.readLine();
        list = str.split(separator);
        for (auto &d: list)
            data.insert(d);
    }
    file.close();

    if (data.isEmpty()){
        ui->dataOut_plainTextEdit->appendPlainText(str_EParsingFile + ":  " + fileName + "\n");
        ui->dataOut_plainTextEdit->appendPlainText(tr("Data:"));
        for (auto &d: data)
            ui->dataOut_plainTextEdit->appendPlainText(d);
        return false;
    }
    return true;
}
