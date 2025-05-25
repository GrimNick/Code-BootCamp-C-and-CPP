
/**
    
    Created by: Newton Shahi Thakuri
    Date: 2025 -05 - 25 

*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

//Get from dictionary.txt. separated using lines.
//Make Sd set of dictionary words
vector<string> dictionary_words(){
    vector<string> words;
    ifstream fileDict("dictionary.txt");
    if(!fileDict){
        cerr <<"Dictionary file not found error.\n";
    }
    
    string line;

    while(getline(fileDict,line)){
       words.push_back(line);
    }
    fileDict.close();
    return words;
}

int num_input =0;
//Make St set of input words
vector<string> input_words(){
    vector<string> words;
    ifstream fileInput("input.txt");

    if(!fileInput){
        cerr <<"Input file not found error.\n";
    }
    char c;
    string l;
    while(fileInput.get(c)){
        if(c =='.' || c=='(' || c ==')' || c ==',' || c == ':' || c== ';' || c=='"' || c== '\'' || c=='[' || c==']' ||  (c >= '0' && c <= '9' ) || c== '!' || c=='\n') continue;
        if(c==' ' || c== '/'){
            words.push_back(l);
            num_input++;
            l="";
        }
        else{
            l+= tolower(c);
        }
        
    }
    if(!l.empty())
    words.push_back(l);


    fileInput.close();
    return words;
}

// Sw = St - Sd; . number of mispelled words set
int no_Missed = 0;
vector<string> misSpelled(vector<string> input, vector<string> dict){
    vector<string> words;
    bool found = false;
    for(int i=0;i<input.size();i++){
        for(int j=0;j<dict.size();j++){
            if((input[i]) == dict[j]) {
                found = true;
                break;
            }    
        }
        if(!found){
            words.push_back(input[i]);
            no_Missed++;
        }
        found = false;
    }

    return words;
}
int main(){
    vector<string> input_array = input_words();
    vector<string> dict_array = dictionary_words();
    cout<<"Input arrays :\n";
    for(int i =0;i<input_array.size(); i++){
        cout<<input_array[i]<<"\n";
    }

    cout<<"Dictionary arrays :\n";
    for(int j =0;j<dict_array.size(); j++){
        cout<<dict_array[j]<<"\n";
    }

    vector<string> misSpelled_array = misSpelled(input_array,dict_array);
    cout<<"\n *****Misspelled arrays (10) *****:\n";


    //do misSpelled_array.size() to see all
    for(int j =0;j<10 ; j++){
        cout<<misSpelled_array[j]<<"\n";
    }

    cout<<"\n Total input words : " << num_input <<" || Total mis spellings : " << no_Missed <<"\n";

    return 0;
}
// Total input words : 2230 || Total mis spellings : 409