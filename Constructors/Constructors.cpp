#include <iostream>
#include <cstring>
#include "Windows.h"

using namespace std;

class Person {
    int ID;
    char* surname;
    char* name;
    char* patronymic;
    int day;
    int month;
    int year;
public:
    static int counter;
    Person(int IDP, const char* surnameP, const char* nameP, const char* patronymicP, int dayP, int monthP, int yearP)
        : ID{ IDP }, surname{ surnameP ? new char[strlen(surnameP) + 1] : nullptr }, name{ nameP ? new char[strlen(nameP) + 1] : nullptr }, patronymic{ patronymicP ? new char[strlen(patronymicP) + 1] : nullptr }, day{ dayP }, month{ monthP }, year{ yearP }
    {
        if (surnameP) strcpy_s(surname, strlen(surnameP) + 1, surnameP);
        else surname = nullptr;
        if (nameP) strcpy_s(name, strlen(nameP) + 1, nameP);
        else name = nullptr;
        if (patronymicP) strcpy_s(patronymic, strlen(patronymicP) + 1, patronymicP);
        else patronymic = nullptr;
        counter++;
    }
    Person() : Person(0, nullptr, nullptr, nullptr, 0, 0, 0) {}
    Person(const Person& object)
        : ID{ object.ID }, surname{ object.surname ? new char[strlen(object.surname) + 1] : nullptr }, name{ object.name ? new char[strlen(object.name) + 1] : nullptr },
        patronymic{ object.patronymic ? new char[strlen(object.patronymic) + 1] : nullptr }, day{ object.day }, month{ object.month }, year{ object.year }
    {
        if (surname) strcpy_s(surname, strlen(object.surname) + 1, object.surname);
        if (name) strcpy_s(name, strlen(object.name) + 1, object.name);
        if (patronymic) strcpy_s(patronymic, strlen(object.patronymic) + 1, object.patronymic);
        counter++;
    }

    void coutPerson() {
        if (surname == nullptr) cout << "Person: nobody" << endl;
        else cout << "Person: " << surname << ' ' << name << ' ' << patronymic << endl;
        cout << "ID: " << ID << endl;
        cout << "Date of birth: " << day << '/' << month << '/' << year << endl;
        cout << endl;
    }

    ~Person() {
        delete[] surname;
        delete[] name;
        delete[] patronymic;
    }
};
int Person::counter;

class Apartment {
    Person* residentData;
    int residentNumber;
    int apartmentNumber;
    int roomsNumber;
    int entranceNumber;

public:
    Apartment(const Person* residentDataA, int residentNumberA, int apartmentNumberA, int roomsNumberA, int entranceNumberA)
        :residentData{ new Person[residentNumberA] }, residentNumber{ residentNumberA },
        apartmentNumber{ apartmentNumberA }, roomsNumber{ roomsNumberA }, entranceNumber{ entranceNumberA }
    {
        for (int i = 0; i < residentNumberA; i++) {
            residentData[i] = residentDataA[i];
        }
    }
    Apartment() : Apartment(nullptr, 0, 0, 0, 0) {}
    Apartment(const Apartment& object)
        : residentData{ new Person[object.residentNumber] }, residentNumber{ object.residentNumber },
        apartmentNumber{ object.apartmentNumber }, roomsNumber{ object.roomsNumber }, entranceNumber{ object.entranceNumber }
    {
        for (int i = 0; i < object.residentNumber; i++) {
            residentData[i] = object.residentData[i];
        }
    }

    int getEntranceNumber() const {
        return entranceNumber;
    }

    void coutApartment() const {
        cout << "Apartment № " << apartmentNumber << endl;
        cout << "Rooms: " << roomsNumber << endl;
        cout << "Residents: " << residentNumber << endl;
        for (int i = 0; i < residentNumber; i++) {
            if (residentData == nullptr) cout << "No residents data" << endl;
            else {
                residentData[i].coutPerson();
            }
        }
        cout << endl;
    }

    ~Apartment() {
        delete[] residentData;
    }
};

class House {
    int numberApartment;
    int numberEntrance;
    Apartment* apartmentData;
public:
    House(int numberApartmentP, int numberEntranceP, const Apartment* apartmentDataP)
        : numberApartment{ numberApartmentP }, numberEntrance{ numberEntranceP }
    {
        apartmentData = new Apartment[numberApartment];
        for (int i = 0; i < numberApartment; i++) {
            apartmentData[i] = apartmentDataP[i];
        }
    }
    House() : House(0, 0, nullptr) {}
    House(const House& object)
        : numberApartment{ object.numberApartment }, numberEntrance{ object.numberEntrance }
    {
        apartmentData = new Apartment[numberApartment];
        for (int i = 0; i < numberApartment; i++) {
            apartmentData[i] = object.apartmentData[i];
        }
    }

    void coutHouse() const {
        cout << "OUR HOUSE" << endl;
        for (int i = 1; i < numberEntrance + 1; i++) {
            cout << "Entrance №" << i << endl;
            for (int j = 0; j < numberApartment; j++) {
                if (apartmentData[j].getEntranceNumber() == i) {
                    apartmentData[j].coutApartment();
                }
            }
        }
    }

    ~House() {
        delete[] apartmentData;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Person person1_1{ 567456, "Shablii", "Aryna", "Aleksandrovna", 12, 01, 2009 };
    Person person1_2{ 345671, "Petrov", "Petro", "Petrovich", 23, 02, 2008 };
    Person person2_1{ person1_1 };
    Person person3_1{ 278917, "Markova", "Mariia", "Markovna", 06, 07, 2003 };
    Person person3_2{ 256723, "Mikolaeva", "Marina", "Nikolaenko", 14, 03, 2001 };
    Person person3_3{ 178209, "Klimenko", "Nikita", "Denisovich", 27, 11, 2008 };
    Person* people1 = new Person[2]{ person1_1, person1_2};
    Person* people2 = new Person[1]{ person2_1 };
    Person* people3 = new Person[3]{ person3_1, person3_2, person3_3 };

    Apartment apartment1{ people1, 2, 1, 3, 1 };
    Apartment apartment2{ people2, 1, 2, 2, 1 };
    Apartment apartment3{ people3, 3, 3, 4, 2 };

    Apartment* apartments = new Apartment[3]{ apartment1, apartment2, apartment3 };

    House house{ 3, 2, apartments };
    house.coutHouse();

    delete[] people1;
    delete[] people2;
    delete[] people3;
    delete[] apartments;
    return 0;
}
