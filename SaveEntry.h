#ifndef SAVEENTRY_H
#define SAVEENTRY_H

#include <string>

class SaveEntry {
public:
    SaveEntry(const std::string& name, const std::string& filename)
        : name_(name), filename_(filename) {}

    const std::string& getName() const { return name_; }
    const std::string& getFilename() const { return filename_; }

private:
    std::string name_;
    std::string filename_;
};

#endif
