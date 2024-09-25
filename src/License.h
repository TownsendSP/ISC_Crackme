//
// Created by tgsp on 9/19/24.
//

#ifndef LICENSE_H
#define LICENSE_H
#include <string>
#include <vector>
#include <unordered_map>


class License {
public:
    License();

    License(std::string encodedInput);

    int importLicense();

    std::string tostring();

    int validateLicense(std::string license);

    std::string inputLicense;

    std::string encoded_b64_license;

    const std::unordered_map<int, std::string> errorMessages = {
            {0, "License Successfully Verified!"},
            {1, "Invalid format"},
            {2, "Invalid number of fields - The license needs more information"},
            {3, "Invalid secret number"},
            {4, "Invalid licensee email address"},
            {5, "License hasn't begun yet"},
            {6, "License expired"},
            {7, "Invalid license dates. Time travel is prohibited"},
            {8, "Invalid license type"},
            {9, "Unknown error"}
    };
    int vv;

    int checkFormat(std::string inLicense);

    std::string getLicenseType(std::string licType);

    std::string interpretError(int errorCode);

    int importLicense(std::string inLicense);

    int validateLicense();

    bool isLicensed;
private:

    std::string email;

    std::string licType;
    std::string luhnNum;
    long int licStart;
    long int licEnd;

    static bool isValidSecretNumber(long int number);

    int checkNumber(long int number);

    bool b64Check(std::string license);

    int checkFormat();

    const std::unordered_map<std::string, std::string> licenseTypes = {
            {"LIC_UNLIC", "Unlicensed"},
            {"LIC_STD", "Standard"},
            {"LIC_PRO", "Professional"},
            {"LIC_PROPLUS", "Professional Plus"},
            {"LIC_APPLE", "Professional Plus Max Pro Ultra"},
            {"LIC_Enterprise", "Enterprise"}
    };

    int timeCheck();

    int isValidLicenseType(const std::string& licenseType);

    void wipeLicense();
};


#endif //LICENSE_H
