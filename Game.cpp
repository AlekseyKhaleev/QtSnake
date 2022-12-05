#include "Game.h"
#include <QKeyEvent>
#include <QPainter>
#include <qrandom.h>
#include <QTime>
#include <QMessageBox>
#include <QDebug>

Game::Game(){

    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    this->setWindowTitle("Course work: FSM robot");
    initGame();
}

void Game::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);

    if(m_inGame){
        check_apple();
        move();
        check_field();
    }
    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *event){
    int key = event->key();

    if(key == Qt::Key_Left && m_dir != Directions::right){m_dir = Directions::left; }
    if(key == Qt::Key_Right && m_dir != Directions::left){m_dir = Directions::right;}
    if(key == Qt::Key_Up && m_dir != Directions::down)   {m_dir = Directions::up;   }
    if(key == Qt::Key_Down && m_dir != Directions::up)   {m_dir = Directions::down; }

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
        gameOver();
    }
}

void Game::locateApple()
{
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    m_apple.rx() = rand() % DOT_WIDTH;
    m_apple.ry() = rand() % DOT_HEIGHT;
}

void Game::move()
{
    for (int i=m_dots.size()-1;i>0;--i){
        m_dots[i] = m_dots[i-1];
    }

    switch(m_dir){
    case left:  {m_dots[0].rx()-= 1;break;}
    case right: {m_dots[0].rx()+= 1;break;}
    case up:    {m_dots[0].ry()-= 1;break;}
    case down:  {m_dots[0].ry()+= 1;break;}
    default:break;
    }
}

void Game::check_field()
{
    if(m_dots.size()>4){
        for(int i=1;i<m_dots.size();++i){
            if(m_dots[0]==m_dots[i]){
                m_inGame = false;
            }
        }
    }
    if(m_dots[0].x() >= FIELD_WIDTH) {m_inGame=false;}
    if(m_dots[0].x() < 0)            {m_inGame=false;}
    if(m_dots[0].y() >= FIELD_HEIGHT){m_inGame=false;}
    if(m_dots[0].y() < 0)            {m_inGame=false;}

    if(!m_inGame){
        killTimer(m_timerId);
    }
}

void Game::check_apple()
{
    if (m_apple == m_dots[0]){
        m_dots.push_back(QPoint(0,0));
        locateApple();
    }
}

void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Game Over");
    msgb.exec();

    initGame();
}

void Game::initGame(){
    m_inGame=true;
    m_dots.resize(3);
    m_dir = right;
    for (int i=0; i<m_dots.size(); ++i){
        m_dots[i].rx()= m_dots.size() - i-1;
        m_dots[i].ry()=0;
    }
    locateApple();

    m_timerId = startTimer(DELAY);

}
