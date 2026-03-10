#ifndef OWCA_H
#define OWCA_H

#include "Zwierze.h"
#include <memory>

class Owca : public Zwierze {
public:
    // siła = 4, inicjatywa = 4
    Owca(int x, int y, Swiat& swiat);
    virtual ~Owca() = default;

    char rysowanie() const override;

protected:
    // tworzy potomka owcy
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override;
};

#endif
