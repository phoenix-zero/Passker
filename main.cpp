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
    QLabel label("Enter your password\nBut remember, this app is not secure",&widget);
    QLineEdit input(&widget);
    QPushButton button("Submit",&widget);
    input.setEchoMode(QLineEdit::EchoMode::Password);
    QObject::connect(&button,&QPushButton::clicked,&input,[&input](){
        std::cout << input.text().toStdString() << std::endl;
        exit(0);
    });
    layout.addWidget(&label);
    layout.addWidget(&input);
    layout.addWidget(&button);
    widget.setLayout(&layout);
    widget.show();

    return a.exec();
}
