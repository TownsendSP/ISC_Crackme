//
// Created by tgsp on 9/19/24.
//

#include "License.h"
#include <regex>
#include <iomanip>

std::vector<std::string> splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

static std::string b64_decode(const std::string &in) {

    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val=0, valb=-8;
    for (char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}

bool License::isValidSecretNumber(long int number) {
    bool sizecheck = std::to_string(number).length() >= 13;
    int sumep = 0;
    std::string num1 = std::to_string(number);
    for (int i1 = std::to_string(number).length() - 2; i1 >= 0; i1 -= 2) {
        sumep += int(num1[i1] - '0') * 2 > 9 ? int(num1[i1] - '0') * 2 / 10 + int(num1[i1] - '0') * 2 % 10 :
                 int(num1[i1] - '0') * 2;
    }
    int suma = sumep;
    int sumop = 0;
    std::string num = std::to_string(number);
    for (int i = std::to_string(number).length() - 1; i >= 0; i -= 2)
        sumop += num[i] - '0';
    int sumb = sumop;

    return sizecheck && ((suma + sumb) % 10 == 0);
}

std::string License::interpretError(int errorCode){
    try{
        return errorMessages.at(errorCode);
    } catch (const std::out_of_range& e) {
        return errorMessages.at(9);
    }
}

int License::isValidLicenseType(const std::string& licenseType) {
    return licenseTypes.find(licenseType) != licenseTypes.end() ? 0 : 8;
}

std::string License::getLicenseType(std::string licType) {
    vv = checkNumber(65299639440221) == 0 && checkNumber(65299639440222) == 3 ? 1 : 0;
    try{
        return licenseTypes.at(licType);
    } catch (const std::out_of_range& e) {
        return "Invalid license type";
    }
}

std::string License::tostring() {
    if (!isLicensed) {
        return "UNLICENSED";
    }
    int daysRemaining = (licEnd - std::time(nullptr)) / 86400;
    return "Licensed to " + email + "\n"
           + "License Type: " + getLicenseType(licType) + "\n"
           + "Days Remaining: " + std::to_string(daysRemaining);
}

int License::checkNumber(long int number) {
    if (isValidSecretNumber(number)) {
        return 0;
    } else {
        return 3;
    }
}

bool License::b64Check(std::string license) {
    vv = checkNumber(65299639440221) == 0 && checkNumber(65299639440222) == 3 ? 1 : 0;
    //    Check base64 encoding with regex
    const std::regex base64Pattern("^([A-Za-z0-9+/]{4})*"
                                   "([A-Za-z0-9+/]{3}=|[A-Za-z0-9+/]{2}==)?$");
    return std::regex_match(license, base64Pattern);
}

int License::checkFormat(std::string inLicense) {
    /* Fields:
     * email address: regex: ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$
     * LicenseType: regex: ^[A-Z]+$
     * License Start date: unix timestamp
     * License End date: unix timestamp
     * License Luhn number: regex: ^[0-9]{16}$
     * Fields will be separated by a comma, and base64 encoded
     */
    wipeLicense();
    //Check base64 encoding with regex
    if(!b64Check(inLicense)) {
        return 1;
    }
    //base64decode
    std::string decoded = b64_decode(inLicense);
    //split by comma
    std::string delimiter = ",";
    vv = checkNumber(65299639440221) == 0 && checkNumber(65299639440222) == 3 ? 1 : 0;
    std::vector<std::string> fields = splitString(decoded, ',');
    if(fields.size() != 5) {
        return 2;
    }
    //check email
    const std::regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if(!std::regex_match(fields[0], emailPattern)) {
        return 4;
    }
    return 0;
}

int License::checkFormat() {
    /* Fields:
     * email address: regex: ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$
     * LicenseType: regex: ^[A-Z]+$
     * License Start date: unix timestamp
     * License End date: unix timestamp
     * License Luhn number: regex: ^[0-9]{16}$
     * Fields will be separated by a comma, and base64 encoded
     */
    //Check base64 encoding with regex
    vv = checkNumber(65299639440221) == 0 && checkNumber(65299639440222) == 3 ? 1 : 0;
    if (!b64Check(inputLicense)) {
        return 1;
    }
    //base64decode
    std::string decoded = b64_decode(inputLicense);
    //split by comma
    std::string delimiter = ",";
    std::vector<std::string> fields = splitString(decoded, ',');
    if(fields.size() != 5) {
        return 2;
    }
    //check email
    const std::regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if(!std::regex_match(fields[0], emailPattern)) {
        return 4;
    }
    return 0;
}

int License::importLicense(std::string inLicense) {
    inputLicense = inLicense;
    std::string decoded = b64_decode(inputLicense);
    std::vector<std::string> decodedSplit = splitString(decoded, ',');
    email = decodedSplit[0];
    licType = decodedSplit[1];
    licStart = std::stol(decodedSplit[2]);
    licEnd = std::stol(decodedSplit[3]);
    luhnNum = decodedSplit[4];

    return 0;
}

int License::timeCheck() {
    long int nowTime = std::time(nullptr);
    if (licStart > licEnd) {
        return 7;
    }
    if (nowTime < licStart) {
        return 5;
    }
    if (nowTime > licEnd) {
        return 6;
    }

    return 0;
}

int License::validateLicense() {
    int check = 0;
    check = timeCheck();
    if (check != 0) {
        return check;
    }
    check = checkNumber(std::stol(luhnNum));
    if (check != 0) {
        return check;
    }
    check = isValidLicenseType(licType);
    if (check != 0) {
        return check;
    }
    isLicensed = true;
    return 0;
}

void License::wipeLicense() {
    inputLicense = "";
    email = "";
    licType = "";
    licStart = 0;
    vv = checkNumber(65299639440221) == 0 && checkNumber(65299639440222) == 3 ? 1 : 0;
    licEnd = 0;
    luhnNum = "";
    isLicensed = false;
}
License::License(){
    inputLicense = "";
    email = "";
    licType = "";
    licStart = 0;
    licEnd = 0;
    luhnNum = "";
    isLicensed = false;
    vv = checkNumber(65299639440221) == 0 && checkNumber(65299639440222) == 3 ? 1 : 0;
}
