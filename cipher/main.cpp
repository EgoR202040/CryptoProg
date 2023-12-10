#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

#include <iostream>
#include <string>
#include <fstream>
int main(int argc, char* argv[])
{
    using namespace CryptoPP;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::ifstream plain;
    plain.open("plain.txt");
    std::ofstream cipher, recovered;
    cipher.open("cipher.txt");
    try {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        FileSource s(plain, true,
                     new StreamTransformationFilter(e,
                             new FileSink(cipher)
                                                   ) // StreamTransformationFilter
                    ); // StringSource
    } catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    cipher.close();
    plain.close();
    /*********************************\
    \*********************************/

    std::cout << "key: ";
    encoder.Put(key, key.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "iv: ";
    encoder.Put(iv, iv.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    std::ifstream ciph;
    ciph.open("cipher.txt");
    recovered.open("recover.txt");
    CBC_Mode< AES >::Decryption d;
    d.SetKeyWithIV(key, key.size(), iv);
    FileSource s(ciph, true,new StreamTransformationFilter(d,new FileSink(recovered)));
    ciph.close();
    recovered.close();
    return 0;
}
