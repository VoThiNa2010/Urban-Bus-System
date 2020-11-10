/*CO2003-DSA-ASSIGMENT1_PHASE2
*MT19KH05
*/

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
int N;
class Bus {
private:
    string CODE;
    string LP;
    int CASE;
    int TIME_A;
    int TIME_B;
    Bus* next;
    Bus* prev;
    friend class BusSystem;
public:
    Bus() {
        string CODE = "";
        string LP = "";
        CASE = 0;
        TIME_A = 0;
        TIME_B = 0;

    }
    Bus(Bus* next, Bus* prev) {
        this->next = next;
        this->prev = prev;
    }
    Bus(string CODE, string LP, int CASE, int TIME_A, int TIME_B, Bus* next, Bus* prev) {
        this->CASE = CASE;
        this->CODE = CODE;
        this->LP = LP;
        this->TIME_A = TIME_A;
        this->TIME_B = TIME_B;
        this->next = next;
        this->prev = prev;
    }
   


};
class BusSystem {

public:
   
    string query(string instruction) {
        // TODO: Your implementation
   
        
        string ex_statement = instruction.substr(0, 3);   // execution statement
         if (ex_statement == "SQ "){
             instruction = instruction.erase(0, 4);
                 N = stoi(instruction);
         }
         if(ex_statement == "INS") {
             instruction = instruction.erase(0, 4);
             Bus* new_Bus = new Bus();
             
             string ex_CODE = ""; // excution code
             string ex_LP = "";
             string ex_CASE = "";
             string ex_TIMEA = "";
             string ex_TIMEB = "";
             
             // lay gia tri code  
             int i = 0;
             while (instruction[i] != ' ') {
                 i++;
             }
             ex_CODE = instruction.substr(0, i);

             instruction = instruction.erase(0, i+1);

             // lay gia tri lp 
             int k = 0;
             while (instruction[k] != ' ') {
                 k++;
             }

             ex_LP = instruction.substr(0, k);

             instruction = instruction.erase(0, k + 1);

             // lay gia tri case (0 ,1)
             int m = 0;
             while (instruction[m] != ' ') {
                 m++;
             }
             ex_CASE = instruction.substr(1, m - 1);

             instruction = instruction.erase(0, m + 1);

             //lay gia tri time_A

             int n = 0;
             while (instruction[n] != ' ') {
                 n++;
             }

             ex_TIMEA = instruction.substr(0, n);
             instruction = instruction.erase(0, n + 1);

             // lay gia tri time_B

             int l = 0;
             while (instruction[l] != '\0') {
                 l++;
             }
             ex_TIMEB = instruction.substr(0, l);

             instruction = instruction.substr(0, l);

             // truyen cac data(thong so ) da cut ra vao new_Bus ,......
             new_Bus->CODE = ex_CODE;
             new_Bus->LP = ex_LP;
             new_Bus->CASE = stoi(ex_CASE);
             new_Bus->TIME_A = stoi(ex_TIMEA);
             new_Bus->TIME_B = stoi(ex_TIMEB);
             new_Bus->next = NULL;




         }
         if (ex_statement == "DEL") {}
         if (ex_statement == "CS ") {}
         if (ex_statement == "CE ") {}
         if (ex_statement == "GS") {}
         if (ex_statement == "GE") {}
        return "-1";
    }
};

int main() {
    BusSystem* bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;
    cout << bs->query("CS 50 2134") << endl;

}

