from cProfile import label
from itertools import count
import math
import itertools
from os import path, sep
from turtle import title
import matplotlib.pyplot as plt
import matplotlib.pyplot as fig
import numpy as np
import pathlib
from pathlib import Path
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter, AutoMinorLocator)
    


E_L_C__X = []
E_L_C__F = []
E_L_R__X = []
E_L_R__F = []
E_N_C__X = []
E_N_C__F = []
E_N_R__X = []
E_N_R__F = []
F_R__X = []
F_R__F = []
F_C__X = []
F_C__F = []
I_L_C__X = []
I_L_C__F = []
I_L_R__X = []
I_L_R__F = []
I_N_C__X = []
I_N_C__F = []
I_N_R__X = []
I_N_R__F = []
P_L_C__X = []
P_L_C__F = []
P_L_R__X = []
P_L_R__F = []
P_N_C__X = []
P_N_C__F = []
P_N_R__X = []
P_N_R__F = []

E_L_C = "" 
E_L_R = '' 
E_N_C = ''
E_N_R = ''
F_R = ''
F_C = ''
I_L_C = ''
I_L_R = ''
I_N_C = ''
I_N_R = ''
P_L_C = ''
P_L_R = ''
P_N_C = ''
P_N_R = ''

#path = 'C:/Users/79236/source/repos/LaboratoryCHM/LaboratoryCHM/'
new_var = ""
path = new_var

file1 = open(path + 'F_R.txt', "r")
F_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
F_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + 'F_R_2.txt', "r")
F_R_2__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
F_R_2__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + 'F_C.txt', "r")
F_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
F_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + 'F_C_2.txt', "r")
F_C_2__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
F_C_2__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "I_L_C.txt", "r")
I_L_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
I_L_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "I_L_R.txt", "r")
I_L_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
I_L_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "I_N_C.txt", "r")
I_N_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
I_N_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "I_N_R.txt", "r")
I_N_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
I_N_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "P_L_C.txt", "r")
P_L_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
P_L_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "P_L_R.txt", "r")
P_L_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
P_L_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "P_N_C.txt", "r")
P_N_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
P_N_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "P_N_R.txt", "r")
P_N_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
P_N_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "E_L_C.txt", "r")
E_L_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
E_L_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "E_L_R.txt", "r")
E_L_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
E_L_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "E_N_C.txt", "r")
E_N_C__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
E_N_C__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close

file1 = open(path + "E_N_R.txt", "r")
E_N_R__X = [float(el) for el in (file1.readline().split('|'))[:-1]]
E_N_R__F = [float(el) for el in (file1.readline().split('|'))[:-1]]
file1.close


fig = plt.figure(figsize=(15,15))
gs = fig.add_gridspec(6,3)

# plt.subplot(111)              #########################################
# plt.plot(I_L_R__X, I_L_R__F, label = "Newton Form")
# plt.grid(True)
# plt.xlabel('X')
# plt.ylabel('f(x) - N(x) Interpolate value')
# plt.legend()

# plt.subplot(111)############################################
# plt.plot(F_R_2__X[7:9], F_R_2__F[7:9], "r-", label = "Tabulate")
# plt.plot(I_N_R__X[7:9], I_N_R__F[7:9], "b--", label = "Newton Form")
# plt.grid(True)
# plt.legend()

# plt.subplot(111)##########################################
# # plt.title("Calculation through a series")
# plt.plot(F_R__X, F_R__F) ##"b--")
# plt.grid(True)
# plt.xlabel('X ')
# plt.ylabel('f(x) - Tabulate value')
# plt.legend()

# plt.subplot()#############################################
# plt.plot(P_L_R__X, P_L_R__F,"r--", label = "Lagrange Form")
# plt.plot(P_N_R__X, P_N_R__F,"b-",label = "Newton 's Form")
# plt.xlabel("X")
# plt.ylabel("Y - L(x) - N(x)")
# plt.grid(True)
# plt.legend()

plt.subplot()#############################################
plt.plot(F_C_2__X[7:9], F_C_2__F[7:9], "r-", label = "Tabulate")
plt.plot(I_N_C__X[7:9], I_N_C__F[7:9],"g*-", label = "Newton Form")
plt.xlabel("X")
print(F_C_2__X)
print(I_L_C__X)
plt.ylabel("Y - N(x)")
plt.grid(True)
plt.legend()


# plt.subplot(111)#############################################
# print(E_L_R__F)
# print(E_N_R__F)
# plt.plot(E_L_R__X, E_L_R__F, label = "uniform (Lagrange)   --uniform (Newton)")
# # plt.plot(E_N_R__X, E_N_R__F, label = "uniform (Newton)")
# plt.grid(True)
# plt.xlabel("X")
# plt.ylabel("Y - L(x) - N(x)")
# plt.legend()

# plt.subplot(341,)##########################################
# plt.title("Calculation through a series")
# plt.plot(F_R__X, F_R__F)
# plt.grid(True)
# plt.legend()
# plt.subplot(342)#############################################
# plt.title("Polynomial error")
# plt.plot(P_L_R__X, P_L_R__F, label = "uniform (Lagrange)")
# plt.grid(True)
# plt.legend()
# plt.subplot(322)#############################################
# plt.title("Max. error with different number of nodes")
# plt.plot(E_L_R__X, E_L_R__F, label = "uniform (Lagrange)")
# plt.grid(True)
# plt.legend()
# plt.subplot(345)#############################################
# plt.title("Approximation by interpolation polynomials")
# plt.plot(I_L_R__X, I_L_R__F, label = "Lagrange Form")
# plt.plot(I_N_R__X, I_N_R__F, label = "Newton 's Form")
# plt.grid(True)
# plt.legend()
# plt.subplot(346)############################################
# plt.title("Polynomial error with different node selection")
# plt.plot(P_L_R__X, P_L_R__F, label = "uniform (Lagrange)")
# #plt.plot(P_N_R__X, P_N_R__F, label = "uniform (Newton)")
# plt.plot(P_L_C__X, P_L_C__F, label = "Chebyshevskoe (Lagrange)")
# #plt.plot(P_N_C__X, P_N_C__F, label = "Chebyshevskoe (Newton)")
# plt.grid(True)
# plt.legend()
# plt.subplot(324)###########################################
# plt.title("Max. error with different number of nodes")
# plt.plot(E_L_R__X, E_L_R__F, label = "uniform (Lagrange)")
# plt.plot(E_L_C__X, E_L_C__F, label = "Chebyshevskoe (Lagrange)")
# plt.grid(True)
# plt.legend()
# plt.subplot(349)############################################
# plt.title("Approximation by interpolation polynomials")
# plt.plot(P_L_R__X, P_L_R__F, label = "Lagrange Form")
# plt.plot(P_N_R__X, P_N_R__F, label = "Newton 's Form")
# plt.grid(True)
# plt.legend()
# ####################################################################
plt.show()


# k = len(s)
# m = math.sqrt(k)
# # print(list_list[0][1],"dceverve", list_list[1][1])
# plt.subplot(121)
# plt.plot( list_list[0][0],list_list[0][1], 'o-', lw = 1)
# plt.locator_params (axis='x', nbins= 60 )
# plt.locator_params (axis='y', nbins= 10 )
# # plt.subplot(122)
# # plt.plot(list_list[1][0],list_list[1][1], 'o-', lw = 1)
# # plt.locator_params (axis='x', nbins= 60 )
# # plt.locator_params (axis='y', nbins= 10 )
# plt.show()


# # plt.figure(figsize=(20, 10))
# # plt.plot(listX, listF, 'o-', lw = 1)
# # plt.locator_params (axis='x', nbins= 60 )
# # plt.locator_params (axis='y', nbins= 10 )
# # plt.show()
# # plt.savefig( graf_name + '.png')
