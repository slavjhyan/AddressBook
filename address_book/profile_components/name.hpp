#ifndef ADDRESS_BOOK_NAME_HPP
#define ADDRESS_BOOK_NAME_HPP

#include <string>
#include <memory>
#include <ostream>

namespace address_book {

class Name;

using NameInfo = std::pair<std::string, std::string>;
using NameRef = std::shared_ptr<Name>;

class Name {
public:
    Name() = default;
    Name(const Name&) = default;
    Name& operator=(const Name&) = default;
    
    Name(const NameInfo& name);

    Name(Name&&) = delete;
    Name& operator=(Name&&) = delete;

public:
    NameInfo get() const;

    std::string forename() const;

    std::string surname() const;

    bool set(NameInfo name);

    bool setForename(std::string forename);

    bool setSurname(std::string surname);

    bool isValid();

private:
    bool validateFullname(const NameInfo& nameInfo);

    bool validateName(const std::string& name);

private:
    static const std::size_t MinCharacterCount = 2;
    static const std::size_t MaxCharacterCount = 20;

private:
    NameInfo _name;
    bool _isValid = false;
};

std::ostream& operator<<(std::ostream& out, const Name& name);

}; // namespace address_book

#endif /* ADDRESS_BOOK_NAME_HPP */
