#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class Patient {
    private: 
        std::string name;
        int age;
        float temperature;
        int heartRate;

    public:
        Patient(std::string n, int a, float t, int h){
            name = n;
            age = a;
            temperature = t ? t : 37.5;
            heartRate = h ? h : 0 ;
        }
        Patient(std::string n, int a) {
            name = n;
            age = a;
            temperature = 37.5;
            heartRate = 0;
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
        
        std::string serialize() const {
            return name + "," +
                    std::to_string(age) + "," +
                    std::to_string(temperature) + "," +
                    std::to_string(heartRate);
        }
        static Patient* deserialize(const std::string& line){
            std::stringstream ss(line);
            std::string name;
            std::string ageStr, tempStr, hrStr;

            std::getline (ss, name, ',');
            std::getline(ss, ageStr, ',');
            std::getline(ss, tempStr, ',');
            std::getline(ss, hrStr, ',');

            int age = std::stoi(ageStr);
            float temp = std::stof(tempStr);
            int hr = std::stoi(hrStr);

            return new Patient(name, age, temp, hr);
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
        void saveToFile(const std::string& filename){
            std::ofstream out(filename);
            for (auto p : patients){
                if(p != nullptr){
                    out << p->serialize() << "\n";
                }
            }
            out.close();
        }
        void loadFromFile(const std::string& filename) {
            std::ifstream in(filename);
            std::string line;
            while (std::getline(in, line)) {
                if (!line.empty()) {
                    Patient* p = Patient::deserialize(line);
                    patients.push_back(p);
                }
            }
            in.close();
        }
        ~Hospital(){
            for (auto p : patients ){
                delete p;
            }
        }
};

int main() {
    Hospital h;
    h.loadFromFile("patients.txt");
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

    h.saveToFile("patients.txt");
    return 0;
}
