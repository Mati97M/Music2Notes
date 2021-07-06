#include "WAVE_file.h"
#include <iostream>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////
WAVE_file::~WAVE_file()
{
   if(m_data) {
            delete []m_data; //dtor
   cout<<"\ndtor \tDeleting m_data for memory optimalization\n";
   }
   else cout<< "\ndtor\n";
   cout<<"\nWAVE_file::~WAVE_file() has done his job\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////
WAVE_file::WAVE_file(ifstream & s): m_Address{this}
{
    try{

    s.read( reinterpret_cast<char*> (&m_Chunk_ID), sizeof(m_Chunk_ID));
    s.read(  reinterpret_cast<char*> ( &m_Chunk_Size), sizeof(m_Chunk_Size));
    s.read( reinterpret_cast<char*> ( &m_Format_Code), sizeof(m_Format_Code));
    s.read(  reinterpret_cast<char*> ( &m_Subchunk1_ID), sizeof(m_Subchunk1_ID));
    s.read(  reinterpret_cast<char*> ( &m_Subchunk1_Size) ,sizeof(m_Subchunk1_Size));
    s.read( reinterpret_cast<char*> ( &m_AudioFormat), sizeof(m_AudioFormat));
    s.read(  reinterpret_cast<char*> ( &m_NumChannels), sizeof(m_NumChannels));
    s.read(  reinterpret_cast<char*> ( &m_SampleRate), sizeof(m_SampleRate));
    s.read(  reinterpret_cast<char*> ( &m_ByteRate), sizeof(m_ByteRate));
    s.read(  reinterpret_cast<char*> ( &m_BlockAlign), sizeof(m_BlockAlign));
    s.read(  reinterpret_cast<char*> ( &m_BitsPerSample), sizeof(m_BitsPerSample));

    s.read(  reinterpret_cast<char*> ( &m_Subchunk2ID), sizeof(m_Subchunk2ID));
    s.read(  reinterpret_cast<char*> ( &m_Subchunk2Size), sizeof(m_Subchunk2Size));



    if(!s){
            DataTransferEXCPT excpt;
            throw excpt;}
    }
    catch(DataTransferEXCPT excpt)
    {
        cout<< "Stream is broken! Couldn`t read the header\n";
    }

    m_data = new char[m_Subchunk2Size];
    try{

    s.read( m_data, m_Subchunk2Size );
    if(!s) {
            DataTransferEXCPT excpt2;
            throw excpt2;}
    }
    catch(DataTransferEXCPT excpt2)
    {
        cout<< "Stream is broken. Couldn`t read the data!\n";
    }

     m_num_of_samples_per_channel_per_sec = static_cast<int>(m_SampleRate/m_NumChannels);

    song_duration_in_sec = static_cast<double>(m_Subchunk2Size) / static_cast<double>(m_ByteRate);


}
////////////////////////////////////////////////////////////////////////////////////////////////
void WAVE_file::View_The_header()
{
    cout<<"music_file.m_Chunk_ID\t"<<m_Chunk_ID<<endl
        <<"music_file.m_Chunk_Size\t"<<m_Chunk_Size<<endl
        <<"music_file.m_Format_Code\t"<<m_Format_Code<<endl
        <<"music_file.m_Subchunk1_ID\t"<<m_Subchunk1_ID<<endl
        <<"music_file.m_Subchunk1_Size\t"<<m_Subchunk1_Size<<endl
        <<"music_file.m_AudioFormat\t"<<m_AudioFormat<<endl
        <<"music_file.m_NumChannels\t"<<m_NumChannels<<endl
        <<"music_file.m_SampleRate\t"<<m_SampleRate<<endl
        <<"music_file.m_ByteRate\t"<<m_ByteRate<<endl
        <<"music_file.BlockAlign\t"<<m_BlockAlign<<endl
        <<"music_file.BitsPerSample\t"<<m_BitsPerSample<<endl

        <<"music_file.m_Subchunk2ID\t"<<m_Subchunk2ID<<endl
        <<"music_file.m_Subchunk2Size\t"<<m_Subchunk2Size<<endl
        <<"m_num_of_samples_per_channel_per_sec\t"<<  m_num_of_samples_per_channel_per_sec<<endl
        <<"song_duration_in_sec\t"<< song_duration_in_sec<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void WAVE_file::View_The_data()
{
    for (int i = 0; i < 30; ++i){ //m_Subchunk2Size/2; ++i){
        cout << reinterpret_cast<int16_t*>(m_data)[i]<<'\t';
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////
void WAVE_file::View_The_channels(int k){
    if (k <= m_Channels[0].size()){
            for (int i = 0; i < m_Channels.size(); ++i){
            cout<<"\nChannel "<<i<<'\n';
        for (int j = 0; j < k; ++j)          //int16_t c: m_Channels[i]){
            cout<<m_Channels[i][j]<<"\t";
        }
        cout<<endl;
    }
    else cout<<"\nGiven number is bigger than the number of samples\n";
}
