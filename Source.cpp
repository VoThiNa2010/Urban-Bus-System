/*CO2003-DSA-ASSIGMENT1_PHASE2
*MT19KH05
*/

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<math.h>  //
#include<vector>
#include<algorithm>
using namespace std;

int N;   // so chuyen toi da trong 1 tuyen
class Bus {
private:
    string CODE;
    string LP;
    int CASE;
    int TIME_A;
    int TIME_B;
    int count;
    Bus* next;
    Bus* prev;
   Bus* head;
   Bus* tail;
    friend class BusSystem;
    friend class Double_Link_List_Bus;
public:
    Bus() {
        string CODE = "";
        string LP = "";
        CASE = 0;
        TIME_A = 0;
        TIME_B = 0;
        head = tail = 0;
        count = 0;
        next = 0;
        prev = 0;
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
private:
    friend class Bus;
    friend class Doube_Link_List_Bus;

    Double_Link_List_Bus List_Bus;
public:
    
    string query(string instruction) ;
    bool SQ_Bus(string instruction) ;
    void INS_Bus(string instruction);
    void DEL_Bus(string instruction) ;
    void CS_Bus(string instruction) ;

    void CE_Bus(string instruction) ;
    void GS_Bus(string instruction) ;
    void  GE_Bus(string instruction) ;
 

    bool check_have_CASE_of_Bus(string instruction) ;
  

    bool check_Excution_Statement(string instruction) ;

    bool check_CODE_LP_Excution_Statement(string codeExcution, string LPExcution) ;  // kiem tra chuoi code vaf LP co hop le hay khong
    
    bool check_TIMEA_TIMEB_of_aBus(string TIMEA, string TIMEB) ; // tra ve true neu no hop le
    bool check_String_to_Int(string temp_string) ;
};
class Double_Link_List_Bus
{
private:
    friend class Bus;
    friend class BusSystem;
protected:
    Bus* head;
    Bus* tail;
    int count;
    Bus* next;
    Bus* prev;


public:
    int add(Bus* Bus_transmit) ;
    bool check_CODE_TIMEA(Bus* Bus_transmits) ;                 // kiem tra Bus them vao cos hop le ko cos cung tuyen cung gio xuat ben khong
    bool check_TIMEA_TIMEB_of_DLL_Bus(Bus* Bus_transmit) ;                //kiem tra time xuat phat cua xe sau cos lown hon time cap ben cua xe truoc ko 

    int number_Bus_CODE(Bus* Bus) ;
    bool check_number_Max_of_CODE(Bus* Bus_transmit_1);
   


};
    /***********************************************************************************************************************************
    *    cac ham check de kiem tra xem no co hop le khong
    *
     *************************************************************************************************************************************/
int Double_Link_List_Bus :: add(Bus* Bus_transmit) {
    if (head == NULL) {
        head = tail = Bus_transmit;
        this->count++;
    }
    else {
        if (check_CODE_TIMEA(Bus_transmit) == true && check_TIMEA_TIMEB_of_DLL_Bus(Bus_transmit) == true && check_number_Max_of_CODE(Bus_transmit) == true) {
            this->tail->next = Bus_transmit;
            Bus_transmit->prev = tail;
            this->tail = Bus_transmit;
        }
        this->count++;
    }

   return  this->count;

}
// kiem tra so chuyen da cos trong tuyen do neu no ddax ddaayf N thif khong add dduoc , neu chua day thi add
// true neu so bus dang co nho hon N
bool Double_Link_List_Bus :: check_number_Max_of_CODE(Bus* Bus_transmit)  {   
       Bus* Bus_cur = this->head;
       int count_Bus = 0;
       while (Bus_cur->next != NULL) {
           if (Bus_cur->CODE == Bus_transmit->CODE) { count_Bus++; }
           else   Bus_cur = Bus_cur->next;
      }

    if (count_Bus >= N) return false;
    else return true;
}



bool Double_Link_List_Bus :: check_CODE_TIMEA( Bus* Bus_transmit)   // true neu ko co chuyen nao cung tuyen cung time_A
{
     Bus* Bus_cur = this->head;
    while (Bus_cur->next != NULL) {

        if (Bus_cur->CODE == Bus_transmit->CODE && Bus_cur->TIME_A == Bus_transmit->TIME_A) return false;
        else {  Bus_cur = Bus_cur->next;  }
    }

    return true;
}

bool Double_Link_List_Bus :: check_TIMEA_TIMEB_of_DLL_Bus( Bus* Bus_transmit)
{
       Bus* Bus_cur = this->head;

    while (Bus_cur->next != NULL) {
        if (Bus_cur->LP == Bus_transmit->LP) {
            if (Bus_cur->TIME_B > Bus_transmit->TIME_A)  return false;
        }
        Bus_cur = Bus_cur->next;
      }

    return true;
}

int Double_Link_List_Bus :: number_Bus_CODE(Bus* Bus_transmit) {
    Bus* Bus_cur = this->head;
    int number_Bus_CODE = 0;     // so chuyen tren mot tuyen 
    while (Bus_cur->next != NULL) {
        if (Bus_cur->CODE == Bus_transmit->CODE) { number_Bus_CODE++; }
        Bus_cur = Bus_cur->next;

    }
    return number_Bus_CODE;

}
bool BusSystem:: check_have_CASE_of_Bus(string instruction)
// kiem tra xem co case trong INS khoong 
{   
    int count_space = 0;
    for (unsigned int i = 0; i < instruction.size(); i++) {
        if (instruction[i] == ' ') count_space++;
    }

    if (count_space == 5) return true;
    if (count_space == 4) return false;
}
bool BusSystem:: check_Excution_Statement(string instruction) {
    
    string ex_statement = instruction.substr(0, 3);   // execution statement
    if (instruction[0] == ' ' || instruction[instruction.size() - 1] == ' ') return false;
    if (ex_statement == "SQ ") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space == 1) return true;
     }
    if (ex_statement == "INS") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space >= 3 && count_space <=  5)  return true;
    }
    if (ex_statement == "DEL") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space <= 3 && count_space >= 1)  return true;
    }
    if (ex_statement == "CS ") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space >=2 && count_space <= 3)  return true;
    }
    if (ex_statement == "CE ") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space >= 2 && count_space <= 3 )  return true;
    }
    if (ex_statement == "GS ") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space >= 2 && count_space <= 3)  return true;
    }
    if (ex_statement == "GE ") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space >= 2 && count_space <= 3)  return true;
    }
    else return false;
}
bool BusSystem::check_CODE_LP_Excution_Statement(string codeExcution , string LPExcution)   // kiem tra chuoi code vaf LP co hop le hay khong
{
    if (codeExcution.size() <= 5 && LPExcution.size() <= 5) return true;
    else return false;
}
bool BusSystem:: check_TIMEA_TIMEB_of_aBus(string TIMEA, string TIMEB)  // tra ve true neu no hop le
{   
    int d_TIMEA = (int)log10(stoi(TIMEA)) + 1;
    int d_TIMEB = (int)log10(stoi(TIMEB)) + 1;

    if ((stoi(TIMEA) < stoi(TIMEB)) && (d_TIMEA == TIMEA.size()) && (d_TIMEB = TIMEB.size()) )return true;
    else return false;
}
bool BusSystem::check_String_to_Int(string temp_string) {
    //int temp = stoi(temp_string);
    if (temp_string[0] > 47 && temp_string[0] < 58) {
        if(stoi(temp_string) == 0  ) { 
            if (temp_string.size() == 1) return true;
        }
        if ( (stoi(temp_string) != 0) && (((int)log10(stoi(temp_string)) + 1) == temp_string.size())) return true;
    }
    else return false;

}
/*****************************************************************
*HIEN THU 7 CAU LENH TRONG BUSSYSTEM                             *
*************************************/
string BusSystem::query(string instruction) {


    /**********************************************************************************************************/
    /**      HIEN THUC LENH QUA VIEC CAT CHUOI LAY DU LIEU                                                    */
    /**********************************************************************************************************/

    if (check_Excution_Statement(instruction) == true) {
        string ex_statement = instruction.substr(0, 3);   // execution statement

        if (ex_statement == "SQ ") {
            instruction = instruction.erase(0, 3);
            if (check_String_to_Int(instruction) == true) {
                N = stoi(instruction);
                return "1"; } 
            else return "-1";
        }
        if (ex_statement == "INS") {
            instruction = instruction.erase(0, 4);
            INS_Bus(instruction);



        }

       


    }
    else return "-1";
}

void BusSystem::INS_Bus(string instruction) {

    Bus* new_Bus = new Bus();

    string ex_CODE = ""; // excution code
    string ex_LP = "";
    string ex_CASE = "";
    string ex_TIMEA = "";
    string ex_TIMEB = "";

    if (check_have_CASE_of_Bus(instruction) == true ) {
        // lay gia tri code
        int i = 0;
        while (instruction[i] != ' ') {
            i++;
        }
        ex_CODE = instruction.substr(0, i);

        instruction = instruction.erase(0, i + 1);

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
        //new_Bus->CASE = stoi(ex_CASE);

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
    }

    if (check_have_CASE_of_Bus(instruction) == false) {
        // lay gia tri code
        int i = 0;
        while (instruction[i] != ' ') {
            i++;
        }
        ex_CODE = instruction.substr(0, i);

        instruction = instruction.erase(0, i + 1);

        // lay gia tri lp
        int k = 0;
        while (instruction[k] != ' ') {
            k++;
        }

        ex_LP = instruction.substr(0, k);

        instruction = instruction.erase(0, k + 1);

        // lay gia tri time_B 
        ex_CASE = '2';
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

    }

    if (check_String_to_Int(ex_CASE) == true && check_String_to_Int(ex_TIMEA) == true && check_String_to_Int(ex_TIMEB) == true) {

        // truyen cac data(thong so ) da cut ra vao new_Bus ,......
        new_Bus->CODE = ex_CODE;
        new_Bus->LP = ex_LP;

        new_Bus->TIME_A = stoi(ex_TIMEA);
        new_Bus->TIME_B = stoi(ex_TIMEB);
        new_Bus->next = NULL;
    }
    
    // add Bus vao DLL_BUs;

    List_Bus.add(new_Bus);
}








int main() {
    BusSystem* bs = new BusSystem();
    cout << bs->query("SQ 0") << endl;
    cout << bs->query("SQ 5000") << endl;
   // cout << N;
    //cout << bs->query("INS 50 50D1-23342 0 1234 5678") << endl;
}
