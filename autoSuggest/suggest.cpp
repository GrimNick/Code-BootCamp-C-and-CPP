/**
    
    Created by: Newton Shahi Thakuri
    Date: 2025 -05 - 25 

*/

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

vector<string> getSingleGrams(string word){
        vector<string> brokeDownString;
        for(int k=2;k<=word.length();k++){
        for(int i=0;i +k <= word.length();i++){
            
                brokeDownString.push_back(word.substr(i,k));
            }   
        }
        return brokeDownString;
}

//gives n gram from 2 to definition
map<string, vector<string>> getn_grams(vector<string> words){
    map<string, vector<string>> n_grams;
    for(int j=0;j<words.size();j++){
        vector<string> brokeDownString = getSingleGrams(words[j]);
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

map<string,int> buildNGramIndex(const map<string, vector<string>>& ngrams){
    map<string,int> ngramIndex;
    int idx=0;
    for(const auto p:ngrams){
        for(const string ng:p.second){
            if(ngramIndex.find(ng) == ngramIndex.end()){
                ngramIndex[ng] = idx ++;
            }
        }
    }
    return ngramIndex;
}

vector<double> vectorizeWord(const vector<string> wordNgrams, const map<string, int>& ngramIndex){
    vector<double> vec(ngramIndex.size(),0.0);
    for(const string ng:wordNgrams){
        auto it = ngramIndex.find(ng);
        if(it!=ngramIndex.end()){
            vec[it->second] += 1.0;
        }
    }
    return vec;
} 

double cosineSimilarity(const vector<double> A,const vector<double> B){
    if(A.size() != B.size()){
        cerr<< "Vectors must be the same size"<<endl;
        return 0.0;
    }

    double dot =0.0,normA =0.0,normB=0.0;
    for( size_t i=0;i<A.size();i++){
        dot+=A[i] * B[i];
        normA += A[i]*A[i];
        normB += B[i]*B[i];
    }
    if(normA ==0 || normB ==0) return 0.0;
    return dot/(sqrt(normA)* sqrt(normB));

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


    map<string,int> ngramIndex = buildNGramIndex(ngram);

    cout<<"\n ------total unique n-gram:"<<ngramIndex.size()<<"\n\n";

    vector<vector<double>> dictVectors;
    for(string w:words){
        dictVectors.push_back(vectorizeWord(ngram[w],ngramIndex));
    }

    //input
    string inputWord;
    cout<<"~~~~~ Enter a word to compare and get auto suggest ~~~"<<"\n\n => ";
    cin>> inputWord;

    vector<string> inputNGrams = getSingleGrams(inputWord);

    //vectorize
    vector<double> inputVec = vectorizeWord(inputNGrams,ngramIndex);
    
    //compute cosine against all dict words
    vector<pair<double,int>> similarityScores;
    for(int i=0;i<dictVectors.size();i++){
        double score = cosineSimilarity(inputVec, dictVectors[i]);
        similarityScores.push_back({score,i});
    }

    //sort descending
    sort(similarityScores.begin(), similarityScores.end(), [](auto& a, auto& b){
        return a.first > b.first;
    });

    cout<<"\n top 10 matches :\n";
    for(int i=0; i<10 && i<similarityScores.size(); i++){
        cout<< words[similarityScores[i].second] << " ( Score : " <<similarityScores[i].first <<")\n";
    }

    return 0;
}