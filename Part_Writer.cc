#include <algorithm>
#include <cmath>
#include <unordered_map>
#include "Part_Writer.h"

using namespace std;

int interval_iterator(int interval);
int calc_distance(string str1, string str2);
string note_convert(string note);
string note_iterator(string note, char accidentals, char direction);
vector<Chords> Sort_Chord_List(vector<Chords> ChordListIn);

void Part_Writer::Analyze_Chord(Chords Prev_Chord){
    cout << "\n----DISTANCE CHECK----\n" << endl;
    for (int i = 0; i < (int)Chord_List.size(); i++){
        Distance_Check(Prev_Chord, Chord_List[i]);
    }    
}

void Part_Writer::Distance_Check(Chords Prev_Chord, Chords &Next_Chord){
    int distance = 0, note = 1;
    string compare1, compare2; //compare notes to find distance
    for (int i = 0; i < Prev_Chord.ChordSize; i++){  //combined[place in chord][interval or note][char place of interval/note]
        compare1 = Prev_Chord.Combined[i][note];  
        compare2 = Next_Chord.Combined[i][note];  
        if( (compare1[1] == '#' && compare2[1] == 'b') || (compare1[1] == 'b' && compare2[1] == '#')){
               compare1 = note_convert(compare1);
        }
        distance += calc_distance(compare1, compare2);
    }
    cout << "--------------------" << endl;
    Next_Chord.ChordScore = abs(((Prev_Chord.ChordSize*4) - distance))+1;
}

void Part_Writer::Show_ChordList(){
    for (int i = 0; i < (int)Chord_List.size(); i++){
        cout << i+1 << ".)\n";
        Chord_List[i].ShowChord();
        cout << "Chord Score = " << Chord_List[i].ChordScore << "\n";
        cout << "------------------------------------------\n";
    }
}

void Part_Writer::Trim_ChordList(){
    vector<Chords> temp;
    //sort by score
    Chord_List = Sort_Chord_List(Chord_List);
    //only show top 6
    for (int i = 0; i < 6; i++){
        temp.push_back(Chord_List.back());
        Chord_List.pop_back();
    }
    Chord_List = temp;
}

void Part_Writer::Generate_Chord_List(Chords Chord_in){
    //build chord
    Chord_in = Generate_Chord(Chord_in);
    Chord_in.SetNotes(); //notes are only set after intervals AND scale notes have been established
    Chord_in.SetCombined();
    Add_to_List(Chord_in);
}

void Part_Writer::Add_to_List(Chords Chord_in){  //list of all permutations of chord interval vectors are generated
    sort(Chord_in.Combined.begin(), Chord_in.Combined.end());
    do{  
        Chord_List.push_back(Chord_in);
    }while (next_permutation(Chord_in.Combined.begin(), Chord_in.Combined.end()));
}

Chords Part_Writer::Generate_Chord(Chords Chord_in){
    int intrvl = Numeral_to_int(Chord_in.Type);
    for (int i = 0; i < Chord_in.ChordSize; i++){
        Chord_in.Intervals.push_back(intrvl);
        intrvl = interval_iterator(intrvl);
    }
    return Chord_in;
}

Chords Part_Writer::Pick_New_Chord(){
    int option;
    cout << "----Choose a Chord----\n";
    for (int i = 0; i < 6; i++){
        cout << i+1 << ".) ";
        for (int j = 0; j < (int)Chord_List[i].ChordSize; j++){
            cout << Chord_List[i].Combined[j][1] << "   ";
        }
        cout << "Quality - "<< Chord_List[i].ChordScore << "\n";
    }
    cout << "\nEnter Here:  ";
    cin >> option;
    if (option < 1 || option > 6){cout << "Option not available setting DEFAULT to 1"; option = 1;}
    return Chord_List[option-1];
}

int Part_Writer::Numeral_to_int(string RN){  //  Converts the roman numerals from I to VII into an integer
    transform(RN.begin(), RN.end(), RN.begin(), ::toupper);
   if (RN == "I"){return 1;}
   else if(RN == "II" || RN == "II*"){return 2;}
   else if(RN == "III"){return 3;}
   else if(RN == "IV"){return 4;}
   else if(RN == "V"){return 5;}
   else if(RN == "VI"){return 6;}
   else if(RN == "VII" || RN == "VII*"){return 7;}
   else{return 0;}
}

int interval_iterator(int interval){ // takes in an interval and returns the next interval in the chord (up 2 notes in the key)
    if (interval+2 > 7){return interval-5;}
    else{return interval+2;}
}
int calc_distance(string str1, string str2){
    char accidental = str2[1];
    int count1 = 0, count2 = 0;
    string compare = str1;
    while (str2 != compare){ //iterate through notes forward ('F')
        compare = note_iterator(compare, accidental, 'F');
        count1++;
    }
    compare = str1;
    while (str2 != compare){  //iterate through notes backwards ('B')
        compare = note_iterator(compare, accidental, 'B');
        count2++;
    }
    cout << str1 << " ----> " << str2;
    cout << "  " << count1 << "  " << count2 << endl;
    if(count1 <= count2){return count1;}
    else{return count2;}
}

string note_convert(string note){
    string ChromaticScaleSharp[12] = {"G#", "A ", "A#", "B ", "C ", "C#", "D ", "D#", "E ", "F ", "F#", "G "};
    string ChromaticScaleFlat[12] =  {"Ab", "A ", "Bb", "B ", "C ", "Db", "D ", "Eb", "E ", "F ", "Gb", "G "};
    int loc = 0;
    if (note[1] == ' ' || note[1] == '#'){ // returns next note using chromatic scale of sharps
        for (int i = 0; i < 12; i++){  //searches for note in chromatic scale 
            if (note == ChromaticScaleSharp[i]){loc = i; break;}
        }
        return ChromaticScaleFlat[loc];
    }
    else{  //same process expect for flat version of chromatic scale
        for (int i = 0; i < 12; i++){
            if (note == ChromaticScaleFlat[i]){loc = i; break;}
        }
        return ChromaticScaleSharp[loc];
    }
}

string note_iterator(string note, char accidentals, char direction){ //iterates notes by half steps only
    string ChromaticScaleSharp[12] = {"A ", "A#", "B ", "C ", "C#", "D ", "D#", "E ", "F ", "F#", "G ", "G#"};
    string ChromaticScaleFlat[12] =  {"Ab", "A ", "Bb", "B ", "C ", "Db", "D ", "Eb", "E ", "F ", "Gb", "G "};
    int loc = 0;

    if (accidentals == ' ' || accidentals == '#'){ // returns next note using chromatic scale of sharps
        for (int i = 0; i < 12; i++){  //searches for note in chromatic scale 
            if (note == ChromaticScaleSharp[i]){loc = i; break;}
        }
        if (direction == 'F'){
            if(loc == 11){return "A ";}
            else{return ChromaticScaleSharp[loc+1];}
        }
        else{
            if(loc == 0){return "G#";}
            else{return ChromaticScaleSharp[loc-1];}
        }
        
    }
    else{  //same process expect for flat version of chromatic scale
        for (int i = 0; i < 12; i++){
            if (note == ChromaticScaleFlat[i]){loc = i; break;}
        }
        if (direction == 'F'){
            if(loc == 11){return "Ab";}
            else{return ChromaticScaleFlat[loc+1];}
        }
        else{
            if(loc == 0){return "G ";}
            else{return ChromaticScaleFlat[loc-1];}
        }
    }
}

vector<Chords> Sort_Chord_List(vector<Chords> ChordListIn){
    Chords temp;
    int min, size;
    size = (int)ChordListIn.size();
    for(int i = 0; i < size-1; i++){
        min = i;
        for(int j = i+1; j < size; j++){
            if(ChordListIn[j].ChordScore < ChordListIn[min].ChordScore){
                min = j;
            }
        }
        temp = ChordListIn[min];
        ChordListIn[min] = ChordListIn[i];
        ChordListIn[i] = temp;
    }
    return ChordListIn;
}