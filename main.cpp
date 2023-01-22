#include "main.hpp"
using namespace std;

/**
// models contents of file 
class DataStorageManager() {

}
**/
// models stop word filter
class StopWordManager {   
    public:
        vector<string> stop_words;
        StopWordManager(string filename) {  
            fstream file;
            string word;
            file.open(filename.c_str());
            while (file >> word) {
                transform(word.begin(), word.end(), word.begin(), ::tolower); //garantir q esteja tudo minúsculo para comparar depos
                stop_words.push_back(word);
            }
        }
        bool is_stop_word(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower); //deixar minusculo pq stop_word ta assim
            for (string stop_word: stop_words) {
                if (word.compare(stop_word) == 0) {
                    return true;
                }
            }
            return false;
        }
};

// keeps word frequency data
class WordFrequencyManager {
    public:
        map <string, int> word_freq;

        // icrement amount of the freq if the word is in the dictionary otherwise add the word to the dictionary with value 1

        void increment_amount(string word) {
            bool found = false;

            for (auto const& [key_word, freq] : word_freq ){ 

                if (key_word.compare(word) == 0) {
                    word_freq[key_word]++;
                    found = true;
                    break;
                }
                
            }
            if (!found) {
                word_freq[word] = 1;
            }
        }
        
        map<string, int> getWordFreq() {return word_freq;};
};

class WordFrequencyController {
    public:
        WordFrequencyManager wfmanager;
        StopWordManager swmanager = StopWordManager("stop_words.txt");
        void showFreq() {               
            for (auto const& [key_word, freq] : wfmanager.getWordFreq()) {  
                cout << key_word << ": "<< freq << endl;
            }
        }
        void run(string phrase) {
            regex regex("[^a-zA-Z]+"); //apenas lê palavras
            vector<string> phrase_vector(
                sregex_token_iterator(phrase.begin(), phrase.end(), regex, -1), 
                sregex_token_iterator()
            );
            for (auto &word: phrase_vector) {
                if (swmanager.is_stop_word(word)){
                    showFreq();
                } else {
                    wfmanager.increment_amount(word);
                }
            }
        }
};

int main(int argc, char** argv) {
    

    ifstream inFile( argv[1] );
    string phrase;

    // reads content from file into strInput

    int count = 0;
    WordFrequencyController wfcontroller;
    WordFrequencyManager wfmanager;
    while (count < 3) // while (inFile)
    {    
        getline(inFile, phrase);
        cout << phrase << endl;
        wfcontroller.run(phrase);
        ++count;
    }

    inFile.close();
    
    return 0;
}