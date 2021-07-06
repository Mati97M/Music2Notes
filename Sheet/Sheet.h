#ifndef SHEET_H
#define SHEET_H
#include"Note.h"
#include <vector>
#include"Wave_file_Manager.h"

using namespace std;
//class Note;

//64th takes 0,0625 s
//32nd takes 0,125 s
//16th takes 0,25 s
//8th takes 0,5 s
//rv_quarter takes 1 s
//rv_half takes 2 s
//rv_whole takes 4 s
// 44100 Hz / bufor_size = 4096 = circa 10,77  => (that is 11)  calls of buffor per 1 second. So on 11th call, the 2nd second begins. See "Uwagi do programu"
// the size of the external vector tells about
//so we increase the duration (length) of each note object
class Sheet
{
    public:
        bool set_wfm(Wave_file_Manager* w){ if(!wfm) {wfm = w; return true;}   return false; }
        virtual ~Sheet();
        //static Sheet* s_Instance; if we wish  that there is only one instance of sheet
        //static Sheet* getInstance() {return s_Instance;}    //niech bedzie tylko jeen sheet, tak jak w soft engine. zeby mozna bylo korzystac z wave file managera
double current_time;
double* fft_output; //for simplicity, just for now, let`s pretend that the fft has taken place, and treat the buffer as the fft`s output
//fft_output niepotrzebne, wywalic

    private:
        Wave_file_Manager* wfm;
        //Sheet();  without comment, the undefined reference in WfM.cpp occures
        vector<vector<Note> > music_sheet;
        void export_notes_to_sheet(vector<double>& sb);
        Note::Note_name match_frequency_to_the_note(double f);
        void View_the_Sheet()const;
        bool remove_the_silence();
friend class Wave_file_Manager;

};

#endif // SHEET_H
