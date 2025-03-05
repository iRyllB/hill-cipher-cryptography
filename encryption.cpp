#include <iostream>
#include <string>

using namespace std;

void encrypt() {
    string message;
    
    cout << "Enter a message to encrypt";
    cin.ignore();
    getline(cin, message);

    string encryptedMessage = "";
    for (char c : message) {
        if (c == ' ') { //if ang character is blank/space himuon natog 0
            encryptedMessage += "0";
        } else if (isalpha(c)) {
            char uppercase = toupper(c);
            encryptedMessage += to_string(uppercase - 'A' + 1); //A ASCII = 65, so to reset to 0, message - (65), + 1 dayun to increment so like 1 = A, 2 = B and so on
        }
    }

    if (encryptedMessage.length() % 2 != 0) { //if odd ang number of numbers, add lang 0 sa last para ma pair nato sila by 2 later
        encryptedMessage += "0";
    }

    cout << "Encrypted message: " << encryptedMessage << endl; // dili pa final since e x pa nato sa atong key matrix
}

int main() {
    encrypt();
    return 0;
}
