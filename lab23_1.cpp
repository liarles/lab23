#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream source(filename);
    string textline;
    while (getline(source,textline)){
        string name;
        int a,b,c;
        char placeholder[100];
        if (sscanf(textline.c_str(), "%[^:]: %d %d %d", placeholder, &a, &b, &c) == 4) {
            name = placeholder;
            int total_score = a + b + c;
            names.push_back(name);
            scores.push_back(total_score);
            grades.push_back(score2grade(total_score));
        }
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    getline(cin, command); 
    while (command != "EXIT") { 
        string x = command;
        size_t start = 0;
        size_t end = x.find_first_of(" ");

        if (end != string::npos) { 
            command = x.substr(start, end - start);
            key = x.substr(end + 1); 
        } else {
            command = x;
            key = "";
        }
        break;
    }
}
void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, string key){
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == key) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    for (size_t i = 0; i < names.size(); i++) {
        if (grades[i] == toupper(key[0])) {
            if (!found) cout << "---------------------------------\n";
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";

}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
