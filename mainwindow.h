#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <sstream>
#include <QProcess>
#include <QTextStream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_encriptFileChooseButton_clicked();

    void on_encryptPushButton_clicked();

    void on_decryptFileChoseButton_clicked();

    void on_decryptButton_clicked();

    void on_encryptTextButton_clicked();

    void on_decryptTextButton_clicked();


private:
    Ui::MainWindow *ui;
    QStringList chipersList;

};

#endif // MAINWINDOW_H
