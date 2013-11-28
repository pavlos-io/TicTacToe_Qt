 #ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

namespace Ui {
    class TicTacToe;
}

class TicTacToe : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicTacToe(QWidget *parent = 0);
    ~TicTacToe();
    QWidget * wind;
    QPushButton * button[3][3];
    QHBoxLayout * hl1;
    QHBoxLayout * hl2;
    QHBoxLayout * hl3;
    QHBoxLayout * hl4;
    QHBoxLayout * hl5;
    QHBoxLayout * main;
    QVBoxLayout * vl1;
    QVBoxLayout * vl2;
    QLabel * lbl;
    QLabel * scoreX;
    QLabel * scoreO;
    QLabel * numX;
    QLabel * numO;
private:
    Ui::TicTacToe *ui;
    int turn;
    QPalette labelPalette;
    bool checkWin();
    void putPalette(QLabel * l);
    void definitions();
    void msg(QString text);
private slots:
    void setButton();
    void reset(bool def);
};


#endif // TICTACTOE_H
