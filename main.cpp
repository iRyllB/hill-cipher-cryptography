#include <iostream>
#include <string>
using namespace std;

void multiplication(string encrypted_message, int keyMatrix[2][2]) {
    cout << "Matrix-multiplied encrypted message: ";

    for (size_t i = 0; i < encrypted_message.length(); i += 2) {
        // e convert to int since wala man to siya na convert sa isa ka function
        int num1 = encrypted_message[i] - '0';
        int num2 = encrypted_message[i + 1] - '0';

        //make them a 1x2 matrix
        int messageMatrix[2][1] = {{num1}, {num2}};

        // multiply each pair sa key matrix
        int resultMatrix[2][1] = {
            {keyMatrix[0][0] * messageMatrix[0][0] + keyMatrix[0][1] * messageMatrix[1][0]},
            {keyMatrix[1][0] * messageMatrix[0][0] + keyMatrix[1][1] * messageMatrix[1][0]}
        };

        //print final encrypted matrix
        cout << resultMatrix[0][0] << " " << resultMatrix[1][0] << " ";
    }
    cout << endl;
}

void encrypt() {
    string message;
    int encryptionKey;

    cout << "Enter a message to encrypt: ";
    getline(cin, message);

    cout << "Enter 4-digit key (key will be used for decrypting): ";
    cin >> encryptionKey;

    int keyMatrix[2][2] = {
        {encryptionKey / 1000, (encryptionKey / 100) % 10}, //Integer digit extraction
        {(encryptionKey / 10) % 10, encryptionKey % 10}
    };

    string encrypted_message = "";
    for (char c : message) {
        if (c == ' ') {
            encrypted_message += "0";
        } else if (isalpha(c)) {
            char uppercase = toupper(c);
            encrypted_message += to_string(uppercase - 'A' + 1);
        }
    }

    if (encrypted_message.length() % 2 != 0) {
        encrypted_message += "0";
    }

    cout << "Encrypted message (number pairs): ";
    for (size_t i = 0; i < encrypted_message.length(); i += 2) {
        cout << encrypted_message.substr(i, 2) << " ";
    }
    cout << endl;

    multiplication(encrypted_message, keyMatrix);
}

void decrypt(){
    cout << "Decryption Goes Here";
}
int main() {
    int choice;
    
    do {
        cout << "\nMatrix Encryption System\n";
        cout << "1. Encrypt Message\n";
        cout << "2. Decrypt Message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();          
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;  
        }
        
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
