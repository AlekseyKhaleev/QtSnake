#pragma once

#include <iostream>
#include <memory>
#include <QPoint>


/*********************** Константы и макроопределения, используемые для работы с классами *****************************/
namespace Fsm_const {

#define ESC                     "\x1B" // начало выражения
    /* переместить курсор в строку row и позицию col */
#define move_cursor(row, col)   std::cout << ESC "[" << (row) << ";" << (col) << "H"

#define L_ARR "\u2B05"
#define R_ARR "\u27a1"
#define U_ARR "\u2B06"
#define D_ARR "\u2B07"

    const int START_ROW = 15;  // Номер строки для начала ввода/вывода данных таблицы
    const int START_ROW_FR = 11;  // Номер строки для начала отрисовки таблицы (FR - Frame)
    const int START_COL = 7;   // Позиция курсора для начала ввода/вывода данных таблицы
    const int STEP_COL = 17;  // Шаг для перемещения позиции курсора при выводе таблицы
    const int STEP_ROW = 3;   // Шаг для перемещения по строкам курсора при выводе таблицы
    const int NUMB_OF_ATTR = 6;
    const int NUMB_OF_ATTR_WR = 4;


}

/***************************** Определения для удобства работы с классами *********************************************/
class IFsm;
using FsmPtr = std::shared_ptr<IFsm>;
using namespace Fsm_const;
typedef bool signal[2];

/**********************************************************************************************************************/

class IFsm {
protected:
    virtual ~IFsm() = default; // защищенный деструктор
    IFsm& operator=(const IFsm&) = default; // запрет присваивания
    [[nodiscard]] static FsmPtr CreateInstance(); // функция-фабрика

    virtual void SetState(bool (*state)())=0;
    virtual void Update()=0;
public:
    virtual QPoint SigHandle(signal sig)=0;

};



class Robot : public IFsm{
private:
    QPoint CS{0, 0};
    QPoint DS{0, 1};
    const char *arrow = U_ARR;

    bool (*ActiveState)()= nullptr; // указатель на активное состояние автомата

    void SetState(bool (*state)()) override;;
    void Update() override;;
    const char * GetArrow(); ;
    static bool wait(signal sig = nullptr);;

    static bool analyze();
    static bool turn();
    static bool move();
    static bool exit();
    static bool left();
    static bool right();

public:
    QPoint SigHandle(signal sig) override;;
    Robot();           // открытый конструктор
    ~Robot() override; // открытый деструктор
};


