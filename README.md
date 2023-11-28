# CREVIBUS Co. Booking System

Overview
This C program implements a simple booking system for CREVIBUS Co., allowing users to sign up, sign in, book seats, and view booking logs.

Code Structure
- *Structures:*
  - User: Stores user details (username and password).
  - BookingLog: Records booking details (username, row, column).
- *Arrays:*
  - users[MAX_USERS]: Array to store user details.
  - bookingLog[MAX_LOG_ENTRIES]: Array to store booking log entries.
- *Functions:*
  - displaySeats: Displays the current seating arrangement.
  - displayReceipt: Displays a booking receipt.
  - writeUserDetailsToFile and readUserDetailsFromFile: Handle user details file I/O.
  - writeBookingLogToFile and readBookingLogFromFile: Handle booking log file I/O.
  - bookSeat: Books a seat, updates the log, and displays a receipt.
  - signUp and signIn: User registration and login functions.

Files
- userDetails.txt: Stores user details.
- bookingLog.txt: Stores booking log entries.

Usage
1. Compile the program.
   bash
   gcc booking_system.c -o booking_system
   
2. Run the executable.
   bash
   ./booking_system
   

Features
- User authentication: Sign up and sign in.
- Seat booking: Choose available seats.
- Display seats: Visual representation of the seating arrangement.
- View booking log: Check previous bookings.
- Data persistence: User details and booking log are stored in files.

 Notes
- Maximum number of users: 10 (MAX_USERS).
- Maximum number of log entries: 50 (MAX_LOG_ENTRIES).
- Seat availability: Displayed as 'X' (booked) or '-' (available).
