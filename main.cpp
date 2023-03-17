#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool check_register(string uname, string known_unames);
void register_user(string uname, string known_unames);
void open();
void open(string uname);
void deny_access();

int main(){
    string known_unames = "known_users.txt";
    string uname, request_access;
    bool user_exists;

    cout << "Enter Username: ";
    cin >> uname;

    user_exists = check_register(uname, known_unames);
    if(user_exists){
        open();
    }
    else{
        cout << "You are a new user, would you like to register (yes or no)? ";
        cin >> request_access;
        if(request_access == "yes"){
            register_user(uname, known_unames);
            open(uname);
        }
        else{
            deny_access();
        }
    }

    return 0;
}

void open(){
    cout << "Access Granted" << endl;
}

void open(string uname){
    cout << "Welcome " << uname << " Access Granted" << endl;
}

void deny_access(){
    cout << "Access Denied" << endl;
}

void register_user(string uname, string known_unames){
    /*
    Parameters:
        uname (string): the username entered through the console
        known_unames (string): the name of the text file that records the known users
    Return:
        void
    */
    
    ofstream fileobj (known_unames);
    if(fileobj.is_open()){
        fileobj << uname << '\n'; // write the username and start a new line
        fileobj.close();
    }
    else{
        cout << "ERROR OPENING " << known_unames << endl;
    }
}

bool check_register(string uname, string known_unames){
    /*
    Parameters:
        uname (string): the username entered through the console
        known_unames (string): the name of the text file that records the known users
    Return:
        user_found (bool): true if the user is listed in known_users.txt
    */
    bool user_found = false;
    string line;
    
    //1. Open up the file with known users
    ifstream infile (known_unames);
    if(infile.is_open()){
        while(getline(infile, line)){
            if(line == uname){
                user_found = true;
                break;
            }
        }
        infile.close();
    }
    else{
        cout << "ERROR OPENING " << known_unames << endl;
    }

    return user_found;
}