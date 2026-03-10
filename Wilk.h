#ifndef WILK_H
#define WILK_H

#include "Zwierze.h"
#include <memory>

class Wilk : public Zwierze {
public:
    // siła = 9, inicjatywa = 5
    Wilk(int x, int y, Swiat& swiat);
    virtual ~Wilk() = default;

    char rysowanie() const override;

protected:
    // Tworzy potomka
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override;
};

#endif
