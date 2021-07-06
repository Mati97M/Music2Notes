#include "Sheet.h"
#include <iostream>
#include <algorithm>
//operator << do przeciazenia  << sheet to raczej w note
#include "Note.h"
//Sheet* s_Instance{nullptr};  if we wish  that there is only one instance of sheet

Sheet::~Sheet()
{
    cout<<"\nSheet::~Sheet()  has done his job\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Note::Note_name Sheet::match_frequency_to_the_note(double f) //looking thru every element in the array, vector? of the buffer. Buffer is a piece of the song, tahtis a tiny part of one second. What frequencies in that moment occured?
{
    if (f < 27.50)  return Note::Note_name::undefined_frequency;
    if (f >= 27.50 && f < 29.14) return Note::Note_name::A0;
    if (f >= 29.14 && f < 30.87) return Note::Note_name::Bb0;
	if (f >= 30.87 && f < 32.70) return Note::Note_name::B0;
    if (f >= 32.70 && f < 34.65) return Note::Note_name::C1;
    if (f >= 34.65 && f < 36.71) return Note::Note_name::Db1;
    if (f >= 36.71 && f < 38.89) return Note::Note_name::D1;
	if (f >= 38.89 && f < 41.20) return Note::Note_name::Eb1;
	if (f >= 41.20 && f < 43.65) return Note::Note_name::E1;
	if (f >= 43.65 && f < 46.25) return Note::Note_name::F1;
	if (f >= 46.25 && f < 49.00) return Note::Note_name::Gb1;
    if (f >= 49.00 && f < 51.91) return Note::Note_name::G1;
    if (f >= 51.91 && f < 55.00) return Note::Note_name::Ab1;
    if (f >= 55.00 && f < 58.27) return Note::Note_name::A1;
    if (f >= 58.27 && f < 61.74) return Note::Note_name::Bb1;
    if (f >= 61.74 && f < 65.41) return Note::Note_name::B1;
	if (f >= 65.41 && f < 69.30) return Note::Note_name::C2;
	if (f >= 69.30 && f < 73.42) return Note::Note_name::Db2;
	if (f >= 73.42 && f < 77.78) return Note::Note_name::D2;
	if (f >= 77.78 && f < 82.41) return Note::Note_name::Eb2;
	if (f >= 82.41 && f < 87.31) return Note::Note_name::E2;
	if (f >= 87.31 && f < 92.50) return Note::Note_name::F2;
	if (f >= 92.50 && f < 98.00 ) return Note::Note_name::Gb2;
	if (f >= 98.00 && f < 103.83) return Note::Note_name::G2;
	if (f >= 103.83 && f < 110.00) return Note::Note_name::Ab2;
    if (f >= 110.00 && f < 116.54) return Note::Note_name::A2;
    if (f >= 116.54 && f < 123.47) return Note::Note_name::Bb2;
	if (f >= 123.47 && f < 130.81) return Note::Note_name::B2;
	if (f >= 130.81 && f < 138.59) return Note::Note_name::C3;
	if (f >= 138.59 && f < 146.83) return Note::Note_name::Db3;
	if (f >= 146.83 && f < 155.56) return Note::Note_name::D3;
	if (f >= 155.56 && f < 164.81) return Note::Note_name::Eb3;
	if (f >= 164.81 && f < 174.61) return Note::Note_name::E3;
	if (f >= 174.61 && f < 185.00) return Note::Note_name::F3;
	if (f >= 185.00 && f < 196.00) return Note::Note_name::Gb3;
	if (f >= 196.00 && f < 207.65) return Note::Note_name::G3;
	if (f >= 207.65 && f < 220.00) return Note::Note_name::Ab3;
	if (f >= 220.00 && f < 233.08) return Note::Note_name::A3;
	if (f >= 233.08 && f < 246.94) return Note::Note_name::Bb3;
    if (f >= 246.94 && f < 261.63) return Note::Note_name::B3;
	if (f >= 261.63 && f < 277.18) return Note::Note_name::C4;
	if (f >= 277.18 && f < 293.66) return Note::Note_name::Db4;
	if (f >= 293.66 && f < 311.13) return Note::Note_name::D4;
	if (f >= 311.13 && f < 329.63) return Note::Note_name::Eb4;
	if (f >= 329.63 && f < 349.23) return Note::Note_name::E4;
	if (f >= 349.23 && f < 369.99) return Note::Note_name::F4;
	if (f >= 369.99 && f < 392.00) return Note::Note_name::Gb4;
	if (f >= 392.00 && f < 415.30) return Note::Note_name::G4;
	if (f >= 415.30 && f < 440.00) return Note::Note_name::Ab4;
    if (f >= 440.00 && f < 466.16) return Note::Note_name::A4;
    if (f >= 466.16 && f < 493.88)return Note::Note_name::Bb4;
	if (f >= 493.88 && f < 523.25) return Note::Note_name::B4;
	if (f >= 523.25 && f < 554.37) return Note::Note_name::C5;
	if (f >= 554.37 && f < 587.33) return Note::Note_name::Db5;
    if (f >= 587.33 && f < 622.25) return Note::Note_name::D5;
    if (f >= 622.25 && f < 659.25) return Note::Note_name::Eb5;
    if (f >= 659.25 && f < 698.46) return Note::Note_name::E5;
	if (f >= 698.46 && f < 739.99) return Note::Note_name::F5;
	if (f >= 739.99 && f < 783.99) return Note::Note_name::Gb5;
	if (f >= 783.99 && f < 830.61) return Note::Note_name::G5;
	if (f >= 830.61 && f < 880.00) return Note::Note_name::Ab5;
	if (f >= 880.00 && f < 932.33) return Note::Note_name::A5;
	if (f >= 932.33 && f < 987.77) return Note::Note_name::Bb5;
	if (f >= 987.77 && f < 1046.50) return Note::Note_name::B5;
	if (f >= 1046.50 && f < 1108.73) return Note::Note_name::C6;
	if (f >= 1108.73 && f < 1174.66) return Note::Note_name::Db6;
	if (f >= 1174.66 && f < 1244.51) return Note::Note_name::D6;
	if (f >= 1244.51 && f < 1318.51) return Note::Note_name::Eb6;
    if (f >= 1318.51 && f < 1396.91) return Note::Note_name::E6;
	if (f >= 1396.91 && f < 1479.98) return Note::Note_name::F6;
	if (f >= 1479.98 && f < 1567.98) return Note::Note_name::Gb6;
	if (f >= 1567.98 && f < 1661.22) return Note::Note_name::G6;
	if (f >= 1661.22 && f < 1760.00) return Note::Note_name::Ab6;
    if (f >= 1760.00 && f < 1864.66) return Note::Note_name::A6;
	if (f >= 1864.66 && f < 1975.53) return Note::Note_name::Bb6;
	if (f >= 1975.53 && f < 2093.00) return Note::Note_name::B6;
	if (f >= 2093.00 && f < 2217.46) return Note::Note_name::C7;
	if (f >= 2217.46 && f < 2349.32) return Note::Note_name::Db7;
    if (f >= 2349.32 && f < 2489.02) return Note::Note_name::D7;
    if (f >= 2489.02 && f < 2637.02) return Note::Note_name::Eb7;
    if (f >= 2637.02 && f < 2793.83) return Note::Note_name::E7;
	if (f >= 2793.83 && f < 2959.96) return Note::Note_name::F7;
	if (f >= 2959.96 && f < 3135.96) return Note::Note_name::Gb7;
	if (f >= 3135.96 && f < 3322.44) return Note::Note_name::G7;
	if (f >= 3322.44 && f < 3520.00) return Note::Note_name::Ab7;
	if (f >= 3520.00 && f < 3729.31) return Note::Note_name::A7;
	if (f >= 3729.31 && f < 3951.07) return Note::Note_name::Bb7;
    if (f >= 3951.07 && f < 4186.01) return Note::Note_name::B7;
	if (f >= 4186.01 && f < 4434.92) return Note::Note_name::C8;
    else return Note::Note_name::undefined_frequency;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sheet::export_notes_to_sheet(vector<double> & sb)
{
    //appending notes to the inner vector
    vector<Note> that_special_moment;
    for (int i = 0; i < wfm->get_size_of_buffer(); ++i){
        Note::Note_name nt_n = match_frequency_to_the_note(sb[i]);
        double time = static_cast<double>(wfm->current_call_of_buffer)/static_cast<double>(wfm->calls_of_buffer) * (wfm->wav_file->get_song_duration_in_sec());

        if (that_special_moment.empty()){

               that_special_moment.push_back(Note(nt_n,Note::rv_64th,i, time) );
            }
         // if the note isn`t already written (does not exist), we create and  append one

         if ( find(that_special_moment.begin(), that_special_moment.end(), Note(nt_n) ) == that_special_moment.end() ) //didnt find that note in current set
               that_special_moment.push_back(Note(nt_n,Note::rv_64th,i, time) );
         }
    music_sheet.push_back(that_special_moment);
       /*
        if (binary_search(&(*that_special_moment.begin().name), &(*that_special_moment.end().name), nt_n )){ //requires defining operator < or >
                that_special_moment.push_back(Note(nt_n,Note::rv_64th,i, static_cast<double>(wfm->current_call_of_buffer)/static_cast<double>(wfm->calls_of_buffer)));
            }
    }
    music_sheet.push_back(that_special_moment);

*/
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sheet::View_the_Sheet()const
{
    for (int that_special_moment = 0; that_special_moment < music_sheet.size(); ++that_special_moment){
        cout<<endl<<'|';
        for(int note = 0; note < music_sheet[that_special_moment].size() - 1; ++note){
            cout <<  music_sheet[that_special_moment][note] << '\t' ;
        }
        cout<<'|' << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sheet::remove_the_silence()
{
    auto it = music_sheet.begin();
    // erasing silence from the beginning
    try
    {

        while (music_sheet[0].size() == 1 && music_sheet.front()[0].name == Note::Note_name::undefined_frequency)
        {
            music_sheet.erase(it);
        }

        // erasing silence from the end
        while (music_sheet.back().size() == 1 && music_sheet.back()[0].name == Note::Note_name::undefined_frequency)
        {
            music_sheet.pop_back();
        }
    }
    catch(...)
    {
        cout<<"\nerasing silence catched!\n";
        return false;
    }

    return true;
}


