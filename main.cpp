#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib> 

using namespace std;

// Function to calculate GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
/* MOD 26 NI SIYA KAY A-Z BIYA ATO ENCRYPTION AND DECRYPTION, SO A-Z IS 26 KA LETTERS, mag ensure ni
na ange values nato is dili mo lapas og 26. if natingala mo nganong 26 == 1 siya and -1 if walay inverse 
na instead of 0, sa mau gi tudlo ni maam. This is because  ga exist ra ang inverse if coprime siya sa 26 */

// Function to find modular inverse of a number under mod 26
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
        cout << "Matrix is not invertible under mod 26.\n";
        return false;
    }

    // Adjugate matrix
    result[0][0] = (A[1][1] * detInv) % 26;
    result[0][1] = (-A[0][1] * detInv % 26 + 26) % 26;
    result[1][0] = (-A[1][0] * detInv % 26 + 26) % 26;
    result[1][1] = (A[0][0] * detInv) % 26;
    return true;
}

// Function to generate a random 2x2 key matrix
void generateKeyMatrix(int keyMatrix[2][2]) {
    srand(time(0)); 
    int a, b, c, d, det;

    do {
        a = rand() % 9 + 1;
        b = rand() % 9 + 1;
        c = rand() % 9 + 1;
        d = rand() % 9 + 1;
        det = (a * d - b * c) % 26;
        if (det < 0) det += 26;
    } while (gcd(det, 26) != 1);  // Ensure matrix is invertible DILI SIYA !=0 since mod 26 atoa lagi gi gamit,

    keyMatrix[0][0] = a;
    keyMatrix[0][1] = b;
    keyMatrix[1][0] = c;
    keyMatrix[1][1] = d;

    cout << "\n-----------------------------------\n";
    cout << " Use this key for decryption:\n";
    cout << " Key: " << a << b << c << d << endl;
    cout << "-----------------------------------\n";
}

// Function to multiply a 1x2 matrix with a 2x2 matrix
vector<vector<int>> multiplyMatrix(const vector<vector<int>>& messageMatrix, int keyMatrix[2][2]) {
    vector<vector<int>> result;
    for (const auto& row : messageMatrix) {
        vector<int> newRow(2, 0);
        newRow[0] = (row[0] * keyMatrix[0][0] + row[1] * keyMatrix[0][1]) % 26;
        newRow[1] = (row[0] * keyMatrix[1][0] + row[1] * keyMatrix[1][1]) % 26;
        if (newRow[0] < 0) newRow[0] += 26;
        if (newRow[1] < 0) newRow[1] += 26;
        result.push_back(newRow);
    }
    return result;
}

// Function to convert text into a matrix (NEED NATO E CONVERT ANG TEXT INTO A MATRIX OR VECTOR PARA MA CALCULATE NATOG TARONG)
vector<vector<int>> textToMatrix(const string& text) {
    vector<vector<int>> matrix;
    vector<int> row;
    for (char c : text) {
        if (c == ' ') row.push_back(0);
        else if (isalpha(c)) row.push_back(toupper(c) - 'A' + 1);
        if (row.size() == 2) {
            matrix.push_back(row);
            row.clear();
        }
    }
    if (!row.empty()) {
        row.push_back(0);
        matrix.push_back(row);
    }
    return matrix;
}

// Function to convert matrix to string (NEED NI SIYA PARA MA PRINT OU NATOG TARONG)
string matrixToString(const vector<vector<int>>& matrix) {
    stringstream ss;
    for (const auto& row : matrix) {
        ss << row[0] << " " << row[1] << " ";
    }
    return ss.str();
}

// Function to encrypt a message
void encrypt() {
    string message;
    int keyMatrix[2][2];

    cout << "\nEnter message to encrypt: ";
    cin.ignore();
    getline(cin, message);

    for (char c : message) {
        if (!isalpha(c) && c != ' ') {
            cout << "Invalid input! Only letters and spaces are allowed.\n";
            return;
        }
    }

    generateKeyMatrix(keyMatrix);
    vector<vector<int>> messageMatrix = textToMatrix(message);
    vector<vector<int>> encryptedMatrix = multiplyMatrix(messageMatrix, keyMatrix);

    cout << "\n-----------------------------------\n";
    cout << "Encrypted Message: " << matrixToString(encryptedMatrix) << endl;
    cout << "-----------------------------------\n";
}


// Function to decrypt a message
void decrypt() {
    string encryptedMessage;
    int keyMatrix[2][2], inverseKeyMatrix[2][2];

    cin.ignore(); // Fix input issue (para dili na mag space before mag input)

    cout << "\nEnter encrypted message (space-separated numbers): ";
    getline(cin, encryptedMessage);

    // Input validation: only numbers and spaces allowed
    for (char c : encryptedMessage) {
        if (!isdigit(c) && c != ' ') {
            cout << "Invalid input! Encrypted message should contain only numbers and spaces.\n";
            return;
        }
    }

    cout << "\nEnter the 4-digit key: ";
    string keyInput;
    cin >> keyInput;

    // Key validation: must be exactly 4 digits
    if (keyInput.length() != 4 || !isdigit(keyInput[0]) || !isdigit(keyInput[1]) || !isdigit(keyInput[2]) || !isdigit(keyInput[3])) {
        cout << "Invalid key! Enter a 4-digit key.\n";
        return;
    }

    // Convert key string to key matrix
    keyMatrix[0][0] = keyInput[0] - '0';
    keyMatrix[0][1] = keyInput[1] - '0';
    keyMatrix[1][0] = keyInput[2] - '0';
    keyMatrix[1][1] = keyInput[3] - '0';

    if (!inverseMatrix(keyMatrix, inverseKeyMatrix)) return;

    vector<vector<int>> encryptedMatrix;
    stringstream ss(encryptedMessage);
    vector<int> row;
    int num;

    while (ss >> num) {
        row.push_back(num);
        if (row.size() == 2) {
            encryptedMatrix.push_back(row);
            row.clear();
        }
    }

    vector<vector<int>> decryptedMatrix = multiplyMatrix(encryptedMatrix, inverseKeyMatrix);
    string decryptedMessage;

    for (const auto& row : decryptedMatrix) {
        for (int val : row) {
            decryptedMessage += (val == 0) ? ' ' : (val - 1 + 'A');
        }
    }

    cout << "\n-----------------------------------\n";
    cout << "Decrypted Message: " << decryptedMessage << endl;
    cout << "-----------------------------------\n";
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
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input! Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: encrypt(); break;
            case 2: decrypt(); break;
            case 3: cout << "\nExiting program...\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
