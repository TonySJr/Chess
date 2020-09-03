#pragma once
bool AI_turn_flag = false;
//Cчетчик черных фигур
uint8_t BlackCounter = 0;
uint8_t BlackSUMM, WhiteSUMM;

//Вес наиболее хорошего хода и координаты этого хода
uint8_t BestAIWeight;
uint8_t AIRowTurn1, AIColumTurn1, AIRowTurn2, AIColumTurn2;
//флаг шаха королю
bool FlagCheckKing = false;
//координаты короля
uint8_t kingRow, kingColum;
int8_t KingRows[] = { -1,0,1 };
int8_t KingColums[] = { -1,0,1 };
