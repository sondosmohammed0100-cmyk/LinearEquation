#include <iostream>
#include "linearEqu.h"

using namespace std;

int main()
{
    int n;
    cout << "Enter number equation: ";
    cin >> n;
    cin.ignore();
    string input;
    vector<linearEqu> equations;

    for (int i = 0; i < n;i++) {

         getline(cin, input);
         linearEqu eq;
         eq.dividEquation(input);
         eq.sortEquation();
         equations.push_back(eq);

    }
    cout << "After rearranging: " << endl;
    for (int i = 0; i < n;i++) {
        
         equations[i].print(); 
    }
    string command;
    while (true) {
        getline(cin, command);
        if (command == "quit") {

            break;
        }
        else if (command == "num_vars") {
            int max_Var = 0;
            for (int i = 0;i < equations.size();i++) {
                int Max_equ = equations[i].Max_Index_variabl();
                if (Max_equ > max_Var) {
                    max_Var = Max_equ;
                }
            }
            cout << max_Var << endl;
        }
//print equation number of i
        else if (command.substr(0,8) == "equation") {
           int equ_i = atoi(command.substr(9).c_str());
            if (equ_i >= 0 && equ_i<= equations.size()) {
                equations[equ_i-1].print();
            }
            else {
                cout << "Out of numbers of equations" << endl;
            }
        }
//print vector of coeff of spacific variable
        else if (command.substr(0, 6) == "column") {
            string x_i = command.substr(7);
            for (int i = 0;i < equations.size();i++) {
                cout << equations[i].get_coaff(x_i) << endl;
            }
           
        }
//Adding Two Equation 
        else if (command.substr(0, 3) == "add") {
    //a d d   99   100
    //0 1 2 3 45 6 789 
          int  first_space = command.find(' ');//index=3
          int sec_space = command.find(' ', first_space + 1);
         
          int first_equ = atoi(command.substr(first_space + 1,sec_space- first_space -1 ).c_str());
          int sec_equ = atoi(command.substr(sec_space + 1).c_str());
          if (first_equ >= 1 && first_equ <= equations.size() && sec_equ >= 1 && sec_equ <= equations.size()){
                  linearEqu res = equations[first_equ - 1] + equations[sec_equ - 1];
                  res.print();
              
          }
          else {
              cout << "These Equations Not found " << endl;
          }

        }
//subtract two equation
        else if (command.substr(0, 8) == "subtract")
        {
            int  first_space = command.find(' ');
            int sec_space = command.find(' ', first_space + 1);
            int first_equ = atoi(command.substr(first_space + 1, sec_space - first_space - 1).c_str());
            int sec_equ = atoi(command.substr(sec_space + 1).c_str());
            if (first_equ >= 1 && first_equ <= equations.size() && sec_equ >= 1 && sec_equ <= equations.size()) {
                    linearEqu res = equations[first_equ - 1] - equations[sec_equ - 1];
                    res.print();
                }
            
            else {
                cout << "These Equations Not found " << endl;
            }
        }
//substitute variable in equation by its equation from another
        else if (command.substr(0, 10) == "substitute") {
            int  first_space = command.find(' ');
            int sec_space = command.find(' ', first_space+1);
            int third_space = command.find(' ', sec_space + 1);
            string var_Name = command.substr(first_space+1,sec_space - first_space - 1);
            int first_equ = atoi(command.substr(sec_space + 1, third_space-sec_space-1).c_str());
            int sec_equ = atoi(command.substr(third_space+1).c_str());
          
            if (first_equ >= 1 && first_equ <= equations.size() && sec_equ >= 1 && sec_equ <= equations.size()) {
                linearEqu eqution_1 = equations[first_equ - 1];
                linearEqu eqution_2 = equations[sec_equ - 1];
                float coeff_var1 = eqution_1.get_coaff(var_Name);
                float coeff_var2 = eqution_2.get_coaff(var_Name);
                if (coeff_var1 == 0 || coeff_var2 == 0) {

                    cout << "can't found this variable" << endl;
                }
                else {
                    linearEqu temp = eqution_2 * (1.0 / coeff_var2);
                    temp = temp * (-coeff_var1);
                   // eqution_1.remove_Var(var_Name);
                    linearEqu result = eqution_1 +temp;
                    result.sortEquation();
                    result.remove_Var(var_Name);
                    result.print();
                }

            
                
            }
             else 
                    cout << "Not Found" << endl;
               
            
        }
        else {
            cout << "This Command not  Found" << endl;
        }


        
    }
    
   
    return 0;
}

