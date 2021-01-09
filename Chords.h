//****************************************************************
//  Created by: Justin Adie
//  Updated   : 11/12/2020
//  Purpose   : Chord storing container class
//****************************************************************
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#ifndef CHORDS_H
#define CHORDS_H
using namespace std;
 
class Chords{
    public:
    //Default Constructor(s)
    Chords();
    //Getters
    vector<string> GetScaleNotes();
    //Mutators
    void MakeNotesDiminished();
    //Setters
    void SetNotes();
    void SetCombined();
    //Random Funcs
    void ShowChord();
    void AddNewChord();
    string NoteIterator(string note, char StepSize);

    int ChordSize, ChordScore;
    char Key, Accidentals;
    string Mode, Type;
    vector<int> Intervals;
    vector<string> ScaleNotes; //root scale notes 
    vector<string> Notes; //notes for actual chord
    vector<vector<string>> Combined; //row 1 = intervals - row 2 = notes 
};

#endif