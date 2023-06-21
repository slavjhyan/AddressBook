#ifndef ADDRESS_BOOK_HPP
#define ADDRESS_BOOK_HPP

#include "profile.hpp"
#include "../file_manipulation/file_handler.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace address_book {

using ProfilesMap = std::unordered_map<ProfileId, ProfileRef>;

class AddressBook {
public:
    AddressBook();

    AddressBook(const AddressBook&) = delete;
    AddressBook& operator=(const AddressBook&) = delete;

    AddressBook(AddressBook&&) = delete;
    AddressBook& operator=(AddressBook&&) = delete;

public:
    ProfileIdVec findProfiles(const OptionsMap& options);

    ProfileIdVec allProfiles();

    bool addProfile(const ProfileRef& profile);

    void displayProfile(ProfileId id);

    void displayAll();

    bool removeProfile(ProfileId id);

    bool updateProfile(ProfileId id, const OptionsMap& newOptions);

private:
    static const std::string _dbFilePath;

private:
    ProfilesMap _profiles;
    file_ops::FileHandler _db;
};

}; // namespace address_book

#endif /* ADDRESS_BOOK_HPP */
