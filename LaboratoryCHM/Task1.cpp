#include <iostream>
#include <Math.h>
#include <string>
#include <array>
#include <vector>
#include <cmath>

class Tasks
{
public:
	void SetValue() 
	{
		std::cout << "Set begin point = ";
		std::cin >> beginPoint;
		std::cout << "Set end point = ";
		std::cin >> endPoint;
		std::cout << "Set count point in interval = ";
		std::cin >> count_Point;
	}

	void GetTask1()
	{
		SetValue();
		SetStep();
		double sum, a, n, q = 0;
		std::string line1 = "";
		std::string line2 = "";
		int len = 0;
		std::cout << "Task1" << "\n" << "Tabulating a function" << "\n";
		for (double x = beginPoint , i = 0; x <= endPoint; x += step, i++)
		{
			tableValueX.push_back(x);
			sum = 0;
			n = 0;
			a = x;//расчет по формуле а_n
			q = 0;
			sum += a;// добавление а_0 к сумме
			while (fabs(a) > 1e-6)// точность
			{
				q = (-pow(x, 2) * (2 * n + 1)) / (pow(2 * n + 3, 2) * (2 * n + 2));
				a *= q;
				sum += a;
				n++;
			}
			tableValueTabul.push_back(sum);
			//вывод 
			line2 += std::to_string(sum) + "|";
			if (sum < 0)
			{
				line1 += " ";
			}
			line1 += std::to_string(x);
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
		std::cout << line1 << "\n" << line2;
	}

	void GetPolinomTabulInterpolinom()
	{
		SetStep();
		double sum, a, n, q = 0;
		std::string line1 = "";
		std::string line2 = "";
		int len = 0;
		for (double x = beginPoint, i = 0; x <= endPoint; x += step, i++)
		{
			tableValueX.push_back(x);
			sum = 0;
			n = 0;
			a = x;//расчет по формуле а_n
			q = 0;
			sum += a;// добавление а_0 к сумме
			while (fabs(a) > 1e-6)// точность
			{
				q = (-pow(x, 2) * (2 * n + 1)) / (pow(2 * n + 3, 2) * (2 * n + 2));
				a *= q;
				sum += a;
				n++;
			}
			LastDopValueTabul.push_back(sum);
		}
	}


	void GetTask2() 
	{
		CreateInterpolatingPolinomLagrange();
		PrintOfTask2_variant1();
		//PrintOfTask2_variant2();
	}

	

private:
	double beginPoint;
	double endPoint;
	int count_Point;//читаем из потока
	int updateCountPoint;
	double step;
	std::vector<double> interpolinomValueX;// = 2*countPoint - 1
	std::vector<double> interpolinomValueF;// = 2*countPoint - 1
	std::vector<double> tableValueX;// = countPoint
	std::vector<double> tableValueTabul;// = countPoint
	std::vector<double> LastDopValueTabul;
	std::vector<double> MaxValue;
	double maxE;

	void SetStep() 
	{
		step = ((endPoint - beginPoint) / (count_Point - 1));
	}

	double CreateBasePolinomLagrange(double x, int indexCur)
	{
		double result = 1;
		for (int j = 0; j < count_Point/updateCountPoint; j++)
		{
			if (j != indexCur)
			{
				result *= (x - tableValueX[j]);
				result /= (tableValueX[indexCur] - tableValueX[j]);
			}
		}
		return result;
	}

	double CreateLagrangePolinom(double x)
	{
		double result = 0;
		for (int i = 0; i < count_Point/updateCountPoint; i++)
		{
			result += tableValueTabul[i] * CreateBasePolinomLagrange(x, i);
		}
		return result;
	}

	void CreateInterpolatingPolinomLagrange() 
	{
		std::cout << "\nSet value update count interval = ";
		std::cin >> updateCountPoint;
		count_Point = (count_Point - 1) * updateCountPoint + 1;
		step /= updateCountPoint;
		for (double i = beginPoint; i <= endPoint; i += step)
		{
			interpolinomValueX.push_back(i);
		}
		if (interpolinomValueX.size() != count_Point ) 
		{
			interpolinomValueX.push_back(endPoint);
		}
		GetPolinomTabulInterpolinom();
		double max = -1;
		double current;
		for (int i = 0; i < count_Point  ; i ++)
		{
			if (fabs(CreateLagrangePolinom(interpolinomValueX[i])) - LastDopValueTabul[i] > max) 
			{
				max = fabs(CreateLagrangePolinom(interpolinomValueX[i])) - LastDopValueTabul[i];
			}
			interpolinomValueF.push_back(fabs(CreateLagrangePolinom(interpolinomValueX[i])));
		}
		maxE = max;
	}

	void PrintOfTask2_variant1() 
	{

		
		std::string line1 = "";
		std::string line2 = "";
		std::string line3 = "";
		int len;
		std::cout << "\n\nTask #2" << "\n" << "The Lagrange interpolating polynomial\n";
		for (int i = 0; i < count_Point; i++)
		{
			double max = -1;
			len = line2.size() - line1.size();
			if (i == count_Point - 1)
			{
				line2 += std::to_string(tableValueTabul[i % count_Point / updateCountPoint]) + "|";
			}
			else
			{
				line2 += std::to_string(interpolinomValueF[i]) + "|";
			}
			if (i != count_Point - 1) 
			{
				line3 += std::to_string(fabs(LastDopValueTabul[i] - interpolinomValueF[i])) + "|";
			}
			else 
			{
				line3 += std::to_string((double)0)+ "|";
			}
			
			if (interpolinomValueF[i] < 0)
			{
				line1 += " ";
			}
			line1 += std::to_string(interpolinomValueX[i]);
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
		std::cout << line1 << "\n" << line2 << "\n" << "Interpolation accuracy\n" << line3 << "\n" << "Max element = " << maxE;
	}

	void PrintOfTask2_variant2() 
	{
		std::cout << "\n";
		for (int i = 0; i < count_Point; i++)
		{
			std::cout << interpolinomValueX[i] << "||" << interpolinomValueF[i] << "\n";
		}
	}
};

