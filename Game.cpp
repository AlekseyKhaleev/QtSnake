#include "Game.h"

Game::Game(){

    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    this->setWindowTitle("Course work: FSM robot");

}

void Game::initGame(){
    m_inGame=true;
    m_dots.resize(3);
}
