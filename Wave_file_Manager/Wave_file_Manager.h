#ifndef WAVE_FILE_MANAGER_H
#define WAVE_FILE_MANAGER_H

#include <iostream>
#include <vector>
#include "../WAVE_file/WAVE_file.h"
#include <complex>
#include "Sheet.h"

using namespace std;
class Sheet;

class Wave_file_Manager
    {
        WAVE_file* wav_file;
        void ShortToReal(const signed short* shrt,double* real,int siz);
        vector <double*> arrays_of_d; //look at get_data_from_channel_as_double

       int size_of_buffer;
       double* buffer;
        double* fake_channel;
        int current_call_of_buffer;
        unsigned buffer_padding{};

        Sheet* music_score;

        public:
        Wave_file_Manager(WAVE_file* p = nullptr);
        ~Wave_file_Manager();
        void set_wav_file(WAVE_file* p){ wav_file = p; cout<< "wav_file set\n";}
        void Create_Channels();
        double* get_data_from_channel_as_double(int n = 0);
        int get_size_of_channel(int = 0);
        bool fill_the_buffer (); //for now, it`s an array of doubles (frequencies); we assume, that fft have already taken place
         bool the_last_call_of_buffer();
        void set_fake_channel(double*s);
        unsigned int samples_of_fake_channel;
        int calls_of_buffer;    //zmienic, do private, i w konstr wartosci od inf w headerze
        int get_size_of_buffer(){ return size_of_buffer;}
        void View_the_Sheet();

        bool Update();
        friend class Sheet;
        //friend void Sheet::export_notes_to_sheet(vector<double>& sorted_buffer);

        bool optimize_the_sheet();



    };
#endif // WAVE_FILE_MANAGER_H
