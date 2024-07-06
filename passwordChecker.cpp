#include <iostream>
#include <cctype>

using namespace std;

bool passwordChecker(const string& password) {
    bool lowerCase = false;
    bool upperCase = false;
    bool digitChar = false;
    bool specialChar = false;

    if (password.length() < 8){
        cout << "Password must be at least 8 characters in length." << endl;
        return false;
    }

    for (char letter : password){
        if (isupper(letter)){
            upperCase = true;
        }else if (islower(letter)){
            lowerCase = true;
        }else if (isdigit(letter)){
            digitChar = true;
        }else if (isalnum(letter)){
            specialChar = true;
        }
    }

    if (!lowerCase){
        cout << "Password must have at least 1 lowercase alphabet." << endl;
    }
    if (!upperCase){
        cout << "Password must have at least 1 uppercase alphabet." << endl;
    }
    if (!digitChar){
        cout << "Password must have at least 1 digit character." << endl;
    }
    if (!specialChar){
        cout << "Password must have at least 1 special character." << endl;
    }
    return lowerCase && upperCase && digitChar && specialChar;
}

int main() {
    string password;

    do {
        cout << "\nEnter Password: ";
        cin >> password;
    } while (!passwordChecker(password));

    cout << "\nThe password is created successfully.";

    return 0;
}