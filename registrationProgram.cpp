#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Project {
    string id;
    string firstName, fnameSmall;
    string middleName, mnameSmall;
    string lastName, lnameSmall;
    string userName;
    string password;
    string confirmPassword;
    string no;
};

string inputUser, inputPass, inputRand, enterRand;
bool passwordCheck, randCheck;
int userCheck;
int option;

const int MAX_ACCOUNTS = 100;
Project accounts[MAX_ACCOUNTS];
int accountCount = 0;
int tries, countTries = 5;

int arr[3][3] = {};
bool magicSquareChecker = false;

bool passwordChecker(const string& password){
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
        }else if (ispunct(letter)){
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


bool phoneNumChecker(const string& no){
    bool phoneDigit = false;

    if (no.length() < 11){
        cout << "Mobile Number must be at least 11 digits in length." << endl;
        return false;
    }
    if (no.length() > 11){
        cout << "Mobile Number must not exceed 11 digits in length." << endl;
        return false;
    }       

    for (char number : no){
        if (!isdigit(number)){
            phoneDigit = false;
            break;
        }else{
            phoneDigit = true;
        }
    }

    if (!phoneDigit){
        cout << "Moblie Number must only have numbers" << endl;
    }
    return phoneDigit;
}

string generateRandomString(int length) {
    const string characters = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string randomString;

    for (int i = 0; i < length; ++i) {
        int index = rand() % characters.length();
        randomString += characters[index];
    }

    return randomString;
}

void accountMenu(){
    cout << "\nACCOUNT MENU" << endl;
    cout << "[1] Sign-in" << endl;
    cout << "[2] Sign-up" << endl;
    cout << "[3] Exit" << endl;
    cout << "\nOption: ";
    cin >> option;
}

void accountCAPTHCHA(){
    srand(static_cast<unsigned int>(time(0)));
    enterRand =  generateRandomString(8);
    for (int i = 1; i <= 5; ++i) {
        cout << "\nRandom String: " << enterRand << endl;
        cout << "Confirm CAPTCHA: ";
        cin >> inputRand;
        
        if (enterRand == inputRand) {
            randCheck = false;
            tries = 0;
            countTries = 5;
            return;
        } else {
            cout << "Incorrect CAPTCHA. Try again. Attempts remaining: " << 5 - i << endl;
        }
    }
    
    cout << "Too many incorrect attempts. Exiting program." << endl;
    exit(0);
}

void signIn() {
    cout << "\nSIGN-IN" << endl;
    do{
        cout << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        int index = -1;
        for (int i = 0; i < accountCount; ++i){
            if (accounts[i].userName == inputUser && accounts[i].password == inputPass){
                index = i;
                break;
            }
        }

        if (index != -1){
            userCheck = 1;
            cout << "\nWelcome, " << accounts[index].firstName << "!\n";
        }else{
            cout << "\nIncorrect username or password. Please try again." << endl;
            countTries--;

            if (countTries == 0) {
                cout << "Too many incorrect attempts. Complete the CAPTCHA." << endl;
                accountCAPTHCHA();
                countTries = 5;
            }else{
                cout << "Number of Tries remaining: " << countTries << endl;
                userCheck = 0;
            }
        }
    } while(userCheck != 1);
}

void menu(){
    cout << "\nMENU" << endl;
    cout << "[1] Show Profile" << endl;
    cout << "[2] Play Game (Magic Square)" << endl;
    cout << "[3] Back" << endl;
    cout << "Option: ";
    cin >> option;
}

void showProfile(int i){
    cout << "\nID: " << accounts[i].id << endl;
    cout << "Full Name: " << accounts[i].firstName + " "  + accounts[i].middleName + " " + accounts[i].lastName << endl;
    cout << "Username: " << accounts[i].userName << endl;
    cout << "Password: " << accounts[i].password << endl;
    cout << "Mobile No. : " << accounts[i].no <<endl;
}

void signUp() {
    cout << "\nSIGN-UP" << endl;
    cout << "ID: ";
    cin >> accounts[accountCount].id;
    cout << "First Name: ";
    cin >> accounts[accountCount].firstName;
    for (char& fLetter : accounts[accountCount].firstName){
        fLetter = tolower(fLetter);
    }accounts[accountCount].fnameSmall = accounts[accountCount].firstName;
    cout << "Middle Name: ";
    cin >> accounts[accountCount].middleName;
    for (char& mLetter : accounts[accountCount].middleName){
        mLetter = tolower(mLetter);
    }accounts[accountCount].mnameSmall = accounts[accountCount].middleName;
    cout << "Last Name: ";
    cin >> accounts[accountCount].lastName;
    for (char& lLetter : accounts[accountCount].lastName){
        lLetter = tolower(lLetter);
    }accounts[accountCount].lnameSmall = accounts[accountCount].lastName;
    
    accounts[accountCount].userName = accounts[accountCount].firstName.substr(0, 1) + accounts[accountCount].middleName.substr(0, 1) + accounts[accountCount].lastName;

    cout << "Username: " << accounts[accountCount].userName << endl;

    do {
        cout << "Password: ";
        cin >> accounts[accountCount].password;
    } while (!passwordChecker(accounts[accountCount].password));

    do {
        cout << "Confirm Password: ";
        cin >> accounts[accountCount].confirmPassword;
        if (accounts[accountCount].confirmPassword != accounts[accountCount].password) {
            passwordCheck = true;
            cout << "Passwords do not match. Try again." << endl;
        } else {
            passwordCheck = false;
        }
    } while (passwordCheck);

    do {
        cout << "Mobile Number: ";
        cin >> accounts[accountCount].no;
    } while (!phoneNumChecker(accounts[accountCount].no));

    accountCount++;
}

void magicSquare() {
    bool leftRight1 = false, leftRight2 = false, leftRight3 = false;
    bool topBot1 = false, topBot2 = false, topBot3 = false;
    bool diagonal1 = false, diagonal2 = false;

    cout << "\n";
    for (int i = 0; i < 3; ++i){
        cout << "Enter #: ";
        for (int j = 0; j < 3; ++j){
            cin >> arr[i][j];
        }
    }

    if ((arr[0][0] + arr[0][1] + arr[0][2]) == 15){
        leftRight1 = true;
    }
    if ((arr[1][0] + arr[1][1] + arr[1][2]) == 15){
        leftRight2 = true;
    }
    if ((arr[2][0] + arr[2][1] + arr[2][2]) == 15){
        leftRight3 = true;
    }
    if ((arr[0][0] + arr[1][0] + arr[2][0]) == 15){
        topBot1 = true;
    }
    if ((arr[0][1] + arr[1][1] + arr[2][1]) == 15){
        topBot2 = true;
    }
    if ((arr[0][2] + arr[1][2] + arr[2][2]) == 15){
        topBot3 = true;
    }
    if ((arr[0][0] + arr[1][1] + arr[2][2]) == 15){
        diagonal1 = true;
    }
    if ((arr[0][2] + arr[1][1] + arr[2][0]) == 15){
        diagonal2 = true;
    }

    if (leftRight1 && leftRight2 && leftRight3 && topBot1 && topBot2 && topBot3 && diagonal1 && diagonal2){
        magicSquareChecker = true;
    } else {
        cout << "The entered values do not form a magic square. Please try again.\n";
        magicSquareChecker = false;
    }

    if (!magicSquareChecker) {
        magicSquare();
    }

    cout << "Congratulations, You have completed the game" << endl;
}

int main() {
    x:
    do{
        cout << "\n";
        accountMenu();
        switch (option){
            case 1:
                signIn();
                menu();
                switch (option){
                    case 1:
                        showProfile(accountCount - 1);
                        goto x;
                        break;
                    case 2:
                        magicSquare();
                        goto x;
                        break;
                    case 3:
                        goto x;
                        break;
                }
                break;
            case 2:
                signUp();
                break;
            case 3:
                break;
        }
    }while(option != 3);
    return 0;
}