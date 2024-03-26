#include <iostream>
#include <filesystem> 

namespace fs = std::filesystem;

int main() {
    std::string tanlangan_papkani_nomi = "Tohir";
    std::string tohir_papkasi_nomi = "TATU_SF";

    fs::path tanlangan_papka(tanlangan_papkani_nomi);
    if (!fs::exists(tanlangan_papka)) {
        std::cerr << "Xatolik: Tanlangan papka mavjud emas." << std::endl;
        return 1;
    }

    fs::path tohir_papka(tohir_papkasi_nomi);
    if (!fs::exists(tohir_papka)) {
        if (!fs::create_directory(tohir_papka)) {
            std::cerr << "Xatolik: TATU_SF papkasini yaratishda xatolik yuz berdi." << std::endl;
            return 1;
        }
    }

    for (const auto& entry : fs::directory_iterator(tanlangan_papka)) {
        if (fs::is_regular_file(entry)) {
            fs::copy_file(entry.path(), tohir_papka / entry.path().filename(), fs::copy_options::overwrite_existing);
        } else if (fs::is_directory(entry)) {
            fs::copy(entry.path(), tohir_papka / entry.path().filename(), fs::copy_options::recursive);
        }
    }

    std::cout << "Fayllar TATU_SF papkasiga nusxalandi." << std::endl;
    return 0;
}
