#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <regex>
#include <fstream>
#include "License.h"

License lic = License();

int testNum = 0;

//creates an alert box with the message "Hello World!"
void get_license_details() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("License Details");
    std::string boxContents = lic.tostring();
    msgBox.setText(QString::fromStdString(boxContents));
    msgBox.exec();
}

void alertBox(const std::string& message) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Alert");
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();
}

void cheers() {
    QMessageBox msgBox;
    msgBox.setText("Congratulations on patching the number check.\n You're well on the way to cracking the program!");
    msgBox.exec();
}

int call_license_validation(const std::string& text) {

    int formatStatus = lic.checkFormat(text);
    if(formatStatus != 0) {
        alertBox(lic.interpretError(formatStatus));
        return -1;
    }
    int status = 0;
    lic.importLicense(text);
    int validationStatus = lic.validateLicense();
    if (lic.vv == 0) {
        cheers();
        status++;
    }
    alertBox(lic.interpretError(validationStatus));
    if(!lic.isLicensed) {
        status = -1;
    }
    return status;
}

//if lic.txt is found, return 0, else return 1
int checkForLicenseFile() {
    std::ifstream file("lic.txt");
    if (file.good()) {
        return 1;
    } else {
        return 0;
    }
}

std::string getLicenseKey() {
    std::ifstream file("lic.txt");
    if (!file.good()) {
        return "";
    }

    std::string line;
    std::getline(file, line);
    return line;
}

int main(int argc, char* argv[]) {
    std::string prefill = "";
    if(checkForLicenseFile()) {
        alertBox("License file found!");
        prefill = getLicenseKey();
    }
    License license = License();

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("License Validator");

    QVBoxLayout* mainLayout = new QVBoxLayout(&window);

// Non-modifiable text field and button in a horizontal layout
    QHBoxLayout* horizontalLayout = new QHBoxLayout();

    QLineEdit* nonModifiableTextField = new QLineEdit(&window);
    nonModifiableTextField->setText("UNLICENSED");
    nonModifiableTextField->setReadOnly(true);
    horizontalLayout->addWidget(nonModifiableTextField);

    // New button
    QPushButton* newButton = new QPushButton("License Details", &window);
    horizontalLayout->addWidget(newButton);

    // Connect the new button's clicked signal to func
    QObject::connect(newButton, &QPushButton::clicked, []() {
        get_license_details();
    });

    // Add the horizontal layout to the main layout
    mainLayout->addLayout(horizontalLayout);

    // Multi-line text box
    QTextEdit* multiLineTextBox = new QTextEdit(&window);
    multiLineTextBox->setText(QString::fromStdString(prefill));
    mainLayout->addWidget(multiLineTextBox);

    // Button
    QPushButton* button = new QPushButton("Check License", &window);
    mainLayout->addWidget(button);

    // Connect the button's clicked signal to a slot
    QObject::connect(button, &QPushButton::clicked, [multiLineTextBox, nonModifiableTextField]() {
        std::string text = multiLineTextBox->toPlainText().toStdString();
        int a = call_license_validation(text);
        nonModifiableTextField->setReadOnly(false);
        nonModifiableTextField->setText(QString::fromStdString(
                a == 1 ? "CRACKED" : (a == 0 ? "LICENSED" : "UNLICENSED")));
        nonModifiableTextField->setReadOnly(true);
    });

    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}