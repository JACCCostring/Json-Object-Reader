#include "FileManager.h"

FileManager::FileManager(const std::string _filename, const FileType &_type)
: filename(_filename), 
  type(_type)
{
    setMode(type);
}

FileManager::~FileManager(){ file.close(); }

void FileManager::setMode(const FileType &mode){
    switch(mode){
        case FileType::WRITE:
        
        if(file.is_open()) file.close();
        
            file.open(filename, std::ios::out); break;

        case FileType::READ:
        
            if(file.is_open()) file.close();
        
            file.open(filename, std::ios::in); break;

        default: break;
    }
}

std::fstream& operator<< (FileManager& _file, const std::string &data){
    if(_file.type != FileType::WRITE){
        std::cout<<"!file not in write mode!" << std::endl;
        return _file.file;
    }
    
    _file.file << data;    
    return _file.file;
}

void operator>> (FileManager& _file, std::string &content){
    _file.setMode(FileType::READ);
    
    while(std::getline(_file.file, content));
}

int FileManager::getFileSize(){
    std::streampos beg, end;

    if(! file.good()){ std::cout << "file not opened!" << std::endl; return 0; }

    beg = file.tellg();

    file.seekg(0, std::ios::end);

    end = file.tellg();
    
    file.close();

    return end - beg;
}
