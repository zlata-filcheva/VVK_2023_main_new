#include "Studentas.h"
#include <iostream>
#include <random>
#include <fstream>
#include <iterator>

Student::Student() = default;

Student::Student(const Student &student) {
    setName(student.name);
    setSurname(student.surname);
    setHomeworksMark(Student::homeworksMark);
    setExamMark(student.examMark);
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setSurname(string surname) {
    this->surname = surname;
}

void Student::setHomeworksMark(vector<double> homeworksMark) {
    this->homeworksMark = homeworksMark;
}

void Student::setExamMark(double examMark) {
    this->examMark = examMark;
}

Student::~Student() {
    this->setName("");
    this->setSurname("");
    this->setHomeworksMark({});
    this->setExamMark(0);
}

void Student::handleInput() {
    int homeworksNumber;

    string inputName;
    string inputSurname;
    vector<double> inputHomeworksMark;
    double inputExamMark = 0.0;
    bool areResultsRandom = false;
    int inputValue = 0;

    cout << name << endl;
    cin >> inputName;

    cout << surname << endl;
    cin >> inputSurname;

    cout << randomMarksResult << endl;
    cin >> inputValue;

    if (inputValue)
        areResultsRandom = true;

    if (areResultsRandom) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> generatedHomeworksNumber(1,5);
        uniform_int_distribution<> generatedMark(1,10);

        homeworksNumber = generatedHomeworksNumber(gen);

        for (int i = 0; i < homeworksNumber; i++) {
            inputHomeworksMark.push_back(generatedMark(gen));
        }

        inputExamMark = generatedMark(gen);
    }
    else {
        cout << semesterHomeworkNumber << endl;
        cin >> homeworksNumber;

        for (int i = 0; i < homeworksNumber; i++) {
            double mark;

            cout << i + 1 << " " << &homeworksMark << endl;
            cin >> mark;

            inputHomeworksMark.push_back(mark);
        }

        cout << examMark << endl;
        cin >> inputExamMark;
    }

    setName(inputName);
    setSurname(inputSurname);
    setHomeworksMark(inputHomeworksMark);
    setExamMark(inputExamMark);

    writeFile();

    printData();
}

void Student::printData() {
    const bool isMeanResult = isCalculatedByMean();

    const double finalMark = calculateFinalMark(homeworksMark, examMark, isMeanResult);

    cout << surname << " " << name << " ";
    cout << (isMeanResult == 1 ? resultMarkMean : resultMarkMedian) << endl;
    cout << name << " " << surname << " " << finalMark << endl;
}

void Student::createFile() {
    ofstream fileOut;

    fileOut.open(FILE_NAME, ios_base::app);

    fileOut << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 Egzaminas" << endl;
}

void Student::writeFile() {
    ofstream fileOut;

    fileOut.open(FILE_NAME, ios_base::app);

    fileOut << surname << " " << name << " ";

    for (double mark: homeworksMark)
        fileOut << mark << " ";

    const int length = (int) homeworksMark.size();

    for (int i = 0; i < 5 - length; i++)
        fileOut << 0 << " ";

    fileOut << examMark << endl;
}

void Student::readFile() {
    vector<vector<string>> modifiedVector;

    ifstream fileIn(FILE_NAME);

    if (!fileIn.is_open())
        return;

    const bool isMeanResult = isCalculatedByMean();

    string inputData = string((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

    vector<vector<string>> arrayVector = splitString(inputData);

    for (const vector<string> sVector: arrayVector) {
        vector<double> homeworkMarksVector;
        vector<string> outputVector;

        homeworkMarksVector.resize(0);
        outputVector.resize(0);

        const int vectorLength = sVector.size();

        for (int i = 2; i < vectorLength - 1; i++) {
            if (sVector[0] == surname)
                break;

            double mark = std::stod(sVector[i]);

            if (mark < 0)
                continue;

            homeworkMarksVector.push_back(mark);
        }

        outputVector.push_back(sVector[0]);
        outputVector.push_back(sVector[1]);

        if (sVector[0] == surname) {
            outputVector.push_back(isMeanResult ? resultMarkMean : resultMarkMedian);
        }
        else {
            double extractedExamMark = stod(sVector[vectorLength - 1]);
            double finalMark = calculateFinalMark(homeworkMarksVector, extractedExamMark, isMeanResult);
            string stringFinalMark = to_string(finalMark);

            outputVector.push_back(stringFinalMark);
        }

        modifiedVector.push_back(outputVector);
    }

    sort(modifiedVector.begin(), modifiedVector.end(),
         [this](const vector<string>& a, const vector<string>& b) {
             string surnameA = a[0];
             string surnameB = b[0];

             if (surnameA == surname)
                 return surnameA < surnameB;
             else if (surnameB == surname)
                 return surnameB < surnameA;

             return surnameA < surnameB;
         });

    for (const vector<string> sVector: modifiedVector) {
        for (const string& dataString: sVector) {
            string stringMixin;
            const int mixinLength = 10 - (int) dataString.size();

            for (int i = 0; i < mixinLength; i++)
                stringMixin += " ";

            const string printString = dataString + stringMixin;

            cout << printString << " ";
        }

        cout << endl;
    }
}

vector<vector<string>> Student::splitString(const string& s, const string& separator) {
    size_t start = 0;
    size_t end = s.find(separator);

    vector<string> stringVector;
    vector<vector<string>> arrayVector;

    while (end != string::npos) {
        const string word = s.substr(start, end - start);

        const size_t wordLineBreakEnd = word.find('\n');

        if (wordLineBreakEnd == string::npos) {
            start = end + separator.size();
            end = s.find(separator, start) != string::npos
                  ? s.find(separator, start)
                  : s.size();

            stringVector.push_back(word);
        }
        else {const size_t lineBreakStart = start;
            const size_t lineBreakEnd = s.find('\n', start);

            const string wordBeforeLineBreak = s.substr(lineBreakStart, lineBreakEnd - lineBreakStart);

            start = lineBreakEnd + 1;
            end = s.find(separator, start);

            stringVector.push_back(wordBeforeLineBreak);

            arrayVector.push_back(stringVector);

            stringVector.resize(0);
        }
    }

    return arrayVector;
}

void Student::handleInputState() {
    bool isAddingData = false;
    int inputValue;

    cout << IS_ADDING_DATA << endl;
    cin >> inputValue;

    if (inputValue)
        isAddingData = true;

    if (isAddingData)
        handleInput();
    else
        readFile();
}

double Student::calculateFinalMark(vector<double> homeworkMarksVector, double ExamMarkVar, bool isCalculatedByMean) {
    double homeworksMarkResult = 0;

    if (isCalculatedByMean) {
        for (double mark: homeworkMarksVector)
            homeworksMarkResult += mark;

        homeworksMarkResult /= (double) homeworkMarksVector.size();
    }
    else {
        int arrayLength = (int) homeworkMarksVector.size();

        if (arrayLength % 2 == 1) {
            int position = (arrayLength + 1) / 2;

            homeworksMarkResult = homeworkMarksVector[position];
        }
        else {
            int position = arrayLength / 2;

            homeworksMarkResult = (homeworkMarksVector[position] + homeworkMarksVector[position + 1]) / 2;
        }
    }

    return 0.4 * homeworksMarkResult + 0.6 * ExamMarkVar;
}

bool Student::isCalculatedByMean() {
    bool isCalculatedByMean = false;
    int inputValue;

    cout << homeworkCountQuestion << endl;
    cout << homeworkCountAnswer << endl;
    cin  >> inputValue;

    if (inputValue == 1)
        isCalculatedByMean = true;

    return isCalculatedByMean;
}