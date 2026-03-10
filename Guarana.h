#ifndef GUARANA_H
#define GUARANA_H

#include "Roslina.h"
#include <memory>

class Guarana : public Roslina {
public:
    // siła = 0, inicjatywa = 0
    Guarana(int x, int y, Swiat& swiat);

    ~Guarana() override = default;

    void akcja(Swiat& swiat) override;

    // zwieksza sile
    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    char rysowanie() const override;

protected:
    std::shared_ptr<Organizm> utworzSadzonke(int x, int y) override;
};

#endif
