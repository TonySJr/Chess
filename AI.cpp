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
    //��������� ��������� �� ������ ���. ������������� ��������������� ����
    // ������� ������ ������, ����������� �������� ���� ������ �����
    FlagCheckKing = !weight[kingColum + kingRow * ROWS];
    //������� ���������� ������ �����
    //BlackCounter = CountBF(ChessBoard);
    //���������� ��������� ��� ��� AI
    BestAIWeight = 0;
    //�������� ����� � �����
    CopyArray(ChessBoard, TempBoard);
    for (uint8_t y = 0; y < ROWS; y++)
    {
        for (uint8_t x = 0; x < COLUMS; x++)
        {
            //���������� ������ � ������� ��� ������� ��� �� 
            //���������� � ������� ���������� ������ � �����
            //��� ������ ������ ����� ���������� ��� �������
            Thinking(x, y, TempBoard);
        }
    }
    //�� ������ ���
    Swap(ChessBoard, AIColumTurn1, AIRowTurn1, AIColumTurn2, AIRowTurn2);
    AI_turn_flag = false;
    std::cout << " AI make turn!\n";
}
void calculate(uint8_t tempAIRow1, uint8_t tempAIColum1, uint8_t tempAIRow2, uint8_t tempAIColum2)
//��������� ���������� ������ � ����� ���� �� �����������
{
    //�������� ������� ����� � �����,
    CopyArray(ChessBoard, TempBoard);
    //������ ��� �� ����������� ����� �� ���������  ����������� 
    Swap(TempBoard, tempAIColum1, tempAIRow1, tempAIColum2, tempAIRow2);
    //������� ���� �������� ��������� ����� ��� �������� ������������ ����
    weightCalculate(TempBoard);
    //������������ ��� ������� ������� ������(����� ������ ������)
    WBSUMMCalc(BlackSUMM, WhiteSUMM);
    //���� ����� ��� ������� ������ �������, ���������� ��� � ���, ��������� � ����
    if (BlackSUMM > BestAIWeight)
    {
        BestAIWeight = BlackSUMM;
        AIRowTurn1 = tempAIRow1;
        AIColumTurn1 = tempAIColum1;
        AIRowTurn2 = tempAIRow2;
        AIColumTurn2 = tempAIColum2;
    }
}
//������� ����������� ����� ��� ���������� ������� ������� ��
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
    //���������� ������
    char check = array[colum + row * ROWS];
    //� ����������� �� ������ ������� ���������� ������� ������
    switch (check)
    {
    case 'p'://����� ������
    {
        //�� ������� ��������� 4 �������
        for (uint8_t t = 0; t < 100; t++)
        {
            //��� ������ �� 1 ������
            if ((array[colum + (row + 1)*ROWS] == '0') && (t == 0))
                calculate(row, colum, row + 1, colum);
            //��� �� 2 ������ �����
            else if (((array[colum + (row + 2)*ROWS] == '0') && (row == 2)) && (t == 1))
                calculate(row, colum, row + 2, colum);
            //���� ������ ����
            else if (((array[(colum + 1) + (row + 1)*ROWS] == 'P') || (array[(colum + 1) + (row + 1) * ROWS] == 'T') || (array[(colum + 1) + (row + 1) * ROWS] == 'F') || (array[(colum + 1) + (row + 1) * ROWS] == 'S')
                || (array[(colum + 1) + (row + 1) * ROWS] == 'L')) && (t == 2))
                calculate(row, colum, row + 1, colum + 1);
            //���� ����� ����
            else if (((array[(colum - 1) + (row + 1) * ROWS] == 'P') || (array[(colum - 1) + (row + 1) * ROWS] == 'T') || (array[(colum - 1) + (row + 1) * ROWS] == 'F') || (array[(colum - 1) + (row + 1) * ROWS] == 'S')
                || (array[(colum - 1) + (row + 1) * ROWS] == 'L')) && (t == 3))
                calculate(row, colum, row + 1, colum - 1);
            if (t > 3)
                break;
        }
        break;
    }
    case 'l'://���� ������
    {
        //�������� � ������, �������� ����� �������� ���� �������, ������� t  �� ��������
        for (uint8_t t = 0; t < 100; t++)
        {
            //����(���� � �����)
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
            //����(��� � ����)
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
            //�����(��� � ����)
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
            //���(���� � �����)
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
    case 's'://���� ������
    {
        bool sflag = false;
        uint8_t counter = 1;
        //����� �����
        while (sflag == false)
        {
            //�������� �� ����. ���� ��������� ������ ����������, �� ��������� �� ������� ���������� ����
            if (((row - counter) > 0) && ((colum - counter) > 0))
            {
                char tempfigure = array[(colum - counter)+(row - counter)*ROWS];
                //���� ��������� ������ �����, �� ��������� ��� � ���
                if (tempfigure == '0')
                    calculate(row, colum, row - counter, colum - counter);
                //���� ��������� ������ ������ ������� ����������, �� ������ ��� � ��� � ��������� ����
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
        //������ �����
        while (sflag == false)
        {
            //�������� �� ����
            if (((row - counter) > 0) && ((colum + counter) < COLUMS))
            {
                char tempfigure = array[(colum + counter) + (row - counter)*ROWS];
                //���� ��������� ������ �����, �� ��������� ��� � ���
                if (tempfigure == '0')
                    calculate(row, colum, row - counter, colum + counter);
                //���� ��������� ������ ������ ������� ����������, �� ������ ��� � ��� � ��������� ����
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
        //���� �����
        while (sflag == false)
        {
            //�������� �� ����
            if (((row + counter) < ROWS) && ((colum - counter) > 0))
            {
                char tempfigure = array[(colum - counter)+(row + counter)*ROWS];
                //���� ��������� ������ �����, �� ��������� ��� � ���
                if (tempfigure == '0')
                    calculate(row, colum, row + counter, colum - counter);
                //���� ��������� ������ ������ ������� ����������, �� ������ ��� � ��� � ��������� ����
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
        //���� ������
        while (sflag == false)
        {
            //�������� �� ����
            if (((row + counter) < ROWS) && ((colum + counter) < COLUMS))
            {
                char tempfigure = array[(colum + counter)+(row + counter)*ROWS];
                //���� ��������� ������ �����, �� ��������� ��� � ���
                if (tempfigure == '0')
                    calculate(row, colum, row + counter, colum + counter);
                //���� ��������� ������ ������ ������� ����������, �� ������ ��� � ��� � ��������� ����
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