#include "GenerateCode.h"
#include <iostream>
#include <math.h>

using namespace std;

vector<string> generateCode(string APP_ID, string PACK_TYPE, string MANUFACTURER_NUM, string input, int numCodes){
    vector<string> barcodes;
    const string ZEROS = "00000000"; // to turn the incrementing number into the full 9 digits
    string barcode = "";
    const int BARCODELIMIT = 17; // total number of digits used to calculate the checkSum value.
    const int MAXDIGITS = 9; // max number of incrementing digits
    int increment = stoi(input); // converting to int so that can increment the barcode numbers
    const int ADD_START = increment;
    string incrementString = "";
    int sum = 0;
    int sumInterval = 0;
    int checkSum = 0;

    for(int c = 0 + ADD_START; c < numCodes + ADD_START; c++){
        incrementString = (to_string(increment).length() < MAXDIGITS) ? incrementString.append(ZEROS,0,MAXDIGITS-to_string(increment).length()).append(to_string(increment)) : to_string(increment); //checks to make sure the incrementing number has 9 digits.
        barcode = APP_ID + PACK_TYPE + MANUFACTURER_NUM + incrementString;

        for(int i = 0; i < BARCODELIMIT; i++){
            sum += (i%2==0) ? (barcode[i+2] - '0') * 3 : barcode[i+2] - '0';
        }

        if((10 - (sum%10)) == 10 ){ // deals with mod returning 0
            sumInterval = sum;
        } else{
            sumInterval = sum + (10 - (sum%10));
        }    
        checkSum = sumInterval - sum;

        /* Creates barcode and adds it to the list */
        barcode.append(to_string(checkSum));
        barcodes.push_back(barcode);

        /* Resetting values to increment to the next barcode */
        ++increment;
        sum = 0;
        sumInterval = 0;
        checkSum = 0;
        barcode = "";
        incrementString = "";
    }

    return barcodes;
}