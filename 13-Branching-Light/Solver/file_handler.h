/**
 * File Handler main module. @jpvanegasc/FileHandler
 * 
 * @author: Juan Vanegas. git: jpvanegasc
 * 
 * Last modification: Feb 8, 2021.
 */
#ifndef __FILE_HANDLER_H
#define __FILE_HANDLER_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<vector>
#include<exception>
#include<memory>


#define vector(type) std::vector<type>
#define vector2D(type) std::vector< std::vector<type> >


struct FileNotOpened: public std::exception{
    const char * what() const throw () {
        return "Unable to open file";
    }
};

/**
 * Opens a file and loads its content and headers (if any) into two std::vectors.
 * 
 * @param filename: name or path of file.
 * @param delim_char : file data delimiter. Default is ','.
 * @param comm_char : file comment indicator. Default is '#'
 */
class FileHandler{
    private:
        int columns = 0, rows = 0;
        char comment, delimiter;

        void load_file(std::ifstream &file);
        void read_line(const std::string &line, vector(std::string) &row);
        void check_content(void);
    public:
        std::vector<std::string> header;
        std::vector< std::vector<double> > content;

        FileHandler(std::string filename, char =',', char ='#', bool =false);
        void content_to_double(double **&data);

        int get_cols(void){return columns;}
        int get_rows(void){return rows;}
};


#endif // __FILE_HANDLER_H