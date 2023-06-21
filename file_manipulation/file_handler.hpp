#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include "../address_book/profile.hpp"

#include <fstream>
#include <vector>
#include <string>

namespace file_ops {

class FileHandler {
public:
    FileHandler(const std::string& filename);

    FileHandler() = default;

    FileHandler(const FileHandler&) = default;
    FileHandler& operator=(const FileHandler&) = default;

    FileHandler(FileHandler&&) = delete;
    FileHandler& operator=(FileHandler&&) = delete;

public:
    bool setFile(const std::string& filename);

    void addProfile(const address_book::ProfileRef& profile);

    bool removeProfile(address_book::ProfileId id);

    bool updateProfile(address_book::ProfileId id, const address_book::OptionsMap& newOptions);

    bool isValid();

private:
    address_book::COMPONENT componentTypeFromStr(const std::string& str);

private:
    std::fstream _file;

    static const std::string _separator;

    static const std::string _dirPath;

    static const std::string _fileName;
};

}; // namespace file_ops

#endif /* FILE_HANDLER_HPP */
