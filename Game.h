#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>

class Game : public QWidget
{
public:
    Game();
private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;

    bool m_inGame;

    QVector<QPoint> m_dots;

    void initGame();
};

