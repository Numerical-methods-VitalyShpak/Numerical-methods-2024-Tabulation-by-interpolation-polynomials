#include "Implementation_laboratory.hpp"

void FubctionForOtchet() 
{
	std::vector<float> data = Get_Info();
	Write_M("I_N_C.txt", Function_Newton_Cheb(data));//Интерполяциия
	Write_M("I_L_R.txt", Function_Lagrange_Row(data));
	Write_M("I_L_C.txt", Function_Lagrange_Cheb(data));
	Write_M("I_N_R.txt", Function_Newton_Row(data));
	Write_M("F_R.txt", Function_Nodes_Row(data));//вычисление функции 6
	Write_M("F_C.txt", Function_Nodes_Cheb(data));
	Write_M("F_R_2.txt", Function_Nodes_Row_2(data));//вычисление функции 11
	Write_M("F_C_2.txt", Function_Nodes_Cheb_2(data));
	Write_M("P_L_R.txt", Pogreshnost_Lagrange_Row(data));//погрешности
	Write_M("P_L_C.txt", Pogreshnost_Lagrange_Cheb(data));
	Write_M("P_N_R.txt", Pogreshnost_Newton_Row(data));
	Write_M("P_N_C.txt", Pogreshnost_Newton_Cheb(data));
	Write_P("E_L_R.txt", Experiment_Lagrange_Row(data));//эксперименты
	Write_P("E_L_C.txt", Experiment_Lagrange_Cheb(data));
	Write_P("E_N_R.txt", Experiment_Newton_Row(data));
	Write_P("E_N_C.txt", Experiment_Newton_Cheb(data));
}

int main()
{
	FubctionForOtchet();
	system("python function_graf.py");
}
