#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>


using namespace std;

class UserLogin {
private:
    
    unordered_map< string, string > table;
    

public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and passWord
       
};

UserLogin::UserLogin() {
}

// COMPLETE THE FOLLOWING FUNCTIONS

void UserLogin::readIn(const string& filename) {
  ifstream fin;

   fin.open(filename);

   if(!fin.is_open())
   {
       return;
   }
  
   string search = "\t"; // search will be delimeter of tab 
   string userName, passWord, line; //initiallizing variables for UN PW and to store each line from txt file
   
  
   while (getline(fin,line))
   {
    size_t i = line.find(search); 
       
    userName = line.substr(0,i); 
    passWord = line.substr(i+1);
     
    cout<<"Username is:"<<userName<<" Password is:"<<passWord<<"\n\n"; //sanity check to verify UN and PW are populating correctly
     
        
    table[userName] = passWord;
      
   }
  return;
}

size_t UserLogin::numberOfUsers() {

     return table.size();

}

string UserLogin::passWordCheck(const string& userName) {

  //return table.find(userName) != table.end() ? table[userName] : "Non-existent User"; //<-this code works to but rewrote the below code when trying to troubleshoot
  
  std::unordered_map<std::string,string>::const_iterator got = table.find(userName);

  if (got == table.end())
    return "Non-existent User";
  else 
    return got->second;
}

size_t UserLogin::wordBucketIdMethod1(const string& userName) {

    return table.bucket(userName);

}

size_t UserLogin::wordBucketIdMethod2(const string& userName) {
    
    unsigned n = table.bucket_count();

   for (unsigned i = 0; i < n; i++) {
       for (auto it = table.begin(i); it != table.end(i); ++it)
           if (it->first == userName)
               return i;
     } 
  return n;
}

bool UserLogin::validateUser(const string& userName) {
    
    return table.find(userName) != table.end();
     
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord) { 
    
     auto userExists = table.find(userName) != table.end();

   if (userExists)
       return (table.find(userName)->second == passWord);

   return false;
      
 }
