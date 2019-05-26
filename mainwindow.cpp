#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "askpass.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chipersList = QStringList{"IDEA", "3DES", "CAST5", "BLOWFISH", "AES", "AES192", "AES256", "TWOFISH",
                 "CAMELLIA128", "CAMELLIA192", "CAMELLIA256" };
    ui->encryptComboBox->addItems(chipersList);
    ui->textChipercomboBox->addItems(chipersList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encriptFileChooseButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, "OpenFile", QDir::homePath(), "Any");
    ui->encryptFileLbl->setText(fileName);
}


void MainWindow::on_encryptPushButton_clicked()
{
    if(ui->encryptFileLbl->text() == "Choose File"){
         ui->statusBar->showMessage("Enter a input file", 5000);
         return;
        }

    std::string passphrase;
    AskPass ask(this);
    ask.exec();
    passphrase = ask.getPass();
    if(!passphrase.empty()){
    QProcess gpg;
    gpg.start("gpg", QStringList() << "--passphrase" << QString::fromStdString(passphrase) << "--batch"
              << "--yes"<<  "--symmetric" <<"--cipher-algo" << ui->encryptComboBox->currentText()
                    << ui->encryptFileLbl->text());
    gpg.waitForFinished();

    if(!gpg.exitCode())
        ui->statusBar->showMessage("File is encrypted", 5000);
    else
        ui->statusBar->showMessage("Error", 5000);
    }

}

void MainWindow::on_decryptFileChoseButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, "OpenFile", QDir::homePath(), "Any");
    ui->decryptFileLbl->setText(fileName);
    fileName.remove(fileName.size() -4, fileName.size());
    ui->decriptOutName->setText(fileName);
}


void MainWindow::on_decryptButton_clicked()
{
    if(ui->encryptFileLbl->text() == "Choose File"){
         ui->statusBar->showMessage("Enter a input file", 5000);
         return;
        }
    std::string passphrase;
    AskPass ask(this);
    ask.exec();
    passphrase = ask.getPass();
    if(!passphrase.empty()){
    QProcess gpg;
    gpg.start("gpg", QStringList() << "--passphrase" << QString::fromStdString(passphrase) << "--batch"
              << "--yes"<< "--output" << ui->decriptOutName->text() << "-d" << ui->decryptFileLbl->text());
    gpg.waitForFinished();
    if(!gpg.exitCode())
        ui->statusBar->showMessage("File is decrypted", 5000);
    else
        ui->statusBar->showMessage("Error", 5000);
    }
}

void MainWindow::on_encryptTextButton_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty()){
         ui->statusBar->showMessage("Enter a input text", 5000);
         return;
        }

    std::string passphrase;
    AskPass ask(this);
    ask.exec();
    passphrase = ask.getPass();
    if(!passphrase.empty()){

    QFile tempFile(QDir::homePath() + "/.tempSimpleCrypyt");
    tempFile.open(QIODevice::WriteOnly);
    QTextStream in(&tempFile);
    in << ui->textEdit->toPlainText();
    tempFile.close();

    QProcess gpg;
    gpg.start("gpg", QStringList() << "--passphrase" << QString::fromStdString(passphrase) << "--batch"
              << "--yes"<< "--armor" <<"--output" << QDir::homePath() + "/.tempSimpleCrypyt1"
                    << "--symmetric" <<"--cipher-algo" << ui->textChipercomboBox->currentText() <<
                        QDir::homePath() + "/.tempSimpleCrypyt");
    gpg.waitForFinished();

    QFile tempFile1(QDir::homePath() + "/.tempSimpleCrypyt1");
    tempFile1.open(QIODevice::ReadOnly);

    QTextStream out(&tempFile1);
    ui->textEdit->setText(out.readAll());
    tempFile.remove();
    tempFile1.remove();


    if(!gpg.exitCode())
        ui->statusBar->showMessage("Text is encrypted", 5000);
    else
        ui->statusBar->showMessage("Error", 5000);
    }
}

void MainWindow::on_decryptTextButton_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty()){
             ui->statusBar->showMessage("Enter a input text", 5000);
             return;
            }

        std::string passphrase;
        AskPass ask(this);
        ask.exec();
        passphrase = ask.getPass();
        if(!passphrase.empty()){

        QFile tempFile(QDir::homePath() + "/.tempSimpleCrypyt");
        tempFile.open(QIODevice::WriteOnly);
        QTextStream in(&tempFile);
        in << ui->textEdit->toPlainText();
        in.flush();

        QProcess gpg;
        gpg.start("gpg", QStringList() << "--passphrase" << QString::fromStdString(passphrase)
                  << "--batch" << "--yes" <<"--output" << QDir::homePath() + "/.tempSimpleCrypyt1"
                        << "-d" << QDir::homePath() + "/.tempSimpleCrypyt");
        gpg.waitForFinished();

        QFile tempFile1(QDir::homePath() + "/.tempSimpleCrypyt1");
        tempFile1.open(QIODevice::ReadOnly);
        QTextStream out(&tempFile1);
        ui->textEdit->setText(out.readAll());
        tempFile.remove();
        tempFile1.remove();
        if(!gpg.exitCode())
            ui->statusBar->showMessage("Text is encrypted", 5000);
        else
            ui->statusBar->showMessage("Error", 5000);
        }
}



