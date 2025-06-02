#include <iostream>
#include <vector>
#include <string>

class Patient {
    private: 
        std::string name;
        int age;
        float temperature;
        int heartRate;

    public:
        Patient(std::string n, int a){
            name = n;
            age = a;
            temperature = 36.5;
            heartRate = 72;
        }
        void updateVitals(float temp, int hr){
            temperature = temp;
            heartRate = hr;
        }
        void displayInfo(){
            std::cout << "Name: " << name << "\n"
            <<"Age: " << age << "\n"
            << "Temp: " << temperature << "deg Celcius" << "\n"
            << "Heart Rate: " << heartRate << " Bpm" << std::endl;
        }
};

class Hospital{
    private:
        std::vector<Patient*> patients;

    public:
        void addPatient(std::string name, int age){
            Patient* p = new Patient(name, age);
            patients.push_back(p);
        }
        void listPatients(){
            if(patients.empty()){
                std::cout << "no patients registered yet" << std::endl;
                return;
            }
            for (int i = 0; i < patients.size(); ++i){
                if(patients[i] != nullptr){
                    std::cout << "Patient " << i + 1 << ":\n";
                    patients[i]->displayInfo();
                }else{
                    std::cout << "Patient " << i + 1 << ": [discharged]\n";
                }
            }
        }
        ~Hospital(){
            for (auto p : patients ){
                delete p;
            }
        }
};

int main() {
    Hospital h;
    std::string choice_str;

    do {
        std::cout << "\n1. Add Patient\n2. List Patients\n3. Exit\nChoose: ";
        std::getline(std::cin, choice_str);

        if (choice_str == "1") {
            std::string name, age_str;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter age: ";
            std::getline(std::cin, age_str);

            int age = std::stoi(age_str);  
            h.addPatient(name, age);

        } else if (choice_str == "2") {
            h.listPatients();
        }
    } while (choice_str != "3");

    return 0;
}
