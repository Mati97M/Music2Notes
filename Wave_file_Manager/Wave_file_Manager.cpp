#include "Wave_file_Manager.h"
#include "Sheet.h"
#include <algorithm>


//////////////////////////////////////////////////////////////

Wave_file_Manager::Wave_file_Manager(WAVE_file* p): wav_file {p},size_of_buffer{2048}, current_call_of_buffer{0}
{
    //ctor
    if (wav_file == nullptr) cout<<"\nCtor - warning: wav_file of Wave_file_Manager is empty\n";
    buffer = new double[size_of_buffer];

    music_score = new Sheet;
    if(music_score -> set_wfm(this)) cout << "\nWFM set in sheet\n";
    else cout << "\nWarning: WFM is not set in sheet\n";


}
void Wave_file_Manager::Create_Channels()
{
    int temp = static_cast<int>(wav_file->m_NumChannels);
    int cells_num{(wav_file->m_Subchunk2Size)/2};

    /// creating chanels
    ///polluting channel from WAVE_file.m_data,
    if (wav_file->m_NumChannels == 1){
            Channel c;
            for (int i = 0; i < cells_num; ++i){
                c.push_back((reinterpret_cast<int16_t*>(wav_file->m_data))[i]); }

            wav_file->m_Channels.push_back(c);
    }
    else{
            while(temp){

                ///polluting channels from WAVE_file.m_data
                Channel c;
                for (int i = temp -1; i < cells_num; i += wav_file->m_NumChannels){
                    c.push_back((reinterpret_cast<int16_t*>(wav_file->m_data))[i]); }
                wav_file->m_Channels.push_back(c);
                temp--;
                }

    }
    ///destroying WAVE_file.m_data, as not necessary. Chanels instead
      delete [](wav_file->m_data);
   cout<<"\nDeleting m_data for memory optimalization\n";

    //wav_file->~WAVE_file();
}
//////////////////////////////////////////////////////////
int Wave_file_Manager::get_size_of_channel(int n)
{
    auto num_of_Channels = wav_file->m_Channels.size();
    if (n <= num_of_Channels && n >=0 ){

       return wav_file->m_Channels[n].size();
    }
    else {
            cout<< "\nwrong number of channel\n";
            return -2;}

}

//////////////////////////////////////////////////////////

void Wave_file_Manager::ShortToReal(const signed short* shrt,double* real,int siz)
{
	for(int i = 0; i < siz; ++i)
	{
		real[i] = shrt[i] / 32768.0;
	}
}

double* Wave_file_Manager::get_data_from_channel_as_double(int n)
{
    auto num_of_Channels = wav_file->m_Channels.size();
    if (n <= num_of_Channels && n >=0){

        /// creating new array - we dont overwrite the original,which is even of a different type
        double* a_of_d  = new double[wav_file->m_Channels[n].size()];
        ShortToReal(reinterpret_cast<int16_t*>(wav_file->m_Channels[n].data()), a_of_d , wav_file->m_Channels[n].size());
        arrays_of_d.push_back(a_of_d);
        return a_of_d;
    }
    else {
            cout<< "\nwrong number of channel\n";
            return nullptr;}

}
/////////////////////////////////////////////////////////////////////////
Wave_file_Manager::~Wave_file_Manager() {
      for (auto a: arrays_of_d){
            cout<<"\ndeleting double arrays\n";
            delete []a;
      }
      delete []buffer;
      if (!wav_file) cout << "Destructor: wav_file of Wave_file_Manager is empty";
      else wav_file = nullptr;
        cout<<"\nDestructor of Wave_file_Manager has done his job\n";
       }
/////////////////////////////////////////////////////////////////////////
bool Wave_file_Manager::fill_the_buffer() {

    //filling the buffer from a curent block of samples
//vector<double> test; /// wyslemy wektor taki sam jak bufor, ale bez sortowania
   if(current_call_of_buffer != calls_of_buffer - 1  ){

    for (int i = 0; i < size_of_buffer; ++i){
        buffer[i]  = fake_channel[current_call_of_buffer * size_of_buffer +i ];
       // test.push_back(buffer[i]);///cos jest nie ok!!!!!!   to chyba nie kwestia sortowania. nadal sa te same wartosci w wektorach wewnetrznych. Blad logiczny
        }
   }
   else {
            cout << "\nsome padding to the buffer\n";
            buffer_padding = size_of_buffer - (samples_of_fake_channel % size_of_buffer);
            for (int i = 0; i < size_of_buffer - buffer_padding; ++i){
                buffer[i]  = fake_channel[current_call_of_buffer * size_of_buffer +i ];
        }
            for (int i = buffer_padding; i > 0; --i ) buffer[size_of_buffer - i] = 0;
   }
    ++current_call_of_buffer;
    //cout<<endl<<current_call_of_buffer<<" filling the buffer";

///performing FFT on buffer.......fft(buffer,size_of_buffer);  sth like that
/// ....................
/// ascending sorting. First we want add the lowest notes. Ordung muss sein!
   vector<double> sorted_buffer;
   sorted_buffer.insert(sorted_buffer.begin(), buffer, buffer + size_of_buffer);
   //vector<double> sorted_buffer (buffer, buffer + sizeof(buffer) / sizeof(double)); tez tak mozna
    sort(sorted_buffer.begin(),sorted_buffer.end());

/// now we have, in the buffer, the frequencies, which were used in that piece of song
///pushing the notes to the sheet

music_score-> export_notes_to_sheet(sorted_buffer);
//music_score->export_notes_to_sheet(test);


/// is there anything left to take?
 return !the_last_call_of_buffer(); //checking function

}
/////////////////////////////////////////////////////////////////////////
bool Wave_file_Manager::Update()
{
    cout<< "\nremaining calls of buffer: " << calls_of_buffer - current_call_of_buffer;
    return fill_the_buffer();
}
/////////////////////////////////////////////////////////////////////////
bool Wave_file_Manager::the_last_call_of_buffer()
{
    return (current_call_of_buffer == calls_of_buffer);   // if no, we are still in the loop
}
/////////////////////////////////////////////////////////////////////////
void Wave_file_Manager::set_fake_channel(double* s)
{
    fake_channel = s;
    cout<< "\nfake channel set" << endl;
}
/////////////////////////////////////////////////////////////////////////
void Wave_file_Manager::View_the_Sheet()
{
    music_score -> Sheet::View_the_Sheet();
}
/////////////////////////////////////////////////////////////////////////

bool Wave_file_Manager::optimize_the_sheet()
{
    // aggregating the notes into bigger rhytmic values when it`s possible

    // removing silence from the begin and the end
    if ( !music_score->remove_the_silence()){
        cout<< "\nRemoving silence failed\n";
        return false;
    }
    return true;
}
