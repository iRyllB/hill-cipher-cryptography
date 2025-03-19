#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// GCD calculator (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a) {
    a = a % 26;
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to find the inverse of a 2x2 matrix in mod 26
bool inverseMatrix(int A[2][2], int result[2][2]) {
    int det = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) % 26;
    if (det < 0) det += 26;
    int detInv = modInverse(det);
    if (detInv == -1) {
        cout << "Matrix is not invertible under mod 26\n";
        return false;
    }
    // Adjugate matrix
    result[0][0] = A[1][1] * detInv % 26;
    result[0][1] = (-A[0][1] * detInv % 26 + 26) % 26;
    result[1][0] = (-A[1][0] * detInv % 26 + 26) % 26;
    result[1][1] = A[0][0] * detInv % 26;
    return true;
}


int modInverse(int a) {
    a = a % 26;
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to find the inverse of a 2x2 matrix in mod 26
bool inverseMatrix(int A[2][2], int result[2][2]) {
    int det = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) % 26;
    if (det < 0) det += 26;
    int detInv = modInverse(det);
    if (detInv == -1) {
        cout << "Matrix is not invertible under mod 26\n";
        return false;
    }
    // Adjugate matrix
    result[0][0] = A[1][1] * detInv % 26;
    result[0][1] = (-A[0][1] * detInv % 26 + 26) % 26;
    result[1][0] = (-A[1][0] * detInv % 26 + 26) % 26;
    result[1][1] = A[0][0] * detInv % 26;
    return true;
}

// Generate random matrix key
int generateKeyMatrix(int keyMatrix[2][2]) {
    srand(time(0));
    int a, b, c, d, det;

    do {
        a = rand() % 9 + 1;
        b = rand() % 9 + 1;
        c = rand() % 9 + 1;
        d = rand() % 9 + 1;
        det = (a * d - b * c);
    } while (gcd(det, 26) != 1);  // Check if invertible

    keyMatrix[0][0] = a;
    keyMatrix[0][1] = b;
    keyMatrix[1][0] = c;
    keyMatrix[1][1] = d;

    cout << "\n-----------------------------------\n";
    cout << " Please use this key when decrypting:\n";
    cout << " Generated Key: " << a << b << c << d << endl;
    cout << "-----------------------------------\n";

    return det;
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

        // Convert to string
        result += to_string(result1) + " " + to_string(result2) + " ";
    }

    return result;
}

// Encryption function
string encrypt() {
    string message;
    int keyMatrix[2][2];

    cout << "\n Enter a message to encrypt: ";
    getline(cin, message);

    generateKeyMatrix(keyMatrix);  // Generate key matrix

    string encrypted_message = "";
    for (char c : message) {
        if (c == ' ') {
            encrypted_message += "0"; // Convert blank/spaces to 0
        } else if (isalpha(c)) {
            char uppercase = toupper(c);
            encrypted_message += to_string(uppercase - 'A' + 1);
        }
    }

    // Add 0 if uneven
    if (encrypted_message.length() % 2 != 0) {
        encrypted_message += "0";
    }

    string encrypted_output = multiplication(encrypted_message, keyMatrix);

    cout << "\n-----------------------------------\n";
    cout << " Encrypted Message: " << encrypted_output << endl;
    cout << "-----------------------------------\n";

    return encrypted_output;
}

// Placeholder function for decryption
string decrypt() {
    string message_d;
    int keyDecryption;

    cout << "\n Enter the encrypted message: ";
    getline(cin, message_d);

    cout << "\n Enter the 4-digit key to decrypt: ";
    cin >> keyDecryption;

    // Decryption logic here...

    return 0;
}

// Main menu system
int main() {
    int choice;

    do {
        cout << "\n===================================\n";
        cout << "      Matrix Encryption System     \n";
        cout << "===================================\n";
        cout << " 1. Encrypt Message\n";
        cout << " 2. Decrypt Message\n";
        cout << " 3. Exit\n";
        cout << "-----------------------------------\n";
        cout << " Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n Invalid input! Please enter a number.\n";
            continue;
        }

        cin.ignore();

        switch (choice) {
            case 1: encrypt(); break;
            case 2: decrypt(); break;
            case 3: cout << "\n Exiting program...\n"; break;
            default: cout << "\n Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 3);

    return 0;
}
