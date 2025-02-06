#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <cstdlib>

bool is_number(const std::string& s){
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

std::int64_t parseFile(const std::string &filename){
    std::ifstream file(filename);
    if(!file.is_open())
        exit(1);

    std::string line;
    std::int64_t result = 0;

    bool do_enabled = true;
    bool firsttime = true;

    while(std::getline(file, line)){
        if(line.empty())
            continue;

        std::string word = "mul(";
        std::int64_t pos = line.find(word, 0);

        std::int64_t rightnum = 0;
        std::int64_t leftnum = 0;

        std::int64_t dontpos = line.find("don\'t()");
        std::int64_t dopos = line.find("do()");
        
        bool doisfirt;

        if(firsttime){
            if(pos < dontpos){
                doisfirt = true;
                dopos = 0;
            }
            else{
                if(dontpos == -1){
                    doisfirt = true;
                    dopos = 0;
                }
                else{
                    doisfirt = false;
                    dontpos = 0;
                }
            }
            firsttime = false;
        }

        while(pos != (std::int64_t)std::string::npos){
            if(doisfirt){
                if((pos >= dopos) && (dopos != -1)){
                    do_enabled = true;
                    
                    dopos = line.find("do()", dopos + 1);
                    
                }

                if((pos > dontpos) && (dontpos != -1)){
                    do_enabled = false;

                    dontpos = line.find("don\'t()", dontpos + 1);
                }
            }
            else{
                if((pos >= dontpos) && (dontpos != -1)){
                    do_enabled = false;

                    dontpos = line.find("don\'t()", dontpos + 1);
                }
                if((pos > dopos) && (dopos != -1)){
                    do_enabled = true;

                    dopos = line.find("do()", dopos + 1);
                }

            }

//////////////////////////////////////////////////////////////////////////////////////////////////////            
            if(!do_enabled){
                pos = line.find(word, pos + 1);
                continue;
            }

            else{
                std::size_t closePar = line.find(")", pos);
                std::string subptr = line.substr((pos + 4), (closePar - (pos + 4)));
                
                if((subptr.size() < 3) || (subptr.size() > 7)){
                    pos = line.find(word, pos + 1);
                    continue;
                }

                std::size_t commapos = line.find(",", (pos + 4)); 
                std::string leftptr = line.substr((pos + 4), (commapos - (pos + 4)));
                std::string rightptr = line.substr((commapos + 1), (closePar - (commapos + 1)));
                
                if(is_number(leftptr) && is_number(rightptr)){
                    leftnum = std::atoi(leftptr.c_str());
                    rightnum = std::atoi(rightptr.c_str());
                    result += leftnum * rightnum;
                }

                pos = line.find(word, pos + 1);
            }
        }
    }
    
    return(result);
}


int main (int argc, char *argv[]){
    if(argc != 2)
        exit(1);

    std::string filename = argv[1];
    
    std::cout << "result: " << parseFile(filename) << std::endl;

    return(0);
}
