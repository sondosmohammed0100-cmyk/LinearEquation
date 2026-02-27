#include "linearEqu.h"
linearEqu::linearEqu()
{
	m_const = 0;
}
void linearEqu::splitEquation(string inputEqu, string& lhs, string& rhs)
{
	lhs = inputEqu.substr(0, inputEqu.find("="));
	rhs = inputEqu.substr(inputEqu.find("=") + 1);
}

//find if variable exist to add it to its variable
void linearEqu::addVariable(string varName, float coeff)
{
	for (int i = 0;i < m_varName.size();i++) {
		if (m_varName[i] == varName) {
			m_coeff[i] += coeff;
			return;
		}
	}
	m_varName.push_back(varName);
	m_coeff.push_back(coeff);
}

void linearEqu::process_Section(string section)
{
	int find_x_indx = section.find('x'); 
	if (find_x_indx >= 0 && find_x_indx < section.size()) {
		string coeff_Str = section.substr(0, find_x_indx);
//Coefficient when equals to one or -1		
		if (coeff_Str == "" || coeff_Str == "+")
			coeff_Str = "1";
		if (coeff_Str == "-")
			coeff_Str = "-1";
		float coeff = atof(coeff_Str.c_str());
		string varName = section.substr(find_x_indx);
		addVariable(varName, coeff);
	}
	else {
//m_const=0-(+ or - constant)
		m_const -= atof(section.c_str());
	}
}

void linearEqu::dividEquation(string inputEqu)
{
//To clear data when make more than one object from class
	m_const = 0;
	m_varName.clear();
	m_coeff.clear();
	string lhs, rhs;
	splitEquation(inputEqu, lhs, rhs);
	string section = "";
	for (int i = 0;i < lhs.size();i++) {
		char c = lhs[i];
		if (c == '+' || c == '-') {
			if (section!="") 
				process_Section(section);
			section = c;
		}
		else 
     		section += c;
	}
	if(section!="")
		process_Section(section);
	m_const += atof(rhs.c_str());
}
void linearEqu::sortEquation()
{
	for (int i = 0; i < m_varName.size(); i++) {
		for (int j = i + 1; j < m_varName.size(); j++)
		{
//Exetract coeff after x to arrangment the equ alphapiticaly
			int num1 = atoi(m_varName[i].substr(1).c_str());
			int num2 = atoi(m_varName[j].substr(1).c_str());
			
			if (num1 > num2) {

				string tempStr;
				tempStr = m_varName[i];
				m_varName[i] = m_varName[j];
				m_varName[j] = tempStr;
				float tempFl;
				tempFl = m_coeff[i];
				m_coeff[i] = m_coeff[j];
				m_coeff[j] = tempFl;
	    	}
		}
	}
}
void linearEqu::print()
{
	for (int i = 0; i < m_varName.size(); i++)
	{
		if (m_coeff[i] > 0 && i != 0)
			cout << "+";
		if (m_coeff[i] == 1)
			cout << m_varName[i];
		else if (m_coeff[i] == -1)
			cout << "-" << m_varName[i];
		else
			cout << m_coeff[i] << m_varName[i];

		
	}
	cout << "= " << m_const << endl;
}

int linearEqu::Max_Index_variabl()
{
	int max_index = 0;
	for (int i = 0;i < m_varName.size();i++) {
		int index = atoi(m_varName[i].substr(1).c_str());
		if (index > max_index) {
			max_index = index;
		}

	}
	return max_index;
}

float linearEqu::get_coaff(string var_N)
{
	for (int i = 0; i < m_varName.size();i++) {
		if (m_varName[i] == var_N)
			return m_coeff[i];
	
	}

	return 0;
}

linearEqu linearEqu::operator+(const linearEqu& obj)
{
	linearEqu result;
	result.m_const = this->m_const + obj.m_const;
	for (int i = 0;i < this->m_varName.size();i++) {
		result.addVariable(this->m_varName[i],this->m_coeff[i]);
	}
	for (int i = 0;i < obj.m_varName.size();i++) {
		result.addVariable(obj.m_varName[i], obj.m_coeff[i]);
	}
	result.sortEquation();

	return result;
}



linearEqu linearEqu::operator-(const linearEqu& obj)
{
	linearEqu result;
	result.m_const = this->m_const - obj.m_const;
	for (int i = 0;i < this->m_varName.size();i++) {
		result.addVariable(this->m_varName[i], this->m_coeff[i]);
	}
	for (int i = 0;i < obj.m_varName.size();i++) {
		result.addVariable(obj.m_varName[i],- obj.m_coeff[i]);
	}
	result.sortEquation();

	return result;
}

void linearEqu::remove_Var(string varName)
{
	for (int i = 0;i < m_varName.size();i++) {
		if (m_varName[i] == varName) {
			for (int j = i;j < m_varName.size() - 1;j++) {
				m_varName[j] = m_varName[j + 1];
				m_coeff[j] = m_coeff[j + 1];
			}
			m_varName.pop_back();
			m_coeff.pop_back();
		}
	}
}

linearEqu linearEqu::operator*(float coeff)
{
	linearEqu res;
	res.m_const = this->m_const * coeff;
	for (int i = 0;i < this->m_varName.size();i++) {
		res.addVariable(m_varName[i], m_coeff[i] * coeff);

	}
	return res;
}




