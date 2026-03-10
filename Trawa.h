#ifndef TRAWA_H
#define TRAWA_H

#include "Roslina.h"
#include <memory>

class Trawa : public Roslina {
public:
    // siła = 0, inicjatywa = 0
    Trawa(int x, int y, Swiat& swiat);

    ~Trawa() override = default;

    char rysowanie() const override;

protected:
    // tworzy sadzonkę trawy
    std::shared_ptr<Organizm> utworzSadzonke(int x, int y) override;
};

#endif
