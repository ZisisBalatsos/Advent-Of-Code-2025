#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <sstream>

bool checkSafety(std::vector<std::int64_t> &array){
    bool dscnd = false;

   if(array[0] > array[1])
        dscnd = true;

    for(int i = 0; i < (array.size() - 1); i++){
        if((std::abs(array[i] - array[i + 1]) < 1) || ((std::abs(array[i] - array[i + 1]) > 3)))
            return(false);

        if(dscnd){
            if(array[i] < array[i + 1])
                return(false);
        }
        else{
            if(array[i] > array[i + 1])
                return(false);
        }
    }
    
    return(true);
}

bool checkDampener(std::vector<std::int64_t> &array){
    bool dscnd = false;
    bool ascnd = false;

    std::vector<std::int64_t> modified = array;
    std::vector<std::int64_t> reversed = array;
    std::reverse(reversed.begin(), reversed.end());

    if(array[0] > array[1])
        dscnd = true;
    else if(array[0] < array[1])
        ascnd = true;

    if(dscnd){
        if(std::is_sorted((modified.begin() + 1), modified.end())){
            ascnd = true;
            dscnd = false;
        }
    }

    else if(ascnd){
        if(std::is_sorted(reversed.begin(), (reversed.end() - 1))){
            ascnd = false;
            dscnd = true;
        }
    }

    for(int i = 0; i < (array.size() - 1); i++){
        if((std::abs(array[i] - array[i + 1]) < 1) || ((std::abs(array[i] - array[i + 1]) > 3))){
            if(i == (array.size() - 2)){
                modified.erase(modified.begin() + (i + 1));

                if(!checkSafety(modified))
                    return(false);
                
                break;
            }
            
            if(std::abs(array[i] - array[i + 2]) <= 3){
                modified.erase(modified.begin() + (i + 1));

                if(!checkSafety(modified))
                    return(false);
                
                break;
            }

            modified.erase(modified.begin() + (i));

            if(!checkSafety(modified))
                return(false);
            
            break;
        }

        if(dscnd){
            if(i > 0){
                if(array[i + 1] == array[i - 1]){
                    modified.erase(modified.begin() + (i + 1));

                    if(!checkSafety(modified))
                        return(false);

                    break;
                }
            }

            if(array[i] < array[i + 1]){
                if(i == (array.size() - 2)){
                    modified.erase(modified.begin() + (i + 1));
                    if(!checkSafety(modified))
                        return(false);

                    break;
                }

                if(std::abs(array[i + 1] - array[i + 2]) >= 3){
                    modified.erase(modified.begin() + (i + 1));

                    if(!checkSafety(modified))
                        return(false);

                    break;
                }

                modified.erase(modified.begin() + (i));

                if(!checkSafety(modified))
                    return(false);

                break;

            }
        }

        if(ascnd){
            if(i > 0){
                if(array[i + 1] == array[i - 1]){
                    modified.erase(modified.begin() + (i + 1));

                    if(!checkSafety(modified))
                        return(false);

                    break;
                }
            }

            if(array[i] > array[i + 1]){
                if(i == (array.size() - 2)){
                    modified.erase(modified.begin() + (i + 1));
                    if(!checkSafety(modified))
                        return(false);

                    break;
                }

                if(std::abs(array[i + 1] - array[i + 2]) >= 3){
                    modified.erase(modified.begin() + (i + 1));

                    if(!checkSafety(modified))
                        return(false);

                    break;
                }
                
                modified.erase(modified.begin() + (i));

                if(!checkSafety(modified))
                    return(false);

                break;
            }
        }
    }
    
    return(true);
}

std::size_t calcSafety(const std::string &filename){
    std::size_t safe = 0;
    std::size_t dampener = 0;


    std::ifstream file(filename);
    if(!file.is_open())
        exit(2);

    std::string line;
    std::int64_t entry;

    while(std::getline(file, line)){
        if(line.empty())
            continue;

        std::vector<std::int64_t> level;
        
        std::istringstream iss(line);
        while(iss >> entry){
            level.push_back(entry);
        }
        
        //if(checkSafety(level))
            //safe++;

        if(checkDampener(level))
            dampener++;
    }
    //return(safe);
    return(dampener);
}

int main (int argc, char *argv[]) {
    if(argc != 2)
        exit(1);
    
    std::string filename = argv[1];

    //std::cout << "Safe: " << calcSafety(filename) << std::endl;

    std::cout << "Problem Dampener: " << calcSafety(filename) << std::endl;

    return(0);
}
