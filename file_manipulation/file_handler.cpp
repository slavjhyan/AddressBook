#include "file_handler.hpp"

#include <iostream>
#include <windows.h>

namespace file_ops {

bool FileHandler::setFile(const std::string& filename) {
    if (_file.is_open()) {
        _file.close();
    }

    _file.open(filename);
    bool success = true;

    if (!_file.is_open()) {
        std::cerr << "Could not set file" << std::endl;
        success = false;
    }

    return success;
}

void FileHandler::addProfile(const address_book::ProfileRef& profile) {
    std::fstream f(FileHandler::_dirPath + FileHandler::_fileName, std::ios::out | std::ios::in | std::ios::app);
    f << "id: " << profile->id() << '\n' << *profile << FileHandler::_separator << '\n';
    f.close();
}

bool FileHandler::removeProfile(address_book::ProfileId id) {
    std::fstream f(FileHandler::_dirPath + FileHandler::_fileName, std::ios::out | std::ios::in | std::ios::app);

    std::string currLine;
    const std::string idLine = "id: ";

    const int profileLengthInLines = 6;
    int startIx = 0;

    bool found = false;
    while (std::getline(f, currLine)) {
        if (!(startIx++ % profileLengthInLines)) {
            address_book::ProfileId currId = std::stoi(currLine.substr(idLine.size(), currLine.size()));
            if (currId == id) {
                found = true;
                break;
            }
        }
    }
    f.seekg(0, f.beg);

    if (found) {
        --startIx;
        std::ofstream temp(FileHandler::_dirPath + "temp.txt");
        int count = 0;
        while (std::getline(f, currLine)) {
            if (count < startIx || count >= startIx + profileLengthInLines) {
                temp << currLine << std::endl;
            }
            ++count;
        }
        f.close();
        temp.close();

        DeleteFileA((FileHandler::_dirPath + FileHandler::_fileName).c_str());
        MoveFileA((FileHandler::_dirPath + "temp.txt").c_str(),
                  (FileHandler::_dirPath + FileHandler::_fileName).c_str());
    }

    return found;
}

bool FileHandler::updateProfile(address_book::ProfileId id, const address_book::OptionsMap& newOptions) {
    std::fstream f(FileHandler::_dirPath + FileHandler::_fileName, std::ios::out | std::ios::in | std::ios::app);

    std::string currLine;
    const std::string idLine = "id: ";

    const int profileLengthInLines = 6;
    int startIx = 0;

    bool found = false;
    while (std::getline(f, currLine)) {
        if (!(startIx++ % profileLengthInLines)) {
            address_book::ProfileId currId = std::stoi(currLine.substr(idLine.size(), currLine.size()));
            if (currId == id) {
                found = true;
                break;
            }
        }
    }
    f.seekg(0, f.beg);

    if (found) {
        --startIx;
        std::ofstream temp(FileHandler::_dirPath + "temp.txt");
        int count = 0;
        while (std::getline(f, currLine)) {
            if (count <= startIx || count >= startIx + profileLengthInLines) {
                temp << currLine << std::endl;
                ++count;
            } else {
                do {
                    if (std::string comp = currLine.substr(0, currLine.find(':')); comp != currLine) {
                        address_book::COMPONENT currCompType = componentTypeFromStr(comp);
                        if (newOptions.count(currCompType)) {
                            std::string newVal = currLine.substr(currLine.find(':') + 2, currLine.size());

                            switch (currCompType) {
                            case address_book::COMPONENT::NAME:
                                if (comp == "First Name") {
                                    if (!newOptions.at(currCompType).first.empty()) {
                                        newVal = newOptions.at(currCompType).first;
                                    }
                                } else if (comp == "Last Name") {
                                    if (!newOptions.at(currCompType).second.empty()) {
                                        newVal = newOptions.at(currCompType).second;
                                    }
                                }
                                break;
                            case address_book::COMPONENT::EMAIL:
                                newVal = newOptions.at(currCompType).first + '@' + newOptions.at(currCompType).second;
                                break;
                            case address_book::COMPONENT::PHONE_NUMBER:
                                newVal = newOptions.at(currCompType).first + '-' + newOptions.at(currCompType).second;
                                break;
                            default:
                                std::cerr << "Unknown Component\n" << std::endl;
                                break;
                            }
                            currLine = comp + ": " + newVal;
                        }
                    }
                    temp << currLine << std::endl;
                    ++count;
                } while ((count - startIx) < profileLengthInLines && std::getline(f, currLine));
            }
        }
        f.close();
        temp.close();

        DeleteFileA((FileHandler::_dirPath + FileHandler::_fileName).c_str());
        MoveFileA((FileHandler::_dirPath + "temp.txt").c_str(),
                  (FileHandler::_dirPath + FileHandler::_fileName).c_str());
    }

    return found;
}

bool FileHandler::isValid() {
    return _file.is_open();
}

address_book::COMPONENT FileHandler::componentTypeFromStr(const std::string& str) {
    if (str == "First Name" || str == "Last Name") {
        return address_book::COMPONENT::NAME;
    }

    if (str == "Email") {
        return address_book::COMPONENT::EMAIL;
    }

    if (str == "Phone") {
        return address_book::COMPONENT::PHONE_NUMBER;
    }

    return address_book::COMPONENT::UNKNOWN;
}

const std::string FileHandler::_separator = "-----------------------------";

const std::string FileHandler::_dirPath = "C:\\Users\\user\\Codes\\C++\\Code Republic\\C++\\AdressBook\\";

const std::string FileHandler::_fileName = "myDB.txt";

}; // namespace file_ops
