#include "backupmanager.h"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

BackupManager::BackupManager(const std::string& directorioBackups)
    : directorioBackups(directorioBackups) {
    if (!fs::exists(directorioBackups)) {
        fs::create_directory(directorioBackups); // Crear el directorio si no existe
    }
}

void BackupManager::crearBackup(const std::string& archivo) {
    if (!fs::exists(archivo)) {
        std::cerr << "Error: El archivo " << archivo << " no existe.\n";
        return;
    }

    std::string archivoBackup = directorioBackups + "/" + fs::path(archivo).filename().string() + ".bak";
    fs::copy(archivo, archivoBackup, fs::copy_options::overwrite_existing);
    std::cout << "Backup creado: " << archivoBackup << "\n";
}

void BackupManager::restaurarBackup(const std::string& archivoOriginal, const std::string& archivoBackup) {
    std::string rutaBackup = directorioBackups + "/" + archivoBackup;
    if (!fs::exists(rutaBackup)) {
        std::cerr << "Error: El archivo de backup " << archivoBackup << " no existe en el directorio de backups.\n";
        return;
    }

    fs::copy(rutaBackup, archivoOriginal, fs::copy_options::overwrite_existing);
    std::cout << "Archivo restaurado desde el backup: " << archivoOriginal << "\n";
}

std::vector<std::string> BackupManager::listarBackups() const {
    std::vector<std::string> backups;
    for (const auto& entrada : fs::directory_iterator(directorioBackups)) {
        backups.push_back(entrada.path().filename().string());
    }
    return backups;
}
