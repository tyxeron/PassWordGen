#include "passwordgen.h"
#include "ui_mainwindow.h"

#include <QClipboard>

PassWordGen::PassWordGen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassWordGen)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(450, 400));

    QValidator *validator = new QIntValidator(1, 999, this);

    // the edit lineedit will only accept integers between 100 and 999
    ui->lengthCombo->setValidator(validator);

}

PassWordGen::~PassWordGen()
{
    delete ui;
}

void PassWordGen::generate(){
    std::string file_name = "result.txt" ;
    std::string alphNumOnlyCharset = "'A-Za-z0-9'";
    std::string extendedCharset = "'A-Za-z0-9!\"#$%&*+,-./:;<=>?@[\\]^_`{|}~()'"; //TODO  ADD '

    std::string command = "</dev/urandom tr -dc ";
    std::string lengthCommand ="| head -c ";

    bool alphaNumericalOnly=ui->alphaNumCheckbox->checkState();
    bool ok;
    int length =ui->lengthCombo->currentText().toInt();

    if(alphaNumericalOnly){
        command.append(alphNumOnlyCharset);
    }else{
        command.append(extendedCharset);
    }

    command.append(lengthCommand);
    command.append(std::to_string(length));

    //Redirect stderr to stdout
    command.append(" 2>&1");

    std::string password;
    FILE * stream;
    const int max_buffer = 256; //MAX LENGTH
    char buffer[max_buffer];


    stream = popen(command.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != nullptr) password.append(buffer);
    pclose(stream);
    }

    QString signal = QString(password.c_str());

     emit passwordGenerated(signal);

}

void PassWordGen::copyclip(){
    QClipboard *clipboard = QApplication::clipboard();
    const QString password = ui->passwordEdit->text();

    clipboard->setText(password);
}
