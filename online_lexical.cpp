#include<iostream>
#include<fstream> //for ifstream
#include<stdlib.h>
#include<string.h>
#include<ctype.h> //for isalnum
 
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
    char ch, buffer[15], operators[] = "*+-=/><%";
	char separators[] = "'(){}[],.:;!";
    ifstream fin("Text.txt");
    int i,j=0,k;
   //int hello = 5;
    if(!fin.is_open()){
        cout<<"error while opening the file\n";
        exit(0);
    }
	cout << "Tokens - Lexemes \n";
    while(!fin.eof()){
        ch = fin.get();
       
        for(i = 0; i < 8; ++i){
            if(ch == operators[i])
				cout << "Operator	=	" << ch << endl;
        }

		for (k = 0; k < 12; k++) {
			if (ch == separators[k])
				cout << "Separator	=	" << ch << endl;
		}
		if (ch == ' ') {
			cout << "Separator	=	" << ch << endl;
		}
        if(isalnum(ch)){
            buffer[j++] = ch;
        }
        else if((ch == ' ' || ch == '\n') && (j != 0)){
                buffer[j] = '\0';
                j = 0;
                               
                if(isKeyword(buffer) == 1)
					cout << "Keyword	=	" << buffer << endl;
                else
					cout << "Identifier	=	" << buffer << endl;
        }
       
    }
   
    fin.close();
	system("pause");
    return 0;
}
