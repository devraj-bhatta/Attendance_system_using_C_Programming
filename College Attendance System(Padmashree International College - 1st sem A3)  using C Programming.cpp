#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STUDENTS 25 // Updated number of students
#define MAX_NAME_LENGTH 50

// Structure to represent a student
struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    bool present;
};

// Predefined list of student names
char* studentNames[MAX_STUDENTS] = {
    "Aakash Bhandari", "Abhinash Thakur", "Anish Bajagain", "Ashwin Dahal", "Asmita Katuwal",
    "Binaya Thapa", "Deekshant Prabin Dahal", "Devraj Bhatta", "Dipendra Kumar Raut", "Ishan Mishra",
    "Manish Awale", "Piyus Shrestha", "Prasamsa Marasini", "Prince", "Ram Sharma", "Ramanand Mahato",
    "Rohan Bhujel", "Samir Bishwokarma", "Sneha Tamang", "Sohan Shrestha", "Suman", "Subash Dahal",
    "Upendra Neupane", "Usha Magar", "Yushis Silwal"
};

// Function prototypes
void displayMenu();
void markAttendance(struct Student students[]);
void viewAttendance(struct Student students[]);
void saveAttendance(struct Student students[]);
void loadAttendance(struct Student students[]);
void initializeStudents(struct Student students[]);
void clearInputBuffer();
void printLine();
void printSummary(struct Student students[]);

int main() {
    struct Student students[MAX_STUDENTS];
    initializeStudents(students); // Initialize student data
    loadAttendance(students);     // Load attendance data from file

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // Clear input buffer to prevent issues with scanf

        switch (choice) {
            case 1:
                markAttendance(students);
                break;
            case 2:
                viewAttendance(students);
                break;
            case 3:
                saveAttendance(students);
                printf("Attendance saved successfully.\n");
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Display menu options
void displayMenu() {
    printLine();
    printf("---- Padmashree International College, Tinkune, Kathmandu ----\n");
    printf("---- 1st Semester, Section A3 Attendance System ----\n");
    printf("---- College Attendance System Menu ----\n");
    printf("1. Mark Attendance\n");
    printf("2. View Attendance\n");
    printf("3. Save Attendance\n");
    printf("4. Exit\n");
    printLine();
}

// Mark attendance for students
void markAttendance(struct Student students[]) {
    printf("\nMark attendance (P for present, A for absent):\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printf("%d. %s: ", students[i].id, students[i].name);
        char attendance;
        do {
            scanf(" %c", &attendance);
            clearInputBuffer(); // Clear input buffer to prevent issues with scanf
            if (attendance != 'P' && attendance != 'p' && attendance != 'A' && attendance != 'a') {
                printf("Invalid input. Please enter 'P' for present or 'A' for absent: ");
            }
        } while (attendance != 'P' && attendance != 'p' && attendance != 'A' && attendance != 'a');

        students[i].present = (attendance == 'P' || attendance == 'p');
    }
    printSummary(students);
}

// View attendance for students
void viewAttendance(struct Student students[]) {
    printLine();
    printf("---- Attendance Report ----\n");
    printf("ID\tName\t\t\tAttendance\n");
    printLine();
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printf("%d\t%s\t\t\t%s\n", students[i].id, students[i].name, students[i].present ? "Present" : "Absent");
    }
    printLine();
    printSummary(students);
}

// Save attendance data to a file
void saveAttendance(struct Student students[]) {
    FILE *file = fopen("attendance.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < MAX_STUDENTS; i++) {
        fprintf(file, "%d,%s,%s\n", students[i].id, students[i].name, students[i].present ? "Present" : "Absent");
    }

    fclose(file);
}

// Load attendance data from a file
void loadAttendance(struct Student students[]) {
    FILE *file = fopen("attendance.txt", "r");
    if (file == NULL) {
        printf("Attendance file not found. Starting with default data.\n");
        return;
    }

    char line[MAX_NAME_LENGTH + 20]; // Assuming max line length
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL && i < MAX_STUDENTS) {
        sscanf(line, "%d,%49[^,],%s", &students[i].id, students[i].name, line);
        students[i].present = (strcmp(line, "Present") == 0);
        i++;
    }

    fclose(file);
}

// Initialize student data
void initializeStudents(struct Student students[]) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        students[i].id = i + 1;
        strcpy(students[i].name, studentNames[i]);
        students[i].present = false; // Initially mark all students as absent
    }
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to print a line for visual separation
void printLine() {
    printf("\n");
}

// Function to print summary of attendance
void printSummary(struct Student students[]) {
    int presentCount = 0;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].present) {
            presentCount++;
        }
    }
    printf("Total Students: %d\n", MAX_STUDENTS);
    printf("Present Students: %d\n", presentCount);
    printf("Absent Students: %d\n", MAX_STUDENTS - presentCount);
}

