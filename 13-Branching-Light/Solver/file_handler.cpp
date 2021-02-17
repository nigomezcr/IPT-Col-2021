#include "file_handler.h"

FileHandler::FileHandler(std::string filename, char delim_char, char comm_char, bool symmetric){
    std::ifstream file(filename);

    delimiter = delim_char;
    comment = comm_char;

    if(file.is_open()){
        load_file(file);
    }
    else throw FileNotOpened();

    file.close();

    rows = content.size();

    if(symmetric) check_content();
}

/**
 * Reads and splits a line into a std::vector of str::strings
 * 
 * @param line : line to be proccessed
 * @param row : std::vector to be loaded with data
 */
void FileHandler::read_line(const std::string &line, vector(std::string) &row){
    std::string temp; int start = 0;
    row.clear();

    if(line[0] == comment) start = 1;

    for(unsigned int i=start; i<line.size(); i++){
        char current = line[i];

        if(current != delimiter) temp += line[i];
        else{
            row.push_back(temp);
            temp = "";
        }
    }

    if(temp != "") row.push_back(temp);

}

/**
 * Takes a std::ifstream file and loads its content and headers
 */
void FileHandler::load_file(std::ifstream &file){
    std::string line;

    int line_num = 0;

    while(getline(file, line)){
        if(line[0] != comment){
            vector(std::string) str_row; vector(double) row;
            read_line(line, str_row);

            if(line_num == 0) columns = str_row.size();

            for(unsigned int i=0; i<str_row.size(); i++) row.push_back(std::stod(str_row[i]));
            content.push_back(row);
        }
        else if(line_num == 0){
            read_line(line, header);
            columns = header.size();
        }

        line_num++;
    }

}

/**
 * Checks that the content has every row with the same size. If not, adds nan to the matrix until 
 *      it becomes square.
 */
void FileHandler::check_content(void){
    for(unsigned int i=1; i<content.size(); i++){
        int current = content[i].size();

        if(current == rows) continue;
        else if(current < rows){
            while(current < rows){
                content[i].push_back(std::nan("1"));
                current += 1;
            }
            std::cerr << "Missing value in file, NaN added to data. Line " 
            << i+1 << " too short" << std::endl;
        }
        else{
            for(unsigned int j=0; j<i; j++){
                int temp = rows;
                while(temp < current){
                    content[j].push_back(std::nan("1"));
                    temp += 1;
                }
            }
            rows = current;
            std::cerr << "Missing values in file, NaN added to data. Line " 
            << i+1 << " too long." << std::endl;
        }
    }
}

/**
 * Load content from file to a null pointer. (Freeing memory is the users' responsability).
 * 
 * @param data: null pointer to be loaded with content from file
 */
void FileHandler::content_to_double(double **&data){
    data = new double *[rows];
    for(int i=0; i<columns; i++) data[i] = new double;

    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
            data[i][j] = content[i][j];
}


#undef vector2D
#undef vector
