#ifndef WINDOW_H
#define WINDOW_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include "sdes.h"

class Window : public QWidget {
    Q_OBJECT
private:
    QLabel* plbl1;
    QLabel* plbl2;
    QLabel* plbl3;
    QLineEdit* pLineEdit;
    QTextEdit* pTextEdit1 ;
    QTextEdit* pTextEdit2;
    QPushButton* pcmd1;
    QPushButton* pcmd2;
    SDES* sdes;

public:
    Window(QWidget* pwgt = nullptr);
public slots:
    void slotEncrypt();
    void slotDecrypt();
};

#endif // WINDOW_H
