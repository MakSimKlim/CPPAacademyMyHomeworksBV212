// ДЗ #14 до 30.09.23_Работа с потоками файлов_Больница.
//
//
//Задание 1. Напишите приложение для больницы.Опишите класс Пациент,
//который имеет имя, дату госпитализации и дату выписки(как строки),
//диагноз и фамилию лечащего врача.Опишите класс Больница, который будет
//хранить массив Пациентов, и который умеет добавлять в массив новых
//пациентов, отображать список всех пациентов, а также может записать их в
//файл и считать их из файла.Обязательно использовать библиотеку fstream.

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int Menu() {
    cout << "\n1. Добавить нового пациента в файл\n";
    cout << "2. Показать всех пациентов из файла\n";
    cout << "3. Выйти\n";
    cout << "> ";
    int choice;
    cin >> choice;
    return choice;
}

class Patient {
private:
    string name;
    string admissionDate;
    string dischargeDate;
    string diagnosis;
    string attendingDoctor;

public:
    Patient(string n, string ad, string dd, string diag, string doctor);
    Patient();
    ~Patient();

    void Put();
    void Show();
    void SaveToFile();
    static void DisplayFromFile();
};

Patient::Patient() {
    name = "";
    admissionDate = "";
    dischargeDate = "";
    diagnosis = "";
    attendingDoctor = "";
}

Patient::Patient(string n, string ad, string dd, string diag, string doctor) :
    name{ n }, admissionDate{ ad }, dischargeDate{ dd }, diagnosis{ diag }, attendingDoctor{ doctor } {}

Patient::~Patient() {}

void Patient::Put() {
    cout << "\nВведите имя пациента: ";
    cin >> name;
    cout << "Введите дату госпитализации: ";
    cin >> admissionDate;
    cout << "Введите дату выписки: ";
    cin >> dischargeDate;
    cout << "Введите диагноз: ";
    cin >> diagnosis;
    cout << "Введите имя лечащего врача: ";
    cin >> attendingDoctor;
}

void Patient::Show() {
    cout << "Имя: " << name << ", Дата госпитализации: " << admissionDate
        << ", Дата выписки: " << dischargeDate << ", Диагноз: " << diagnosis
        << ", Лечащий врач: " << attendingDoctor << "\n";
}

void Patient::SaveToFile() {
    ofstream file("patients.txt", ios::out | ios::app);
    if (!file) {
        cout << "Не удалось открыть файл для записи." << endl;
        exit(1);
    }

    file << name << "\n"
        << admissionDate << "\n"
        << dischargeDate << "\n"
        << diagnosis << "\n"
        << attendingDoctor << "\n";

    file.close();
}

void Patient::DisplayFromFile() {
    ifstream file("patients.txt", ios::in);
    if (!file) {
        cout << "Не удалось открыть файл для чтения." << endl;
        exit(1);
    }

    string n, ad, dd, diag, doctor;

    while (file >> n >> ad >> dd >> diag >> doctor) {
        Patient patient{ n, ad, dd, diag, doctor };
        patient.Show();
    }

    file.close();
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int answer;
    do {
        answer = Menu();
        if (answer == 1) {
            Patient patient;
            patient.Put();
            patient.SaveToFile();
        }
        else {
            Patient::DisplayFromFile();
        }
    } while (answer != 3);

    return 0;
}