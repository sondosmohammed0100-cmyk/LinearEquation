#ifndef LINEAREQU_H_
#define LINEAREQU_H_
#include<vector>
#include<string>
#include<iostream>
#include<cstdlib> 
#include<sstream>
using namespace std;
class linearEqu
{
private:
	vector<string>m_varName;
	vector<float>m_coeff;
	float m_const;


public:
	linearEqu();
//split equation to rhs and lhs
	void splitEquation(string inputEqu, string& lhs, string& rhs);

//make constants appear in the RHS 	
	void process_Section(string section);

//make any variable appears only one time
	void addVariable(string varName, float coeff);
	void dividEquation(string inputEqu);

//ordered Equations alphabetically from left to right
	void sortEquation();

//print Equations in proper form
	void print();

//get Max index of variable in the equation
	int Max_Index_variabl();

//get coeff
	float get_coaff(string var_N);

//add two equation
	linearEqu operator+(const linearEqu& obj);

	
//subtract two equ
	linearEqu operator-(const linearEqu& obj);
//remove variable from equation
	void remove_Var(string varName);
//multiply the coeff of variable * the other equ
	linearEqu operator*(float coeff);
};

#endif // !LINEAREQU_H_


