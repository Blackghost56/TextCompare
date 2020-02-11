#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFile1_pushButton_clicked();

    void on_openFile2_pushButton_clicked();

    void on_run_pushButton_clicked();

    void on_save_pushButton_clicked();

private:
    bool fileParse(const QString &fileName, const QString &separator, QSet<QString> &data);
    Ui::MainWindow *ui;
    QSet<QString> data1;
    QSet<QString> data2;
    QList<QString> dataOut;
    const QString str_endl = "endl";
    const QString str_EFileNameMiss = tr("Error file name is missing");
    const QString str_EFileExists = tr("Error file is not exists");
    const QString str_EOpenFile = tr("Error opening file");
    const QString str_EParsingFile = tr("Error parsing file");
    QString fileName1;
    QString fileName2;
};

#endif // MAINWINDOW_H
