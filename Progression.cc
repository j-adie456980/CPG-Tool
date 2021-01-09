#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Progression.h"

using namespace std;

void Prog::Begin(){
    Chords new_chord;
    new_chord.AddNewChord();
    Add_Prog(new_chord);
}

void Prog::Build_List(){
    int choice = 0;
    cout << "Choose a Chord to add" << endl;
    for (int i = 0; i < (int)Possible_Chords.size(); i++){cout << i+1 << ".)  " << Possible_Chords[i].Type << endl;}
    cout << "Enter Here:   ";
    cin >> choice;
    if ( (choice > 0) && (choice <= (int)Possible_Chords.size()) ){Chosen_Chord = Possible_Chords[choice-1];}
    else{cout << "Invalid Choice - setting default to option 1" << endl;  Chosen_Chord = Possible_Chords[0];}
    Possible_Chords.clear(); //clears for future use if a new chord is to be added

    //Transfer the following properties over to the chosen chord type
    Chosen_Chord.Mode = Progs[(int)Progs.size()-1].Mode;
    Chosen_Chord.Key = Progs[(int)Progs.size()-1].Key;
    Chosen_Chord.Accidentals = Progs[(int)Progs.size()-1].Accidentals;
    Chosen_Chord.ScaleNotes = Progs[(int)Progs.size()-1].ScaleNotes;

    //Displaying the possible permutations of the chord are stored here temporarily
    cout << "---ALL PERMUTATIONS OF FIRST POSSIBLE CHORD---" << endl;
    Part_Writer part;
    part.Generate_Chord_List(Chosen_Chord);
    part.Analyze_Chord(Progs[(int)Progs.size()-1]); // analyzes last chord in prog and each chord in the chordlist
    part.Trim_ChordList();
    Add_Prog(part.Pick_New_Chord());
}

void Prog::Show_Progs(){
    if ((int)Progs.size() != 0){
        cout << "\n-----SCALE of " << Progs[0].Key << Progs[0].Accidentals << ' ' << Progs[0].Mode << "-----\n\n";
    }
    for (int i = 0; i < (int)Progs.size(); i++){
        Progs[i].ShowChord(); 
        cout << "\n\n";
    }
    
}

void Prog::Add_Prog(Chords NewChord){
    Progs.push_back(NewChord);
}

void Prog::Find_Possible_Chords(Chords NewChord){
    Chords temp;
    string romans[9] = { "i", "ii", "ii*", "iii", "iv", "V", "vi", "vii", "vii*" };
    string romans_upper[6] = { "I", "II", "III", "IV", "VI", "VII"};

    temp.ChordSize = NewChord.ChordSize;
    
    for (int i = 0; i < 9; i++){
        temp.Type = romans[i];
        if (Check_Validity(NewChord, temp)){
            Possible_Chords.push_back(temp);
        }
    }
    for (int j = 0; j < 6; j++){
        temp.Type = romans_upper[j];
        if (Check_Validity(NewChord, temp)){Possible_Chords.push_back(temp);}
    }
}

void Prog::Show_Possible_Chords(){

    cout << "\nHere are " << Possible_Chords.size() << " possible chords to follow this:  " << endl;

    for (int i = 0; i < (int)Possible_Chords.size(); i++){
        cout << Possible_Chords[i].Type << " ";
        if (((i+1)%5) == 0){cout << "\n";}  //creates a newline every five iterations
    }
    cout << "\n";
}

bool Prog::Check_Validity(Chords NewChord, Chords CheckChord){
    if (NewChord.Mode == "Ionian"){return Type_Check_Ionian(NewChord, CheckChord);}
    else if(NewChord.Mode == "Aeolian"){return Type_Check_Aeolian(NewChord, CheckChord);}
    else{return Type_Check_Ionian(NewChord, CheckChord);}
}


bool Prog::Type_Check_Ionian(Chords NewChord, Chords CheckChord){
    if (NewChord.Type == "I"){
        return (CheckChord.Type == "ii") || (CheckChord.Type == "iii") || 
                (CheckChord.Type == "IV") || (CheckChord.Type == "V")   || 
                (CheckChord.Type == "vi") || (CheckChord.Type == "vii*");
    }
    else if (NewChord.Type == "ii") {return (CheckChord.Type == "V") || (CheckChord.Type == "vii*");}
    else if (NewChord.Type == "iii") {return (CheckChord.Type == "IV") || (CheckChord.Type == "vi");}
    else if (NewChord.Type == "IV") {
        return (CheckChord.Type == "ii") || (CheckChord.Type == "V") || 
               (CheckChord.Type == "vii*");
    }
    else if (NewChord.Type == "V") {return (CheckChord.Type == "I") || (CheckChord.Type == "vii*");}
    else if (NewChord.Type == "vi") {return (CheckChord.Type == "ii") || (CheckChord.Type == "IV");}
    else if (NewChord.Type == "vii*") {return (CheckChord.Type == "I") || (CheckChord.Type == "vi");}
    else {return false;}
}

bool Prog::Type_Check_Aeolian(Chords NewChord, Chords CheckChord){
    if (NewChord.Type == "i"){
        return (CheckChord.Type == "ii*") || (CheckChord.Type == "III") || 
                (CheckChord.Type == "iv") || (CheckChord.Type == "V")   || 
                (CheckChord.Type == "VI") || (CheckChord.Type == "vii*") ||
                (CheckChord.Type == "VII");
    }
    else if (NewChord.Type == "ii*") {return (CheckChord.Type == "V") || (CheckChord.Type == "vii*");}
    else if (NewChord.Type == "III") {return (CheckChord.Type == "iv") || (CheckChord.Type == "VI");}
    else if (NewChord.Type == "iv") {
        return (CheckChord.Type == "i") || (CheckChord.Type == "ii*") || 
               (CheckChord.Type == "V")   || (CheckChord.Type == "vii*");
    }
    else if (NewChord.Type == "V") {return (CheckChord.Type == "i") || (CheckChord.Type == "VI");}
    else if (NewChord.Type == "VI") {
        return (CheckChord.Type == "ii*") || (CheckChord.Type == "iv") ||
               (CheckChord.Type == "V");}
    else if (NewChord.Type == "vii*") {return (CheckChord.Type == "i") || (CheckChord.Type == "V");}
    else if (NewChord.Type == "VII") {return (CheckChord.Type == "III");}
    else {return false;}
}