#include <iostream>
#include <Math.h>
#include <string>
#include <array>
#include <vector>
#include <cmath>

float GetStepInterval(float beginPoint, float endPoint, int interavalCount)
{
	return (endPoint - beginPoint) / interavalCount;
}

std::vector<std::vector<float>> GetTabulPolinom(float beginPoint, float endPoint, int interavalCount)
{
	std::vector<float> ValueTabulF;
	std::vector<float> ValueTabulX;
	std::vector<std::vector<float>> result;
	float sum, n, a, q;
	float step = GetStepInterval(beginPoint, endPoint, interavalCount);
	for (float x = beginPoint, i = 0; x <= endPoint; x += step, i++)
	{
		ValueTabulX.push_back(x);
		sum = 0;
		n = 0;
		a = x;
		q = 0;
		sum += a;
		while (fabs(a) > 1e-6)
		{
			q = (-pow(x, 2) * (2 * n + 1)) / (pow(2 * n + 3, 2) * (2 * n + 2));
			a *= q;
			sum += a;
			n++;
		}
		ValueTabulF.push_back(sum);
	}
	result.push_back(ValueTabulX);
	result.push_back(ValueTabulF);
	return result;
}

void PrintResult_2_vector(std::vector<float> valueX, std::vector<float> valueF)
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
	std::cout << line1 + "\n" + line2;
}
