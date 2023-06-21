#include "phone_number.hpp"

#include <algorithm>

namespace address_book {

PhoneNumber::PhoneNumber(PhoneNumberInfo numberInfo) {
    set(numberInfo);
}

PhoneNumberInfo PhoneNumber::get() const {
    return _phoneNumber;
}

std::string PhoneNumber::countryCode() const {
    return _phoneNumber.first;
}

std::string PhoneNumber::local() const {
    return _phoneNumber.second;
}

bool PhoneNumber::set(const PhoneNumberInfo& numberInfo) {
    bool success = false;
    if (validateNumber(numberInfo)) {
        _phoneNumber.first = numberInfo.first;
        _phoneNumber.second = numberInfo.second;
        success = true;
    }

    return success;
}

bool PhoneNumber::setCountryCode(const std::string& countryCode) {
    bool success = false;
    if (validateCountryCode(countryCode)) {
        _phoneNumber.first = countryCode;
        success = true;
    }

    return success;
}

bool PhoneNumber::setLocal(const std::string& localNumber) {
    bool success = false;
    if (validateCountryCode(localNumber)) {
        _phoneNumber.first = localNumber;
        success = true;
    }

    return success;
}

bool PhoneNumber::isValid() {
    return _isValid;
}

bool PhoneNumber::validateNumber(const PhoneNumberInfo& numberInfo) {
    return validateCountryCode(numberInfo.first) ||
           validateLocalNumber(numberInfo.second); 
}

bool PhoneNumber::validateCountryCode(const std::string& code) {
    bool validSize = (code.size() >= CountryCodeMinLength &&
                      code.size() <= CountryCodeMaxLength);

    return validSize && code[0] == '+' &&
        std::all_of(code.begin() + 1, code.end(),
        [](char ch) {
            return (isdigit(ch));
        });
}

bool PhoneNumber::validateLocalNumber(const std::string& localNumber) {
    bool validSize = (localNumber.size() >= CountryCodeMinLength &&
                      localNumber.size() <= CountryCodeMaxLength);

    return validSize &&
           std::all_of(localNumber.begin() + 1, localNumber.end(),
            [](char ch) {
                return (isdigit(ch) || isspace(ch));
            });
}

std::ostream& operator<<(std::ostream& out, const PhoneNumber& number) {
    out << "Phone Number: " << number.countryCode() << ' ' << number.local() << '\n';
    return out;
}

}; // namespace address_book
