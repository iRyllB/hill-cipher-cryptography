#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//gcd calculator (greatest common divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//generate random matrix key
void generateKeyMatrix(int keyMatrix[2][2]) {
    srand(time(0));
    int a, b, c, d, det;

    do {
        a = rand() % 9 + 1;
        b = rand() % 9 + 1;
        c = rand() % 9 + 1;
        d = rand() % 9 + 1;
        det = (a * d - b * c);
    } while (gcd(det, 26) != 1);  //check if invertible

    keyMatrix[0][0] = a;
    keyMatrix[0][1] = b;
    keyMatrix[1][0] = c;
    keyMatrix[1][1] = d;

    cout << "Please use this key when decrypting: \n";
    cout << "Generated Key: " << a << b << c << d << endl;
}

// Multiplication for matrix
string multiplication(string encrypted_message, int keyMatrix[2][2]) {
    string result = "";

    for (size_t i = 0; i < encrypted_message.length(); i += 2) {
        int num1 = encrypted_message[i] - '0';
        int num2 = encrypted_message[i + 1] - '0';

        // 1x2 paired matrix multiply by keymatrix
        int result1 = num1 * keyMatrix[0][0] + num2 * keyMatrix[1][0];
        int result2 = num1 * keyMatrix[0][1] + num2 * keyMatrix[1][1];

        //convert to string
        result += to_string(result1) + " " + to_string(result2) + " ";
    }

    return result;
}

// Encryption function
string encrypt() {
    string message;
    int keyMatrix[2][2];

    cout << "Enter a message to encrypt: ";
    getline(cin, message);

    generateKeyMatrix(keyMatrix);  // Generate key matrix

    string encrypted_message = "";
    for (char c : message) {
        if (c == ' ') {
            encrypted_message += "0"; //convert blank/spaces to 0
        } else if (isalpha(c)) {
            char uppercase = toupper(c);
            encrypted_message += to_string(uppercase - 'A' + 1);
        }
    }

    // add 0 if uneven
    if (encrypted_message.length() % 2 != 0) {
        encrypted_message += "0";
    }

    string encrypted_output = multiplication(encrypted_message, keyMatrix);

    cout << "Encrypted Message: " << encrypted_output << endl;
    return encrypted_output;
}

// Placeholder function for decryption
void decrypt() {
    cout << "Decryption logic goes here\n";
}

// Main menu system
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
