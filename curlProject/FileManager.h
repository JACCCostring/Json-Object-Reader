#ifndef __FILEMANAGER__
#define __FILEMANAGER__

#include <iostream>
#include <fstream>

enum class                      FileType{WRITE, READ, ABSTRACT};

class FileManager{

public:
     explicit                   FileManager(const std::string _filename = "example.txt", 
                                const FileType &_type = FileType::ABSTRACT);
    ~FileManager();

    //operator
    friend std::fstream&        operator<< (FileManager&, const std::string &);
    friend void                 operator>> (FileManager&, std::string &);

    //methods
    void                        setMode(const FileType &);
    int                         getFileSize();

private:
    std::fstream                file;
    std::string                 filename;
    FileType                    type;
};

#endif
