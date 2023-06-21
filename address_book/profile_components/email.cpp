#include "email.hpp"

#include <iostream>

namespace address_book {

Email::Email(const EmailInfo& emailInfo) {
    set(emailInfo);
}

EmailInfo Email::get() const {
    return _email;
}

std::string Email::localAddress() const {
    return _email.first;
}

std::string Email::domain() const {
    return _email.second;
}

bool Email::set(const EmailInfo& emailInfo) {
    if (!validateEmail(emailInfo)) {
        std::cerr << "Invalid email info: " << emailInfo.first + "@" + emailInfo.second << std::endl;
        _isValid = false;
    } else {
        _email.first = emailInfo.first;
        _email.second = emailInfo.second;
        _isValid = true;
    }

    return _isValid;
}

bool Email::isValid() {
    return _isValid;
}

bool Email::validateEmail(const EmailInfo& emailInfo) {
    return validateLocalAddress(emailInfo.first) || 
           validateDomain(emailInfo.second);
}

bool Email::validateLocalAddress(const std::string& local) {
    return (local.size() >= MinCharacters && local.size() <= MaxCharacters);
}

bool Email::validateDomain(const std::string& domain) {
    return (domain.size() >= MinCharacters && domain.size() <= MaxCharacters &&
           !isalnum(domain[0]) && isalnum(domain[domain.size() - 1]));
}

std::ostream& operator<<(std::ostream& out, const Email& email) {
    out << "Email: '" << email.localAddress() << '@' << email.domain() << "'\n";
    return out;
}

}; // namespace address_book
