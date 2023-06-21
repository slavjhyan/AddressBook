#ifndef ADDRESS_BOOK_PHONE_NUMBER_HPP
#define ADDRESS_BOOK_PHONE_NUMBER_HPP

#include <string>
#include <memory>
#include <ostream>

namespace address_book {

class PhoneNumber;

using PhoneNumberInfo = std::pair<std::string, std::string>;
using PhoneNumberRef = std::shared_ptr<PhoneNumber>;

class PhoneNumber {
public:
    PhoneNumber() = default;
    PhoneNumber(const PhoneNumber&) = default;
    PhoneNumber& operator=(const PhoneNumber&) = default;

    PhoneNumber(PhoneNumberInfo numberInfo);

    PhoneNumber(PhoneNumber&&) = delete;
    PhoneNumber& operator=(PhoneNumber&&) = delete;

public:
    PhoneNumberInfo get() const;

    std::string countryCode() const;

    std::string local() const;

    bool set(const PhoneNumberInfo& numberInfo);

    bool setCountryCode(const std::string& countryCode);

    bool setLocal(const std::string& localNumber);

    bool isValid();

private:
    static const std::size_t CountryCodeMinLength = 1; 
    static const std::size_t CountryCodeMaxLength = 4;

    static const std::size_t LocalNumberMinLength = 6;
    static const std::size_t LocalNumberMaxLength = 25;

private:
    bool validateNumber(const PhoneNumberInfo& numberInfo);

    bool validateCountryCode(const std::string& code);

    bool validateLocalNumber(const std::string& localNumber);


private:
    PhoneNumberInfo _phoneNumber;
    bool _isValid = false;
};

std::ostream& operator<<(std::ostream& out, const PhoneNumber& number);

}; // namespace address_book

#endif /* ADDRESS_BOOK_PHONE_NUMBER_HPP */
