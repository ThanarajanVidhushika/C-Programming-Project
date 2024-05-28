#include <stdio.h>
#include <string.h>


int main() {

    char studentName[100];
    char enrollmentNumber[50];
    char degreeName[100];
    char storedUsername[] = "admin";
    char storedPassword[] = "admin123";
    char username[50], password[50];
    char distributorSignature [50];
    char class_value[5]={};
    int numSubjects, credits[10];
    float grades[10], semesterGPA, yearGPA[4] = {0}, FGPA = 0;
    float weights[4] = {0.20, 0.25, 0.30, 0.25};

    FILE *file;

    // Input grades and credits for each semester
    char gradeStr[3];


    printf("\t\t\t=========================================================\n");

    printf("\t\t\t\tUVA WELLASSA UNIVERSITY EXAM DIVISION\n");
    printf("\t\t\t\t\t\tCGPA SYSTEM\t\t\n");
    printf("\t\t\t=========================================================\n");

    // User authentication
    printf("\n\t\t\tEnter username: ");
    scanf("\t\t%49s", username);
    printf("\n\t\t\tEnter password: ");
    scanf("\t\t%49s", password);

    if (strcmp(username, storedUsername) != 0 || strcmp(password, storedPassword) != 0) {
        printf("\n\t\t\tAuthentication failed. Incorrect username or password.\n");
        return 1; // Exit the program if authentication fails
    }

    printf("\n\t\t\tAuthentication successful.\n");
    printf("\n\t\t\t=========================================================\n");

    // Get student's name and enrollment number
    getchar();
    printf("\n\t\t\tEnter student's name: ");
    fgets(studentName, 100, stdin); // fgets to accommodate spaces in name
    studentName[strcspn(studentName, "\n")] = 0; // Remove newline character

    printf("\n\t\t\tEnter Degree Name : ");
    fgets(degreeName, 100, stdin); // fgets to accommodate spaces in name
    studentName[strcspn(degreeName, "\n")] = 0; // Remove newline character

    printf("\n\t\t\tEnter enrollment number: ");
    fgets(enrollmentNumber, 50, stdin);
    enrollmentNumber[strcspn(enrollmentNumber, "\n")] = 0;

    printf("\n\t\t\t=========================================================\n");

        float gradeToPoint(char grade[]) {
    if (strcmp(grade, "A+") == 0 || strcmp(grade, "A") == 0) return 4.0;
    if (strcmp(grade, "A-") == 0) return 3.7;
    if (strcmp(grade, "B+") == 0) return 3.3;
    if (strcmp(grade, "B") == 0) return 3.0;
    if (strcmp(grade, "B-") == 0) return 2.7;
    if (strcmp(grade, "C+") == 0) return 2.3;
    if (strcmp(grade, "C") == 0) return 2.0;
    if (strcmp(grade, "C-") == 0) return 1.7;
    if (strcmp(grade, "D+") == 0) return 1.3;
    if (strcmp(grade, "D") == 0) return 1.0;
    if (strcmp(grade, "F") == 0) return 0.0;
    return -1; // Invalid grade


}
float calculateGPA(int numSubjects, int credits[], float grades[]) {
    float totalPoints = 0;
    int totalCredits = 0;
    for (int i = 0; i < numSubjects; i++) {
        totalPoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }
    return totalCredits > 0 ? totalPoints / totalCredits : 0;
}


    // Input grades and credits for each semester
    for (int year = 0; year < 4; year++) {
        float sumGPA = 0;
        for (int semester = 1; semester <= 2; semester++) {
            printf("\n\t\t\tYear %d, Semester %d\n", year + 1, semester);
            printf("\n\t\t\tEnter number of subjects: ");
            scanf("%d", &numSubjects);

            for (int i = 0; i < numSubjects; i++) {
                printf("\n\t\t\tEnter credits for subject %d: ", i + 1);
                scanf("%d", &credits[i]);
                printf("\n\t\t\tEnter grade (e.g., A, B+, C-) for subject %d: ", i + 1);
                scanf("%2s", gradeStr);

                float gradePoint = gradeToPoint(gradeStr);
                if (gradePoint == -1) {
                    printf("\n\t\t\tInvalid grade entered. Exiting.\n");
                    return 1;
                }
                grades[i] = gradePoint;
            }

            semesterGPA = calculateGPA(numSubjects, credits, grades);
            printf("\n\t\t\tGPA for this semester: %.2f\n", semesterGPA);

            printf("\n\t\t\t=========================================================\n");
            sumGPA += semesterGPA;
        }
        yearGPA[year] = sumGPA / 2; // Average GPA for the year


    }


    // Calculate FGPA
    for (int i = 0; i < 4; i++) {
        FGPA += yearGPA[i] * weights[i];//FGPA=FGPA+yearGPA[i]*weights[i];
    }

    const char *determineClass(float fgpa) {
    if (fgpa >= 3.70) {
        return "First Class )";
    }  else if (fgpa >= 3.30) {
        return "Second Class (Upper Division)";
    } else if (fgpa >= 3.00) {
        return "Second Class (Lower Division)";
    } else if (fgpa <= 3.00) {
        return "General";
    }
     else {
        return "Repeat";
    }
}
     const char *studentClass = determineClass(FGPA);


    // Open a file to write the output
    file = fopen("student_report.txt", "a+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("\n\t\t\tYour FGPA :%2f\n",FGPA);
    printf("\n\t\t\tDetermine Class is  :%s\n",determineClass);
    printf("\t\t\t=========================================================\n");


    printf("\n\t\t\tEnter Distributor Name : ");
    scanf("%s", distributorSignature);

    // Write to the file
    fprintf(file, "\n=========================================================\n");
    fprintf(file, "             UVA WELLASSA UNIVERSITY EXAM DIVISION        \n");
    fprintf(file, "                     CGPA SYSTEM INVOICE                 \n");
    fprintf(file, "\n=========================================================\n");



    // Write student information to the file
    fprintf(file, "\nStudent Name: %s", studentName);
    fprintf(file, "Degree: %s", degreeName);
    fprintf(file, "Enrollment Number: %s", enrollmentNumber);
    fprintf(file, "\n=========================================================\n");

    fprintf(file, "Final CGPA: %.2f\n", FGPA);
    fprintf(file, "Class: %s\n\n", studentClass);

    fprintf(file, "\t\t\tDistributor Name:",distributorSignature);



    // Close the file
    fclose(file);


    printf("\n\n\n\t\t\tOutput written to student_report.txt\n");

    return 0;
}
