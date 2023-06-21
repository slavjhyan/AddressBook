#include "name.hpp"

#include <algorithm>

namespace address_book {
    
Name::Name(const NameInfo& name) {
    set(name);
}

NameInfo Name::get() const {
    return _name;
}

std::string Name::forename() const {
    return _name.first;
}

std::string Name::surname() const {
    return _name.second;
}

bool Name::set(NameInfo name) {
    bool success = false;
    if (validateFullname(name)) {
        _name.first = name.first;
        _name.second = name.second;
        _isValid = success = true;
    }

    return success;
}

bool Name::setForename(std::string forename) {
    bool success = false;
    if (validateName(forename)) {
        _name.first = forename;
        success = true;

        if (!_name.second.empty()) {
            _isValid = true;
        }
    }

    return success;
}

bool Name::setSurname(std::string surname) {
    bool success = false;
    if (validateName(surname)) {
        _name.second = surname;
        success = true;
    
        if (!_name.first.empty()) {
            _isValid = true;
        }
    }

    return success;
}

bool Name::isValid() {
    return _isValid;
}

bool Name::validateFullname(const NameInfo& nameInfo) {
    return validateName(nameInfo.first) ||
           validateName(nameInfo.second);
}

bool Name::validateName(const std::string& name) {
    bool valid = (name.size() >= MinCharacterCount &&
                  name.size() <= MaxCharacterCount);

    return valid &&
           std::all_of(name.cbegin(), name.cend(),
            [](char ch) {
                return isalpha(ch);
            });
}

std::ostream& operator<<(std::ostream& out, const Name& name) {
    out << "First Name: '" << name.forename() << "'\n"
        << "Last Name: '" << name.surname() << "'\n";

    return out;
}

}; // namespace address_book