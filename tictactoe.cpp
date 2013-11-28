#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QMessageBox>
#include <QListView>
#include <QDesktopWidget>
#include <QTextCodec>

TicTacToe::TicTacToe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icon.png"));

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":/images/1.png")));
    this->setPalette(palette);
    definitions();
}

TicTacToe::~TicTacToe()
{
    delete ui;
}

void TicTacToe::reset(bool def)
{
    turn = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int ii = 0; ii < 3; ii++)
        {
            if (def)
            {
                button[i][ii] = new QPushButton(this);
                button[i][ii]->setStyleSheet("*{background-color: rgba(1, 40, 83, 100)}");
                button[i][ii]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            }

            button[i][ii]->setIcon(QIcon());
            button[i][ii]->setProperty("player", i+ii+i*ii);
            connect(button[i][ii], SIGNAL(clicked()), this, SLOT(setButton()));
        }
    }
}

void TicTacToe::setButton()
{
    turn++;
    if (turn % 2 != (numX->text().toInt() + numO->text().toInt()) % 2) //If plays X
    {
                ((QPushButton *)sender())->setIcon(QIcon(":/images/ex.png"));
                ((QPushButton *)sender())->setProperty("player", 'x');
                ((QPushButton *)sender())->setIconSize(QSize(64,64));
                ((QPushButton *)sender())->disconnect();
                lbl->setText("<b>'O' Plays</b>");
                if (checkWin())
                {
                    lbl->setText("<b>'X' Has Won!</b>");
                    numX->setNum(numX->text().toInt() + 1);
                    msg("X has won.Do you want to play again?");
                }
    }
    else if (turn % 2 == (numX->text().toInt() + numO->text().toInt()) % 2) //If plays O
    {
                ((QPushButton *)sender())->setIcon(QIcon(":/images/o.png"));
                ((QPushButton *)sender())->setProperty("player", 'o');
                ((QPushButton *)sender())->setIconSize(QSize(64,64));
                ((QPushButton *)sender())->disconnect();
                lbl->setText(QString::fromLocal8Bit("<b>'X' Plays</b>"));
                if (checkWin())
                {
                    lbl->setText(QString::fromLocal8Bit("<b>'O' Has Won!</b>"));
                    numO->setNum(numO->text().toInt() + 1);
                    msg("O has won.Do you want to play again?");
                }
    }

    if(turn > 8 && !checkWin())
    {
                lbl->setText("<b>Draw!</b>");
                    msg("Draw.Do you want to play again?");
    }

}

bool TicTacToe::checkWin()
{
    int h,v;
    for(int i = 0; i < 3; i++)
    {
        h=0;
        v=0;
        for(int ii = 0; ii < 3; ii++)
        {
            if(button[i][ii]->property("player") == button[i][0]->property("player"))
                h++;
            if(button[ii][i]->property("player")==button[0][i]->property("player"))
                v++;
        }

    if(h == 3 || v == 3)
        return true;
}
    if(button[0][0]->property("player") == button[1][1]->property("player") && button[1][1]->property("player") == button[2][2]->property("player"))
        return true;
    if(button[1][1]->property("player") == button[2][0]->property("player") && button[1][1]->property("player") == button[0][2]->property("player"))
        return true;
    return false;
}
void TicTacToe::putPalette(QLabel * l)
{
    labelPalette = l->palette();
    labelPalette.setColor(l->backgroundRole(), Qt::white);
    labelPalette.setColor(l->foregroundRole(), Qt::white);
    l->setPalette(labelPalette);
}
void TicTacToe::definitions()
{

    wind = new QWidget;
    this->setFixedSize(400, 271);

    numX = new QLabel(this);
    putPalette(numX);
    numX->setText("0");

    numO = new QLabel(this);
    putPalette(numO);
    numO->setText("0");

    reset(true);

    hl1 = new QHBoxLayout;
    hl2 = new QHBoxLayout;
    hl3 = new QHBoxLayout;
    hl4 = new QHBoxLayout;
    hl5 = new QHBoxLayout;
    vl1 = new QVBoxLayout;
    vl2 = new QVBoxLayout;
    main = new QHBoxLayout;



    hl1->addWidget(button[0][0]);
    hl1->addWidget(button[0][1]);
    hl1->addWidget(button[0][2]);

    hl2->addWidget(button[1][0]);
    hl2->addWidget(button[1][1]);
    hl2->addWidget(button[1][2]);

    hl3->addWidget(button[2][0]);
    hl3->addWidget(button[2][1]);
    hl3->addWidget(button[2][2]);

    lbl = new QLabel("<b>'X' Plays</b>", this);
    putPalette(lbl);
    scoreX = new QLabel("X's Score: ", this);
    putPalette(scoreX);
    scoreO = new QLabel("O's score: ", this);
    putPalette(scoreO);

    hl4->addWidget(scoreX);
    hl4->addWidget(numX);

    hl5->addWidget(scoreO);
    hl5->addWidget(numO);

    vl1->addLayout(hl1);
    vl1->addLayout(hl2);
    vl1->addLayout(hl3);

    vl2->addWidget(lbl);
    vl2->addSpacing(5);
    vl2->addLayout(hl4);
    vl2->addLayout(hl5);
    vl2->addStretch();

    main->addLayout(vl1);
    main->addLayout(vl2);

    wind->setLayout(main);
    TicTacToe::setCentralWidget(wind);
}

void TicTacToe::msg(QString text)
{

    int msgbox = QMessageBox::question(this, ("Game Over!"), text,
                                        QMessageBox::Yes | QMessageBox::No);
    if(msgbox == QMessageBox::No)
     this->close();
    else if(msgbox == QMessageBox::Yes)
      reset(false);
}

