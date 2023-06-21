#ifndef ADDRESS_BOOK_EMAIL_HPP
#define ADDRESS_BOOK_EMAIL_HPP

#include <ostream>
#include <string>
#include <memory>

namespace address_book {

class Email;

using EmailInfo = std::pair<std::string, std::string>;
using EmailRef = std::shared_ptr<Email>;

class Email {
public:
    Email() = default;
    Email(const Email&) = default;
    Email& operator=(const Email&) = default;

    Email(const EmailInfo& email);

    Email(Email&&) = delete;
    Email& operator=(Email&&) = delete;

public:
    EmailInfo get() const;

    std::string localAddress() const;

    std::string domain() const;

    bool set(const EmailInfo& email);

    bool isValid();

private:
    bool validateEmail(const EmailInfo& emailInfo);

    bool validateLocalAddress(const std::string& local);

    bool validateDomain(const std::string& domain);

private:
    const static std::size_t MaxCharacters = 30;
    const static std::size_t MinCharacters = 2;

private:
    EmailInfo _email;
    bool _isValid = false;
};

std::ostream& operator<<(std::ostream& out, const Email& email);

}; // namespace address_book

#endif /* ADDRESS_BOOK_EMAIL_HPP */
