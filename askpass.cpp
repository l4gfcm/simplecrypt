#include "askpass.h"
#include "ui_askpass.h"

AskPass::AskPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AskPass)
{
    ui->setupUi(this);
}

AskPass::~AskPass()
{
    delete ui;
}

void AskPass::on_buttonBox_accepted()
{
    if(ui->firstPass->text() == ui->secondPass->text() && !ui->firstPass->text().isEmpty() ){
        pass = ui->firstPass->text().toStdString();
        this->close();
    }
    else {
        QMessageBox::warning(this, "GnuPG", "Passphrase is not correct");
    }
}

std::string AskPass::getPass(){
    return pass;
}

void AskPass::on_secondPass_editingFinished()
{
    if(ui->secondPass->text() != ui->firstPass->text()){
        ui->buttonBox->setEnabled(false);
        ui->label_2->setText("Error: Re-type passphrase");
    }
    else {
        ui->buttonBox->setEnabled(true);
    }
}
