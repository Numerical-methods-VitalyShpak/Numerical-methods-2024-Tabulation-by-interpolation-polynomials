#define M_PI 3.14159265358979323846
#include <iostream>
#include <Math.h>
#include <string>
#include <array>
#include <vector>
#include <cmath>

               ////////////////Вывод/////////////////////

void Print(std::vector<float> valueX, std::vector<float> valueF)
{
	std::string line1 = "";
	std::string line2 = "";
	int len, count = valueX.size();
	for (int i = 0; i < count;i++)
	{
		line2 += std::to_string(valueF[i]) + "|";
		if (valueF[i] < 0)
		{
			line1 += " ";
		}
		line1 += std::to_string(valueX[i]);
		len = line2.size() - line1.size();
		if (len > 1)
		{
			for (int i = 0; i < len; i++)
			{
				line1 += " ";
			}
		}
		line1 += "|";
	}
	std::cout << line1 + "\n" + line2 + "\n";
}

                       ////////////////Нахождение шага/////////////////////

float Get_Step(float beginPoint, float endPoint, int interavalCount)
{
	return (endPoint - beginPoint) / interavalCount;
}

                        //////////////получение узлов/////////////////////

std::vector<float> Get_Nodes_Row(float beginPoint, float endPoint, int interavalCount) 
{
	std::vector<float> Nodes;
	float step = Get_Step(beginPoint, endPoint, interavalCount);
	for (float x = beginPoint; x <= endPoint; x += step)
	{
		Nodes.push_back(x);
	}
	if (Nodes.size() != interavalCount + 1)
	{
		Nodes.push_back(endPoint);
	}
	return Nodes;
}

std::vector<float> Get_Nodes_Cheb(float beginPoint, float endPoint, int interavalCount)
{
	std::vector<float> Nodes = Get_Nodes_Row(beginPoint, endPoint, interavalCount);
	std::vector<float> Nodes_Cheb;
	for (int i = 0; i < Nodes.size(); i++)
	{
		float a = Nodes[0], b = Nodes[Nodes.size() - 1], n = Nodes.size() - 1;
		Nodes_Cheb.push_back(0.5 * (a + b) + 0.5 * (b - a) * cos(((2 * i + 1) / (2 * n + 2)) * M_PI));
	}
	std::reverse(Nodes_Cheb.begin(), Nodes_Cheb.end());
	return Nodes_Cheb;
}

                                    //////////////табулирование////////////////////////

std::vector<std::vector<float>> Tabulate(std::vector<float> Nodes_R_CH)
{
	std::vector<float> ValueNodes;
	std::vector<std::vector<float>> result;
	for (int i = 0; i < Nodes_R_CH.size(); i++)
	{
		float n = 0,x = Nodes_R_CH[i], a = x, sum = a, q = 0;
		while (fabs(a) > 1e-6)
		{
			q = -(x * x * (2 * n + 1)) / ((2 * n + 3) * (2 * n + 3) * (2 * n + 2));
			a *= q;
			sum += a;
			n++;
		}
		ValueNodes.push_back(sum);
	}
	result.push_back(Nodes_R_CH);
	result.push_back(ValueNodes);
	return result;
}

                  ///////////////////Интерполяция////////////////////////

double Create_Base_Polinom_Lagrange(double x, int indexCur, std::vector<std::vector<float>> TabulPolinom)
{
	double result = 1;
	int count = TabulPolinom[0].size();
	for (int j = 0; j < count; j++)
	{
		if (j != indexCur)
		{
			result *= (x - TabulPolinom[0][j]);
			result /= (TabulPolinom[0][indexCur] - TabulPolinom[0][j]);
		}
	}
	return result;
}

double Create_Lagrange_Polinom(double x, std::vector<std::vector<float>> TabulPolinom)
{
	int count = TabulPolinom[0].size();
	double result = 0;
	for (int i = 0; i < count; i++)
	{
		result += TabulPolinom[1][i] * Create_Base_Polinom_Lagrange(x, i, TabulPolinom);
	}
	return result;
}

std::vector<std::vector<float>> Lagrange_interpolate(std::vector<std::vector<float>> TabulPolinom, std::vector<float> Points)
{
	std::vector<float> InterPolinomF;
	for(int i = 0; i < Points.size(); i++)
	{
		InterPolinomF.push_back(Create_Lagrange_Polinom(Points[i], TabulPolinom));
	}
	std::vector<std::vector<float>> interpolate_polinom = { Points, InterPolinomF };
	return interpolate_polinom;
}



std::vector<std::vector<float>> Newton_interpolate(std::vector<std::vector<float>> TabulPolinom, std::vector<float> Points)
{
	std::vector<float> InterPolinomF;
	std::vector<float> raz = TabulPolinom[1];
	for (float k = 1; k < TabulPolinom[0].size(); k++)
	{
		for (float i = TabulPolinom[0].size() - 1; i > k - 1; i--)
		{
			raz[i] = (raz[i] - raz[i - 1]) / (TabulPolinom[0][i] - TabulPolinom[0][i - k]);
		}
	}
	for (float j = 0; j < Points.size(); j++)
	{
		InterPolinomF.push_back(raz[0]);
		for (float k = 1; k < TabulPolinom[0].size(); k++)
		{
			float cur = raz[k];
			for (float i = 0; i < k; i++)
			{
				cur *= Points[j] - TabulPolinom[0][i];
			}
			InterPolinomF[j] += cur;
		}
	}
	std::vector<std::vector<float>> result = { Points, InterPolinomF };
	return result;
}

                   /////////////////Погрешность///////////////////

std::vector<std::vector<float>> Get_Pogreshnost(std::vector<std::vector<float>> TabulatePolinom, std::vector<std::vector<float>> InterpolatePolinom)
{
	std::vector<float> Pogreshnost;
	for (size_t i = 0; i < InterpolatePolinom[1].size(); i++)
	{
		Pogreshnost.push_back(fabs(TabulatePolinom[1][i] - InterpolatePolinom[1][i]));
	}
	std::vector<std::vector<float>> result = { TabulatePolinom[0], Pogreshnost };
	return result;
}

float Get_Max_Pogreshnost(std::vector<std::vector<float>> Pogreshnost)
{
	float max = Pogreshnost[1][0], point = Pogreshnost[0][0], count = Pogreshnost[1].size();
	for (float i = 1; i < count; i++)
	{
		if (max < Pogreshnost[1][i])
		{
			max = Pogreshnost[1][i];
			point = Pogreshnost[0][i];
		}
	}
	return max;
}

                      ///////////////////Чтение информации/////////////////////

std::vector<float> Get_Info() 
{
	std::vector<float> data;
	float a;
	std::cout << "Write begin point = ";///0 начальная точка
	std::cin >> a;
	data.push_back(a);
	std::cout << "Write end point = ";//1 конечная точка
	std::cin >> a;
	data.push_back(a);
	std::cout << "Write count interval in tabulation = ";//2 количество интервалов при табуляции
	std::cin >> a;
	data.push_back(a);
	std::cout << "Write count interval in interpolation polynomial = ";//3 количество интервалов при интерполяции
	std::cin >> a;
	data.push_back(a);
	std::cout << "Write count begin interval in research = ";//4 начальное количество интервалов при эксперименте
	std::cin >> a;
	data.push_back(a);
	std::cout << "Write count limit interval in research = ";//5 конечное количество интервалов при эксперименте
	std::cin >> a;
	data.push_back(a);
	return data;
}

                      ///////////////////Эксперименты//////////////////

std::vector<std::vector<float>> Experiment_Lagrange_Row(std::vector<float> data)
{
	std::vector<std::vector<float>> experiment_result;
	for (float i = data[4]; i < data[5]; i++)
	{
		std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], i);//получили разбиение отрезка
		std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
		std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
		std::vector<std::vector<float>> interpolate_polinom = Lagrange_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
		nodes = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для протабулированного полинома для вычисления погрешности
		tabulate_polinom = Tabulate(nodes);//получили протабулированный полином для вычисления погрешности
		experiment_result.push_back({ i + 1, Get_Max_Pogreshnost(Get_Pogreshnost(tabulate_polinom, interpolate_polinom)) });//записали промежуточный результат эксперимента в виде (количество узлов, макс погрешность )
	}
	return experiment_result;
}

std::vector<std::vector<float>> Experiment_Lagrange_Cheb(std::vector<float> data)
{
	std::vector<std::vector<float>> experiment_result;
	for (float i = data[4]; i < data[5]; i++)
	{
		std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], i);//получили разбиение отрезка
		std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);
		std::vector<float> points_interpolate = Get_Nodes_Cheb(data[0], data[1], data[3]);
		std::vector<std::vector<float>> interpolate_polinom = Lagrange_interpolate(tabulate_polinom, points_interpolate);
		nodes = Get_Nodes_Cheb(data[0], data[1], data[3]);
		tabulate_polinom = Tabulate(nodes);
		experiment_result.push_back({ i + 1, Get_Max_Pogreshnost(Get_Pogreshnost(tabulate_polinom, interpolate_polinom)) });
	}
	return experiment_result;
}

std::vector<std::vector<float>> Experiment_Newton_Row(std::vector<float> data)
{
	std::vector<std::vector<float>> experiment_result;
	for (float i = data[4]; i < data[5]; i++)
	{
		std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], i);//получили разбиение отрезка
		std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
		std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
		std::vector<std::vector<float>> interpolate_polinom = Newton_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
		nodes = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для протабулированного полинома для вычисления погрешности
		tabulate_polinom = Tabulate(nodes);//получили протабулированный полином для вычисления погрешности
		experiment_result.push_back({ i + 1, Get_Max_Pogreshnost(Get_Pogreshnost(tabulate_polinom, interpolate_polinom)) });//записали промежуточный результат эксперимента в виде (количество узлов, макс погрешность )
	}
	return experiment_result;
}

std::vector<std::vector<float>> Experiment_Newton_Cheb(std::vector<float> data)
{
	std::vector<std::vector<float>> experiment_result;
	for (float i = data[4]; i < data[5]; i++)
	{
		std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], i);//получили разбиение отрезка
		std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);
		std::vector<float> points_interpolate = Get_Nodes_Cheb(data[0], data[1], data[3]);
		std::vector<std::vector<float>> interpolate_polinom = Newton_interpolate(tabulate_polinom, points_interpolate);
		nodes = Get_Nodes_Cheb(data[0], data[1], data[3]);
		tabulate_polinom = Tabulate(nodes);
		experiment_result.push_back({ i + 1, Get_Max_Pogreshnost(Get_Pogreshnost(tabulate_polinom, interpolate_polinom)) });
	}
	return experiment_result;
}

                  ////////////////////Подготовка к построению графиков/////////////////

#include <fstream>

void Write_P(std::string filename, std::vector<std::vector<float>> dt)
{
	std::ofstream out;
	std::string path = "C:/Users/79236/source/repos/LaboratoryCHM/LaboratoryCHM/";
	out.open(filename);
	if (out.is_open())
	{
		std::string writer = "";
		for (size_t i = 0; i < dt.size(); i++)
		{
			writer += std::to_string(dt[i][0]) + "|";
		}
		writer += "\n";
		for (size_t i = 0; i < dt.size(); i++)
		{
			writer += std::to_string(dt[i][1]) + "|";
		}

		out << writer;
	}
	out.close();
}

void Write_M(std::string filename, std::vector<std::vector<float>> dt)
{
	std::ofstream out;
	std::string path = "C:/Users/79236/source/repos/LaboratoryCHM/LaboratoryCHM/";
	out.open(filename);
	if (out.is_open())
	{
		std::string writer = "";
		for (size_t i = 0; i < dt[0].size(); i++)
		{
			writer += std::to_string(dt[0][i]) + "|";
		}
		writer += "\n";
		for (size_t i = 0; i < dt[1].size(); i++)
		{
			writer += std::to_string(dt[1][i]) + "|";
		}
		out << writer;
	}
	out.close();
}

            ///////////////////////////Вычисление Функции//////////////////////

std::vector<std::vector<float>> Function_Nodes_Row(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	return tabulate_polinom;
}

std::vector<std::vector<float>> Function_Nodes_Cheb(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	return tabulate_polinom;
}

             ////////////////////Интерполирование Функции///////////////////////////////////

std::vector<std::vector<float>> Function_Lagrange_Row(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Lagrange_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	return interpolate_polinom;
}

std::vector<std::vector<float>> Function_Lagrange_Cheb(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Cheb(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Lagrange_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	return interpolate_polinom;
}

std::vector<std::vector<float>> Function_Newton_Row(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Newton_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	return interpolate_polinom;
}

std::vector<std::vector<float>> Function_Newton_Cheb(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Newton_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	return interpolate_polinom;
}

                 //////////////////////Погрешности//////////////////////////

std::vector<std::vector<float>> Pogreshnost_Lagrange_Row(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Lagrange_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	nodes = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для протабулированного полинома для вычисления погрешности
	tabulate_polinom = Tabulate(nodes);//получили протабулированный полином для вычисления погрешности
	std::vector<std::vector<float>> pogreshnost = Get_Pogreshnost(tabulate_polinom, interpolate_polinom);
	return pogreshnost;
}

std::vector<std::vector<float>> Pogreshnost_Lagrange_Cheb(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Cheb(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Lagrange_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	nodes = Get_Nodes_Cheb(data[0], data[1], data[3]);//получили разбиение для протабулированного полинома для вычисления погрешности
	tabulate_polinom = Tabulate(nodes);//получили протабулированный полином для вычисления погрешности
	std::vector<std::vector<float>> pogreshnost = Get_Pogreshnost(tabulate_polinom, interpolate_polinom);
	return pogreshnost;
}

std::vector<std::vector<float>> Pogreshnost_Newton_Row(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Row(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Newton_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	nodes = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для протабулированного полинома для вычисления погрешности
	tabulate_polinom = Tabulate(nodes);//получили протабулированный полином для вычисления погрешности
	std::vector<std::vector<float>> pogreshnost = Get_Pogreshnost(tabulate_polinom, interpolate_polinom);
	return pogreshnost;
	return interpolate_polinom;
}

std::vector<std::vector<float>> Pogreshnost_Newton_Cheb(std::vector<float> data)
{
	std::vector<float> nodes = Get_Nodes_Cheb(data[0], data[1], data[2]);//получили разбиение отрезка
	std::vector<std::vector<float>> tabulate_polinom = Tabulate(nodes);//протабулировали
	std::vector<float> points_interpolate = Get_Nodes_Row(data[0], data[1], data[3]);//получили разбиение для интерполяции
	std::vector<std::vector<float>> interpolate_polinom = Newton_interpolate(tabulate_polinom, points_interpolate);//проинтерполировали
	nodes = Get_Nodes_Cheb(data[0], data[1], data[3]);//получили разбиение для протабулированного полинома для вычисления погрешности
	tabulate_polinom = Tabulate(nodes);//получили протабулированный полином для вычисления погрешности
	std::vector<std::vector<float>> pogreshnost = Get_Pogreshnost(tabulate_polinom, interpolate_polinom);
	return pogreshnost;
	return interpolate_polinom;
}