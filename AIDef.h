#pragma once
bool AI_turn_flag = false;
//C������ ������ �����
uint8_t BlackCounter = 0;
uint8_t BlackSUMM, WhiteSUMM;

//��� �������� �������� ���� � ���������� ����� ����
uint8_t BestAIWeight;
uint8_t AIRowTurn1, AIColumTurn1, AIRowTurn2, AIColumTurn2;
//���� ���� ������
bool FlagCheckKing = false;
//���������� ������
uint8_t kingRow, kingColum;
int8_t KingRows[] = { -1,0,1 };
int8_t KingColums[] = { -1,0,1 };
