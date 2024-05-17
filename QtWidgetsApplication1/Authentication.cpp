#include <QMainWindow>
#include "Authentication.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        ui.setupUi(this);
    }

private:
    Ui::MainWindow ui;
};

