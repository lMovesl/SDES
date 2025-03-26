#include "sdes.h"

SDES::SDES(QObject* pobj) : QObject(pobj) {}

void SDES::p10(QString& key) {
    QVector<int> newPos = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    QString temp;

    for (int i = 0; i < 10; ++i) {
        temp += key[newPos[i] - 1];
    }

    key = temp;
}

void SDES::p8(QString& key) {
    QVector<int> newPos = {6, 3, 7, 4, 8, 5, 10, 9};
    QString temp;

    for (int i = 0; i < 8; ++i) {
        temp += key[newPos[i] - 1];
    }

    key = temp;
}

void SDES::p4(QString& key) {
    QVector<int> newPos = {2, 4, 3, 1};
    QString temp;

    for (int i = 0; i < 4 ; ++i) {
        temp += key[newPos[i] - 1];
    }

    key = temp;
}

void SDES::leftShift(QString& key, int shift) {
    int n = key.size() / 2;
    QString temp1;
    QString temp2;
    for (int i = 0; i < n; ++i) {
        temp1 += key[i];
        temp2 += key[i + n];
    }

    for (int i = 0; i < n; ++i) {
        key[i] = temp1[(i + shift + n) % n];
        key[i + n] = temp2[(i + shift + n) % n];
    }
}

void SDES::GenerateKeys(QString& key) {
    p10(key);
    leftShift(key, 1);
    p8(m_key1);
    leftShift(key, 2);
    p8(key);
    m_key2 = key;
}

void SDES::IP(QString &plaintText) {
    QVector<int> newPos = {2, 6, 3, 1, 4, 8, 5, 7};
    QString temp = plaintText;

    for (int i = 0; i < 8; ++i) {
        plaintText[i] = temp[newPos[i] - 1];
    }
    ip = plaintText;
}

void SDES::IPRev(QString &plaintText) {
    QVector<int> newPos = {4, 1, 3, 5, 7, 2, 8, 6};
    QString temp = plaintText;

    for (int i = 0; i < 8; ++i) {
        plaintText[i] = temp[newPos[i] - 1];
    }
}

QString SDES::XOR(QString l, QString r) {
    QString result;
    for (int i = 0; i < l.size(); ++i) {
        if (l[i] == r[i])
            result += '0';
        else
            result += '1';
    }

    return result;
}

QString SDES::F(QString& plaintText, const QString& key) {
    QString L = plaintText.sliced(0, 4);
    QString L2 = L;
    QString R = plaintText.sliced(4, 4);

    QVector<int> newPos = {4, 1, 2, 3, 2, 3, 4, 1};
    QString EP;
    for (int i = 0; i < newPos.size(); ++i) {
        EP += R[newPos[i] - 1];
    }

    QString xr = XOR(EP, key);
    L = xr.sliced(0, 4);
    R = xr.sliced(4, 4);

    QString center = L.sliced(1, 2);
    QString sides = L[0];
    sides.append(L[3]);

    int col = ToDec(center);
    int row = ToDec(sides);
    QString l = GetSL(row, col);

    center = R.sliced(1, 2);
    sides = R[0];
    sides.append(R[3]);
    col = ToDec(center);
    row = ToDec(sides);

    QString r = GetSR(row, col);
    QString seq = l + r;
    p4(seq);

    xr = XOR(L2, seq);
    return xr;
}

QString SDES::GetSL(int row, int col) {
    QVector<QVector<QString>> SL = { {"01", "00", "11", "10"},
                                     {"11", "10", "01", "00"},
                                     {"00", "10", "01", "11"},
                                     {"11", "01", "11", "01"} };

    return SL[row][col];
}
QString SDES::GetSR(int row, int col) {
    QVector<QVector<QString>> SR = { {"01", "01", "10", "11"},
                                     {"10", "00", "01", "11"},
                                     {"11", "00", "01", "00"},
                                     {"10", "01", "00", "11"} };

    return SR[row][col];
}

void SDES::SW(QString& f, QString& s){
    swap(f, s);
}

int SDES::ToDec(QString& bin) {
    int num = bin.toInt();
    int dec = 0, last;
    int i = 0;

    while (num > 0)
    {
        last = num % 10;
        if (last == 1) dec = dec + pow(2, i);
        num = num / 10;
        i = i + 1;
    }

    return dec;
}

QString SDES::Encode(QString text, QString key) {
    GenerateKeys(key);
    IP(text);

    QString L = text.sliced(0, 4);
    QString R = text.sliced(4, 4);

    L = F(text, m_key1);

    SW(L, R);

    text = L + R;
    L = F(text, m_key2);
    text = L + R;
    IPRev(text);

    return text;
}

QString SDES::Decode(QString text, QString key) {
    GenerateKeys(key);
    IP(text);

    QString L = text.sliced(0, 4);
    QString R = text.sliced(4, 4);

    L = F(text, m_key2);

    SW(L, R);

    text = L + R;
    L = F(text, m_key1);
    text = L + R;
    IPRev(text);

    return text;
}
