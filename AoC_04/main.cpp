#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int rows = 0;
int columns = 0;
int x_mas = 0;

void calcDims(const std::string &filename){
    std::ifstream file(filename);
    if(!file.is_open())
        exit(2);

    std::string line;
    bool countcols = true;

    while(std::getline(file, line)){
        if(line.empty())
            continue;
        if(countcols){
            for(std::string::iterator cntr = line.begin(); cntr != line.end(); ++cntr)
                columns++;
            countcols = false;
        }

        rows++;
    }
}

void calcxmas(std::vector<std::vector<char>> &array){
    const std::vector<std::pair<int, int>> dirs = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
    
    for(int i = 1; i < rows - 1; i++){
        for(int j = 1; j < columns - 1; j++){
            if(array[i][j] == 'A'){
                std::string temp;

                for(std::pair<int, int> direction : dirs)
                    temp += array[i + direction.first][j + direction.second];
                
                if(temp == "MMSS" || temp == "MSSM" || temp == "SSMM" || temp == "SMMS")
                    x_mas++;
            }
        }
    }
}

int parseFile(const std::string &filename){
    int xmas = 0;
    calcDims(filename);

    std::ifstream file(filename);
    if(!file.is_open())
        exit(2);

    std::string line;
    std::vector<std::vector<char>> array(rows, std::vector<char>(columns));
    int rownum = 0;

    while(std::getline(file, line)){
        if(line.empty())
            continue;

        for(std::string::size_type pos = 0; pos < line.size(); ++pos)
            array[rownum][pos] = line[pos];
        
        rownum++;
    }

    calcxmas(array);
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(array[i][j] == 'X'){
                // 'X''M''A''S'
                if((array[i][j + 1] == 'M') && (array[i][j + 2] == 'A') && (array[i][j + 3] == 'S')){
                    xmas++;
                }

                // 'S''A''M''X'
                if((j - 3 >= 0) && (j - 2 >= 0) && (j - 1 >= 0)){
                    if((array[i][j - 1] == 'M') && (array[i][j - 2] == 'A') && (array[i][j - 3] == 'S')){
                        xmas++;
                    }
                }
                
                // 'X'
                // 'M'
                // 'A'
                // 'S'
                if((i + 1 < rows) && (i + 2 < rows) && (i + 3 < rows)){
                    if((array[i + 1][j] == 'M') && (array[i + 2][j] == 'A') && (array[i + 3][j] == 'S')){
                        xmas++;
                    }
                }

                // 'S'
                // 'A'
                // 'M'
                // 'X'
                if((i - 3 >= 0) && (i - 2 >= 0) && (i - 1 >= 0)){
                    if((array[i - 1][j] == 'M') && (array[i - 2][j] == 'A') && (array[i - 3][j] == 'S')){
                        xmas++;
                    }
                }

                // 'X'
                //  'M'
                //   'A'
                //    'S'
                if(((i + 1 < rows) && (j + 1 < columns)) && ((i + 2 < rows) && (j + 2 < columns)) && ((i + 3 < rows) && (j + 3 < columns))){
                    if((array[i + 1][j + 1] == 'M') && (array[i + 2][j + 2] == 'A') && (array[i + 3][j + 3] == 'S')){
                        xmas++;
                    }
                }

                // 'S'
                //  'A'
                //   'M'
                //    'X'
                if(((i - 1 >= 0) && (j - 1 >= 0)) && ((i - 2 >= 0) && (j - 2 >= 0)) && ((i - 3 >= 0) && (j - 3 >= 0))){
                    if((array[i - 1][j - 1] == 'M') && (array[i - 2][j - 2] == 'A') && (array[i - 3][j - 3] == 'S')){
                        xmas++;
                    }
                }

                //    'X'
                //   'M'
                //  'A'
                // 'S'
                if(((i + 1 < rows) && (j - 1 >= 0)) && ((i + 2 < rows) && (j - 2 >= 0)) && ((i + 3 < rows) && (j - 3 >= 0))){
                    if((array[i + 1][j - 1] == 'M') && (array[i + 2][j - 2] == 'A') && (array[i + 3][j - 3] == 'S')){
                        xmas++;
                    }
                }

                //    'S'
                //   'A'
                //  'M'
                // 'X'
                if(((i - 1 >= 0) && (j + 1 < columns)) && ((i - 2 >= 0) && (j + 2 < columns)) && ((i - 3 >= 0) && (j + 3 < columns))){
                    if((array[i - 1][j + 1] == 'M') && (array[i - 2][j + 2] == 'A') && (array[i - 3][j + 3] == 'S')){
                        xmas++;
                    }
                }
                
            }
        }
    }

    return(xmas);
}


int main (int argc, char *argv[]) {
    if(argc != 2)
        exit(1);

    std::string filename = argv[1];

    std::cout << "XMAS: " << parseFile(filename) << std::endl;
    std::cout << "rows: " << rows << "\ncols: " << columns << std::endl;
    std::cout << "X-MAS: " << x_mas << std::endl;

    return(0);
}
