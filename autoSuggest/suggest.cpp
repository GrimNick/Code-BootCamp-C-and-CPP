#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <map>

using namespace std;

string fileName = "google-10000-english.txt";


bool checkIfExist(int num, vector<int> addedIndex){
    if(addedIndex.empty()) return false;

    for(int i=0;i<addedIndex.size(); i++){
        if(num == addedIndex[i]) return true;
    }
    return false;;
}

vector<string> sampleWords(){
    ifstream fileEng(fileName);
    if(!fileEng) cerr<<"No file of such name found :" <<fileName<<"\n";
    string line;
    vector<string> words;
    while(getline(fileEng,line)){
        words.push_back(line);
    } 
    vector<string> sampledWords;


    srand(time(0));
    int wordsSampled =0;
    vector<int> addedIndex;
    int num;
    while(wordsSampled<2500){

        num = rand() % 10000;
        if(words[num].length() <3) continue;
        if(checkIfExist(num,addedIndex)) continue;
        addedIndex.push_back(num);
        wordsSampled++;
        sampledWords.push_back(words[num]);
    }

    fileEng.close();
    return sampledWords;
}


map<string, vector<string>> getn_grams(vector<string> words){
    map<string, vector<string>> n_grams;
    for(int j=0;j<words.size();j++){
        vector<string> brokeDownString;
        int k =2;
        for(int k=2;k<=words[j].length();k++){
        for(int i=0;i +k <= words[j].length();i++){
            
                brokeDownString.push_back(words[j].substr(i,k));
            }   
        }
        n_grams.insert({words[j],brokeDownString});
    }

    return n_grams;
}

int main(){
    vector<string> words = sampleWords();
    cout<<"\n******** Sampled words are : *******\n" <<endl;
    for(int i=0;i<words.size(); i++) cout<<words[i]<<",";
    cout<<"\n\n**** End of samppled words *****\n\n";
    map<string, vector<string>> ngram = getn_grams(words);
    cout<<"\n******** n-gram of words are : *******\n" <<endl;

    for(int i=0;i<2;i++){
        vector<string> toDisplayString = ngram[words[i]];
        cout<<words[i]<<"\t";
        for(int j=0;j<toDisplayString.size();j++){
            cout<< toDisplayString[j]<<" | ";
        }
        cout<<"\n";
    }

    cout<<"\n\n**** End of n-gram of words *****\n\n";

    return 0;
}