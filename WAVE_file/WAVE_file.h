#ifndef WAVE_FILE_H
#define WAVE_FILE_H


#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
using Channel = vector<int16_t>; // dokladny typ trzeba uzaleznic od format code i bits_per_sample
class Wave_file_Manager;

struct DataTransferEXCPT{};

class WAVE_file
{
    private:
    WAVE_file* m_Address;

    //RIFF chunk
    char m_Chunk_ID[4];
    int m_Chunk_Size;
    char m_Format_Code[4];

    // fmt sub-chunk
    char m_Subchunk1_ID[4];
    int m_Subchunk1_Size;
    short int m_AudioFormat;        // 1 = consists of raw PCM samples as integers. Rozpoznac to najpierw.
    short int m_NumChannels;
    int m_SampleRate;
    int m_ByteRate;
    short int m_BlockAlign;
    short int m_BitsPerSample;      //indicates the range of the samples. to okresli jaki typ w szczeg jest potrzebny

    //data sub-chunk
    char m_Subchunk2ID[4];
    int m_Subchunk2Size;
    char * m_data;


    vector<Channel> m_Channels;
    int m_num_of_samples_per_channel_per_sec;
    double song_duration_in_sec;

    public:

        //functions
        ///////////////////
        WAVE_file(ifstream &s);   //trzeba sie jeszcze upewnic, ze strumien jest do pracy bin
        virtual ~WAVE_file();
        void View_The_header();
        void View_The_channels(int k = 20);
        void View_The_data();
        double get_song_duration_in_sec(){return song_duration_in_sec;}
    /*private:
        Wave_file_Manager m_Manager;// = Wave_file_Manager(m_Address); */
friend class Wave_file_Manager;

};



#endif // WAVE_FILE_H
