#include "pch.h"
#include "FigureNames.h"
#include "functions.h"
//#include "AIDef.h"

extern int8_t weight[];
extern uint8_t kingRow, kingColum;
extern int8_t KingRows[];
extern int8_t KingColums[];
//алгоритм определения весов
//j - x i - y
void weightCalculate(char* array)
{
  for(uint8_t y = 1; y < ROWS; y++)
  {
    for(uint8_t x = 1; x < COLUMS; x++)
    {
      //если на данной ячейке фигура, то пересчитываем веса позиций
      char check = array[x+y*ROWS];
      switch (check){
        case 'p'://Пешка черных
        {
          weight[x + y * ROWS]++;
          //проверка на край
          if((y+1) < ROWS)
          {
            if(((x+1) < COLUMS) && (array[(x + 1)+(y + 1)*ROWS] != 'k'))
              weight[(x + 1) + (y + 1) * ROWS]++;
            if(((x-1) > 0) && (array[(x-1)+(y + 1)*ROWS] != 'k'))
              weight[(x - 1) + (y + 1) * ROWS]++;
          }
          break;
        }
        case 'P'://Пешка белых
        {
          weight[x + y * ROWS]--;
          //проверка на край
          if((y-1) > 0)
          {
            if(((x+1) < COLUMS) && (array[(x+1)+(y - 1) * ROWS] != 'K'))
              weight[(x + 1) + (y - 1) * ROWS]--;
            if(((x-1) > 0) && (array[(x - 1) + (y - 1) * ROWS] != 'K'))
              weight[(x - 1) + (y - 1) * ROWS]--;
          }
          break;
        }
        case 't'://Тура черных
        {
          weight[x + y * ROWS] += 5;
          //вниз
          bool tflag = false;
          uint8_t counter = 1;
          while(tflag == false)
          {
            if((array[x +(y + counter)*ROWS] == '0') && ((y + counter) < ROWS ))
              weight[x + (y + counter) * ROWS]++;
            else {
              if(array[x + (y + counter) * ROWS] != 'k')
                weight[x + (y + counter) * ROWS]++;
              tflag = true;
            }
            counter++;
          }
          //вверх
          tflag = false;
          counter = 1;
          while(tflag == false)
          {
            if((array[x +(y - counter)*ROWS] == '0') && ((y - counter) > 0))
              weight[x + (y - counter) * ROWS]++;
            else {
              if(array[x + (y - counter) * ROWS] != 'k')
                weight[x + (y - counter) * ROWS]++;
              tflag = true;
            }
            counter++;
          }
          //вправо
          tflag = false;
          counter = 1;
          while(tflag == false)
          {
            if((array[(x + counter) + y*ROWS] == '0') && ((y + counter) < COLUMS)){
              weight[(x + counter) + y * ROWS]++;
            } else {
              if(array[(x + counter) + y * ROWS] != 'k')
                weight[(x + counter) + y * ROWS]++;
              tflag = true;
            }
            counter++;
          }
          //влево
          tflag = false;
          counter = 1;
          while(tflag == false)
          {
            if((array[(x - counter) + y * ROWS] == '0') && ((y - counter) > 0))
            {
              weight[(x - counter) + y * ROWS]++;
            } else {
              if(array[(x - counter) + y * ROWS] != 'k')
                weight[(x - counter) + y * ROWS]++;
              tflag = true;
            }
            counter++;
          }     
          break;
        }
        case 'T'://Тура белых
        {
          weight[x + y * ROWS] -= 5;
          bool tflag = false;
          uint8_t counter = 1;
          //вниз
          while(tflag == false)
          {
            if((array[x + (y + counter)*ROWS] == '0') && ((y + counter) < ROWS ))
              weight[x + (y + counter) * ROWS]--;
            else {
              if(array[x + (y + counter) * ROWS] != 'K')
                weight[x + (y + counter) * ROWS]--;
              tflag = true;
            }
            counter++;
          }
          //вверх
          tflag = false;
          counter = 1;
          while(tflag == false)
          {
            if((array[x + (y - counter) * ROWS] == '0') && ((y - counter) > 0))
              weight[x + (y - counter) * ROWS]--;
            else {
              if(array[x + (y - counter) * ROWS] != 'K')
                weight[x + (y - counter) * ROWS]--;
              tflag = true;
            }
            counter++;
          }
          //вправо
          tflag = false;
          counter = 1;
          while(tflag == false)
          {
            if((array[(x + counter) + y*ROWS] == '0') && ((x + counter) < COLUMS)){
              weight[(x + counter) + y * ROWS]--;
            } else {
              if(array[(x + counter) + y * ROWS] != 'K')
                weight[(x + counter) + y * ROWS]--;
              tflag = true;
            }
            counter++;
          }
          //влево
          tflag = false;
          counter = 1;
          while(tflag == false)
          {
            if((array[(x - counter) + y * ROWS] == '0') && ((x - counter) > 1))
            {
              weight[(x - counter) + y * ROWS]--;
            } else {
              if(array[(x - counter) + y * ROWS] != 'K')
                weight[(x - counter) + y * ROWS]--;
              tflag = true;
            }
            counter++;
          }     
          break;
        }
        case 'k'://Король черных
        {
          kingRow = y;
          kingColum = x;
          //мутная тема, короли могут встретится, надо учесть при переборе ходов, что короли не могут быть атакованы
          for(uint8_t k = 0; k < 3; k++)
          {
            for(uint8_t l = 0; l < 3; l++)
            {
              //проверка на край
              if(((y + KingRows[k]) < 1) || ((y + KingRows[k]) > ROWS) || ((x + KingColums[l]) < 1) || ((x + KingColums[l]) > COLUMS))
              {
                continue;
              } else {
                weight[(x + KingColums[l])+(y + KingRows[k])*ROWS]++;
              }
            }
          }
          break;
        }
        case 'K'://Король белых
        {
          for(uint8_t k = 0; k < 3; k++)
          {
            for(uint8_t l = 0; l < 3; l++)
            {
              //проверка на край
              if(((y + KingRows[k]) < 1) || ((y + KingRows[k]) > ROWS) || ((x + KingColums[l]) < 1) || ((x + KingColums[l]) > COLUMS))
              {
                continue;
              } else {
                weight[(x + KingColums[l])+(y + KingRows[k])*ROWS]--;
              }
            }
          }
          break;
        }
        case 's'://Слон черных
        {
          weight[x + y * ROWS] += 3;
          bool sflag = false;
          uint8_t counter = 1;
          //Влево вверх
          while(sflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y - counter)*ROWS] != '0')
                sflag = true;
              if(array[(x - counter) + (y - counter) * ROWS] != 'k')
                weight[(x - counter) + (y - counter) * ROWS]++;
            } else {
              sflag = true;
            }
            counter++;
          }
          sflag = false;
          counter = 1;
          //вправо вверх
          while(sflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter) + (y - counter) * ROWS] != '0')
                sflag = true;
              if(array[(x + counter) + (y - counter) * ROWS] != 'k')
                weight[(x + counter) + (y - counter) * ROWS]++;
            } else {
              sflag = true;
            }
            counter++;
          }
          sflag = false;
          counter = 1;
          //Вниз влево
          while(sflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y + counter)*ROWS] != '0')
                sflag = true;
              if(array[(x - counter) + (y + counter) * ROWS] != 'k')
                weight[(x - counter) + (y + counter) * ROWS]++;
            } else {
              sflag = true;
            }
            counter++;
          }
          sflag = false;
          counter = 1;
          //Вниз вправо
          while(sflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter)+(y + counter)*ROWS] != '0')
                sflag = true;
              if(array[(x + counter) + (y + counter) * ROWS] != 'k')
                weight[(x + counter) + (y + counter) * ROWS]++;
            } else {
              sflag = true;
            }
            counter++;
          }
          break;
        }
        case 'S'://Слон белых
        {
          weight[x + y * ROWS] -= 3;
          bool sflag = false;
          uint8_t counter = 1;
          //Влево вверх
          while(sflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y - counter)*ROWS] != '0')
                sflag = true;
              if(array[(x - counter) + (y - counter) * ROWS] != 'K')
                weight[(x - counter) + (y - counter) * ROWS]--;
            } else {
              sflag = true;
            }
            counter++;
          }
          sflag = false;
          counter = 1;
          //вправо вверх
          while(sflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter)+(y - counter)*ROWS] != '0')
                sflag = true;
              if(array[(x + counter) + (y - counter) * ROWS] != 'K')
                weight[(x + counter) + (y - counter) * ROWS]--;
            } else {
              sflag = true;
            }
            counter++;
          }
          sflag = false;
          counter = 1;
          //Вниз влево
          while(sflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y + counter)*ROWS] != '0')
                sflag = true;
              if(array[(x - counter) + (y + counter) * ROWS] != 'K')
                weight[(x - counter) + (y + counter) * ROWS]--;
            } else {
              sflag = true;
            }
            counter++;
          }
          sflag = false;
          counter = 1;
          //Вниз вправо
          while(sflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter) + (y + counter) * ROWS] != '0')
                sflag = true;
              if(array[(x + counter) + (y + counter) * ROWS] != 'K')
                weight[(x + counter) + (y + counter) * ROWS]--;
            } else {
              sflag = true;
            }
            counter++;
          }
          break;
        }
        case 'f'://Ферзь черных
        {
          weight[x + y * ROWS] += 9;
          //вниз
          bool fflag = false;
          uint8_t counter = 1;
          while(fflag == false)
          {
            if((array[x+(y + counter)*ROWS] == '0') && ((y + counter) < ROWS ))
              weight[x + (y + counter) * ROWS]++;
            else {
              if(array[x + (y + counter) * ROWS] != 'k')
                weight[x + (y + counter) * ROWS]++;
              fflag = true;
            }
            counter++;
          }
          //вверх
          fflag = false;
          counter = 1;
          while(fflag == false)
          {
            if((array[x + (y - counter) * ROWS] == '0') && ((y - counter) > 0))
              weight[x + (y - counter) * ROWS]++;
            else {
              if(array[x + (y - counter) * ROWS] != 'k')
                weight[x + (y - counter) * ROWS]++;
              fflag = true;
            }
            counter++;
          }
          //вправо
          fflag = false;
          counter = 1;
          while(fflag == false)
          {
            if((array[(x + counter) + y * ROWS] == '0') && ((y + counter) < COLUMS)){
              weight[(x + counter) + y * ROWS]++;
            } else {
              if(array[(x + counter) + y * ROWS] != 'k')
                weight[(x + counter) + y * ROWS]++;
              fflag = true;
            }
            counter++;
          }
          //влево
          fflag = false;
          counter = 1;
          while(fflag == false)
          {
            if((array[(x - counter) + y * ROWS] == '0') && ((y - counter) > 0))
            {
              weight[(x - counter) + y * ROWS]++;
            } else {
              if(array[(x - counter) + y * ROWS] != 'k')
                weight[(x - counter) + y * ROWS]++;
              fflag = true;
            }
            counter++;
          }   
          //slon
          fflag = false;
          counter = 1;
          //Влево вверх
          while(fflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y - counter)*ROWS] != '0')
                fflag = true;
              if(array[(x - counter) + (y - counter) * ROWS] != 'k')
                weight[(x - counter) + (y - counter) * ROWS]++;
            } else {
              fflag = true;
            }
            counter++;
          }
          fflag = false;
          counter = 1;
          //вправо вверх
          while(fflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter) + (y - counter)*ROWS] != '0')
                fflag = true;
              if(array[(x + counter) + (y - counter) * ROWS] != 'k')
                weight[(x + counter) + (y - counter) * ROWS]++;
            } else {
              fflag = true;
            }
            counter++;
          }
          fflag = false;
          counter = 1;
          //Вниз влево
          while(fflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y+counter)*ROWS] != '0')
                fflag = true;
              if(array[(x - counter) + (y + counter) * ROWS] != 'k')
                weight[(x - counter) + (y + counter) * ROWS]++;
            } else {
              fflag = true;
            }
            counter++;
          }
          fflag = false;
          counter = 1;
          //Вниз вправо
          while(fflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter) + (y + counter) * ROWS] != '0')
                fflag = true;
              if(array[(x + counter) + (y + counter) * ROWS] != 'k')
                weight[(x + counter) + (y + counter) * ROWS]++;
            } else {
              fflag = true;
            }
            counter++;
          }
          break;
        }
        case 'F'://Ферзь белых
        {
          weight[x + y * ROWS] -= 9;
          bool fflag = false;
          uint8_t counter = 1;
          //вниз
          while(fflag == false)
          {
            if((array[x + (y + counter) * ROWS] == '0') && ((y + counter) < ROWS ))
              weight[x + (y + counter) * ROWS]--;
            else {
              if(array[x + (y + counter) * ROWS] != 'K')
                weight[x + (y + counter) * ROWS]--;
              fflag = true;
            }
            counter++;
          }
          //вверх
          fflag = false;
          counter = 1;
          while(fflag == false)
          {
            if((array[x + (y - counter) * ROWS] == '0') && ((y - counter) > 0))
              weight[x + (y - counter) * ROWS]--;
            else {
              if(array[x + (y - counter) * ROWS] != 'K')
                weight[x + (y - counter) * ROWS]--;
              fflag = true;
            }
            counter++;
          }
          //вправо
          fflag = false;
          counter = 1;
          while(fflag == false)
          {
            if((array[(x + counter)+y*ROWS] == '0') && ((x + counter) < COLUMS)){
              weight[(x + counter) + y * ROWS]--;
            } else {
              if(array[(x + counter) + y * ROWS] != 'K')
                weight[(x + counter) + y * ROWS]--;
              fflag = true;
            }
            counter++;
          }
          //влево
          fflag = false;
          counter = 1;
          while(fflag == false)
          {
            if((array[(x - counter) + y * ROWS] == '0') && ((x - counter) > 1))
            {
              weight[(x - counter) + y * ROWS]--;
            } else {
              if(array[(x - counter) + y * ROWS] != 'K')
                weight[(x - counter) + y * ROWS]--;
              fflag = true;
            }
            counter++;
          } 
          //слон белый
          fflag = false;
          counter = 1;
          //Влево вверх
          while(fflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y - counter)*ROWS] != '0')
                fflag = true;
              if(array[(x - counter) + (y - counter) * ROWS] != 'K')
                weight[(x - counter) + (y - counter) * ROWS]--;
            } else {
              fflag = true;
            }
            counter++;
          }
          fflag = false;
          counter = 1;
          //вправо вверх
          while(fflag == false)
          {
            //проверка на край
            if(((y - counter) > 0) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter) + (y - counter) * ROWS] != '0')
                fflag = true;
              if(array[(x + counter) + (y - counter) * ROWS] != 'K')
                weight[(x + counter) + (y - counter) * ROWS]--;
            } else {
              fflag = true;
            }
            counter++;
          }
          fflag = false;
          counter = 1;
          //Вниз влево
          while(fflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x - counter) > 0))
            {
              if(array[(x - counter)+(y + counter)*ROWS] != '0')
                fflag = true;
              if(array[(x - counter) + (y + counter) * ROWS] != 'K')
                weight[(x - counter) + (y + counter) * ROWS]--;
            } else {
              fflag = true;
            }
            counter++;
          }
          fflag = false;
          counter = 1;
          //Вниз вправо
          while(fflag == false)
          {
            //проверка на край
            if(((y + counter) < ROWS) && ((x + counter) < COLUMS))
            {
              if(array[(x + counter)+(y+counter)*ROWS] != '0')
                fflag = true;
              if(array[(x + counter) + (y + counter) * ROWS] != 'K')
                weight[(x + counter) + (y + counter) * ROWS]--;
            } else {
              fflag = true;
            }
            counter++;
          }
          break;
        }
        case 'l'://Конь черных
        {
          weight[x + y * ROWS] += 3;
          //верх(лево и право)
          if(((y - 2) > 0) && ((x - 1) > 0) && (array[(x-1)+(y - 2)*ROWS] != 'k'))
          {
            weight[(x - 1) + (y - 2) * ROWS]++;
          }
          if(((y - 2) > 0) && ((x + 1) < COLUMS) && (array[(x+1)+(y-2)*ROWS] != 'k'))
          {
            weight[(x + 1) + (y - 2) * ROWS]++;
          }
          //лево(низ и верх)
          if(((y - 1) > 0) && ((x - 2) > 0) && (array[(x-2)+(y-1)*ROWS] != 'k'))
          {
            weight[(x - 2) + (y - 1) * ROWS]++;
          }
          if(((y + 1) < ROWS) && ((x - 2) > 0) && (array[(x-2)+(y+1)*ROWS] != 'k'))
          {
            weight[(x - 2) + (y + 1) * ROWS]++;
          }
          //право(низ и верх)
          if(((y - 1) > 0) && ((x + 2) < COLUMS) && (array[(x+2)+(y - 1)*ROWS] != 'k'))
          {
            weight[(x + 2) + (y - 1) * ROWS]++;
          }
          if(((y + 1) < ROWS) && ((x + 2) < COLUMS) && (array[(x + 2) + (y + 1) * ROWS] != 'k'))
          {
            weight[(x + 2) + (y + 1) * ROWS]++;
          }
          //низ(лево и право)
          if(((y + 2) < ROWS) && ((x - 1) > 0) && (array[(x-1)+(y+2)*ROWS] != 'k'))
          {
            weight[(x - 1) + (y + 2) * ROWS]++;
          }
          if(((y + 2) < ROWS) && ((x + 1) < COLUMS)&& (array[(x + 1) + (y + 2) * ROWS] != 'k'))
          {
            weight[(x + 1) + (y + 2) * ROWS]++;
          }
          break;
        }
        case 'L'://Конь белых
        {
            weight[x + y * ROWS] -= 3;
            //верх(лево и право)
            if (((y - 2) > 0) && ((x - 1) > 0) && (array[(x - 1) + (y - 2) * ROWS] != 'K'))
            {
                weight[(x - 1) + (y - 2) * ROWS]--;
            }
            if (((y - 2) > 0) && ((x + 1) < COLUMS) && (array[(x + 1) + (y - 2) * ROWS] != 'K'))
            {
                weight[(x + 1) + (y - 2) * ROWS]--;
            }
            //лево(низ и верх)
            if (((y - 1) > 0) && ((x - 2) > 0) && (array[(x - 2) + (y - 1) * ROWS] != 'K'))
            {
                weight[(x - 2) + (y - 1) * ROWS]--;
            }
            if (((y + 1) < ROWS) && ((x - 2) > 0) && (array[(x - 2) + (y + 1) * ROWS] != 'K'))
            {
                weight[(x - 2) + (y + 1) * ROWS]--;
            }
            //право(низ и верх)
            if (((y - 1) > 0) && ((x + 2) < COLUMS) && (array[(x + 2) + (y - 1) * ROWS] != 'K'))
            {
                weight[(x + 2) + (y - 1) * ROWS]--;
            }
            if (((y + 1) < ROWS) && ((x + 2) < COLUMS) && (array[(x + 2) + (y + 1) * ROWS] != 'K'))
            {
                weight[(x + 2) + (y + 1) * ROWS]--;
            }
            //низ(лево и право)
            if (((y + 2) < ROWS) && ((x - 1) > 0) && (array[(x - 1) + (y + 2) * ROWS] != 'K'))
            {
                weight[(x - 1) + (y + 2) * ROWS]--;
            }
            if (((y + 2) < ROWS) && ((x + 1) < COLUMS) && (array[(x + 1) + (y + 2) * ROWS] != 'K'))
            {
                weight[(x + 1) + (y + 2) * ROWS]--;
            }
            break;
        }
      }
    }
  }
}
void weightClear(int8_t* array)
{
  for(uint8_t y = 1;y < ROWS; y++)
  {
    for(uint8_t x = 1; x < COLUMS; x++)
    {
      array[x + y * ROWS] = 0;
    }
  }
}
void WBSUMMCalc(uint8_t& Black,uint8_t& White)
{
  for(uint8_t y = 1; y < ROWS; y++)
  {
    for(uint8_t x = 1; x < COLUMS; x++)
    {
      if(weight[x+y*ROWS] > 0)
      {
        Black += abs(weight[x + y * ROWS]);
      }
      else if (weight[x + y * ROWS] < 0)
      {
        White += abs(weight[x + y * ROWS]);
      } 
    }
  }
}

//изменение позиций фигур
void swap(char array[ROWS][COLUMS],uint8_t colums1,uint8_t rows1,uint8_t colums2,uint8_t rows2){  
  array[rows2][colums2] = array[rows1][colums1];
  array[rows1][colums1] = '0';
}
//отрисовка поля
/*
void draw()
{
  for(uint8_t i = 0;i < ROWS; i++)
  {
    for(uint8_t j = 0; j < COLUMS; j++)
    {
      Serial.print(ChessBoard[i][j]);
      Serial.print("  ");
    }
    if(i != 0){
      Serial.print("|  | ");
      for(uint8_t j = 1; j < COLUMS; j++)
      {
        if(weight[i][j] < 0){
          Serial.print(weight[i][j]);
          if(weight[i][j] > -10)
            Serial.print(" ");  
        }else{
          Serial.print(' ');
          Serial.print(weight[i][j]);  
          if(weight[i][j] < 10) 
            Serial.print(' '); 
        } 
      }  
    } else {
      Serial.print("    ");
      for(uint8_t i = 1;i < COLUMS; i++)
      {
        Serial.print("  ");
        Serial.print(i);
      }
    }
    Serial.println();
  }
}
*/
