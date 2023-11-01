#include "StudentuRusiavimas.h"

#include <iostream>
#include <random>
#include <fstream>
#include <iterator>
#include <vector>

StudentuRusiavimas::StudentuRusiavimas() = default;

StudentuRusiavimas::StudentuRusiavimas(const StudentuRusiavimas& student) {
    setName(student.name);
    setSurname(student.surname);
    setHomeworksMark(student.homeworksMark);
    setExamMark(student.examMark);
}

void StudentuRusiavimas::setName(string name) {
    this->name = name;
}

void StudentuRusiavimas::setSurname(string surname) {
    this->surname = surname;
}

void StudentuRusiavimas::setHomeworksMark(vector<double> homeworksMark) {
    this->homeworksMark = homeworksMark;
}

void StudentuRusiavimas::setExamMark(double examMark) {
    this->examMark = examMark;
}

StudentuRusiavimas::~StudentuRusiavimas() {
    this->setName("");
    this->setSurname("");
    this->setHomeworksMark({});
    this->setExamMark(0);
}

void StudentuRusiavimas::handleInput() {
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
        uniform_int_distribution<> generatedHomeworksNumber(1, 5);
        uniform_int_distribution<> generatedMark(1, 10);

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

            cout << i + 1 << " " << homeworkMark << endl;
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

void StudentuRusiavimas::printData() {
    const bool isMeanResult = isCalculatedByMean();

    const double finalMark = calculateFinalMark(homeworksMark, examMark, isMeanResult);

    cout << surname << " " << name << " ";
    cout << (isMeanResult == 1 ? resultMarkMean : resultMarkMedian) << endl;
    cout << name << " " << surname << " " << finalMark << endl;
}

void StudentuRusiavimas::createFile() {
    string fileName;
    int inputValue = 0;

    cout << CREATE_FILE_QUESTION << endl;
    cin >> inputValue;

    if (inputValue != 1)
        return;

    cout << TYPE_FILE_NAME << endl;
    cin >> fileName;

    ofstream fileOut;

    fileOut.open(fileName, ios_base::in);

    if (fileOut)
        return;

    fileOut.open(fileName, ios_base::app);

    fileOut << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 ND6 ND7 ND8 ND9 ND10 Egzaminas" << endl;
}

void StudentuRusiavimas::writeFile() {
    ofstream fileOut;

    fileOut.open(DEFAULT_FILE_NAME, ios_base::app);

    fileOut << surname << " " << name << " ";

    for (double mark : homeworksMark)
        fileOut << mark << " ";

    const int length = (int)homeworksMark.size();

    for (int i = 0; i < 5 - length; i++)
        fileOut << 0 << " ";

    fileOut << examMark << endl;
}

void StudentuRusiavimas::readFile() {
    vector<vector<string>> modifiedVector;

    ifstream fileIn(DEFAULT_FILE_NAME);

    if (!fileIn.is_open())
        return;

    const bool isMeanResult = isCalculatedByMean();

    string inputData = string((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

    vector<vector<string>> arrayVector = splitString(inputData);

    for (const vector<string> sVector : arrayVector) {
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

    for (const vector<string> sVector : modifiedVector) {
        for (const string& dataString : sVector) {
            string stringMixin;
            const int mixinLength = STRING_MIXIN_SIZE - (int)dataString.size();

            for (int i = 0; i < mixinLength; i++)
                stringMixin += " ";

            const string printString = dataString + stringMixin;

            cout << printString << " ";
        }

        cout << endl;
    }
}

vector<vector<string>> StudentuRusiavimas::splitString(const string& s, const string& separator) {
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
        else {
            const size_t lineBreakStart = start;
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

void StudentuRusiavimas::handleInputState() {
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

double StudentuRusiavimas::calculateFinalMark(vector<double> homeworkMarksVector, double ExamMarkVar, bool isCalculatedByMean) {
    double homeworksMarkResult = 0;

    if (isCalculatedByMean) {
        for (double mark : homeworkMarksVector)
            homeworksMarkResult += mark;

        homeworksMarkResult /= (double)homeworkMarksVector.size();
    }
    else {
        int arrayLength = (int)homeworkMarksVector.size();

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

bool StudentuRusiavimas::isCalculatedByMean() {
    bool isCalculatedByMean = false;
    int inputValue;

    cout << homeworkCountQuestion << endl;
    cout << homeworkCountAnswer << endl;
    cin >> inputValue;

    if (inputValue == 1)
        isCalculatedByMean = true;

    return isCalculatedByMean;
}

void StudentuRusiavimas::fillFileWithRandomData() {
    string fileName;
    int cycleNumber;

    cout << TYPE_FILE_NAME << endl;
    cin >> fileName;

    cout << CYCLE_NUMBER_QUESTION << endl;
    cin >> cycleNumber;

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> generatedHomeworksNumber(1, 10);
    uniform_int_distribution<> generatedMark(1, 10);
    uniform_int_distribution<> generatedNameKey(0, 53);
    uniform_int_distribution<> generatedSurnameKey(0, 27);

    ofstream fileOut;

    fileOut.open(fileName, ios_base::app);

    cout << cycleNumber << endl;

    for (int i = 0; i < cycleNumber; i++) {
        string outputData;
        vector<string> dataVector;

        dataVector.resize(0);
        dataVector.push_back(nameArray[generatedNameKey(gen)]);
        dataVector.push_back(surnameArray[generatedSurnameKey(gen)]);

        int homeworksNumber = generatedHomeworksNumber(gen);

        for (int j = 0; j < homeworksNumber; j++) {
            const string mark = to_string(generatedMark(gen));

            dataVector.push_back(mark);
        }

        for (int j = 0; j < 10 - homeworksNumber; j++)
            dataVector.emplace_back("-1");

        const string examMarkVar = to_string(generatedMark(gen));
        dataVector.push_back(examMarkVar);

        for (const string& s : dataVector) {
            outputData += s;
            outputData += " ";
        }

        fileOut << outputData << endl;
    }

    fileOut.close();
}

void StudentuRusiavimas::exportSortedData() {
    vector<vector<string>> modifiedVector;
    string fileName;

    cout << TYPE_FILE_NAME << endl;
    cin >> fileName;

    ifstream fileIn(fileName);

    if (!fileIn.is_open())
        return;

    const bool isMeanResult = isCalculatedByMean();

    string inputData = string((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

    fileIn.close();

    vector<vector<string>> arrayVector = splitString(inputData);

    for (const vector<string> sVector : arrayVector) {
        if (sVector[0] == surname)
            continue;

        vector<double> homeworkMarksVector;
        vector<string> outputVector;

        homeworkMarksVector.resize(0);
        outputVector.resize(0);

        const int vectorLength = (int)sVector.size();

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


        double extractedExamMark = stod(sVector[vectorLength - 2]);
        double finalMark = calculateFinalMark(homeworkMarksVector, extractedExamMark, isMeanResult);
        string stringFinalMark = to_string(finalMark);

        outputVector.push_back(stringFinalMark);

        modifiedVector.push_back(outputVector);
    }

    sort(modifiedVector.begin(), modifiedVector.end(),
        [](const vector<string>& a, const vector<string>& b) {
            string finalMarkA = a[2];
            string finalMarkB = b[2];

            return finalMarkA > finalMarkB;
        });

    vector<vector<string>> passedStudentsVector;
    vector<vector<string>> failedStudentsVector;

    for (const vector<string> sVector : modifiedVector) {
        const double mark = stod(sVector[2]);

        vector<string> passedStudentsV;
        vector<string> failedStudentsV;

        passedStudentsV.resize(0);
        failedStudentsV.resize(0);

        if (mark > 5) {
            passedStudentsV.push_back(sVector[0]);
            passedStudentsV.push_back(sVector[1]);
            passedStudentsV.push_back(sVector[2]);

            passedStudentsVector.push_back(passedStudentsV);
        }
        else {
            failedStudentsV.push_back(sVector[0]);
            failedStudentsV.push_back(sVector[1]);
            failedStudentsV.push_back(sVector[2]);

            failedStudentsVector.push_back(failedStudentsV);
        }
    }

    vector<string> headVector;

    headVector.push_back(arrayVector[0][0]);
    headVector.push_back(arrayVector[0][1]);
    headVector.push_back(isMeanResult ? resultMarkMean : resultMarkMedian);

    modifiedVector.insert(modifiedVector.begin(), headVector);
    passedStudentsVector.insert(passedStudentsVector.begin(), headVector);
    failedStudentsVector.insert(failedStudentsVector.begin(), headVector);

    ofstream fileOutPassedStudents;
    ofstream fileOutFailedStudents;

    fileOutPassedStudents.open(fileName + "_passed_students", ios_base::app);

    for (vector<string> outputV : passedStudentsVector) {
        string outputString;

        for (const string s : outputV) {
            outputString += s;
            outputString += " ";
        }

        fileOutPassedStudents << outputString << endl;
    }

    fileOutPassedStudents.close();

    fileOutFailedStudents.open(fileName + "_failed_students", ios_base::app);

    for (vector<string> outputV : failedStudentsVector) {
        string outputString;

        for (const string s : outputV) {
            outputString += s;
            outputString += " ";
        }

        fileOutFailedStudents << outputString << endl;
    }

    fileOutFailedStudents.close();
}
