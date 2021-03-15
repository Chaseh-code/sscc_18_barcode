/*
Generates SSCC_18 Barcodes
*/
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctype.h>
#include "GenerateCode.cpp"

using namespace std;

string inputCheck(string,int); // Checks that the user inputs correct sscc-18 barcode syntax
string inputCheck(string);

int main() {
// should add a piece of code that prints the last incrementing number from the csv file, so the user would know what that last number would be.
    vector<string> barcodes;
    ofstream file("FootLocker_Barcodes.txt");
    const string APP_ID= "00"; // sets barcode as SSCC_18
    const string PACK_TYPE = "0"; // Determines the type of package being shipped
    const string MANUFACTURER_NUM = "0016604"; 
    string input = "";
    string inputNum = "                    "; // bad way of setting a 20 character limit
    int numCodes = 0; // stores inputNum after it has been converted
    
    cout << "How many barcodes need to be made: ";
    cin >> inputNum;
    inputNum = inputCheck(inputNum);
    numCodes = stoi(inputNum);
    

    cout << "What would you like the starting incrementing number to be: ";
    cin >> input;
    input = inputCheck(input,input.length());
    
    barcodes = generateCode(APP_ID, PACK_TYPE, MANUFACTURER_NUM, input, numCodes);
    for(const auto &e : barcodes) file << e << "\n"; // outputs the barcodes to the file

    return 0;
}

string inputCheck(string input, int length) { // confirms that the incrementing value inputed from the user is ok to use.
    const int MAXDIGITS = 9; // user only only to specify up to 9 digits. 
    bool digit = true; // user can only input digits, no symbols or alphabetical letters.

    for(int i = 0; i < length; i ++){
        if(!isdigit(input[i])){
            digit = false;
            break;
        }
    }

    if(cin.fail() || length > MAXDIGITS || digit == false){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Sorry, that number was either too large or did not only contain numbers. \nA vaild incrementing number has 17 or less digits total and contains only numbers.\nPlease enter a valid starting incrementing number." << endl;
        cout << "Input Number: ";
        cin >> input;
        input = inputCheck(input, input.length());
    }

    return input;
}

string inputCheck(string input) { // confirms that the number of barcodes the user wants was enter correctly
    int length = input.length();
    bool digit = true; // user can only input digits, no symbols or alphabetical letters.

    for(int i = 0; i < length; i ++){
        if(!isdigit(input[i])){
            digit = false;
            break;
        }
    }

    if(cin.fail() || digit == false){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Sorry, that number did not only contain numbers. \nPlease only enter numerical values."<< endl;
        cout << "How many barcodes need to be made: ";
        cin >> input;
       input = inputCheck(input);
    }

    return input;
}