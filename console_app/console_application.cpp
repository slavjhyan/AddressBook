#include "console_application.hpp"

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

namespace exec {

ConsoleApplication::ConsoleApplication() {
    initFunctionsMap();
}

void ConsoleApplication::execute() {
    while (true) {
        getInput();
        parseInput();
        executeInstruction();
    }
}

void ConsoleApplication::getInput() {
    do {
        std::getline(std::cin, _input);
    } while (!validateInput());
}

void ConsoleApplication::parseInput() {
    _profileOptions.clear();
    std::vector<std::string> instructionComponents = splitStr(_input, ' ');
    if (instructionComponents.size() <= 1) {
        if (!instructionComponents.empty()) {
            std::cerr << "\nToo little arguments\n" << std::endl;
        } else if (instructionComponents[0] == ExitCommand) {
            exit(0);
        }
        clearCurrentInputData();
        return;
    }

    _currentCommand = toCommand(instructionComponents[0]);

    if (_currentCommand == COMMAND::UNKNOWN) {
        std::cerr << "\nUnknown command '" << instructionComponents[0] << "'\n" << std::endl;
        clearCurrentInputData();
        return;
    }

    if (instructionComponents[1] == "--all" && instructionComponents.size() == 2) {
        _all = true;
    }

    int i = 1;
    for (; i < instructionComponents.size() && instructionComponents[i] != "to"; ++i) {
        if (!fillOption(_profileOptions, instructionComponents[i])) {
            return;
        }
    }

    ++i;
    for (; i < instructionComponents.size(); ++i) {
        if (!fillOption(_updateOptions, instructionComponents[i])) {
            return;
        }
    }
}


void ConsoleApplication::executeInstruction() {
    (this->*_execFunctionsMap[_currentCommand])();
    std::cout << std::endl;
}

void ConsoleApplication::executeUnknownInstruction() {
    return;
}

void ConsoleApplication::executeCreateInstruction() {
    const address_book::ProfileRef newProfile = std::make_shared<address_book::Profile>(_profileOptions);
    _book.addProfile(newProfile);
}

void ConsoleApplication::executeDisplayInstruction() {
    address_book::ProfileIdVec profileIds;
    if (_all) {
        profileIds = _book.allProfiles();
    } else {
        profileIds = _book.findProfiles(_profileOptions);
    }

    for (address_book::ProfileId id : profileIds) {
        _book.displayProfile(id);
    }
}

void ConsoleApplication::executeUpdateInstruction() {
    address_book::ProfileIdVec profileIds = _book.findProfiles(_profileOptions);
    for (address_book::ProfileId id : profileIds) {
        _book.updateProfile(id, _updateOptions);
    }
}

void ConsoleApplication::executeDeleteInstruction() {
    address_book::ProfileIdVec profileIds;
    if (_all) {
        profileIds = _book.allProfiles();
    } else {
        profileIds = _book.findProfiles(_profileOptions);
    }

    for (address_book::ProfileId id : profileIds) {
        _book.removeProfile(id);
    }
}

bool ConsoleApplication::validateInput() {
    return true;
}

void ConsoleApplication::initFunctionsMap() {
    _execFunctionsMap[COMMAND::UNKNOWN] = &executeUnknownInstruction;
    _execFunctionsMap[COMMAND::CREATE] = &executeCreateInstruction;
    _execFunctionsMap[COMMAND::DISPLAY] = &executeDisplayInstruction;
    _execFunctionsMap[COMMAND::UPDATE] = &executeUpdateInstruction;
    _execFunctionsMap[COMMAND::DELETE] = &executeDeleteInstruction;
}

std::vector<std::string> ConsoleApplication::splitStr(const std::string& str, char delimiter) {
    std::istringstream iss(str);
    std::vector<std::string> result;

    std::string token;
    while (std::getline(iss, token, delimiter)) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }

    return result;
}

COMMAND ConsoleApplication::toCommand(const std::string& str) {
    if (str == CreateCommand) {
        return COMMAND::CREATE;
    }

    if (str == DisplayCommand) {
        return COMMAND::DISPLAY;
    }

    if (str == UpdateCommand) {
        return COMMAND::UPDATE;
    }

    if (str == DeleteCommand) {
        return COMMAND::DELETE;
    }

    return COMMAND::UNKNOWN;
}

void ConsoleApplication::clearCurrentInputData() {
    _input.clear();
    _profileOptions.clear();
    _updateOptions.clear();
    _all = false;
    _currentCommand = COMMAND::UNKNOWN;
}

bool ConsoleApplication::fillOption(address_book::OptionsMap& optionsMap, const std::string& component) {
    auto res = splitStr(component, ':');
    if (res.size() != 2) {
        std::cerr << "\nInvalid Contact Info: '" << component << "'\n";
        clearCurrentInputData();
        return false;
    }

    if (res[0] == ForenameKey) {
        optionsMap[address_book::COMPONENT::NAME].first = res[1];
    } else if (res[0] == SurnameKey) {
        optionsMap[address_book::COMPONENT::NAME].second = res[1];
    } else if (res[0] == EmailKey) {
        address_book::EmailInfo emailInfo;

        std::size_t atIx = res[1].find('@');
        if (atIx == std::string::npos) {
            std::cerr << "\nInvalid Email Info: '" << res[1] << "'\n";
            clearCurrentInputData();
            return false;
        }
    
        emailInfo.first = res[1].substr(0, atIx);
        emailInfo.second = res[1].substr(atIx + 1, res[1].size());
    
        optionsMap[address_book::COMPONENT::EMAIL] = emailInfo;
    } else if (res[0] == PhoneNumberKey) {
        address_book::PhoneNumberInfo phoneNumberInfo;

        std::size_t codeSepIx = res[1].find('-');
        if (codeSepIx == std::string::npos) {
            std::cerr << "\nInvalid Email Info: '" << res[1] << "'\n";
            clearCurrentInputData();
            return false;
        }
    
        phoneNumberInfo.first = res[1].substr(0, codeSepIx);
        phoneNumberInfo.second = res[1].substr(codeSepIx + 1, res[1].size());
    
        optionsMap[address_book::COMPONENT::PHONE_NUMBER] = phoneNumberInfo;
    } else {
        std::cerr << "\nUnknown component: '" << res[0] << "'\n";
        clearCurrentInputData();
        return false;
    }

    return true;
}

}; // namespace exec
