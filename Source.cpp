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
    //int count;
    Bus* next;
    Bus* prev;
   
    friend class BusSystem;
    friend class Double_Link_List_Bus;
public:
    Bus() {
        string CODE = "";
        string LP = "";
        CASE = 0;
        TIME_A = 0;
        TIME_B = 0;
        
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
    int count_DEL;

public:
    void add(Bus* Bus_transmit);
    bool check_CODE_TIMEA(Bus* Bus_transmits);                 // kiem tra Bus them vao cos hop le ko cos cung tuyen cung gio xuat ben khong
    bool check_TIMEA_TIMEB_of_DLL_Bus(Bus* Bus_transmit);                //kiem tra time xuat phat cua xe sau cos lown hon time cap ben cua xe truoc ko 

    int number_Bus_CODE(Bus* Bus);
    bool check_number_Max_of_CODE(Bus* Bus_transmit_1);
    //dung trong DEL_BUS
    void delete_Bus_CODE_TIMEA_TIMEB(string CODE, int TIMEA, int TIMEB);  // xoa Bus cos du TIMEA , TIMEB 
    void delete_Bus_CODE_TIMEA(string CODE, int TIMEA); // xoa BUS co TIME A;
    void delete_Bus_CODE(string CODE); //xoa BUS ma khong co TIMEA , TIMEB


    void delete_a_Bus_of_List_Bus(Bus* Bus_transmit);// dung de xoa mot bus trong danh sach , duoc goi lai khi muon xoa mot Bus nao do thoa yeu cau 


};
class BusSystem {
private:
    friend class Bus;
    friend class Doube_Link_List_Bus;

    Double_Link_List_Bus List_Bus; //
public:

    string query(string instruction);
    bool SQ_Bus(string instruction);
    string INS_Bus(string instruction);
    string DEL_Bus(string instruction);
    void CS_Bus(string instruction);

    void CE_Bus(string instruction);
    void GS_Bus(string instruction);
    void  GE_Bus(string instruction);


    bool check_have_CASE_of_Bus(string instruction);


    bool check_Excution_Statement(string instruction);

    bool check_CODE_LP_Excution_Statement(string codeExcution, string LPExcution);  // kiem tra chuoi code vaf LP co hop le hay khong
    bool check_CASE(string ex_CASE);  // DUNG TRONG INS
    bool check_TIMEA_TIMEB_of_aBus(string TIMEA, string TIMEB); // tra ve true neu no hop le
    bool check_String_to_Int(string temp_string);
    bool check_CASE_of_CS_CE_GS_GE(string instruction);
};

/***********************************************************************************************************************************
*    cac ham check de kiem tra xem no co hop le khong
*
 *************************************************************************************************************************************/
//INS
// kiem tra so chuyen da cos trong tuyen do neu no ddax ddaayf N thif khong add dduoc , neu chua day thi add
// true neu so bus dang co nho hon N 
// de hien thuc xem co them vao duoc hay khong
//DEL
void Double_Link_List_Bus::add(Bus* Bus_transmit) {
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

    
  

}

void Double_Link_List_Bus::delete_Bus_CODE_TIMEA_TIMEB(string CODE, int TIMEA, int TIMEB) {

    Bus* Bus_cur = this->head;
    while (Bus_cur->next != NULL) {
        if (Bus_cur->CODE == CODE && Bus_cur->TIME_A >= TIMEA && Bus_cur->TIME_B <= TIMEB) delete_a_Bus_of_List_Bus(Bus_cur);
        Bus_cur = Bus_cur->next;
    }


}
void Double_Link_List_Bus::delete_Bus_CODE(string CODE) {
    Bus* Bus_cur = this->head;
    while (Bus_cur->next != NULL) {
        if (Bus_cur->CODE == CODE ) delete_a_Bus_of_List_Bus(Bus_cur);
        Bus_cur = Bus_cur->next;
    }

}
void Double_Link_List_Bus::delete_Bus_CODE_TIMEA(string CODE, int TIMEA) {
    Bus* Bus_cur = this->head;
    while (Bus_cur->next != NULL) {
        if (Bus_cur->CODE == CODE && Bus_cur->TIME_A == TIMEA) delete_a_Bus_of_List_Bus(Bus_cur);
        Bus_cur = Bus_cur->next;
    }


}
void Double_Link_List_Bus::delete_a_Bus_of_List_Bus(Bus* Bus_transmit) {
    if ((head->CASE == Bus_transmit->CASE) && (head->CODE == Bus_transmit->CODE) && (head->LP == Bus_transmit->LP) && (head->TIME_A == Bus_transmit->TIME_A) && (head->TIME_B == Bus_transmit->TIME_B)) {

        head = head->next;
        this->count_DEL++;

    }
    if ((tail->CASE == Bus_transmit->CASE) && (tail->CODE == Bus_transmit->CODE) && (tail->LP == Bus_transmit->LP) && (tail->TIME_A == Bus_transmit->TIME_A) && (tail->TIME_B == Bus_transmit->TIME_B)) {
        tail = tail->prev;
        tail->next == NULL;
        this->count_DEL++;
    }
    else {
        Bus* Bus_cur = this->head;
        while (Bus_cur->next != NULL) {
            if ((Bus_cur->CASE == Bus_transmit->CASE) && (Bus_cur->CODE == Bus_transmit->CODE) && (Bus_cur->LP == Bus_transmit->LP) && (Bus_cur->TIME_A == Bus_transmit->TIME_A) && (Bus_cur->TIME_B == Bus_transmit->TIME_B)) {

                Bus_cur->prev->next = Bus_cur->next;
                Bus_cur->next->prev = Bus_cur->prev;
                Bus_cur = Bus_cur->next;


            }
            else {
                Bus_cur = Bus_cur->next;
            }

        }
    }
}
bool Double_Link_List_Bus::check_number_Max_of_CODE(Bus* Bus_transmit) {
    Bus* Bus_cur = this->head;
    int count_Bus = 0;
    while (Bus_cur->next != NULL) {
        if (Bus_cur->CODE == Bus_transmit->CODE) { count_Bus++; }
        else   Bus_cur = Bus_cur->next;
    }

    if (count_Bus >= N) return false;
    else return true;
}


// kiem tra xem da co bus nao cung tuyen , cung time a khong ?
// true neu khong co 
// false neu co
// su dung de check trong dk INS
bool Double_Link_List_Bus::check_CODE_TIMEA(Bus* Bus_transmit)   // true neu ko co chuyen nao cung tuyen cung time_A
{
    Bus* Bus_cur = this->head;
    while (Bus_cur->next != NULL) {

        if (Bus_cur->CODE == Bus_transmit->CODE && Bus_cur->TIME_A == Bus_transmit->TIME_A) return false;
        else { Bus_cur = Bus_cur->next; }
    }

    return true;
}
//kiem tra xem neu da co cung ma tuyen (CODE) thi phai dam bao TIMEA cua xe sau lon hon TIMEB cua xe (cungf bien LP) tai thoi diem  truoc
// true neu hople
//... nguoc lai
// su dung de check trong ham INS .. hop le thi thuc hien
bool Double_Link_List_Bus::check_TIMEA_TIMEB_of_DLL_Bus(Bus* Bus_transmit)
{
    Bus* Bus_cur = this->head;

    while (Bus_cur->next != NULL) {
        if (Bus_cur->LP == Bus_transmit->LP) {
            if (Bus_cur->TIME_B >= Bus_transmit->TIME_A)  return false;
        }
        Bus_cur = Bus_cur->next;
    }

    return true;
}

// .. dung de dem so Bus trong 1 tuyen CODE
//.. chua dung den .. neu yeu cau tra ve so chuyen trong 1 tuyen
int Double_Link_List_Bus::number_Bus_CODE(Bus* Bus_transmit) {
    Bus* Bus_cur = this->head;
    int number_Bus_CODE = 0;     // so chuyen tren mot tuyen 
    while (Bus_cur->next != NULL) {
        if (Bus_cur->CODE == Bus_transmit->CODE) { number_Bus_CODE++; }
        Bus_cur = Bus_cur->next;

    }
    return number_Bus_CODE;

}

// kiem tra trong chuoi co ton tai CASE hay khong ? chua xet den truong hop case do co hop le ?
// tra ve true neu co CASE ( co 5 space )
// tra ve false neu khong co CASE (co 4 space )
//.. con cac truong hop 3space , 6 space ==> da duoc hien thuc trong check_ins.._ex...

bool BusSystem::check_have_CASE_of_Bus(string instruction)


{
    int count_space = 0;
    for (unsigned int i = 0; i < instruction.size(); i++) {
        if (instruction[i] == ' ') count_space++;
    }

    if (count_space == 4) return true;
    else if(count_space == 3 ) return false;  // count_space = 4 , truong hop khac da duoc xu ly trong hamf check chuoi thuc thi
}

// check xem case phu hop chua... phu hop khi case chuyen sang int chir co 2 gia tri 0 va 1
//tra ve true neu no phuf hop 
//.. nguoc lai

bool BusSystem::check_CASE(string ex_CASE) {
    
    if (check_String_to_Int(ex_CASE) == true) {
        if ((stoi(ex_CASE) == 0) || (stoi(ex_CASE) == 1)) return true;
        else return false;
    }
    else return false;

}

// kiem tra chuoi xu ly lenh de lay thong so cho Bus ...
//chi xet dau space chu xet xem no co hop ly khong 
// true :: khi khong co space dau va cuoi chuoi  && so space xen giua phai hop ly
// false :: ... truong hop khac
bool BusSystem::check_Excution_Statement(string instruction) {

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
        if (count_space == 4 ||count_space == 5)  return true;
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
        if (count_space >= 2 && count_space <= 3)  return true;
    }
    if (ex_statement == "CE ") {
        int count_space = 0;
        for (unsigned int i = 0; i < instruction.size(); i++) {
            if (instruction[i] == ' ') count_space++;
        }
        if (count_space >= 2 && count_space <= 3)  return true;
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
//check xem CODE , LP da hop ly chua 
//true :...matuyen(CODE) toi da 5 ki tu ,... maLP toi da 10ki tu
//else false
bool BusSystem::check_CODE_LP_Excution_Statement(string codeExcution, string LPExcution)   // kiem tra chuoi code vaf LP co hop le hay khong
{
    if (codeExcution.size() <= 5 && LPExcution.size() <= 10) return true;
    else return false;
}
//check xem trong 1 xe bus TIME_B > TIMEA khong ?
// true : hop le
// false :: khong hop le
bool BusSystem::check_TIMEA_TIMEB_of_aBus(string TIMEA, string TIMEB)
{
    if ((check_String_to_Int(TIMEA) == true) && (check_String_to_Int(TIMEB) == true)) {
        if (stoi(TIMEA) < stoi(TIMEB)) return true;
        else return false;
    }

    else return false;
}
// kiem tra CASE, TIMEA , TIMEB co toan la so nguyen hay khong ?
//true :: ...
//false :: a123 , 123a , 1a2356 ...
bool BusSystem::check_String_to_Int(string temp_string) {

    if (temp_string[0] > 47 && temp_string[0] < 58) {
        if ((stoi(temp_string) == 0) && (temp_string.size() == 1)) return true;
         
        if ((stoi(temp_string) != 0) && (((int)log10(stoi(temp_string)) + 1) == temp_string.size())) return true;
        else return false;
        

    }
    else return false;

}
// check cos CASE trong Leenhj CS , CE , GS, GE
// vi cu phap lenh CS, CE, GS, GE giong nhau 
// tra ve true neu co CASE 
//false :.... khong co CASE
//instruction truyen vao trong Check nay laf instruction da xoa 2 kis tu dau kem dau space ngay sau do
bool BusSystem::check_CASE_of_CS_CE_GS_GE(string instruction) {


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
                return "1";
            }
            else return "-1";
        }
        if (ex_statement == "INS") {
            instruction = instruction.erase(0, 4);
            return INS_Bus(instruction);
            //cout << this->List_Bus.count;


        }




    }
    else return "-1";
}

// instruction vao trong cac hamf INS,DEL... la instruction de cho nhung da xoa may ki tu ddau
string BusSystem::INS_Bus(string instruction) {


  
    // truong hop co CASE
    //..
    if (check_have_CASE_of_Bus(instruction) == true) {
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

        instruction = instruction.erase(0, i + 1);
          
        // lay gia tri lp
        int k = 0;
        while (instruction[k] != ' ') {
            k++;
        }

        ex_LP = instruction.substr(0, k);

        instruction = instruction.erase(0, k + 1);
    
        //lay gia tri case
        int m = 0;
        while (instruction[m] != ' ') {
            m++;
        }
      
        ex_CASE = instruction.substr(0, m);

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

     
      

        if ((check_CASE(ex_CASE) == true) && (check_String_to_Int(ex_CASE) == true) && (check_String_to_Int(ex_TIMEA) == true) && (check_String_to_Int(ex_TIMEB) == true) && (check_TIMEA_TIMEB_of_aBus(ex_TIMEA, ex_TIMEB) == true) && (check_CODE_LP_Excution_Statement(ex_CODE, ex_LP) == true)) {

            // truyen cac data(thong so ) da cut ra vao new_Bus ,......
            new_Bus->CODE = ex_CODE;
            new_Bus->LP = ex_LP;

            new_Bus->TIME_A = stoi(ex_TIMEA);
            new_Bus->TIME_B = stoi(ex_TIMEB);
            new_Bus->next = NULL;
            this->List_Bus.add(new_Bus);
            return to_string(List_Bus.count);

        }

        else  return "-1";
        
    }
    //truong hop khong co case
    //..
    if (check_have_CASE_of_Bus(instruction) == false) {
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

        instruction = instruction.erase(0, i + 1);

        // lay gia tri lp
        int k = 0;
        while (instruction[k] != ' ') {
            k++;
        }

        ex_LP = instruction.substr(0, k);

        instruction = instruction.erase(0, k + 1);

        ex_CASE = '0';
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

        if ((check_CASE(ex_CASE) == true) && (check_String_to_Int(ex_CASE) == true) && (check_String_to_Int(ex_TIMEA) == true) && (check_String_to_Int(ex_TIMEB) == true) && (check_TIMEA_TIMEB_of_aBus(ex_TIMEA, ex_TIMEB) == true) && (check_CODE_LP_Excution_Statement(ex_CODE, ex_LP) == true)) {

            // truyen cac data(thong so ) da cut ra vao new_Bus ,......
            new_Bus->CODE = ex_CODE;
            new_Bus->LP = ex_LP;

            new_Bus->TIME_A = stoi(ex_TIMEA);
            new_Bus->TIME_B = stoi(ex_TIMEB);
            new_Bus->next = NULL;
            this->List_Bus.add(new_Bus);
            return to_string(List_Bus.count);
         

        }

        else  return "-1";
    }

    

}

// instruction vao trong cac hamf INS,DEL... la instruction de cho nhung da xoa may ki tu ddau
string BusSystem::DEL_Bus(string instruction) {
    string CODE = "";
    string TIMEA = "";
    string TIMEB = "";


    int count_space = 0;  // xet xem co TIMEA,TIMEB, hay co car hai hay khong co cai nao het trong chuoi lenh
    for (int i = 0; i < instruction.size(); i++) {
        if (instruction[i] == ' ') count_space++;
    }
    if(count_space == 0) {
        CODE = instruction;
        List_Bus.delete_Bus_CODE(CODE);
        return to_string(List_Bus.count_DEL);

    }
    else if(count_space == 1){
    
        int n = 0;
        while (instruction[n] != ' ') {
            n++;
        }
        CODE = instruction.substr(0, n);

        instruction = instruction.erase(0, n + 1);

        TIMEA = instruction;

        if (check_String_to_Int(TIMEA) == true) {
            List_Bus.delete_Bus_CODE_TIMEA(CODE, stoi(TIMEA));
            return to_string(List_Bus.count_DEL);
        }
        else return"-1";

    
    }
    else if(count_space == 2){

        int n = 0;
        while (instruction[n] != ' ') {
            n++;
        }
        CODE = instruction.substr(0, n);

        instruction = instruction.erase(0, n + 1);

        int m= 0;
        while (instruction[m] != ' ') {
            m++;
        }
        TIMEA = instruction.substr(0, m);

        instruction = instruction.erase(0, m + 1);

        TIMEB = instruction;

        if (check_String_to_Int(TIMEA) == true && check_String_to_Int(TIMEB)) {
            List_Bus.delete_Bus_CODE_TIMEA_TIMEB(CODE, stoi(TIMEA), stoi(TIMEB));
            return to_string(List_Bus.count_DEL);
        }
        else return "-1";
    }

}






int main() {
    BusSystem* bs = new BusSystem();

    cout << bs->query("SQ 50") << endl;
   
    cout << bs->query("INS A12 50D-23342 1 1235 5678") << endl;
    cout << bs->query("INS B23 32C-55555 0 1235 9121") << endl;
    cout << bs->query("INS C4 54D1-89391 0 1277 2100") << endl;
    //cout << bs->query("INS C4 54D1-89391 0 1277 2100") << endl;
    cout << bs->query("DEL C4") << endl;

   
}
