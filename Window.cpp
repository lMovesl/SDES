#include "Window.h"

Window::Window(QWidget* pwgt) : QWidget(pwgt) {
    plbl1 = new QLabel(this);
    plbl2 = new QLabel(this);
    plbl3 = new QLabel(this);
    pLineEdit = new QLineEdit(this);
    pTextEdit1 = new QTextEdit(this);
    pTextEdit2 = new QTextEdit(this);
    pcmd1 = new QPushButton("&Encode", this);
    pcmd2 = new QPushButton("&Decode", this);
    sdes = new SDES;

    plbl1->setText("Enter &Key (dec or bin)");
    plbl2->setText("Enter &Text");
    plbl3->setText("Decoded Text");
    plbl1->setBuddy(pLineEdit);
    plbl2->setBuddy(pTextEdit1);
    pTextEdit2->setReadOnly(true);

    QGridLayout* pGridLayout = new QGridLayout;
    pGridLayout->addWidget(plbl1, 0, 0);
    pGridLayout->addWidget(pLineEdit, 1, 0, 1, 2);
    pGridLayout->addWidget(plbl2, 2, 0, 1, 2);
    pGridLayout->addWidget(pTextEdit1, 3, 0, 2, 2);
    pGridLayout->addWidget(plbl3, 2, 2, 1, 2);
    pGridLayout->addWidget(pTextEdit2, 3, 2, 2, 2);
    pGridLayout->addWidget(pcmd1, 5, 1);
    pGridLayout->addWidget(pcmd2, 5, 2);

    this->setLayout(pGridLayout);

    QObject::connect(pcmd1, &QPushButton::clicked, this, &Window::slotEncrypt);
    QObject::connect(pcmd2, &QPushButton::clicked, this, &Window::slotDecrypt);
}

void Window::slotEncrypt() {
    QString text = pTextEdit1->toPlainText();
    QString key =  pLineEdit->text();

    if (text.isEmpty() || key.isEmpty()) {
        return ;
    }

    if (text.size() == 1 && !text[0].isDigit())
        text = QString("%1").arg(text[0].toLatin1(), 8, 2, QChar('0'));
    else if (text.size() > 0 && text.size() != 8) {
        text = QString("%1").arg(text.toInt(), 8, 2, QChar('0'));
    }

    if (key.size() != 10) {
        key = QString("%1").arg(key.toInt(), 10, 2, QChar('0'));
    }

    QString bin = sdes->Encode(text, key);
    QString dec = QString::number(sdes->ToDec(bin));
    pTextEdit2->setPlainText("bin: " + bin + "\ndec: " + dec);
}

void Window::slotDecrypt() {
    QString text = pTextEdit1->toPlainText();
    QString key =  pLineEdit->text();

    if (text.isEmpty() || key.isEmpty()) {
        return ;
    }

    if (text.size() == 1 && !text[0].isDigit())
        text = QString("%1").arg(text[0].toLatin1(), 8, 2, QChar('0'));
    else if (text.size() > 0 && text.size() != 8) {
        text = QString("%1").arg(text.toInt(), 8, 2, QChar('0'));
    }

    if (key.size() != 10) {
        key = QString("%1").arg(key.toInt(), 10, 2, QChar('0'));
    }

    QString bin = sdes->Decode(text, key);
    QString dec = QString::number(sdes->ToDec(bin));
    pTextEdit2->setPlainText("bin: " + bin + "\ndec: " + dec);
}
