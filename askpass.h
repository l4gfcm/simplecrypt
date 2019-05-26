#ifndef ASKPASS_H
#define ASKPASS_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AskPass;
}

class AskPass : public QDialog
{
    Q_OBJECT

public:
    explicit AskPass(QWidget *parent = nullptr);
    ~AskPass();
    std::string getPass();

private slots:
    void on_buttonBox_accepted();
    void on_secondPass_editingFinished();

private:
    Ui::AskPass *ui;
    std::string pass;
};

#endif // ASKPASS_H
