#include "profile.hpp"

namespace address_book {

Profile::Profile() {
    ++_id;
}

Profile::Profile(const OptionsMap& options) {
    _name = std::make_shared<Name>();
    _email = std::make_shared<Email>();
    _phoneNumber = std::make_shared<PhoneNumber>();

    for (const auto& [component, value] : options) {
        if (component == COMPONENT::NAME) {
            _name->set(value);
        } else if (component == COMPONENT::EMAIL) {
            _email->set(value);
        } else if (component == COMPONENT::PHONE_NUMBER) {
            _phoneNumber->set(value);
        }
    }

    ++_id;
}

Profile::Profile(const NameRef& name,
                 const EmailRef& email,
                 const PhoneNumberRef& phoneNumber)
    : _name(name),
      _email(email),
      _phoneNumber(phoneNumber) { ++_id; }

std::size_t Profile::id() {
    return _id;
}

NameRef Profile::name() const {
    return _name;
}

EmailRef Profile::email() const {
    return _email;
}

PhoneNumberRef Profile::phoneNumber() const {
    return _phoneNumber;
}

void Profile::update(const OptionsMap& newOptions) {
    for (const auto& [comp, option] : newOptions) {
        switch (comp) {
        case COMPONENT::NAME:
            _name->set(option);
            break;
        case COMPONENT::EMAIL:
            _email->set(option);
            break;
        case COMPONENT::PHONE_NUMBER:
            _phoneNumber->set(option);
            break;
        }
    }
}

bool Profile::isValid() {
    return _name->isValid() && _email->isValid() && _phoneNumber->isValid();
}

std::size_t Profile::_id = 0;

std::ostream& operator<<(std::ostream& out, const Profile& profile) {
    out << *(profile.name()) <<
           *(profile.email()) <<
           *(profile.phoneNumber());

    return out;
}

}; // namespace address_book
