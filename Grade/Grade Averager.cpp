// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>


using std::cin, std::cout, std::endl;
using std::string, std::getline;


void print_instructions();

void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);


void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();


    int numberOfLabs = 0;
    int numberOfReadings = 0;
    int numberOfHmwk = 0;
    int numberOfCompile = 0;
    int numberOfEngagementPts = 0;
    double examScore = 0;
    double labScore = 0 ;
    double readingScore = 0;
    double hmwkScore = 0;
    double compileScore = 0;
    double engagementScore = 0;
    double finalScore = 0;
    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);
        // process the grade entry
        if (category == "exam") {
    
            examScore += score;
        } 
        else if (category == "final-exam") {

            finalScore += score;
        } 
        else if (category == "hw") {
            numberOfHmwk += 1;
            hmwkScore += score;
        } 
        else if (category == "lw") {
            numberOfLabs += 1;
            labScore += score;
        } 
        else if (category == "reading") {
            numberOfReadings += 1;
            readingScore += score;
        }
        else if (category == "engagement") {
            numberOfEngagementPts += 1;
            engagementScore += score;
        }
        else if  (category == "compile-check") {
            numberOfCompile += 1;
            compileScore += score;
        }
        else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // compute component averages
    double exam_average = 0;
    double hw_average = 0;
    double lw_average = 0;
    double reading = 0;
    double engagement = 0;

    if (examScore >= 0) {
        exam_average = (examScore + finalScore) / 3;
        if (exam_average < finalScore) {
            exam_average = finalScore;
        }        
        
    }
    if (hmwkScore > 0) {

        hw_average = hmwkScore / numberOfHmwk;
    }
    if (labScore > 0) {
        lw_average = (labScore / numberOfLabs) * 100;
    }
    if (readingScore >= 0) {
        if (readingScore == 0) {
            reading = 15;
        }
        else {
            reading = readingScore / numberOfReadings;
            reading += 15;
            if (reading > 100) {
                reading = 100;
            }
        }     
    }
    if (engagementScore >= 0) {
        if (engagementScore == 0) {
            engagement = 15;
        }

        else {
            engagement = engagementScore / numberOfEngagementPts;
            engagement += 15;
            if (engagement > 100) {
                engagement = 100;
            }

        }
    }
    if (compileScore == 0) {
        lw_average = lw_average * 0;
    }
    else if (compileScore == 1) {
        lw_average = lw_average * .5;
    }
    


    //compute weighted total of components

    double weighted_total = 0;
    weighted_total = (exam_average * .4) + (hw_average * .4) + (lw_average * .1) + (reading * .05) + (engagement * .05);
    // compute final letter grade
    char final_letter_grade = 'X';
    if (weighted_total < 59.5) {
        final_letter_grade = 'F';
    }
    else if (weighted_total < 69.5) {
        final_letter_grade = 'D';
    }
    else if (weighted_total < 79.5) {
        final_letter_grade = 'C';
    }
    else if (weighted_total < 89.5) {
        final_letter_grade = 'B';
    }
    else if (weighted_total < 101) {
        final_letter_grade = 'A';
    }
    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}



void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement | compile-check" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
