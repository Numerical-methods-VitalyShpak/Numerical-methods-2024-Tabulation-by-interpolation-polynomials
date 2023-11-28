#include <iostream>
#include <string>
#include <vector>

////////////////�����/////////////////////

void Print(std::vector<float> valueX, std::vector<float> valueF);

////////////////���������� ����/////////////////////

float Get_Step(float beginPoint, float endPoint, int interavalCount);

//////////////��������� �����/////////////////////

std::vector<float> Get_Nodes_Row(float beginPoint, float endPoint, int interavalCount);

std::vector<float> Get_Nodes_Cheb(float beginPoint, float endPoint, int interavalCount);

//////////////�������������////////////////////////

std::vector<std::vector<float>> Tabulate(std::vector<float> Nodes_R_CH);

///////////////////������������////////////////////////

double Create_Base_Polinom_Lagrange(double x, int indexCur, std::vector<std::vector<float>> TabulPolinom);

double Create_Lagrange_Polinom(double x, std::vector<std::vector<float>> TabulPolinom);

std::vector<std::vector<float>> Lagrange_interpolate(std::vector<std::vector<float>> TabulPolinom, std::vector<float> Points);

std::vector<std::vector<float>> Newton_interpolate(std::vector<std::vector<float>> TabulPolinom, std::vector<float> Points);

/////////////////�����������///////////////////

std::vector<std::vector<float>> Get_Pogreshnost(std::vector<std::vector<float>> TabulatePolinom, std::vector<std::vector<float>> InterpolatePolinom);

float Get_Max_Pogreshnost(std::vector<std::vector<float>> Pogreshnost);

///////////////////������ ����������/////////////////////

std::vector<float> Get_Info();

///////////////////������������//////////////////

std::vector<std::vector<float>> Experiment_Lagrange_Row(std::vector<float> data);

std::vector<std::vector<float>> Experiment_Lagrange_Cheb(std::vector<float> data);

std::vector<std::vector<float>> Experiment_Newton_Row(std::vector<float> data);

std::vector<std::vector<float>> Experiment_Newton_Cheb(std::vector<float> data);

////////////////////���������� � ���������� ��������/////////////////

void Write_P(std::string filename, std::vector<std::vector<float>> dt);

void Write_M(std::string filename, std::vector<std::vector<float>> dt);

///////////////////////////���������� �������//////////////////////

std::vector<std::vector<float>> Function_Nodes_Row(std::vector<float> data);

std::vector<std::vector<float>> Function_Nodes_Cheb(std::vector<float> data);

////////////////////���������������� �������///////////////////////////////////

std::vector<std::vector<float>> Function_Lagrange_Row(std::vector<float> data);

std::vector<std::vector<float>> Function_Lagrange_Cheb(std::vector<float> data);

std::vector<std::vector<float>> Function_Newton_Row(std::vector<float> data);

std::vector<std::vector<float>> Function_Newton_Cheb(std::vector<float> data);

//////////////////////�����������//////////////////////////

std::vector<std::vector<float>> Pogreshnost_Lagrange_Row(std::vector<float> data);

std::vector<std::vector<float>> Pogreshnost_Lagrange_Cheb(std::vector<float> data);

std::vector<std::vector<float>> Pogreshnost_Newton_Row(std::vector<float> data);

std::vector<std::vector<float>> Pogreshnost_Newton_Cheb(std::vector<float> data);