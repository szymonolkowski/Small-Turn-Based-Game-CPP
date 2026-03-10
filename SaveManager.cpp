#include "SaveManager.h"
#include "Swiat.h"
#include <fstream>

SaveManager::SaveManager(const std::string& indexFile)
  : indexFile_(indexFile)
{
    loadIndex();
}

void SaveManager::loadIndex() {
    entries_.clear();
    std::ifstream in(indexFile_);
    if (!in) return;
    std::string name, filename;
    while (in >> name >> filename) {
        entries_[name] = filename;
    }
}

void SaveManager::writeIndex() const {
    std::ofstream out(indexFile_);
    for (auto& [name, filename] : entries_) {
        out << name << ' ' << filename << "\n";
    }
}

std::vector<std::string> SaveManager::listSaves() const {
    std::vector<std::string> names;
    for (auto& p : entries_) names.push_back(p.first);
    return names;
}

void SaveManager::addSave(const std::string& name, const std::string& filename) {
    entries_[name] = filename;
    writeIndex();
}

void SaveManager::saveWorld(const std::string& filename, const Swiat& world) const {
    world.zapiszDoPliku(filename);
}

bool SaveManager::loadWorld(const std::string& filename, Swiat& world) const {
    world.wczytajZPliku(filename);
    return true;
}
