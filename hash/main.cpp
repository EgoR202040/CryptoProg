#include <sstream>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cryptopp/files.h>
using namespace CryptoPP;
int main(){
try{
	std::ifstream input_file;

    Weak::MD5 hash;
    std::ofstream output_file;
    input_file.open("input.txt");
    output_file.open("output.txt");
    if(!output_file.is_open() or !input_file.is_open()){
    	throw std::invalid_argument("Ошибка пути к файлу");
    }
    CryptoPP::FileSource(input_file, true,
    new CryptoPP::HashFilter(hash,
        new CryptoPP::HexEncoder(new CryptoPP::FileSink(output_file))));
    
    output_file.close();
    input_file.close();
    }catch(std::invalid_argument& e){
    	std::cerr<< e.what() << std::endl;
    }
	return 0;
}
