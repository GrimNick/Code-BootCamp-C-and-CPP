#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

string fileName = "google-10000-english.txt";

//compares to find if num exists in vector
bool checkIfExist(int num, vector<int> addedIndex){
    if(addedIndex.empty()) return false;

    for(int i=0;i<addedIndex.size(); i++){
        if(num == addedIndex[i]) return true;
    }
    return false;;
}

//returns samlping using uniform distribution
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

//gives n gram from 2 to definition
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



vector<string> dictVectorizer(map<string, vector<string>> ngram,vector<string> keyWords){
    vector<string> words;
    for(int i=0;i<ngram.size();i++){
        vector<string> col = ngram[keyWords[i]];
            
        for(int j=0;j<col.size();j++){
            words.push_back(col[j]);
        }
    }
    return words;
}



map<string, int> getFregMap(vector<string> words){
    map<string, int> FregMap;
    //allnWords.size()
    for(string word: words){
        FregMap[word]++;
    }
    return FregMap;
}

int main(){
    vector<string> words = sampleWords();
    cout<<"\n******** Sampled words are : *******\n" <<endl;
    
    //do words.size() to see all

    for(int i=0;i<100; i++) cout<<words[i]<<",";
    cout<<"\n\n**** End of samppled words *****\n\n";
    map<string, vector<string>> ngram = getn_grams(words);
    cout<<"\n******** n-gram of words are : *******\n" <<endl;

    //do ngram.size() for displpaying all words n grams
    for(int i=0;i<4;i++){
        vector<string> toDisplayString = ngram[words[i]];
        cout<<words[i]<<":\t";
        for(int j=0;j<toDisplayString.size();j++){
            cout<< toDisplayString[j]<<" | ";
        }
        cout<<"\n\n";
    }

    cout<<"\n\n**** End of n-gram of words *****\n\n";


    vector<string> allnWords =  dictVectorizer(ngram,words);
    cout<<"\n******** Vectorized n gram words are : *******\n" <<endl;
    //do allnWords.size() to see all
    for(int i =0;i<100;i++){
        cout<<allnWords[i]<<" | ";
    }

    cout<<"\n\n**** End Vectorized n gram words *****\n\n";

    map<string, int> freqNGram = getFregMap(allnWords);

    cout<<"\n******** frequency of n gram words are : *******\n" <<endl;
    //do allnWords.size() to see all
    for(int i =0;i<100;i++){
        cout<<allnWords[i]<<" | ";
    }

    //for sorting in descending
    vector<pair<string,int>> vec(freqNGram.begin(),freqNGram.end());
    sort(vec.begin(),vec.end(),[](const pair<string,int>& a,const pair<string,int>& b){
        return a.second>b.second;
    });

    int stopper=0;
    for(auto p:vec){
        cout<<"Key : "<<p.first <<"| Value: "<<p.second<<endl;
        if(stopper==10) break; //remove this to see value of all.
        stopper++;
    } 
    cout<<"\n\n**** End frequency of n gram words *****\n\n";


    return 0;
}