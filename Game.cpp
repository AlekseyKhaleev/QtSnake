#include "Game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <qrandom.h>
#include <QTime>

Game::Game(){

    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    this->setWindowTitle("Course work: FSM robot");
    initGame();
}

void Game::timerEvent(QTimerEvent *){
    //qDebug()<<1;
}

void Game::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    switch(key){
    case Qt::Key_Left:
        qDebug() <<"Key_Left";
        break;
    case Qt::Key_Right:
        qDebug()<<"Key_Right";
        break;
    case Qt::Key_Up:
        qDebug()<<"Key_Up";
        break;
    default:
        break;
    };
}

void Game::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    doDrawing();
}

void Game::doDrawing()
{
    QPainter qp(this);
    if (m_inGame){
        qp.setBrush(Qt::red);
        qp.drawEllipse(m_apple.x()*DOT_WIDTH, m_apple.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        for(int i=0; i<m_dots.size();++i){
            if(i==0){
                qp.setBrush(Qt::white);
                qp.drawEllipse(m_dots[i].x()*DOT_WIDTH, m_dots[i].y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

            }else{
                qp.setBrush(Qt::green);
                qp.drawEllipse(m_dots[i].x()*DOT_WIDTH, m_dots[i].y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

            }
        }

    }else{
        //gameOver();
    }
}

void Game::localApple()
{
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    m_apple.rx() = rand() % DOT_WIDTH;
    m_apple.ry() = rand() % DOT_HEIGHT;
}

void Game::initGame(){
    m_inGame=true;
    m_dots.resize(3);
    m_dir = right;
    for (int i=0; i<m_dots.size(); ++i){
        m_dots[i].rx()= m_dots.size() - i;
        m_dots[i].ry()=0;
    }
    localApple();

    timerId = startTimer(DELAY);

}
