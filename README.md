# Banking System Demo

This project is a **simple simulation of a banking system**, developed as a practical application of a C++ course. The program allows basic banking operations to be performed through a console-based interface, with client data stored persistently in a file.

## Features

- 📋 Display a list of all clients with their account details.
- ➕ Add new clients.
- ✏️ Update existing client information.
- 🗑️ Delete clients securely.
- 🔍 Search for a client by their account number.
- 💰 Perform deposits and withdrawals.
- 📊 Show the total balance of all clients.

## File Structure

- **Main Program File**: Contains the core functionality and menu logic.
- **`File.txt`**: Stores client data persistently in the following format:

# Example Output

====================================================
               Main Menu Screen
====================================================
   [1] Show Client List.
   [2] Add New Client.
   [3] Delete Client.
   [4] Update Client.
   [5] Find Client.
   [6] Exit.
====================================================
Choose what you want to do? [1 to 6]: 1

Client list (3) client(s).
-----------------------------------------------------------------------------------------------
| Account Number | Pin Code | Name                          | Phone       | Balance    |
-----------------------------------------------------------------------------------------------
| 12345          | 0000     | John Doe                      | 123-456-7890| 5000.00    |
| 67890          | 1234     | Jane Smith                    | 987-654-3210| 1500.50    |
| 11223          | 5678     | Mark Johnson                  | 555-123-4567| 3000.75    |
-----------------------------------------------------------------------------------------------

Press any key to go the main menu...


# After selecting "Add New Client," the user is prompted to enter the following details:

Enter Account Num: 33445
Enter Pin Code: 4321
Enter Your Name: Michael Brown
Enter Phone: 777-888-9999
Enter Account Balance: 2000.25

# Example of Operations:

1- Adding a Client: The system will prompt for new client details and store them.
2- Updating a Client: After selecting a client to update, the system will allow changes to their account balance or personal information.
3 -Deleting a Client: The system will ask for confirmation before removing a client’s record.
4 -Depositing Funds: When performing a deposit, the program will update the client’s balance accordingly.
5- Withdrawing Funds: Similarly, withdrawals will decrease the client's balance, ensuring the system reflects accurate data.
6- Total Balance: The program will compute and display the total of all client account balances.


