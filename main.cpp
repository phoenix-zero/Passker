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
    QHBoxLayout passField(&widget);
    QLabel label("Enter your password\nBut remember, this app is not secure",&widget);
    QLineEdit input(&widget);
    QPushButton button("Submit",&widget), showPass(&widget);
    input.setEchoMode(QLineEdit::EchoMode::Password);
    showPass.setFlat(true);
    QObject::connect(&button,&QPushButton::clicked,&input,[&input](){
        std::cout << input.text().toStdString() << std::endl;
        exit(0);
    });
    QObject::connect(&input,&QLineEdit::returnPressed,&button,&QPushButton::click);
    QObject::connect(&showPass,&QPushButton::clicked,&input,[&input](){
        if(input.echoMode() == QLineEdit::EchoMode::Password)
            input.setEchoMode(QLineEdit::EchoMode::Normal);
        else
            input.setEchoMode(QLineEdit::EchoMode::Password);
    });
    layout.addWidget(&label);
    passField.addWidget(&input);
    passField.addWidget(&showPass);
    layout.addLayout(&passField);
    layout.addWidget(&button);
    widget.setLayout(&layout);
    widget.show();

    return a.exec();
}
