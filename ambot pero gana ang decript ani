#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// GCD calculator
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Modular inverse using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    int m0 = m, y = 0, x = 1;
    if (m == 1) return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;
    return (a == 1) ? x : -1;
}

// Generate invertible 2x2 matrix key
void generateKeyMatrix(int keyMatrix[2][2]) {
    srand(time(0));
    int det;
    do {
        keyMatrix[0][0] = rand() % 25 + 1;
        keyMatrix[0][1] = rand() % 25 + 1;
        keyMatrix[1][0] = rand() % 25 + 1;
        keyMatrix[1][1] = rand() % 25 + 1;
        det = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]);
    } while (gcd(det % 26, 26) != 1);

    cout << "Generated Key Matrix:\n";
    cout << "[" << keyMatrix[0][0] << " " << keyMatrix[0][1] << "]\n";
    cout << "[" << keyMatrix[1][0] << " " << keyMatrix[1][1] << "]\n";
    cout << "Key Numbers: " 
         << keyMatrix[0][0] << " " 
         << keyMatrix[0][1] << " " 
         << keyMatrix[1][0] << " " 
         << keyMatrix[1][1] << "\n";
}

// Matrix multiplication with modulo 26
vector<int> multiplyMatrix(const vector<int>& message, int keyMatrix[2][2]) {
    vector<int> result;
    for (size_t i = 0; i < message.size(); i += 2) {
        int a = message[i];
        int b = (i+1 < message.size()) ? message[i+1] : 0; // Pad with 0 if needed
        
        // Matrix multiplication
        int c = (keyMatrix[0][0] * a + keyMatrix[0][1] * b) % 26;
        int d = (keyMatrix[1][0] * a + keyMatrix[1][1] * b) % 26;
        
        // Ensure non-negative
        c = (c + 26) % 26;
        d = (d + 26) % 26;
        
        result.push_back(c);
        result.push_back(d);
    }
    return result;
}

// Encryption function
string encrypt() {
    string plaintext;
    cout << "Enter message to encrypt (A-Z, spaces allowed): ";
    getline(cin, plaintext);

    // Convert to uppercase and create numeric vector (0-25)
    vector<int> numericMessage;
    for (char c : plaintext) {
        if (c == ' ') {
            numericMessage.push_back(0);
        } else if (isalpha(c)) {
            numericMessage.push_back(toupper(c) - 'A' + 1);
        }
    }

    // Pad with 0 if odd length
    if (numericMessage.size() % 2 != 0) {
        numericMessage.push_back(0);
    }

    // Generate key matrix
    int keyMatrix[2][2];
    generateKeyMatrix(keyMatrix);

    // Encrypt using matrix multiplication
    vector<int> ciphertext = multiplyMatrix(numericMessage, keyMatrix);

    // Convert to string output
    string output;
    for (int num : ciphertext) {
        output += to_string(num) + " ";
    }

    cout << "Encrypted Message: " << output << "\n";
    return output;
}

// Decryption function
string decrypt() {
    string ciphertext;
    int key[4];
    cout << "Enter encrypted numbers (space-separated): ";
    getline(cin, ciphertext);
    cout << "Enter 4 key numbers (space-separated): ";
    for (int i = 0; i < 4; i++) cin >> key[i];
    cin.ignore(); // Clear input buffer

    // Create inverse matrix
    int det = key[0]*key[3] - key[1]*key[2];
    int detInv = modInverse((det % 26 + 26) % 26, 26);
    
    if (detInv == -1) {
        cout << "Invalid key (non-invertible determinant)\n";
        return "";
    }

    int invMatrix[2][2] = {
        {(key[3] * detInv) % 26, (-key[1] * detInv) % 26},
        {(-key[2] * detInv) % 26, (key[0] * detInv) % 26}
    };

    // Ensure positive values
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invMatrix[i][j] = (invMatrix[i][j] + 26) % 26;
        }
    }

    // Parse ciphertext numbers
    vector<int> numbers;
    istringstream iss(ciphertext);
    int num;
    while (iss >> num) numbers.push_back(num);

    // Decrypt using inverse matrix
    vector<int> plainNums = multiplyMatrix(numbers, invMatrix);

    // Convert back to text
    string result;
    for (int n : plainNums) {
        if (n == 0) {
            result += ' ';
        } else {
            result += (n - 1) + 'A';
        }
    }

    // Remove padding space if present
    if (!result.empty() && result.back() == ' ') result.pop_back();

    cout << "Decrypted Message: " << result << "\n";
    return result;
}

int main() {
    int choice;
    do {
        cout << "\nHill Cipher System\n";
        cout << "1. Encrypt\n2. Decrypt\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: encrypt(); break;
            case 2: decrypt(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
