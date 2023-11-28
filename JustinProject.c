#include <stdio.h>
#include <string.h>

#define NUM_ROWS 5
#define NUM_COLS 10
#define MAX_USERS 10
#define MAX_LOG_ENTRIES 50

struct User {
    char username[20];
    char password[20];
};

struct BookingLog {
    char username[20];
    int row;
    int col;
};

struct User users[MAX_USERS]; // Array to store user details
int numUsers = 0; // Variable to keep track of the number of registered users

struct BookingLog bookingLog[MAX_LOG_ENTRIES]; // Array to store booking log entries
int numBookings = 0; // Variable to keep track of the number of bookings

// Function to display the seating arrangement
void displaySeats(int seats[NUM_ROWS][NUM_COLS]) {
    printf("\n\tSeats\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("Row %d:\t", i + 1);
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%c ", seats[i][j] == 0 ? '-' : 'X');
        }
        printf("\n");
    }
}

// Function to display a receipt for a booked seat
void displayReceipt(const char username[20], int row, int col) {
    printf("\n***** Booking Receipt ****\n");
    printf("Customer: %s\n", username);
    printf("Booked Seat - Row: %d, Column: %d\n", row, col);
    printf("Thank you for choosing CREVIBUS Co.!\n");
}

// Function to write user details to a file
void writeUserDetailsToFile() {
    FILE *userFile = fopen("userDetails.txt", "w");

    if (userFile == NULL) {
        printf("Error opening file for writing user details.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(userFile, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(userFile);
}

// Function to read user details from a file
void readUserDetailsFromFile() {
    FILE *userFile = fopen("userDetails.txt", "r");

    if (userFile == NULL) {
        printf("Error opening file for reading user details.\n");
        return;
    }

    while (fscanf(userFile, "%s %s", users[numUsers].username, users[numUsers].password) == 2) {
        numUsers++;
        if (numUsers >= MAX_USERS) {
            printf("Maximum number of users reached.\n");
            break;
        }
    }

    fclose(userFile);
}

// Function to write booking log to a file
void writeBookingLogToFile() {
    FILE *bookingFile = fopen("bookingLog.txt", "w");

    if (bookingFile == NULL) {
        printf("Error opening file for writing booking log.\n");
        return;
    }

    for (int i = 0; i < numBookings; i++) {
        fprintf(bookingFile, "%s %d %d\n", bookingLog[i].username, bookingLog[i].row, bookingLog[i].col);
    }

    fclose(bookingFile);
}

// Function to read booking log from a file
void readBookingLogFromFile() {
    FILE *bookingFile = fopen("bookingLog.txt", "r");

    if (bookingFile == NULL) {
        printf("Error opening file for reading booking log.\n");
        return;
    }

    while (fscanf(bookingFile, "%s %d %d", bookingLog[numBookings].username, &bookingLog[numBookings].row,
                  &bookingLog[numBookings].col) == 3) {
        numBookings++;
        if (numBookings >= MAX_LOG_ENTRIES) {
            printf("Maximum number of bookings reached.\n");
            break;
        }
    }

    fclose(bookingFile);
}

// Function to book a seat
void bookSeat(int seats[NUM_ROWS][NUM_COLS], int row, int col, const char username[20]) {
    if (seats[row - 1][col - 1] == 0) {
        seats[row - 1][col - 1] = 1;

        // Record the booking in the log
        strcpy(bookingLog[numBookings].username, username);
        bookingLog[numBookings].row = row;
        bookingLog[numBookings].col = col;
        numBookings++;

        // Display the booking receipt
        displayReceipt(username, row, col);

        // Write the booking log to a file
        writeBookingLogToFile();
    } else {
        printf("Seat is already booked. Please choose another seat.\n");
    }
}

// Function to sign up a new user
void signUp() {
    if (numUsers < MAX_USERS) {
        printf("Enter a new username: ");
        scanf("%s", users[numUsers].username);

        printf("Enter a password: ");
        scanf("%s", users[numUsers].password);

        printf("Sign up successful!\n");
        numUsers++;

        // Write user details to a file
        writeUserDetailsToFile();
    } else {
        printf("Maximum number of users reached. Cannot sign up.\n");
    }
}

// Function to sign in an existing user
int signIn(char username[20]) {
    char password[20];

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return 1; // Return 1 to indicate successful login
        }
    }

    printf("Login failed. Please check your username and password.\n");
    return 0; // Return 0 to indicate failed login
}

int main() {
    readUserDetailsFromFile();
    readBookingLogFromFile();

    int seats[NUM_ROWS][NUM_COLS] = {0}; // 0 represents an available seat

    int choice, row, col;
    int loggedIn = 0; // Variable to track login status
    char currentUsername[20]; // Variable to store the username of the logged-in user

    do {
        printf("\n*****Welcome to CREVIBUS Co.****\n");

        if (!loggedIn) {
            printf("1. Sign Up\n");
            printf("2. Sign In\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice
) {
                case 1:
                    signUp();
                    break;
                case 2:
                    printf("Enter username: ");
                    scanf("%s", currentUsername);
                    loggedIn = signIn(currentUsername);
                    break;
                case 3:
                    printf(" Thank you for using CREVIBUS Co.\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        } else {
            printf("1. Display Seats\n");
            printf("2. Book a Seat\n");
            printf("3. View Booking Log\n");
            printf("4. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    displaySeats(seats);
                    break;
                case 2:
                    printf("Enter row and column to book a seat: ");
                    scanf("%d %d", &row, &col);
                    if (row >= 1 && row <= NUM_ROWS && col >= 1 && col <= NUM_COLS) {
                        bookSeat(seats, row, col, currentUsername);
                    } else {
                        printf("Invalid row or column number. Please try again.\n");
                    }
                    break;
                case 3:
                    // Display the booking log
                    printf("\n***** Booking Log ****\n");
                    for (int i = 0; i < numBookings; i++) {
                        printf("Username: %s, Row: %d, Column: %d\n", bookingLog[i].username, bookingLog[i].row,
                               bookingLog[i].col);
                    }
                    break;
                case 4:
                    loggedIn = 0; // Logout the user
                    printf("Logout successful!\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        }
    } while (choice != 3);

    return 0;
}