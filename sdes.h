#ifndef SDES_H
#define SDES_H

#include <QObject>
#include <QVector>
#include <QString>

class SDES : public QObject {
Q_OBJECT
public:
    QString m_key1;
    QString m_key2;
    QString ip;

    void p10(QString& key);
    void p8(QString& key);
    void p4(QString& key);
    void leftShift(QString& key, int shift);
    void IP(QString& plaintText);
    void IPRev(QString& plaintText);
    QString F(QString& plaintText, const QString& key);
    QString XOR(QString l, QString r);
    QString GetSL(int row, int col);
    QString GetSR(int row, int col);
    void SW(QString& f, QString& s);
public:
    int ToDec(QString& bin);
    QString Encode(QString text, QString key);
    QString Decode(QString text, QString key);
    SDES(QObject* pobj = nullptr);
    void GenerateKeys(QString& key);

};

#endif // SDES_H
