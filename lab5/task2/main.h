#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstddef>
#include <filesystem>


class encoder {
private:
    std::vector<std::byte> encoding_key;
    std::vector<std::byte> s_block;

    void KSA();
    std::byte PRGA(int i, int j);
public:

    encoder(std::vector<std::byte> &key);

    void change_key(std::vector<std::byte> &new_key);

    int encode(const std::string &in_path, const std::string &out_path);



};

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
