#ifndef CONSOLE_APPLICATION_H
#define CONSOLE_APPLICATION_H

#include "../address_book/address_book.hpp"

#include <map>
#include <vector>
#include <string>

namespace exec {

enum class COMMAND {
    UNKNOWN,
    CREATE,
    DISPLAY,
    UPDATE,
    DELETE
};

class ConsoleApplication {
public:
    ConsoleApplication();

public:
    void execute();

private:
    void getInput();

    void parseInput();

    void executeInstruction();

    void executeUnknownInstruction();

    void executeCreateInstruction();

    void executeDisplayInstruction();

    void executeUpdateInstruction();

    void executeDeleteInstruction();

    bool validateInput();
 
    void initFunctionsMap();

    std::vector<std::string> splitStr(const std::string& str, char delimeter);

    COMMAND toCommand(const std::string& str);

    void clearCurrentInputData();

    bool fillOption(address_book::OptionsMap& optionsMap, const std::string& component);

private:
    std::string _input;

    bool _all = false;

    COMMAND _currentCommand = COMMAND::UNKNOWN;

    address_book::OptionsMap _profileOptions;

    address_book::OptionsMap _updateOptions;

    std::map<COMMAND, void(exec::ConsoleApplication::*)()> _execFunctionsMap;

    address_book::AddressBook _book;
};

const std::string ExitCommand = "exit";

const std::string CreateCommand = "create";

const std::string DisplayCommand = "display";

const std::string UpdateCommand = "update";

const std::string DeleteCommand = "delete";

const std::string ForenameKey = "forename";

const std::string SurnameKey = "surname";

const std::string EmailKey = "email";

const std::string PhoneNumberKey = "phone";

}; // namespace exec

#endif /* CONSOLE_APPLICATION_H */
