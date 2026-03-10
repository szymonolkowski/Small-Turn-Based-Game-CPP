#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include <map>
#include <vector>

class Swiat;

class SaveManager {
public:
    SaveManager(const std::string& indexFile = "saves.idx");

    // zapisane światy (wczytywanie) z indexFile_
    void loadIndex();

    // zapisane światy (zapisywanie) <name->filename> do indexFile_
    void writeIndex() const;

    // lista zapisanych swiatow
    std::vector<std::string> listSaves() const;

    void addSave(const std::string& name, const std::string& filename);

    void saveWorld(const std::string& filename, const Swiat& world) const;

    bool loadWorld(const std::string& filename, Swiat& world) const;

private:
    std::string indexFile_;
    std::map<std::string, std::string> entries_;
};

#endif