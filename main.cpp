#include <iostream>

#include <QApplication> // For Qt applications
#include <QWidget> // For Qt widgets
#include <QPushButton> // For Qt buttons

int main(int argc, char* argv[]) {
    // Create a Qt application
    QApplication app(argc, argv);

    // Create a main window
    QWidget window;
    window.setWindowTitle("Cross-Platform Window");

    // Create a button
    QPushButton button(&window);
    button.setText("Click Me!");
    button.setGeometry(100, 100, 100, 30);

    // Connect the button's clicked signal to a slot
    QObject::connect(&button, &QPushButton::clicked, []() {
        std::cout << "Button clicked!" << std::endl;
    });

    // Show the window
    window.show();

    // Start the application's event loop
    return app.exec();
}