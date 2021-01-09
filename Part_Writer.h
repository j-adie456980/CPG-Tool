//****************************************************************
//  Created by: Justin Adie
//  Updated   : 11/12/2020
//  Purpose   : Chord storing container class
//****************************************************************
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Chords.h"
#ifndef PART_WRITER_H
#define PART_WRITER_H
using namespace std;
 
class Part_Writer{
    public:
    //Analysis Methods
    void Analyze_Chord(Chords Prev_Chord);
    void Distance_Check(Chords Prev_Chord, Chords &Next_Chord);
    //void Tritone_Check(Chords &Next_Chord);
    //void Parallels_Check(Chords Prev_Chord, Chords &Next_Chord);

    //getters
    Chords Pick_New_Chord();
    
    //Random Funcs
    void Show_ChordList();
    void Trim_ChordList();
    int Numeral_to_int(string RN);
    void Generate_Chord_List(Chords Chord_in);
    void Add_to_List(Chords Chord_in);
    Chords Generate_Chord(Chords Chord_in); // initially builds the chord

    private:
    int chord_score;
    vector<Chords> Chord_List;  //  Chord_List contains every possible permutation of a single chord
};

#endif