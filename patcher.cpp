#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

// Function to patch the file in memory with multiple patches
void PatchFileInMemory(const std::string& filePath, const std::vector<std::pair<uintptr_t, std::vector<char>>>& patches) {
    // Open the file in binary mode
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // Read the entire file into a buffer
    std::vector<char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Apply each patch
    for (const auto& patch : patches) {
        uintptr_t offset = patch.first;
        const std::vector<char>& newValue = patch.second;

        // Check if the offset is within the file size
        if (offset + newValue.size() > buffer.size()) {
            std::cerr << "Offset 0x" << std::hex << offset << " is out of bounds!" << std::endl;
            continue; // Skip this patch and proceed with others
        }

        // Patch the value at the specified offset
        std::copy(newValue.begin(), newValue.end(), buffer.begin() + offset);
    }

    // Save the modified file to a new location
    std::string outputFilePath = "/storage/emulated/0/libil2cpp.so";
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Failed to create output file: " << outputFilePath << std::endl;
        return;
    }

    outputFile.write(buffer.data(), buffer.size());
    outputFile.close();

    std::cout << "File patched successfully! Saved to: " << outputFilePath << std::endl;
}

int main() {
    // Path to the original libil2cpp.so file
    std::string filePath = "/storage/emulated/0/libil2cpp.so"; // Replace with the actual path

    // Define the patches as a vector of (offset, newValue) pairs
    std::vector<std::pair<uintptr_t, std::vector<char>>> patches = {
        //GetFinalCoins offset 0x796AF8
        {0x796AF8, {
        //this is for armv7a 32bit games return 999999999L you can replace with this for arm64 64 bit games
     /*(arm64) E0, 3F, 99, 52, 40, 73, 
               A7, 72, C0, 03, 5F, D6
     
     */
      0xFF, 0x09, 0x0C, 0xE3,       0x00, 0x10, 0xA0, 0xE3,
      0x9A, 0x0B, 0x43, 0xE3,       0x1E, 0xFF, 0x2F, 0xE1
        }},
        //long GetFinalDiamonds offset 0x796B6C
        {0x796B6C, {
      0xFF, 0x09, 0x0C, 0xE3,       0x00, 0x10, 0xA0, 0xE3,
      0x9A, 0x0B, 0x43, 0xE3,       0x1E, 0xFF, 0x2F, 0xE1
        }},
        //long GetFinalOnlineChips Offset: 0x796C68
        {0x796C68, {
      0xFF, 0x09, 0x0C, 0xE3,       0x00, 0x10, 0xA0, 0xE3,
      0x9A, 0x0B, 0x43, 0xE3,       0x1E, 0xFF, 0x2F, 0xE1
        }},
        
        //long GetFinalEnergy Offset: 0x796CB4
        {0x796CB4, {
      0xFF, 0x09, 0x0C, 0xE3,       0x00, 0x10, 0xA0, 0xE3,
      0x9A, 0x0B, 0x43, 0xE3,       0x1E, 0xFF, 0x2F, 0xE1
        }},
        //long GetFinalTokens Offset: 0x796C88
        {0x796C88, {
      0xFF, 0x09, 0x0C, 0xE3,       0x00, 0x10, 0xA0, 0xE3,
      0x9A, 0x0B, 0x43, 0xE3,       0x1E, 0xFF, 0x2F, 0xE1
        }},
        //long GetTotalCafeIAPCount Offset: 0x796CD0
        {0x796CD0, {
      0xFF, 0x09, 0x0C, 0xE3,       0x00, 0x10, 0xA0, 0xE3,
      0x9A, 0x0B, 0x43, 0xE3,       0x1E, 0xFF, 0x2F, 0xE1
        }},
        
        //bool IsNoAdPurchased offset 0x7F4F90
        {0x7F4F90, {
 //and this is for armv7a return true
     0x01, 0x00, 0xA0, 0xE3, 
     0x1E, 0xFF, 0x2F, 0xE1
        }}
    };

    // Patch the file with all specified patches
    PatchFileInMemory(filePath, patches);

    return 0;
}
