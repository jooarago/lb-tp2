#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <map>
using namespace std;

/**
// models contents of file 
class DataStorageManager()
{

}
**/
// models stop word filter
class StopWordManager
{   
    public:

        static vector <string> _stop_words;
        // reads filepath = filename and add the words to _stop_words dictionary (Assuming the stop_words file does not repeat words)
        void init(string filename) {  
            fstream file;
            string word;
            file.open(filename.c_str());
            while (file >> word) {
                _stop_words.push_back(word);
            }

        }
        // checks if the word is a stop word
        bool check_word(string word) {
            bool result = true;
            for (int i=0; i<size(_stop_words); i++) {
                if (word.compare(_stop_words[i]) < 0) {
                    result = false;
                    break;
                }
            }
            return result;
        }

};

// keeps word frequency data
class WordFrequencyManager
{
    public:
        map <string, int> _word_freq;
        // icrement amount of the freq if the word is in the dictionary otherwise add the word to the dictionary with value 1
        void increment_amount(string word) {
            bool found = false;
            for (auto const& [k_word, freq] : _word_freq ){  
                if (k_word.compare(word) == 0) {
                    _word_freq[k_word]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                _word_freq[word] = 1;
            }
        }
};

class WordFrequencyController
{
    public:
        void dispatch(const string& input, const string& text)
        {
            if (input.compare("init") == 0)
            {
                WordFrequencyManager wfmanager;
                StopWordManager swmanager;
                swmanager.init("stop_words.txt");
                
                cout << "nice\n";
            }
        }
};

int main(int argc, char** argv)
{
    WordFrequencyController wfcontroller;

    ifstream inFile( argv[1] );
    string strInput;

    // reads content from file into strInput
    while (inFile)
    {    
        getline(inFile, strInput);
    }

    wfcontroller.dispatch("init", strInput);
    //wfcontroller.dispatch(['run']);

    inFile.close();
    
    return 0;
}