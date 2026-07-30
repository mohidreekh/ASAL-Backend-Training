#include <iostream>
#include<string>
#include <climits> 
#include <cctype> 

using namespace std;

const int NUM_COURSES = 3;

/**
 * @brief Checks if a string contains only numeric characters.
 *
 * Used to prevent invalid user input such as letters or symbols
 * when reading numbers from the console.
 *
 * @param input User input string.
 * @return true if the string is a valid number, false otherwise.
 */
bool isValidNumber(const std::string& input)
{
    if (input.empty()) {
        return false;
    }

    for (char c : input) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Reads and validates an integer value from the user.
 *
 * The function keeps asking the user until a valid integer is entered
 * within the specified range.
 *
 * @param message Message displayed before reading input.
 * @param min Minimum accepted value.
 * @param max Maximum accepted value.
 *
 * @return A valid integer entered by the user.
 */
int readNumber(string message, int min = INT_MIN, int max = INT_MAX)
{
    string input;

    while (true)
    {
        cout << message;
        cin >> input;

        if (!isValidNumber(input))
        {
            cout << "Invalid input! Enter numbers only.\n";
            continue;
        }

        int num = stoi(input);

        if (num < min || num > max)
        {
            cout << "Number must be between "
                << min << " and " << max << endl;
            continue;
        }

        return num;
    }
}

/**
 * @brief Converts a numerical mark into a letter grade.
 *
 * Grade mapping:
 * 90-100 -> A
 * 80-89  -> B
 * 70-79  -> C
 * 60-69  -> D
 * Below 60 -> E
 *
 * @param mark Student mark.
 *
 * @return Corresponding letter grade.
 */
char getGrade(int mark)
{
    if (mark >= 90)
        return 'A';
    else if (mark >= 80)
        return 'B';
    else if (mark >= 70)
        return 'C';
    else if (mark >= 60)
        return 'D';
    else
        return 'E';
}

/**
 * @brief Collects marks for all students and courses.
 *
 * Dynamically allocates a two-dimensional array where each row
 * represents a student and each column represents a course mark.
 *
 * @param numberOfStudents Number of students.
 *
 * @return Pointer to a dynamic 2D array containing student marks.
 */
int** collectStudentsMarks(int numberOfStudents)
{
    int** arr = new int* [numberOfStudents];

    for (int i = 0; i < numberOfStudents; i++)
    {
        arr[i] = new int[NUM_COURSES];

        cout << "student" << i + 1 << endl;

        for (int j = 0; j < NUM_COURSES; j++)
        {
            int mark = readNumber(
                "Enter the student mark " + to_string(j + 1) + " : ",
                0,
                100
            );

            arr[i][j] = mark;
        }
    }

    return arr;
}

/**
 * @brief Displays all students' letter grades.
 *
 * Converts each student's course marks into letter grades
 * and prints them.
 *
 * @param marks Two-dimensional array containing student marks.
 * @param numOfstudents Number of students.
 */
void printAllStudents(int** marks, int numOfstudents)
{
    for (int i = 0; i < numOfstudents; i++)
    {
        cout << "student" << i + 1 << " : ";

        for (int j = 0; j < NUM_COURSES; j++)
        {
            cout << getGrade(marks[i][j]) << " ";
        }

        cout << endl;
    }
}


/**
 * @brief Calculates and displays statistics for each student.
 *
 * Calculates:
 * - Highest mark
 * - Lowest mark
 * - Average mark
 *
 * Then converts the results into letter grades.
 *
 * @param marks Two-dimensional array containing student marks.
 * @param numberOfStudents Number of students.
 */
void printStudentsStatistics(int** marks, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; i++)
    {
        int highest = marks[i][0];
        int lowest = marks[i][0];
        int sum = 0;

        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (marks[i][j] > highest)
                highest = marks[i][j];

            if (marks[i][j] < lowest)
                lowest = marks[i][j];

            sum += marks[i][j];
        }

        double average = (double)sum / NUM_COURSES;

        cout << "\nStudent " << i + 1 << endl;
        cout << "Highest Grade: " << getGrade(highest) << endl;
        cout << "Lowest Grade : " << getGrade(lowest) << endl;
        cout << "Average Grade: " << getGrade(average) << endl;
    }
}

/**
 * @brief Counts the number of students who passed.
 *
 * A student is considered passing if their average mark
 * is greater than or equal to 50.
 *
 * @param marks Two-dimensional array containing student marks.
 * @param numberOfStudents Number of students.
 *
 * @return Number of passing students.
 */
int numOfPassingStudents(int** marks, int numberOfStudents)
{
    int count = 0;

    for (int i = 0; i < numberOfStudents; i++)
    {
        int sum = 0;

        for (int j = 0; j < NUM_COURSES; j++)
        {
            sum += marks[i][j];
        }

        double average = (double)sum / NUM_COURSES;

        if (average >= 50)
            count++;
    }

    return count;
}

/**
 * @brief Calculates the number of failing students.
 *
 * Uses the total number of students minus the number of
 * passing students.
 *
 * @param marks Two-dimensional array containing student marks.
 * @param numberOfStudents Number of students.
 *
 * @return Number of failing students.
 */
int numOfFailingStudents(int** marks, int numberOfStudents)
{
    return numberOfStudents - numOfPassingStudents(marks, numberOfStudents);
}

int main()
{
    int numberOfStudents = readNumber("Enter the number of students: ", 1);

    int** marks = collectStudentsMarks(numberOfStudents);

    int choice;

    do {

        cout << "\n\n1_Show all students." << endl;
        cout << "2_Show Statistics." << endl;
        cout << "3_exit\n\n" << endl;

        choice = readNumber("chose number: ", 1, 3);


        switch (choice) {
        case 1:
            printAllStudents(marks, numberOfStudents);
            break;

        case 2:
            printStudentsStatistics(marks, numberOfStudents);
            cout << "\nNumber of passing students: " << numOfPassingStudents(marks, numberOfStudents) << endl;
            cout << "\nNumber of failing students: " << numOfFailingStudents(marks, numberOfStudents) << endl;
            break;

        case 3:
            cout << "Good Bye" << endl;
            break;

        default:
            cout << "Invalid Choice" << endl;
        }

    } while (choice != 3);

    for (int i = 0; i < numberOfStudents; i++)
    {
        delete[] marks[i];
    }

    delete[] marks;
}