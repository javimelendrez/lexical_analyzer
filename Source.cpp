#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <vector>
#include <string>
using namespace std;
vector<string> toke;
vector<char> lex;
int token_index = 0;
string token(int i) {
    return toke[i];
}
char lexer(int i) {
    return lex[i];
}
int isKeyword(char buffer[]) {
    char keywords[32][10] = { "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while" };
    int i, flag = 0;
    
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    
    return flag;
}
//function for assignment
bool assignment(int i) {
    if (toke[i] == "identifier")
    {
       // token_index++;
        if (toke[i].size() > i + 1 && toke[i+1] == "=")
        {
            //token_index++;
            if (toke[token_index] == "identifier")
            {
                cout << "S --> i = " << endl;
//            }else
//            {
//                cout << "error was expecting identifier" << endl;
//                exit(0);
//            }
//        }else
//        {
//            token_index--;
//            exit(0);
//        }
                if (problem_set_e(i+2)) {
                    cout << "E" << endl;
                    return true;
                }
            }
    }
        return false;
}
void problem_set_f(int i) {
    if (lex[i] == '(') {
        if (i+1 < toke.size() && problem_set_e(i+1)) {
            if (i+2 < toke.size() && problem_set_e(i+2)) {
                cout << "(E)" << endl;
                return true;
            }
        }
    }else if(toke[i] == "identifier")
    {
        cout << "id" << endl;
        return true;
    }
    return false;
}
void problem_set_r() {
    if (lex[i] == '*')
    {
        cout << "*" << endl;
        if ( i + 1 < toke.size() && problem_set_f(i+1)) {
            cout << "F" << endl;
            if ( i + 2 < toke.size() && problem_set_r( i + 2)) {
                cout << "R" << endl;
                return true;
            }
        }
    }else if (lex[i] == '/')
    {
        cout << "/" << endl;
        if ( i + 1 < toke.size() && problem_set_f( i + 2)) {
            cout << "F" << endl;
            if (i + 2 < toke.size() && probelem_set_r(i + 2)) {
                cout << "R" << endl;
                return true;
            }
        }
    }else
    {
        if (i + 1 == toke.size()) {
            cout << "Epsilon" << endl;
            return true;
        }
    }else
    {
        return false;
        
    }
}
bool problem_set_t(int i)
{
    if (probelem_set_f(i)) {
        if (i + 1 < toke.size() && problem_set_r(i + 1)) {
            cout << "T --> F R" << endl;
            return true;
        }
    }
    return false;
}
bool problem_set_q(int i)
    {
    if (lex[i] == '+')
    {
        cout << "+" << endl;
        if ( i + 1 < toke.size() && problem_set_t(i+1)) {
            cout << "T" << endl;
            if ( i + 2 < toke.size() && problem_set_q( i + 2)) {
                cout << "Q" << endl;
                return true;
            }
        }
    }else if (lex[i] == '-')
    {
        cout << "-" << endl;
        if ( i + 1 < toke.size() && problem_set_t( i + 2)) {
            cout << "T" << endl;
            if (i + 2 < toke.size() && probelem_set_t(i + 2)) {
                cout << "Q" << endl;
                return true;
            }
        }
    }else
    {
        if (i == toke.size() - 1) {
            cout << "Epsilon" << endl;
            return true;
        }
    }else
    {
        return false;
        
    }
        
    }
//function for problem set E
bool problem_set_e(int i)
{
    if (problem_set_t(i))
    {
        cout << "E --> T" << endl;
        if (problem_set_q(i+1))
        {
            cout << "Q" << endl;
            return true;
        }
    }
    return false;
}
bool analyze(int i)
{
    return assignment(int i) || problem_set_q(int i) || problem_set_t(int i) || problem_set_q(int i)  || problem_set_f(int i) || problem_set_r(int i);
}

int main() {
    char ch, buffer[15], operators[] = "+-*/%=;";
    ifstream fin("text.txt");
    int i, j = 0;
    
    if (!fin.is_open()) {
        cout << "error while opening the file\n";
        exit(0);
    }
    
    while (!fin.eof()) {
        ch = fin.get();
        
        for (i = 0; i < 6; ++i) {
            if (ch == operators[i])
            {
                //cout << ch << " is operator\n";
                lex.push_back(ch);
                toke.push_back("operator");
            }
        }
        
        if (isalnum(ch)) {
            buffer[j++] = ch;
        }
        else if ((ch == ' ' || ch == '\n') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            
            if (isKeyword(buffer) == 1)
                cout << buffer << " is keyword\n";
            else
            {
                //cout << buffer << " is indentifier\n";
                string temp = buffer;
                lex.push_back(temp.at(0));
                toke.push_back("identifier");
            }
        }
        
    }
    for (int i = 0; i < toke.size(); i++)
    {
        cout << toke[i] << " " << lex[i] << endl;
    }

    
    fin.close();
    system("pause");
    if (!analyze(0)) {
        cout << "error";
    }
    return 0;
}




}
