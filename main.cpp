#include <iostream>
#include <fstream>

#include "WAVE_file/WAVE_file.h"
#include "Wave_file_Manager.h"

#include <cstdlib>
//#include <complex>
#include"simple_fft/fft_settings.h"
#include"simple_fft/fft.h"
#include <time.h>
#include"Note.h"
#include<cmath>

using namespace std;

///////////////////////////////////////////
/*
void swap_bigEndian_to_little(char* bit,int amount){
    char temp[amount];
    for (int i = 0; i<amount; ++i) temp[i] = bit[i];
    int index = amount- 1;
    for(int j = 0; j<amount; ++j) {bit[j] = temp[index--] ;}

}*/
template <typename T> void View_the_array (T* type, int n){
    cout<<endl;
    for (int i = 0; i < n; ++i){
        cout<<type[i]<<"\t";
    }
    cout<<endl;
}




int main()
{
    ifstream s("akord.wav",ios::in | ios::binary);
    if(!s){
        cout<<"Can`t open the file :(\n";
        return 1;
    }

    WAVE_file music_file(s);

    ///
       //  swap_bigEndian_to_little(reinterpret_cast<char*> (&music_file.m_Chunk_ID),sizeof(music_file.m_Chunk_ID));
    ///
    s.close();

    music_file.View_The_header();
    music_file.View_The_data();

    Wave_file_Manager music_manager;
    music_manager.set_wav_file(&music_file);
    music_manager.Create_Channels();

    music_file.View_The_channels();

   /*////////////   Transformacja_Fouriera///////////)
    double* chanel_0 = music_manager.get_data_from_channel_as_double(0);    //pamietaj, zeby zwolnic pamiec
    double* chanel_1 = music_manager.get_data_from_channel_as_double(1);
//////////// creating channels of complex numbers for FFT
    complex<double>* temp_arrayA = new complex<double>[music_manager.get_size_of_channel()];
    complex<double>* temp_arrayB = new complex<double>[music_manager.get_size_of_channel()];

    for (int i = 0; i < music_manager.get_size_of_channel(); ++i){
        temp_arrayB[i] = complex<double>(chanel_0[i],0.0);

    }

    //const char * error_desc;
    //bool test = simple_fft::FFT(temp_arrayB,temp_arrayA,music_manager.get_size_of_channel(),music_manager.get_size_of_channel(),error_desc);
    //if(test)
View_the_array<double>(chanel_0,15);
    */


///symulation of the FFT output. Normally, the FFT will be proceed ON the buffer, which is just a piece of the whole song. For now, The FFT is beeing omitted.
    srand(time(nullptr));
/// buildying the "fake" channel
     double* fake_channel = new double[4096*100 + 200];    // 4096*100    4096 samples is the size of the buffer. Normally we have 44100Hz in a WAVE file, that is 44100 samples per second. So for now, we extracting frquencies from 4096/44100 of second, e.i circa 0,1s. Let it be ~10 s
    for (int i = 0; i < 4096*97; ++i) fake_channel[i] = 0;
    for (int i = 4096*97; i < 4096*100; ++i) fake_channel[i] = static_cast<double>(rand()% 20000) + static_cast<double>((rand()%100)/100.0);
    for (int i = 4096*100; i < 4096*100 + 200; ++i) fake_channel[i] = 0;
    ///inczej inicjalizowac, skoro to ma byc zawartsc po fft, to niech to zawiera góra trzy/ cztery czestot na 4096 komorek                                                                      //4186 - 28  <= full range of piano => (4435 - 28) + 28)
    View_the_array<double>(fake_channel,15);

    music_manager.set_fake_channel(fake_channel);
    music_manager.samples_of_fake_channel = 4096*100 + 200;
    music_manager.calls_of_buffer = ceil(static_cast<double>(music_manager.samples_of_fake_channel)/2048.0 );

    /*const char* animation[26] = {"********                        ********", "*********                       ********",
                "******** *                      ********", "********  *                     ********", "********   *                    ********",
                "********   *                    ********", "********    *                   ********","********     *                  ********",
                "********      *                 ********", "********       *                ********", "********        *               ********",
                "********         *              ********", "********          *             ********", "********           *            ********",
                "********            *           ********", "********             *          ********", "********              *         ********",
                "********               *        ********", "********                *       ********", "********                 *      ********",
                "********                  *     ********", "********                   *   ********", "********                    *  ********",
                "********                     * ********", "********                      *********", "********                       ********"};
    int a{0};*/
    cout<<"\nCreating Sheet\n";
    while (music_manager.Update() ){
        //cout<< animation[a++%26] << '\r'; //to display the animation properly, mark as a comment cout instruction, in Update() function

    }

    music_manager.View_the_Sheet();

    cout<<endl<<Note::Note_name_as_Cstring[21];
    cout<<endl<<Note::Note_name_as_Cstring[0];

    cout<<"\nPerforming optimalization\n";

    music_manager.optimize_the_sheet();
    music_manager.View_the_Sheet();

    delete []fake_channel;
    return 0;
}
