#include <iostream>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int generateKeyMatrix(int keyMatrix[2][2]) {
    srand(time(0));
    int a, b, c, d, det;

    do {
        a = rand() % 9 + 1;
        b = rand() % 9 + 1;
        c = rand() % 9 + 1;
        d = rand() % 9 + 1;
        det = (a * d - b * c);
    } while (gcd(det, 26) != 1); 

    keyMatrix[0][0] = a;
    keyMatrix[0][1] = b;
    keyMatrix[1][0] = c;
    keyMatrix[1][1] = d;

    cout << "Please use this key when decrypting: \n";
    cout << "Generated Key: " << a << " " << b << " " << c << " " << d << endl;

    return det; 
}

int modInverse(int det, int mod) {
    det = det % mod;
    for (int x = 1; x < mod; x++) {
        if ((det * x) % mod == 1) {
            return x;
        }
    }
    return -1; 
}

bool inverseMatrix(int keyMatrix[2][2], int inverse[2][2]) {
    int a = keyMatrix[0][0], b = keyMatrix[0][1];
    int c = keyMatrix[1][0], d = keyMatrix[1][1];

    int det = (a * d - b * c) % 26;
    if (det < 0) det += 26;  

    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        cout << "Matrix has no modular inverse under mod 26.\n";
        return false;
    }

    // Compute inverse matrix using the formula:
    //  1/det * [ d  -b ]
    //          [ -c  a ]
    inverse[0][0] = (d * detInv) % 26;
    inverse[0][1] = (-b * detInv) % 26;
    inverse[1][0] = (-c * detInv) % 26;
    inverse[1][1] = (a * detInv) % 26;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverse[i][j] < 0)
                inverse[i][j] += 26;
        }
    }

    return true;
}

// Test function
int main() {
    int keyMatrix[2][2], inverse[2][2];

    int determinant = generateKeyMatrix(keyMatrix);
    cout << "Determinant: " << determinant << endl;

    if (inverseMatrix(keyMatrix, inverse)) {
        cout << "Inverse Matrix (mod 26):\n";
        cout << inverse[0][0] << " " << inverse[0][1] << endl;
        cout << inverse[1][0] << " " << inverse[1][1] << endl;
    } else {
        cout << "Matrix inversion failed.\n";
    }

    return 0;
}
