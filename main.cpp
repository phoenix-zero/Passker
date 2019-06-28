#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <iostream>
#ifdef Q_OS_WIN32
# include <windows.h>
#else
# include <X11/XKBlib.h>
#endif


std::pair<bool,bool> checkLock()
{
    // platform dependent method of determining if CAPS LOCK is on
#ifdef Q_OS_WIN32 // MS Windows version
    return GetKeyState(VK_CAPITAL) == 1;
#else // X11 version (Linux/Unix/Mac OS X/etc...)
    Display * d = XOpenDisplay(static_cast<char*>(nullptr));
    bool caps_state = false, num_state = false;
    if (d)
    {
        unsigned n;
        XkbGetIndicatorState(d, XkbUseCoreKbd, &n);
        caps_state = (n & 0x01) == 1;
        num_state = (n & 0x02) == 2;
    }
    return {caps_state, num_state};
#endif
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDialog widget;
    QVBoxLayout layout(&widget);
    QHBoxLayout passField;
    QLabel label(((argc<2)?"Called for more-or-less nothing":argv[1]));
    QLineEdit input;
    QPushButton button("Submit"), showPass;
    auto [caps,nums] = checkLock();

    if(nums)
        label.setText(label.text() + "\nHint: Num lock is on");
    if(caps)
        label.setText(label.text() + "\nHint: Caps lock is on");

    input.setEchoMode(QLineEdit::EchoMode::Password);
    showPass.setIcon(QIcon(":/inv"));
    QObject::connect(&button,&QPushButton::clicked,&input,[&input]()
    {
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
