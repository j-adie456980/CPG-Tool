//****************************************************************
//  Created by: Justin Adie
//  Updated   : 11/12/2020
//  Purpose   : Class to predict chord progressions
//****************************************************************
#include "Part_Writer.h"
#ifndef PROGRESSION_H
#define PROGRESSION_H
using namespace std;
 
class Prog{
    public:
    //getters
    vector<Chords> Get_Progs(){return Progs;}
    //Misc. Func(s)
    void Add_Next();
    void Add_Prog(Chords NewChord);
    void Begin();
    void Show_Progs();
    void Find_Possible_Chords(Chords NewChord);
    void Build_List(); // builds list of every permutation of a chord
    void Show_Possible_Chords();
    bool Check_Validity(Chords NewChord, Chords CheckChord);
    bool Type_Check_Ionian(Chords NewChord, Chords CheckChord);
    bool Type_Check_Aeolian(Chords NewChord, Chords CheckChord);

    private:
    vector<Chords> Progs;
    vector<Chords> Possible_Chords;
    Chords Chosen_Chord;  // Chord that list of possible inversions will be built from
};

#endif