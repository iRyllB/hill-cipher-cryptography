#include <iostream>
#include <cstring>
#include "main.cpp"

using namespace std;

// Fixed 2x2 encryption key matrix
const int KEY[2][2] = {{3, 2}, {1, 2}};

// Fixed inverse key (precomputed for simplicity)
const int INV_KEY[2][2] = {{2, -2}, {-1, 3}};

// Function to encrypt a message
void encrypt() {
    char message[100];
    
    cout << "Enter message (max 100 characters): ";
    cin.ignore();
    cin.getline(message, 100);

    int length = strlen(message);
    
    // Ensure even length by padding with a space
    if (length % 2 != 0) {
        strcat(message, " ");
        length++;
    }

    // Convert characters to ASCII values and store in a matrix
    int matrix[50][2]; // Supports up to 100 chars (50x2)
    for (int i = 0, k = 0; i < length; i += 2, k++) {
        matrix[k][0] = message[i];
        matrix[k][1] = message[i + 1];
    }

    // Encrypt the matrix using matrix multiplication
    int encryptedMatrix[50][2];
    for (int i = 0; i < length / 2; i++) {
        encryptedMatrix[i][0] = (KEY[0][0] * matrix[i][0] + KEY[0][1] * matrix[i][1]);
        encryptedMatrix[i][1] = (KEY[1][0] * matrix[i][0] + KEY[1][1] * matrix[i][1]);
    }

    // Display encrypted message as numerical values
    cout << "Encrypted message (numerical values): ";
    for (int i = 0; i < length / 2; i++) {
        cout << encryptedMatrix[i][0] << " " << encryptedMatrix[i][1] << " ";
    }
    cout << endl;
}

// Function to decrypt a message
void decrypt() {
    int length;
    cout << "Enter number of encrypted values: ";
    cin >> length;

    int encryptedMatrix[50][2];
    cout << "Enter encrypted values: ";
    for (int i = 0; i < length / 2; i++) {
        cin >> encryptedMatrix[i][0] >> encryptedMatrix[i][1];
    }

    // Decrypt using the inverse key matrix
    char decryptedMessage[100];
    for (int i = 0; i < length / 2; i++) {
        int char1 = (INV_KEY[0][0] * encryptedMatrix[i][0] + INV_KEY[0][1] * encryptedMatrix[i][1]);
        int char2 = (INV_KEY[1][0] * encryptedMatrix[i][0] + INV_KEY[1][1] * encryptedMatrix[i][1]);
        
        decryptedMessage[i * 2] = char1;
        decryptedMessage[i * 2 + 1] = char2;
    }
    
    decryptedMessage[length] = '\0'; // Null-terminate the string
    
    cout << "Decrypted message: " << decryptedMessage << endl;
}
