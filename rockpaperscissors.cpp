#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>

using namespace std;

int userHealth = 10;
int computerHealth = 10;

string userInput;
string userName;

string generateRandomString(int length) {
    const string characters = "RPS";
    string randomString;

    string shuffledCharacters = characters;
    for (int i = shuffledCharacters.size() - 1; i > 0; --i){
        int j = rand() % (i + 1);
        swap(shuffledCharacters[i], shuffledCharacters[j]);
    }

    for (int i = 0; i < length; ++i){
        int index = rand() % shuffledCharacters.length();
        randomString += shuffledCharacters[index];
    }

    return randomString;
}

void gameMenu();
void rpsGame();

int main(){
    cout << "__________________________________________________________________" << endl;
    cout << "                     ROCK PAPER SCISSORS GAME                     " << endl;
    cout << "==================================================================" << endl;
    cout << "Enter your Name: ";
    getline(cin, userName);

    cout << "Welcome, " << userName << endl;
    cout << endl << userName << "'s Health - " << userHealth << endl;
    cout << "Computer's Health - " << computerHealth << endl;

    do{
        gameMenu();
        rpsGame();
        
        if (computerHealth == 0){
            cout << "\n-----------{CONGRATS, YOU BEAT THE GAME]-----------" << endl;
            break;
        }else if (userHealth == 0){
            cout << "\n-----------{YOU DIED]-----------" << endl;
        }
    }while(userHealth != 0);


    return 0;
}

void gameMenu(){
    cout << "\n__________________________________________________________________" << endl;
    cout << "                               MENU                               " << endl;
    cout << "==================================================================" << endl;
    cout << "[R] - Rock" << endl;
    cout << "[P] - Paper" << endl;
    cout << "[S] - Scissors" << endl;
    cout << "Choose your choice: ";
    cin >> userInput;
    for (char& letters : userInput){
        letters = toupper(letters);
    }

    cout << "\n";
}    

void rpsGame(){
    srand(static_cast<unsigned int>(time(0)));
    string game = generateRandomString(1);

    for (char& letters : userName){
        letters = toupper(letters);
    }
    for (char& letters : userInput){
        letters = toupper(letters);
    }

    if (userInput == "P"){
        cout << userName << " = PAPER" << endl;
    }else if (userInput == "R"){
        cout << userName << " = ROCK" << endl;
    }else if (userInput == "S"){
        cout << userName << " = SCISSORS" << endl;
    }else{
        cout << userName << " = INVALID INPUT" << endl;
    }

    if (game == "P"){
        cout << "COMPUTER = PAPER" << endl;
    }else if (game == "R"){
        cout << "COMPUTER = ROCK" << endl;
    }else if (game == "S"){
        cout << "COMPUTER = SCISSORS" << endl;
    }

    if (userInput == "R" && game == "R"){
        cout << "\n[TIE]" << endl;
    }else if (userInput == "R" && game == "P"){
        userHealth--;
        cout << "\n[YOU LOSE]" << endl;
    }else if (userInput == "R" && game == "S"){
        computerHealth--;
        cout << "\n[YOU WON]" << endl;
    }else if (userInput == "P" && game == "P"){
        cout << "\n[TIE]" << endl;
    }else if (userInput == "P" && game == "S"){
        userHealth--;
        cout << "\n[YOU LOSE]" << endl;
    }else if (userInput == "P" && game == "R"){
        computerHealth--;
        cout << "\n[YOU WON]" << endl;
    }else if (userInput == "S" && game == "S"){
        cout << "\n[TIE]" << endl;
    }else if (userInput == "S" && game == "R"){
        userHealth--;
        cout << "\n[YOU LOSE]" << endl;
    }else if (userInput == "S" && game == "P"){
        computerHealth--;
        cout << "\n[YOU WON]" << endl;
    }else{
        cout << "\nPLEASE ONLY SELECT - [R][P][S]";
    }

    cout << endl << userName << "'s Health - " << userHealth << endl;
    cout << "Computer's Health - " << computerHealth << endl;
}