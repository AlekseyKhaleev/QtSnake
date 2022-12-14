#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>


class Game : public QWidget
{
public:
    Game();

protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:

    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;
    static const int DELAY = 150;

    void doDrawing();
    void locateApple();
    void move();
    void check_field();
    void check_apple();
    void gameOver();


    int m_timerId;
    QPoint m_apple;

    enum Directions{
        left, right, up, down
    } m_dir;

    bool m_inGame;

    QVector<QPoint> m_dots;

    void initGame();
};

