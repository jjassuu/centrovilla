#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>

class BackupManager {
public:
    BackupManager(const std::string& directorioBackups = "./backups"); 
    void crearBackup(const std::string& archivo);               
    void restaurarBackup(const std::string& archivoOriginal, const std::string& archivoBackup);
    std::vector<std::string> listarBackups() const;             

private:
    std::string directorioBackups;                              
};

#endif
