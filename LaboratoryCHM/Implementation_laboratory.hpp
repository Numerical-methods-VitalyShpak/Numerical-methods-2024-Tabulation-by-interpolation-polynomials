#include <iostream>
#include <string>
#include <vector>

////////////////Вывод/////////////////////

void Print(std::vector<float> valueX, std::vector<float> valueF);

////////////////Нахождение шага/////////////////////

float Get_Step(float beginPoint, float endPoint, int interavalCount);

//////////////получение узлов/////////////////////

std::vector<float> Get_Nodes_Row(float beginPoint, float endPoint, int interavalCount);

std::vector<float> Get_Nodes_Cheb(float beginPoint, float endPoint, int interavalCount);

//////////////табулирование////////////////////////

std::vector<std::vector<float>> Tabulate(std::vector<float> Nodes_R_CH);

///////////////////Интерполяция////////////////////////

double Create_Base_Polinom_Lagrange(double x, int indexCur, std::vector<std::vector<float>> TabulPolinom);

double Create_Lagrange_Polinom(double x, std::vector<std::vector<float>> TabulPolinom);

std::vector<std::vector<float>> Lagrange_interpolate(std::vector<std::vector<float>> TabulPolinom, std::vector<float> Points);

std::vector<std::vector<float>> Newton_interpolate(std::vector<std::vector<float>> TabulPolinom, std::vector<float> Points);

/////////////////Погрешность///////////////////

std::vector<std::vector<float>> Get_Pogreshnost(std::vector<std::vector<float>> TabulatePolinom, std::vector<std::vector<float>> InterpolatePolinom);

float Get_Max_Pogreshnost(std::vector<std::vector<float>> Pogreshnost);

///////////////////Чтение информации/////////////////////

std::vector<float> Get_Info();

///////////////////Эксперименты//////////////////

std::vector<std::vector<float>> Experiment_Lagrange_Row(std::vector<float> data);

std::vector<std::vector<float>> Experiment_Lagrange_Cheb(std::vector<float> data);

std::vector<std::vector<float>> Experiment_Newton_Row(std::vector<float> data);

std::vector<std::vector<float>> Experiment_Newton_Cheb(std::vector<float> data);

////////////////////Подготовка к построению графиков/////////////////

void Write_P(std::string filename, std::vector<std::vector<float>> dt);

void Write_M(std::string filename, std::vector<std::vector<float>> dt);

///////////////////////////Вычисление Функции//////////////////////

std::vector<std::vector<float>> Function_Nodes_Row(std::vector<float> data);

std::vector<std::vector<float>> Function_Nodes_Cheb(std::vector<float> data);

////////////////////Интерполирование Функции///////////////////////////////////

std::vector<std::vector<float>> Function_Lagrange_Row(std::vector<float> data);

std::vector<std::vector<float>> Function_Lagrange_Cheb(std::vector<float> data);

std::vector<std::vector<float>> Function_Newton_Row(std::vector<float> data);

std::vector<std::vector<float>> Function_Newton_Cheb(std::vector<float> data);

//////////////////////Погрешности//////////////////////////

std::vector<std::vector<float>> Pogreshnost_Lagrange_Row(std::vector<float> data);

std::vector<std::vector<float>> Pogreshnost_Lagrange_Cheb(std::vector<float> data);

std::vector<std::vector<float>> Pogreshnost_Newton_Row(std::vector<float> data);

std::vector<std::vector<float>> Pogreshnost_Newton_Cheb(std::vector<float> data);