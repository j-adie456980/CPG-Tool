#include "Chords.h"

using namespace std;

char GetAccidentals();
char GetKey();
int GetChordSize();
int IntervalIterator(int interval);
string GetMode();
string GetType(string mode);
vector<int> GetIntervals(int chordsize);

Chords::Chords(){  //Constructor for Chords
    Key = 'C'; Accidentals = ' '; Mode = "Ionian"; Type = "I";
    ChordSize = 0;
    ChordScore = 0;
}

vector<string> Chords::GetScaleNotes(){ //returns a vector containing all of the notes in a particular scale based on the chords key
    vector<string> temp;
    string note = ".."; note[0] = Key; note[1] = Accidentals;
    vector<char> steps;
    
    //each mode has it's own way of adding accidentals (check notes folder for more info :)
         if (Mode == "Ionian") {steps = {'W','W','H','W','W','W','H'};}
    else if (Mode == "Aeolian"){steps = {'W','H','W','W','H','W','W'};}
                          else {steps = {'W','W','H','W','W','W','H'};} //DEFAULT to Ionian steps
    for (int i = 0; i < (int)steps.size(); i++){
            temp.push_back(note);
            note = NoteIterator(note, steps[i]);
    }
    return temp;
}

void Chords::ShowChord(){
    vector<char> steps;
    string NoteTemp;
    for (int i = 0; i < ChordSize; i++){cout << Combined[i][0] << "    ";}
    cout << "Root - " << Combined[0][1] << "  " << Mode << "  " << Type << endl;
    if (ScaleNotes.size() > 0){  //makes sure to only show the notes if the vector has notes
        for (int j = 0; j < (int)Notes.size(); j++){  //notes are chosen based on their place in the intervals vector
            cout << Combined[j][1] << "   ";
        } 
    }
}

void Chords::AddNewChord(){ //setter for a new chord
    //sets all variables using functions native to this cc file
    Mode = GetMode();
    Key = GetKey();
    Accidentals = GetAccidentals();
    ChordSize = GetChordSize();
    ScaleNotes = GetScaleNotes();
    Type = GetType(Mode);
    Intervals = GetIntervals(ChordSize);
    SetNotes();
    SetCombined();
}

void Chords::MakeNotesDiminished(){
    string TempNote = "..";
    vector<char> HalfStepBack = {'W','W','W','W','W','H'};

    TempNote = Notes[2];//flat fifth
    for(int i = 0; i < (int)HalfStepBack.size(); i++){TempNote = NoteIterator(TempNote, HalfStepBack[i]);} //iterates note back a half step
    Notes[2] = TempNote;
    if(ChordSize > 3){
        TempNote = Notes[3];
        for(int i = 0; i < (int)HalfStepBack.size(); i++){TempNote = NoteIterator(TempNote, HalfStepBack[i]);}
        Notes[3] = TempNote;//flat seventh
    }
}

void Chords::SetNotes(){
    Notes.clear();
    Chords temp;
    string NoteToChar = ScaleNotes[Intervals[0]-1];
    if (Type[0] == 'I' || Type[0] == 'V'){temp.Mode = "Ionian";} //updates mode depending on case value
    if (Type[0] == 'i' || Type[0] == 'v'){temp.Mode = "Aeolian";}
    temp.Key = NoteToChar[0];
    temp.Accidentals = NoteToChar[1];
    temp.ScaleNotes = temp.GetScaleNotes();
    for (int i = 0, j = 0; i < ChordSize; i++){
        Notes.push_back(temp.ScaleNotes[j]);
        j = IntervalIterator(j);
    }
    //add diminished functions maybe here
    if (Type.back() == '*'){MakeNotesDiminished();}
}

void Chords::SetCombined(){ //creates a combined version of both the intervals and notes vectors
    Combined.clear();
    vector<string> temp(2);
    string to_int = " ";
    for (int i = 0; i < ChordSize; i++){
        to_int[0] = Intervals[i]+48;//int to string
        temp[0] = to_int;
        temp[1] = Notes[i];
        Combined.push_back(temp);
    }
}

string Chords::NoteIterator(string note, char StepSize){
    string ChromaticScaleSharp[12] = {"A ", "A#", "B ", "C ", "C#", "D ", "D#", "E ", "F ", "F#", "G ", "G#"};
    string ChromaticScaleFlat[12] =  {"Ab", "A ", "Bb", "B ", "C ", "Db", "D ", "Eb", "E ", "F ", "Gb", "G "};
    int loc = 0;
    char temp = Accidentals;
    if(Mode == "Ionian"){
        if(Key == 'F' && Accidentals == ' '){temp = 'b';}
    }
    if(Mode == "Aeolian"){
        if((Key == 'C' && Accidentals == ' ') || (Key == 'D' && Accidentals == ' ') ||
           (Key == 'F' && Accidentals == ' ') || (Key == 'G' && Accidentals == ' '))
        {temp = 'b';}
    }

    if (temp == ' ' || temp == '#'){ // returns next note using chromatic scale of sharps
        for (int i = 0; i < 12; i++){  //searches for note in chromatic scale 
            if (note == ChromaticScaleSharp[i]){loc = i; break;}
        }
        if (StepSize == 'W'){ //whole steps
            if (loc == 10){return "A ";} //loop back around from G.
            else if(loc == 11){return "A#";}  //loop back around from G#
            else{return ChromaticScaleSharp[loc+2];}
        }
        else{  //half steps
            if(loc == 11){return "A ";}
            else{return ChromaticScaleSharp[loc+1];}
        }
    }
    else{  //same process expect for flat version of chromatic scale
        for (int i = 0; i < 12; i++){
            if (note == ChromaticScaleFlat[i]){loc = i; break;}
        }
        if (StepSize == 'W'){
            if (loc == 10){return "Ab";}
            else if(loc == 11){return "A ";}
            else{return ChromaticScaleFlat[loc+2];}
        }
        else{
            if(loc == 11){return "Ab";}
            else{return ChromaticScaleFlat[loc+1];}
        }
    }
}

//-------------------    NON-CLASS FUNCTIONS ---------------------------//

char GetKey(){
    char key;
    cout << "\nEnter a Key ( A - G ):  ";
    cin >> key;
    key = toupper(key);
    if (key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == 'E' || key == 'F' || key == 'G'){return key;}
    else{cout << "Invalid Key - Setting DEFAULT to C" << endl;  return 'C';}
}

char GetAccidentals(){
    int option = 0;
    cout << "\n--Choose an Accidental Type--\n";
    cout << "1.) None\n";
    cout << "2.) Sharp -->  #\n";
    cout << "3.) Flat  -->  b\n";
    cout << "\nEnter here :  ";
    cin >> option;

    if(option == 1){return ' ';}
    else if(option == 2){return '#';}
    else if(option == 3){return 'b';}
    else{cout << "Invalid Accidental - Setting DEFAULT to NONE\n";  return ' ';}
}

int GetChordSize(){
    int size;
    cout << "\nEnter a chord size (3-5):  ";
    cin >> size;
    if(size > 2 && size < 6){return size;}
    else{ cout << "ChordSize too small / large -- Setting Default to 3" << endl;  return 3;}
}

int IntervalIterator(int interval){ // takes in an interval and returns the next interval in the chord (up 2 notes in the key)
    if (interval+2 > 7){return interval-5;}
    else{return interval+2;}
}

string GetMode(){
    int option;
    cout << "\n--Enter a mode for your code--\n" << endl;
    cout << "1.)  Ionian  ( Major )\n";
    cout << "2.)  Aeolian ( Minor )\n";
    cout << "\nEnter here :  ";
    cin >> option;

    if(option == 1) {return "Ionian";}
    else if (option == 2) {return "Aeolian";}
    else {cout << "Invalid option. \nSetting default to Ionian" << endl; return "Ionian";}
}

string GetType(string mode){
    if (mode == "Ionian"){return "I";}
    else if (mode == "Aeolian"){return "i";}
    else{cout << "Invalid Mode - Setting DEFAULT roman to I" << endl; return "I";}
}

vector<int> GetIntervals(int chordsize){
    vector<int> temp;
    int interval = 1;
    for (int i = 0; i < chordsize; i++){
        temp.push_back(interval);
        interval = IntervalIterator(interval);
    }
    return temp;
}