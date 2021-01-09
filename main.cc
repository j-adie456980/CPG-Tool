//****************************************************************
//  Created by: Justin Adie
//  Updated   : 11/12/2020
//  Purpose   : Main Function For Music Theory Assist App
//****************************************************************
#include "Progression.h"
using namespace std;

int main()
{
    char response;
    Prog testprog;
    int Prog_loc = 0; // Iterator for chord prog 
    
    testprog.Begin();
    do{
        testprog.Find_Possible_Chords(testprog.Get_Progs()[Prog_loc]); // build pathways from the initial chord
        testprog.Show_Progs();
        testprog.Show_Possible_Chords();
        testprog.Build_List();
        cout << "\n----Add another Chord?----\n";
        cout << "\nAnswer Here ( Y / N ):   ";
        cin >> response;
        Prog_loc++;
    }while(response == 'Y' || response == 'y');

    cout << "\n----FINAL CHORD PROGRESSION----\n";
    testprog.Show_Progs();
    char tmp;
    cout << "\n--Enter a key a close--\n";
    cin >> tmp;
    return 0;
}

