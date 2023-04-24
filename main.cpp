#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "./cpp-base64/base64.h"

std::string BitConvert(std::string message, std::string password); // Converts the originalMessage and the password to bitset
std::bitset<8> XORbit(std::bitset<8> originalBit, std::bitset<8> password); // Calculates the symmetric difference between the password and the originalMessage

int main()
{
    std::string originalMessage {"Your Plain Text Message"};
    std::string password {"Your Password"};

    std::cout << "Type your message: " << std::endl;
    std::cin >> originalMessage;

    std::cout << "Type the password: " << std::endl;
    std::cin >> password;

    std::ofstream file("myEncryptedMessage.txt");
    if(file.is_open()){
        file << BitConvert(originalMessage, password);
        file.close();
    } else {
        std::cout << "[ERROR] Could not open file.";
        return 1;
    }

    return 0;
}

std::string BitConvert(std::string message, std::string password)
{
    std::string crypto;
    std::bitset<8> charBinary {'c'};
    std::bitset<8> binaryMessage[message.length()]; // Sets dynamic sized binary array, based on the message length
    std::bitset<8> binaryPassword[password.length()]; // Sets dynamic sized binary array, based on the password length

    for(int i = 0; i < message.length(); i++)
    {
        charBinary = message[i];
        binaryMessage[i] = charBinary;
    }

    for(int i = 0; i < password.length(); i++)
    {
        charBinary = password[i];
        binaryPassword[i] = charBinary;
    }

    std::bitset<8> binaryCrypto[message.length()]; // Cryptographed Binary of message
    if(message.length() >= password.length()){
        int passwordCount {0};
        for(int i = 0; i < message.length(); i++)
        {
            if(passwordCount >= password.length()){
                passwordCount = 0;
            }
            binaryCrypto[i] = XORbit(binaryMessage[i], binaryPassword[i]);
            passwordCount++;
        }

        for(int i = 0; i < message.length(); i++)
        {
            std::cout << static_cast<char>(binaryCrypto[i].to_ulong()) << std::endl;
        }
    } else {

    }

    return crypto;
}

std::bitset<8> XORbit(std::bitset<8> originalBitChar, std::bitset<8> passwordChar)
{
    std::bitset<8> cryptographedChar {0};

    cryptographedChar = originalBitChar ^ passwordChar;
    return cryptographedChar;
} 
