#include<iostream>
#include<fstream> //for ifstream
#include<stdlib.h>
#include<string.h>
#include<ctype.h> //for isalnum
#include <vector>
using namespace std;
//array of keywords
int isKeyword(char buffer[]){
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"};
    int i, flag = 0;
    
    for(i = 0; i < 32; ++i){
        if(strcmp(keywords[i], buffer) == 0){ //Compare two strings
            flag = 1;
            break;
        }
    }
    
    return flag;
}

int main(){
    vector<char> g1;
    char ch, buffer[15], operators[] = "*+-=/><%";
    char separators[] = "'(){}[],.:;";
    ifstream fin("sample_text.txt");
    int i,j=0,k;
    //int hello = 5;
    if(!fin.is_open()){
        cout<<"error while opening the file\n";
        exit(0);
    }
    cout << "Tokens - Lexemes \n";
    while(!fin.eof()){
        ch = fin.get();
        g1.push_back(ch);
        
    }
    fin.close();
//    for (auto i = g1.begin(); i != g1.end(); ++i)
//        cout << *i << " ";
    for (auto i = g1.begin(); i != g1.end(); ++i){
        for ( int a = 0; a < 8; a++){
            if (*i == operators[a]) {
                cout << "operator " << *i << endl;
            }
        }
        for (int b = 0; b < 11; b++) {
            if (*i == separators[b]) {
                cout << "separator " << *i << endl;
            }
        }
        if ( *i == '!')
        {
            for (auto z = i+1; z != g1.end(); ++z){
                if (*z == '!'){
                    //set the outer counter to the new
                    i = z; //this should skip everything between comments
                }
            }
        }
//        if (*i == ' ') {
//            cout << "separator sp" << endl;
//        } this recognizes if the char is a space
        if(isalnum(*i)){
            buffer[j++] = *i;
        }
        else if((*i == ' ' || *i == '\n') && (j != 0)){
            buffer[j] = '\0';
            j = 0;
            
            if(isKeyword(buffer) == 1)
                cout << "Keyword " << buffer << endl;
            else
                cout << "Identifier " << buffer << endl;
        }
    }
    //system("pause");
    return 0;
}

