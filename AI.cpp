#include "pch.h"
#include "FigureNames.h"
#include "functions.h"
#include "AIDef.h"

extern void weightCalculate(char*);
extern void WBSUMMCalc(uint8_t&, uint8_t&);

void CopyArray(char* arrayFrom, char* arrayTo);
void Thinking(uint8_t colum, uint8_t row, char* array);
char TempBoard[Board_Cells];
int8_t weight[Board_Cells];

void AI_Main_Function()
{
    weightCalculate(ChessBoard);
    //проверяем поставлен ли королю шах. устанавливаем соответствующий флаг
    // смотрим клетку короля, присваеваем значение веса клетки флагу
    FlagCheckKing = !weight[kingColum + kingRow * ROWS];
    //считаем количество черных фигур
    //BlackCounter = CountBF(ChessBoard);
    //записываем начальный вес для AI
    BestAIWeight = 0;
    //копируем доску в буфер
    CopyArray(ChessBoard, TempBoard);
    for (uint8_t y = 0; y < ROWS; y++)
    {
        for (uint8_t x = 0; x < COLUMS; x++)
        {
            //опрелеляем фигуру и считаем все позиции для неё 
            //отправляем в функцию координаты клетки и доску
            //для каждой клетки будет вызываться это функция
            Thinking(x, y, TempBoard);
        }
    }
    //ИИ делает ход
    Swap(ChessBoard, AIColumTurn1, AIRowTurn1, AIColumTurn2, AIRowTurn2);
    AI_turn_flag = false;
    std::cout << " AI make turn!\n";
}
void calculate(uint8_t tempAIRow1, uint8_t tempAIColum1, uint8_t tempAIRow2, uint8_t tempAIColum2)
//принимает координаты фигуры и места куда ее передвинуть
{
    //копируем главную доску в буфер,
    CopyArray(ChessBoard, TempBoard);
    //делаем ход на виртуальной доске по пришедшим  координатам 
    Swap(TempBoard, tempAIColum1, tempAIRow1, tempAIColum2, tempAIRow2);
    //считаем веса текущего состояния доски для подсчета позиционного веса
    weightCalculate(TempBoard);
    //рассчитываем вес позиции каждого игрока(важен только черный)
    WBSUMMCalc(BlackSUMM, WhiteSUMM);
    //если новый вес позиций больше старого, записываем его и ход, приведший к нему
    if (BlackSUMM > BestAIWeight)
    {
        BestAIWeight = BlackSUMM;
        AIRowTurn1 = tempAIRow1;
        AIColumTurn1 = tempAIColum1;
        AIRowTurn2 = tempAIRow2;
        AIColumTurn2 = tempAIColum2;
    }
}
//функция копирования доски для временного расчета позиций ИИ
void CopyArray(char* arrayFrom, char* arrayTo)
{
    for (uint8_t x = 0; x < ROWS; x++)
    {
        for (uint8_t y = 0; y < COLUMS; y++)
        {
            arrayTo[x + y * ROWS] = arrayFrom[x + y * ROWS];
        }
    }
}
void Thinking(uint8_t colum, uint8_t row, char* array)
{
    //определяем фигуру
    char check = array[colum + row * ROWS];
    //в зависимости от фигуры считаем возможнные позиции фигуры
    switch (check)
    {
    case 'p'://Пешка черных
    {
        //по очереди проверяем 4 позиции
        for (uint8_t t = 0; t < 100; t++)
        {
            //ход вперед на 1 клетку
            if ((array[colum + (row + 1)*ROWS] == '0') && (t == 0))
                calculate(row, colum, row + 1, colum);
            //ход на 2 клетки врерёд
            else if (((array[colum + (row + 2)*ROWS] == '0') && (row == 2)) && (t == 1))
                calculate(row, colum, row + 2, colum);
            //удар вправо вниз
            else if (((array[(colum + 1) + (row + 1)*ROWS] == 'P') || (array[(colum + 1) + (row + 1) * ROWS] == 'T') || (array[(colum + 1) + (row + 1) * ROWS] == 'F') || (array[(colum + 1) + (row + 1) * ROWS] == 'S')
                || (array[(colum + 1) + (row + 1) * ROWS] == 'L')) && (t == 2))
                calculate(row, colum, row + 1, colum + 1);
            //удар влево вниз
            else if (((array[(colum - 1) + (row + 1) * ROWS] == 'P') || (array[(colum - 1) + (row + 1) * ROWS] == 'T') || (array[(colum - 1) + (row + 1) * ROWS] == 'F') || (array[(colum - 1) + (row + 1) * ROWS] == 'S')
                || (array[(colum - 1) + (row + 1) * ROWS] == 'L')) && (t == 3))
                calculate(row, colum, row + 1, colum - 1);
            if (t > 3)
                break;
        }
        break;
    }
    case 'l'://Конь черных
    {
        //проблема с циклом, возможно когда сходятся одни условия, условие t  не сходится
        for (uint8_t t = 0; t < 100; t++)
        {
            //верх(лево и право)
            if ((((row - 2) > 0) && ((colum - 1) > 0)) &&
                ((array[(colum - 1)+(row - 2)*ROWS] == '0') || (array[(colum - 1) + (row - 2) * ROWS] == 'P') || (array[(colum - 1) + (row - 2) * ROWS] == 'T') || (array[(colum - 1) + (row - 2) * ROWS] == 'S')
                    || (array[(colum - 1) + (row - 2) * ROWS] == 'F') || (array[(colum - 1) + (row - 2) * ROWS] == 'L')) &&
                (t == 0))
            {
                calculate(row, colum, row - 2, colum - 1);
            }
            else if ((((row - 2) > 0) && ((colum + 1) < COLUMS)) &&
                ((array[(colum + 1)+(row - 2)*ROWS] == '0') || (array[(colum + 1) + (row - 2) * ROWS] == 'P') || (array[(colum + 1) + (row - 2) * ROWS] == 'T') || (array[(colum + 1) + (row - 2) * ROWS] == 'S')
                    || (array[(colum + 1) + (row - 2) * ROWS] == 'F') || (array[(colum + 1) + (row - 2) * ROWS] == 'L')) &&
                (t == 1))
            {
                calculate(row, colum, row - 2, colum + 1);
            }
            //лево(низ и верх)
            else if ((((row - 1) > 0) && ((colum - 2) > 0)) &&
                ((array[(colum - 2)+(row -1)*ROWS] == '0') || (array[(colum - 2) + (row - 1) * ROWS] == 'P') || (array[(colum - 2) + (row - 1) * ROWS] == 'T') || (array[(colum - 2) + (row - 1) * ROWS] == 'S')
                    || (array[(colum - 2) + (row - 1) * ROWS] == 'F') || (array[(colum - 2) + (row - 1) * ROWS] == 'L')) &&
                (t == 2))
            {
                calculate(row, colum, row - 1, colum - 2);
            }
            else if ((((row + 1) < ROWS) && ((colum - 2) > 0)) &&
                ((array[(colum - 2)+(row+1)*ROWS] == '0') || (array[(colum - 2) + (row + 1) * ROWS] == 'P') || (array[(colum - 2) + (row + 1) * ROWS] == 'T') || (array[(colum - 2) + (row + 1) * ROWS] == 'S')
                    || (array[(colum - 2) + (row + 1) * ROWS] == 'F') || (array[(colum - 2) + (row + 1) * ROWS] == 'L')) &&
                (t == 3))
            {
                calculate(row, colum, row + 1, colum - 2);
            }
            //право(низ и верх)
            else if ((((row - 1) > 0) && ((colum + 2) < COLUMS)) &&
                ((array[(colum + 2)+(row -1)*ROWS] == '0') || (array[(colum + 2) + (row - 1) * ROWS] == 'P') || (array[(colum + 2) + (row - 1) * ROWS] == 'T') || (array[(colum + 2) + (row - 1) * ROWS] == 'S')
                    || (array[(colum + 2) + (row - 1) * ROWS] == 'F') || (array[(colum + 2) + (row - 1) * ROWS] == 'L')) &&
                (t == 4))
            {
                calculate(row, colum, row - 1, colum + 2);
            }
            else if ((((row + 1) < ROWS) && ((colum + 2) < COLUMS)) &&
                ((array[(colum + 2)+(row + 1)*ROWS] == '0') || (array[(colum + 2) + (row + 1) * ROWS] == 'P') || (array[(colum + 2) + (row + 1) * ROWS] == 'T') || (array[(colum + 2) + (row + 1) * ROWS] == 'S')
                    || (array[(colum + 2) + (row + 1) * ROWS] == 'F') || (array[(colum + 2) + (row + 1) * ROWS] == 'L')) &&
                (t == 5))
            {
                calculate(row, colum, row + 1, colum + 2);
            }
            //низ(лево и право)
            else if ((((row + 2) < ROWS) && ((colum - 1) > 0)) &&
                ((array[(colum - 1)+(row +2)*ROWS] == '0') || (array[(colum - 1) + (row + 2) * ROWS] == 'P') || (array[(colum - 1) + (row + 2) * ROWS] == 'T') || (array[(colum - 1) + (row + 2) * ROWS] == 'S')
                    || (array[(colum - 1) + (row + 2) * ROWS] == 'F') || (array[(colum - 1) + (row + 2) * ROWS] == 'L')) &&
                (t == 6))
            {
                calculate(row, colum, row + 2, colum - 1);
            }
            else if ((((row + 2) < ROWS) && ((colum + 1) < COLUMS)) &&
                ((array[(colum + 1)+(row+2)*ROWS] == '0') || (array[(colum + 1) + (row + 2) * ROWS] == 'P') || (array[(colum + 1) + (row + 2) * ROWS] == 'T') || (array[(colum + 1) + (row + 2) * ROWS] == 'S')
                    || (array[(colum + 1) + (row + 2) * ROWS] == 'F') || (array[(colum + 1) + (row + 2) * ROWS] == 'L')) &&
                (t == 7))
            {
                calculate(row, colum, row + 2, colum + 1);
            }
            if (t > 7)
                break;
        }
        break;
    }
    case 's'://Слон черных
    {
        bool sflag = false;
        uint8_t counter = 1;
        //Влево вверх
        while (sflag == false)
        {
            //проверка на край. если следующая клетка существует, то проверяем на наличие возможного хода
            if (((row - counter) > 0) && ((colum - counter) > 0))
            {
                char tempfigure = array[(colum - counter)+(row - counter)*ROWS];
                //если следующая клетка пуста, то проверяем ход с ней
                if (tempfigure == '0')
                    calculate(row, colum, row - counter, colum - counter);
                //если следующая клетка занята фигурой противника, то делаем ход в нее и поднимаем флаг
                else if (tempfigure == 'P' || tempfigure == 'T' || tempfigure == 'L' || tempfigure == 'F' || tempfigure == 'S')
                {
                    calculate(row, colum, row - counter, colum - counter);
                    sflag = true;
                }
                else if (tempfigure != 'p' || tempfigure != 's' || tempfigure != 'f' || tempfigure != 'k' || tempfigure != 'l' || tempfigure != 't')
                    sflag = true;
            }
            else {
                sflag = true;
            }
            counter++;
        }
        sflag = false;
        counter = 1;
        //вправо вверх
        while (sflag == false)
        {
            //проверка на край
            if (((row - counter) > 0) && ((colum + counter) < COLUMS))
            {
                char tempfigure = array[(colum + counter) + (row - counter)*ROWS];
                //если следующая клетка пуста, то проверяем ход с ней
                if (tempfigure == '0')
                    calculate(row, colum, row - counter, colum + counter);
                //если следующая клетка занята фигурой противника, то делаем ход в нее и поднимаем флаг
                else if (tempfigure == 'P' || tempfigure == 'T' || tempfigure == 'L' || tempfigure == 'F' || tempfigure == 'S')
                {
                    calculate(row, colum, row - counter, colum + counter);
                    sflag = true;
                }
                else if (tempfigure != 'p' || tempfigure != 's' || tempfigure != 'f' || tempfigure != 'k' || tempfigure != 'l' || tempfigure != 't')
                    sflag = true;
            }
            else {
                sflag = true;
            }
            counter++;
        }
        sflag = false;
        counter = 1;
        //Вниз влево
        while (sflag == false)
        {
            //проверка на край
            if (((row + counter) < ROWS) && ((colum - counter) > 0))
            {
                char tempfigure = array[(colum - counter)+(row + counter)*ROWS];
                //если следующая клетка пуста, то проверяем ход с ней
                if (tempfigure == '0')
                    calculate(row, colum, row + counter, colum - counter);
                //если следующая клетка занята фигурой противника, то делаем ход в нее и поднимаем флаг
                else if (tempfigure == 'P' || tempfigure == 'T' || tempfigure == 'L' || tempfigure == 'F' || tempfigure == 'S')
                {
                    calculate(row, colum, row + counter, colum - counter);
                    sflag = true;
                }
                else if (tempfigure != 'p' || tempfigure != 's' || tempfigure != 'f' || tempfigure != 'k' || tempfigure != 'l' || tempfigure != 't')
                    sflag = true;
            }
            else {
                sflag = true;
            }
            counter++;
        }
        sflag = false;
        counter = 1;
        //Вниз вправо
        while (sflag == false)
        {
            //проверка на край
            if (((row + counter) < ROWS) && ((colum + counter) < COLUMS))
            {
                char tempfigure = array[(colum + counter)+(row + counter)*ROWS];
                //если следующая клетка пуста, то проверяем ход с ней
                if (tempfigure == '0')
                    calculate(row, colum, row + counter, colum + counter);
                //если следующая клетка занята фигурой противника, то делаем ход в нее и поднимаем флаг
                else if (tempfigure == 'P' || tempfigure == 'T' || tempfigure == 'L' || tempfigure == 'F' || tempfigure == 'S')
                {
                    calculate(row, colum, row + counter, colum + counter);
                    sflag = true;
                }
                else if (tempfigure != 'p' || tempfigure != 's' || tempfigure != 'f' || tempfigure != 'k' || tempfigure != 'l' || tempfigure != 't')
                    sflag = true;
            }
            else {
                sflag = true;
            }
            counter++;
        }
        break;
    }
    }
}