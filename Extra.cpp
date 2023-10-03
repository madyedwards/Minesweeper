#include "Extra.h"
#include <iostream>
using namespace std;

vector<char> Extra::inputFile(int test_board) {

    //load file in
    string newFile = "boards/testboard" + std::to_string(test_board) + ".brd";
    vector<char> totalMines;
    ifstream inFile(newFile);

    if (inFile.is_open()) {
        char index;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
                inFile.get(index);
                totalMines.push_back(index);
            }
            //ignore() function to help with reading
            inFile.ignore(1);
        }
        inFile.close();
    }
    return totalMines;
}
//TA HELP??????
//imm gonna scream
//AaAaaaaaaa
vector<int> Extra::numbers(int value) {
    vector<int> totalNumbers;
    //helps with adjustment??
    //not entirely sure
    if (value < -99) {
        totalNumbers.push_back(10);
        totalNumbers.push_back(9);
        totalNumbers.push_back(9);
    }
    else if (value < 0) {
        totalNumbers.push_back(10);
        totalNumbers.push_back(0);
        totalNumbers.push_back(value * -1);
    }
    else if (value < 10) {
        totalNumbers.push_back(0);
        totalNumbers.push_back(0);
        totalNumbers.push_back(value);
    }
    else if (value < 100) {
        totalNumbers.push_back(0);
        int val2 = value/10;
        totalNumbers.push_back(val2);
        val2 = value % 10;
        totalNumbers.push_back(val2);
    }
    else{
        int val3 = value/100;
        totalNumbers.push_back(val3);
        val3 = value% 100;
        val3 = val3 / 10;
        totalNumbers.push_back(val3);
        val3 = value % 10;
        totalNumbers.push_back(val3);
    }

    return totalNumbers;
}