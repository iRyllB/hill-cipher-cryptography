#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
// kani
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
    result[0][0] = (A[1][1] * detInv) % 26;
    result[0][1] = (-A[0][1] * detInv % 26 + 26) % 26;
    result[1][0] = (-A[1][0] * detInv % 26 + 26) % 26;
    result[1][1] = (A[0][0] * detInv) % 26;
    return true;
}

// Generate random matrix key
int generateKeyMatrix(int keyMatrix[2][2]) {
    srand(static_cast<unsigned int>(time(0)));
    int a, b, c, d, det;

    do {
        a = rand() % 9 + 1;
        b = rand() % 9 + 1;
        c = rand() % 9 + 1;
        d = rand() % 9 + 1;
        det = (a * d - b * c);
        if (det < 0) det += 26;
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

// Multiplication for matrix (1x2) * (2x2) → (1x2)
vector<vector<int>> multiplication(const vector<vector<int>>& messageMatrix, int keyMatrix[2][2]) {
    vector<vector<int>> encryptedMatrix;

    for (const auto& row : messageMatrix) {
        vector<int> encryptedRow(2, 0);

        // Matrix multiplication: [P1 P2] * [k00 k01]
        //                                    [k10 k11]
        encryptedRow[0] = (row[0] * keyMatrix[0][0] + row[1] * keyMatrix[0][1]) % 26;
        encryptedRow[1] = (row[0] * keyMatrix[1][0] + row[1] * keyMatrix[1][1]) % 26;

        // Ensure non-negative values
        if (encryptedRow[0] < 0) encryptedRow[0] += 26;
        if (encryptedRow[1] < 0) encryptedRow[1] += 26;

        encryptedMatrix.push_back(encryptedRow);
    }

    return encryptedMatrix;
}

// Function to convert encrypted matrix to a string for display
string matrixToString(const vector<vector<int>>& encryptedMatrix) {
    string encrypted_message = "";
    for (const auto& row : encryptedMatrix) {
        encrypted_message += to_string(row[0]) + " " + to_string(row[1]) + " ";
    }
    return encrypted_message;
}

// Convert message into a 1x2 matrix format
vector<vector<int>> convertToMatrix(const string& message) {
    vector<vector<int>> matrix;
    vector<int> row;

    for (char c : message) {
        if (c == ' ') {
            row.push_back(0);
        } else if (isalpha(c)) {
            row.push_back(toupper(c) - 'A' + 1);
        }

        if (row.size() == 2) {
            matrix.push_back(row);
            row.clear();
        }
    }

    // If the last pair is incomplete, pad with 0
    if (!row.empty()) {
        row.push_back(0);
        matrix.push_back(row);
    }

    return matrix;
}

// Encryption function
string encrypt() {
    string message;
    int keyMatrix[2][2];

    cout << "\nEnter a message to encrypt: ";
    getline(cin, message);

    generateKeyMatrix(keyMatrix);  // Generate key matrix

    // Convert message to 1x2 matrix
    vector<vector<int>> messageMatrix = convertToMatrix(message);

    // Encrypt using matrix multiplication
    vector<vector<int>> encryptedMatrix = multiplication(messageMatrix, keyMatrix);

    // Convert encrypted matrix to string
    string encrypted_output = matrixToString(encryptedMatrix);

    cout << "\n-----------------------------------\n";
    cout << "Encrypted Message: " << encrypted_output << endl;
    cout << "-----------------------------------\n";

    return encrypted_output;
}

// Decryption function
string decrypt() {
    string encrypted_message;
    int keyMatrix[2][2], inverseKeyMatrix[2][2];

    cout << "\n Enter the encrypted message (space-separated numbers): ";
    cin.ignore();
    getline(cin, encrypted_message);

    cout << "\n Enter the 4-digit key to decrypt: ";
    string keyInput;
    cin >> keyInput;

    // Convert keyInput into keyMatrix
    if (keyInput.length() != 4) {
        cout << "Invalid key format! Please enter a 4-digit key.\n";
        return "";
    }

    keyMatrix[0][0] = keyInput[0] - '0';
    keyMatrix[0][1] = keyInput[1] - '0';
    keyMatrix[1][0] = keyInput[2] - '0';
    keyMatrix[1][1] = keyInput[3] - '0';

    // Find inverse matrix
    if (!inverseMatrix(keyMatrix, inverseKeyMatrix)) {
        return "";
    }

    // Convert encrypted message into a matrix
    vector<vector<int>> encryptedMatrix;
    stringstream ss(encrypted_message);
    int num;
    vector<int> row;
    while (ss >> num) {
        row.push_back(num);
        if (row.size() == 2) {
            encryptedMatrix.push_back(row);
            row.clear();
        }
    }

    // Decrypt using matrix multiplication
    vector<vector<int>> decryptedMatrix = multiplication(encryptedMatrix, inverseKeyMatrix);

    // Convert decrypted matrix to string
    string decrypted_message;
    for (const auto& row : decryptedMatrix) {
        for (int val : row) {
            if (val == 0) {
                decrypted_message += ' ';
            } else {
                decrypted_message += (val - 1 + 'A');
            }
        }
    }

    cout << "\n-----------------------------------\n";
    cout << "Decrypted Message: " << decrypted_message << endl;
    cout << "-----------------------------------\n";

    return decrypted_message;
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
