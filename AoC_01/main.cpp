#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

void parseFile(const std::string &filename, std::vector<std::int64_t> &array_l, std::vector<std::int64_t> &array_r){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "can not open file!" << std::endl;
        exit(2);
    }

    std::string line;
    std::int64_t rNum;
    std::int64_t lNum;

    while(std::getline(file, line)){
        if(line.empty())
            continue;
        
        std::istringstream iss(line);
        iss >> lNum >> rNum;

        
        array_l.push_back(lNum); 
        array_r.push_back(rNum); 
    }
}

void printArray(std::vector<std::int64_t> &array){
    for(int i: array)
        std::cout << i << std::endl;
}

void sortArray(std::vector<std::int64_t> &array){
    std::sort(array.begin(), array.end());
}

std::int64_t calcDist(std::vector<std::int64_t> &array_l, std::vector<std::int64_t> &array_r){
    std::int64_t distance = 0;
    
    for(int i = 0; i < array_l.size(); i++){
        distance += std::abs(array_l[i]  - array_r[i]);
    }

    return(distance);
}

std::int64_t calcSmlrt( std::vector<std::int64_t> &array_l ,std::vector<std::int64_t> &array_r){
    std::int64_t totalSim = 0;
    std::int64_t tempSim;

    for(int i = 0; i < array_l.size(); i++){
        tempSim = 0;
        for(int j = 0; j < array_r.size(); j++){
            if(array_r[j] > array_l[i])
                break;
            if(array_r[j] == array_l[i])
                tempSim++;
        }
        totalSim += array_l[i] * tempSim;
    }
    
    return(totalSim);   
}

int main (int argc, char *argv[]) {
    if(argc != 2){
        std::cout << "wrong input!" << std::endl;
        exit(1);
    }
    std::vector<std::int64_t> rList;
    std::vector<std::int64_t> lList;

    std::string filename = argv[1];
    parseFile(filename, lList, rList);

    std::cout << "Original lists:" << std::endl;
    printArray(lList);
    std::cout << std::endl;
    printArray(rList);

    sortArray(rList);
    sortArray(lList);

    std::cout << "Sorted lists:" << std::endl;
    printArray(lList);
    std::cout << std::endl;
    printArray(rList);

    std::cout << "Distance: " << calcDist(lList, rList) <<  std::endl;
    
    std::cout << "Similarity: " << calcSmlrt(lList, rList) <<  std::endl;

    return(0);
}
