#include "main.h"

int main() {
    // Test 1: Basic encoding with a simple key
    std::vector<std::byte> key1 = {std::byte(0x01), std::byte(0x02), std::byte(0x03)};
    encoder enc1(key1);
    int result1 = enc1.encode("rofls.txt", "test_output.txt");
    if (result1 == 0) {
        std::cout << "Test 1: Encoding successful" << std::endl;
    } else {
        std::cout << "Test 1: Encoding failed" << std::endl;
    }

    // Test 2: Decode the encoded file
    int result2 = enc1.encode("test_output.txt", "test_decoded.txt");
    if (result2 == 0) {
        std::cout << "Test 2: Decoding successful" << std::endl;
    } else {
        std::cout << "Test 2: Decoding failed" << std::endl;
    }

    // Test 3: Change key and encode again
    std::vector<std::byte> key2 = {std::byte(0x04), std::byte(0x05), std::byte(0x06)};
    enc1.change_key(key2);
    int result3 = enc1.encode("rofls.txt", "test_output_changed_key.txt");
    if (result3 == 0) {
        std::cout << "Test 3: Encoding with changed key successful" << std::endl;
    } else {
        std::cout << "Test 3: Encoding with changed key failed" << std::endl;
    }

    // Test 4: Decode the encoded file with changed key
    int result4 = enc1.encode("test_output_changed_key.txt", "test_decoded_changed_key.txt");
    if (result4 == 0) {
        std::cout << "Test 4: Decoding with changed key successful" << std::endl;
    } else {
        std::cout << "Test 4: Decoding with changed key failed" << std::endl;
    }

    // Test 5: Encode with the same input and output path (should fail)
    int result5 = enc1.encode("rofls.txt", "rofls.txt");
    if (result5 == 1) {
        std::cout << "Test 5: Encoding with same input and output path failed as expected" << std::endl;
    } else {
        std::cout << "Test 5: Encoding with same input and output path did not fail as expected" << std::endl;
    }

    // Test 6: Encode a non-existent file (should fail)
    int result6 = enc1.encode("non_existent_file.txt", "test_output_non_existent.txt");
    if (result6 == 1) {
        std::cout << "Test 6: Encoding non-existent file failed as expected" << std::endl;
    } else {
        std::cout << "Test 6: Encoding non-existent file did not fail as expected" << std::endl;
    }

    return 0;
}