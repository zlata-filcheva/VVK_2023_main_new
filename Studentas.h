#include "vector"
#include "string"

using namespace std;

const string name = "Vardas";
const string surname = "Pavarde";
const string semesterHomeworkNumber = "Number of homeworks per semester";
const string homeworkMark = "homework mark";
const string examMark = "exam mark";
const string resultMarkMean = "Galutinis (Vid.)";
const string resultMarkMedian = "Galutinis (Med.)";
const string randomMarksResult = "Paspauskite 1, kad sugeneruotumėte atsitiktinius ženklus."
                                 " Paspauskite kitą, kad duomenis įvestumėte rankiniu būdu";
const string homeworkCountQuestion = "Kaip norėtumėte skaičiuoti namų darbų pažymius (vidurkis arba mediana)?";
const string homeworkCountAnswer = "Paspauskite 1, kad gautumėte rezultatus pagal vidurkį. "
                                   "Paspaudus dar ką nors, rezultatai bus skaičiuojami pagal medianą";

const string FILE_NAME = "kursiokai.txt";

const string IS_ADDING_DATA = "Do you want to add data? Press 1 for yes. Press 0 to view data only.";

class Student {
private:
    string name;
    string surname;
    vector<double> homeworksMark;
    double examMark;
public:
    Student();

    Student(const Student &student);

    ~Student();

    void printData();

    void readFile();

    void createFile();

    void handleInputState();

private:
    void setName(string name);

    void setSurname(string surname);

    void setHomeworksMark(vector<double> homeworksMark);

    void setExamMark(double examMark);

    void writeFile();

    vector<vector<string>> splitString(const string& s, const string& separator = " ");

    void handleInput();

    double calculateFinalMark(vector<double> homeworkMarksVector, double convertedExamMark, bool isCalculatedByMean);

    bool isCalculatedByMean();
};