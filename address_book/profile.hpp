#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "profile_components/name.hpp"
#include "profile_components/email.hpp"
#include "profile_components/phone_number.hpp"

#include <vector>
#include <map>
#include <memory>

namespace address_book {

enum class COMPONENT {
    UNKNOWN,
    NAME,
    EMAIL,
    PHONE_NUMBER
};

class Profile;

using Option = std::pair<std::string, std::string>;
using OptionsMap = std::map<COMPONENT, Option>;


using ProfileId = std::size_t;
using ProfileIdVec = std::vector<std::size_t>;

using ProfileRef = std::shared_ptr<Profile>;

class Profile {
public:
    Profile();

    Profile(const OptionsMap& inputOptions);

    Profile(const NameRef& name,
            const EmailRef& email,
            const PhoneNumberRef& phoneNumber);

    Profile(const Profile&) = default;
    Profile& operator=(const Profile&) = default;

    Profile(Profile&&) = delete;
    Profile& operator=(Profile&&) = delete;

public:
    std::size_t id();

    // template<typename T>
    // std::shared_ptr<T> operator[](COMPONENT comp);

    NameRef name() const;

    EmailRef email() const;

    PhoneNumberRef phoneNumber() const;

    void update(const OptionsMap& newOptions);

    bool isValid();

private:
    static std::size_t _id;

private:
    NameRef _name;
    EmailRef _email;
    PhoneNumberRef _phoneNumber;
};

std::ostream& operator<<(std::ostream& out, const Profile& profile);

}; // namespace address_book

#endif /* PROFILE_HPP */