#ifndef ZOLW_H
#define ZOLW_H

#include "Zwierze.h"
#include <memory>

class Zolw : public Zwierze {
public:
    // siła = 2, inicjatywa = 1
    Zolw(int x, int y, Swiat& swiat);
    virtual ~Zolw() = default;

    // 75% bez ruchu
    void akcja(Swiat& swiat) override;

    // Odpiera ataki słabszych zwierząt (<5)
    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    char rysowanie() const override;

protected:
    // Tworzy potomka żółwia
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override;
};

#endif
