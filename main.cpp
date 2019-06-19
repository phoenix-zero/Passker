#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDialog widget;
    QVBoxLayout layout(&widget);
    QHBoxLayout passField;
    QLabel label(((argc<2)?"Called for more-or-less nothing":argv[1]));
    QLineEdit input;
    QPushButton button("Submit"), showPass;
    input.setEchoMode(QLineEdit::EchoMode::Password);
    showPass.setIcon(QIcon(":/inv"));
    QObject::connect(&button,&QPushButton::clicked,&input,[&input](){
        std::cout << input.text().toStdString() << std::endl;
        exit(0);
    });
    QObject::connect(&input,&QLineEdit::returnPressed,&button,&QPushButton::click);
    QObject::connect(&showPass,&QPushButton::clicked,&input,[&input,&showPass](){
        if(input.echoMode() == QLineEdit::EchoMode::Password)
        {
            input.setEchoMode(QLineEdit::EchoMode::Normal);
            showPass.setIcon(QIcon(":/vis"));
        }
        else
        {
            input.setEchoMode(QLineEdit::EchoMode::Password);
            showPass.setIcon(QIcon(":/inv"));
        }
    });
    layout.addWidget(&label);
    passField.addWidget(&input);
    passField.addWidget(&showPass);
    layout.addLayout(&passField);
    layout.addWidget(&button);
    widget.show();

    return a.exec();
}
