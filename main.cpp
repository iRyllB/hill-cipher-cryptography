#include <iostream>
#include "encryption.cpp"
using namespace std;

// Function prototypes
void encrypt();
void decrypt();

int main() {
    int choice;
    
    do {
        cout << "\nMatrix Encryption System\n";
        cout << "1. Encrypt Message\n";
        cout << "2. Decrypt Message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        cin.ignore(); 
        
        switch (choice) {
            case 1:
                encrypt();
                break;
            case 2:
                decrypt();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 3);
    
    return 0;
}

void encrypt() {
    cout << "Encryption process (to be implemented)\n";
    // Implement encryption logic here
}

void decrypt() {
    cout << "Decryption process (to be implemented)\n";
    // Implement decryption logic here
}
