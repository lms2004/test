#ifndef _UPLOADER_H
#define _UPLOADER_H
#include "ui_uploader.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

class uploader : public QWidget {
    Q_OBJECT

public:
    uploader(QWidget* parent = nullptr);

private slots:
    void on_browseButton_clicked();
    void on_pushButton_clicked();
    void on_browseButton1_clicked();

private:
    std::string repoPath = "C:\\Users\\lms\\Desktop\\哈  说是撒谎安定";
    std::string repoUrl = "git@github.com:lms2004/aa.git";

    Ui::uploader* ui;
    QLineEdit* projectPathLineEdit;    
    QLineEdit*  repoPath_;
    QLineEdit* ssh_Address;
    QLabel* statusLabel;  


    void generateSSHKey(const std::string& keyPath);
    void runCommand(const std::string& command);
    bool isGitRepository(const std::string& path);
    void copyProjectFiles(const std::string& source, const std::string& destination);
    void gitPush(const std::string& repoUrl, const std::string& branchName, const std::string& projectSourcePath);
    void outputSSHKey(std::string ssh);
    void logError(const std::string& errorMsg);
        
    std::string makeLegalPath(const std::string& path);
};

#endif  _UPLOADER_H
