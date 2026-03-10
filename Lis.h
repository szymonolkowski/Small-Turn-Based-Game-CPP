#ifndef LIS_H
#define LIS_H

#include "Zwierze.h"
#include <memory>

class Lis : public Zwierze {
public:
    // siła = 3, inicjatywa = 7
    Lis(int x, int y, Swiat& swiat);
    virtual ~Lis() = default;

    // nie wchodzi na pole silniejszego
    void akcja(Swiat& swiat) override;

    char rysowanie() const override;

protected:
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override;
};

#endif
