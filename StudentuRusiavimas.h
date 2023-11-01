#pragma once

#ifndef CPPPROJECT_StudentuRusiavimas_H
#define CPPPROJECT_StudentuRusiavimas_H


#include "vector"
#include "string"

using namespace std;

const string name = "Vardas";
const string surname = "Pavarde";
const string semesterHomeworkNumber = "Namų darbų skaičius per semestrą";
const string homeworkMark = "namų darbų pažymys";
const string examMark = "egzamino pažymys";
const string resultMarkMean = "Galutinis (Vid.)";
const string resultMarkMedian = "Galutinis (Med.)";
const string randomMarksResult = "Paspauskite 1, kad sugeneruotumėte atsitiktinius ženklus. "
                                 "Paspauskite kitą, kad duomenis įvestumėte rankiniu būdu";
const string homeworkCountQuestion = "Kaip norėtumėte skaičiuoti namų darbų pažymius (vidurkis arba mediana)?";
const string homeworkCountAnswer = "Paspauskite 1, kad gautumėte rezultatus pagal vidurkį. "
                                   "Paspaudus dar ką nors, rezultatai bus skaičiuojami pagal medianą";

const string DEFAULT_FILE_NAME = "kursiokai.txt";

const string CREATE_FILE_QUESTION = "Ar norite sukurti failą? Paspauskite 1, jei norite, ir 0, jei nenorite";

const string TYPE_FILE_NAME = "Įveskite failo pavadinimą";

const string CYCLE_NUMBER_QUESTION = "Parašykite ciklų skaičius, prašome (~100 max)";

const string IS_ADDING_DATA = "Ar norite pridėti duomenų? Paspauskite 1, kad patvirtintumėte taip. Norėdami peržiūrėti tik duomenis, paspauskite 0";

const int STRING_MIXIN_SIZE = 10;

class StudentuRusiavimas {
private:
    string name;
    string surname;
    vector<double> homeworksMark;
    double examMark{};

    vector<string> nameArray = { "Vardas1","Vardas2",
                                "Vardas3","Vardas4",
                                "Vardas5","Vardas6",
                                "Vardas7","Vardas8",
                                "Vardas9","Vardas10",
                                "Vardas11","Vardas12",
                                "Vardas13","Vardas14",
                                "Vardas15","Vardas16",
                                "Vardas17","Vardas18",
                                "Vardas19","Vardas20",
                                "Vardas21","Vardas22",
                                "Vardas23","Vardas24",
                                "Vardas25","Vardas26",
                                "Vardas27", "Vardas28",
                                "Vardas29","Vardas30",
                                "Vardas31","Vardas32",
                                "Vardas33","Vardas34",
                                "Vardas35","Vardas36",
                                "Vardas37","Vardas38",
                                "Vardas39","Vardas40",
                                "Vardas41","Vardas42",
                                "Vardas43","Vardas44",
                                "Vardas45","Vardas46",
                                "Vardas47","Vardas48",
                                "Vardas49","Vardas50",
                                "Vardas51","Vardas52",
                                "Vardas53","Vardas54" };

    vector<string> surnameArray = {
            "Pavarde1","Pavarde2",
            "Pavarde3","Pavarde4",
            "Pavarde5","Pavarde6",
            "Pavarde7","Pavarde8",
            "Pavarde9","Pavarde10",
            "Pavarde11","Pavarde12",
            "Pavarde13","Pavarde14",
            "Pavarde15","Pavarde16",
            "Pavarde17","Pavarde18",
            "Pavarde19","Pavarde20",
            "Pavarde21","Pavarde22",
            "Pavarde23","Pavarde24",
            "Pavarde25","Pavarde26",
            "Pavarde27","Pavarde28",
            "Pavarde29", "Pavarde30",
            "Pavarde31", "Pavarde32",
            "Pavarde33", "Pavarde34",
            "Pavarde35", "Pavarde36",
            "Pavarde37", "Pavarde38",
            "Pavarde39", "Pavarde40",
            "Pavarde41", "Pavarde42",
            "Pavarde43","Pavarde44",
            "Pavarde45","Pavarde46",
            "Pavarde47","Pavarde48",
            "Pavarde49","Pavarde50",
            "Pavarde51","Pavarde52",
            "Pavarde53",
    };
public:
    StudentuRusiavimas();

    StudentuRusiavimas(const StudentuRusiavimas& student);

    ~StudentuRusiavimas();

    
    void printData();

    void readFile();

    void createFile();

    void handleInputState();

    void fillFileWithRandomData();

    void exportSortedData();

private:
    void setName(string name);

    void setSurname(string surname);

    void setHomeworksMark(vector<double> homeworksMark);

    void setExamMark(double examMark);

    void writeFile();

    
    static vector<vector<string>> splitString(const string& s, const string& separator = " ");

    void handleInput();

    double calculateFinalMark(vector<double> homeworkMarksVector, double convertedExamMark, bool isCalculatedByMean);

   
    bool isCalculatedByMean();


};


#endif 
