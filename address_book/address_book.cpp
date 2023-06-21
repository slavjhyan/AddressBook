#include "address_book.hpp"

#include <iostream>

namespace address_book {

AddressBook::AddressBook() {
    // bool success = _db.setFile(AddressBook::_dbFilePath);
    // if (!success) {
    //     std::cerr << "Could not open db file\n" << std::endl;
    //     exit(1);
    // }
}

void AddressBook::displayAll() {
    for (const auto& [id, _] : _profiles) {
        displayProfile(id);
    }
}

ProfileIdVec AddressBook::findProfiles(const OptionsMap& options) {
    ProfileIdVec ids;

    for (const auto& [id, profile] : _profiles) {
        bool corresponds = true;
        for (const auto& [component, value] : options) {
            if (component == COMPONENT::NAME) {
                if (!value.first.empty()) {
                    corresponds = (value.first == profile->name()->forename());
                }
                if (!value.second.empty()) {
                    corresponds = corresponds && (value.second == profile->name()->surname());
                }
            } else if (component == COMPONENT::EMAIL) {
                corresponds =
                    corresponds &&
                    (value.first == profile->email()->localAddress()) &&
                    (value.second == profile->email()->domain());
            } else if (component == COMPONENT::PHONE_NUMBER) {
                corresponds =
                    corresponds &&
                    (value.first == profile->phoneNumber()->countryCode()) &&
                    (value.second == profile->phoneNumber()->local());
            }
        }

        if (corresponds) {
            ids.push_back(id);
        }
    }

    return ids;
}

ProfileIdVec AddressBook::allProfiles() {
    ProfileIdVec ids;

    ids.reserve(_profiles.size());
    for (const auto& [id, _] : _profiles) {
        ids.push_back(id);
    }

    return ids;
}

bool AddressBook::addProfile(const ProfileRef& profile) {
    if (_profiles.count(profile->id())) {
        std::cerr << "\nProfile already exists\n" << std::endl;
        return false;
    }
    _profiles.emplace(profile->id(), profile);
    // if (_db.isValid()) {
        _db.addProfile(profile);
    // } else {
    //     std::cerr << "\ndb file is not openned\n" << std::endl;
    // }

    return true;
}

void AddressBook::displayProfile(ProfileId id) {
    std::cout << *_profiles[id] << std::endl;
}

bool AddressBook::removeProfile(ProfileId id) {
    if (_profiles.erase(id)) {
        return _db.removeProfile(id);
    }

    return false;
}

bool AddressBook::updateProfile(ProfileId id, const OptionsMap& newOptions) {
    bool success = false;
    if (auto it = _profiles.find(id); it != _profiles.end()) {
        it->second->update(newOptions);
        success = true;
    }

    return success && _db.updateProfile(id, newOptions);
}

const std::string AddressBook::_dbFilePath = "../myDB.txt";

}; // namespace address_book
