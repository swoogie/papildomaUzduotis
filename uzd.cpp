#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>


using namespace std;

string symbols = "<>?,./:{}[]()+-='123456789";

struct word{
   int count = 1;
   vector<int> indicator;
};

void removeSymbolsFront(string &wrd){
   for(int i=0;i<symbols.size();i++){  
      if(wrd.front() == symbols[i] || wrd.front() == '"'){
         wrd.erase(wrd.begin());
         removeSymbolsFront(wrd);
      }
   }
}

void removeSymbolsBack(string &wrd){
   for(int i=0;i<symbols.size();i++){
      if(wrd.back() == symbols[i] || wrd.back() == '"'){
         wrd.erase(wrd.size() - 1);
         removeSymbolsBack(wrd);
      }
   }
}

bool isLink(string &wrd){
   for(int i=0;i<wrd.size();i++){
      if(wrd[i] == '.'){
         return true;
      }
   }
   if(wrd.substr(0,4) == "www." || wrd.substr(0,4) == "http"){
      return true;
   }
   else{
      return false;
   }
}
 
int main(){
   int lineNumber = 1;
   vector<string> links;
   map<string, word> words;
   fstream rd;
   rd.open("duom.txt");
   stringstream fileStream;
   fileStream << rd.rdbuf();
   rd.close();

   while(!fileStream.eof()){
      string buff;
      getline(fileStream, buff);
      stringstream lineStream(buff);

      while(!lineStream.eof()){
        lineStream >> buff;
        removeSymbolsFront(buff);
        removeSymbolsBack(buff);
        auto thing = words.find(buff);
        if(isLink(buff)){
           links.push_back(buff);
        }
        else if(thing==words.end() || words.size()==0){
            word newWord;
            newWord.indicator.push_back(lineNumber);
            words.insert(make_pair(buff,newWord));
        }
        else{
            thing->second.count++;
            thing->second.indicator.push_back(lineNumber);
        }
      }
      lineNumber++;
   }

   for(auto word : words){
        if(word.second.count <1 ) continue;
        cout<<word.first<<setw(15-word.first.size())<<word.second.count<<setw(14)<<"Eilutes: ";
        for(auto lineNumber : word.second.indicator){
            cout<<lineNumber<<" ";
        }
        cout<<endl;
    }
    
    cout<<"Nuorodos:\n";
    for(auto link : links){
        cout<<link<<endl;
    }

}