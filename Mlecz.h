#ifndef MLECZ_H
#define MLECZ_H

#include "Roslina.h"
#include <memory>

class Mlecz : public Roslina {
public:
    // siła = 0, inicjatywa = 0
    Mlecz(int x, int y, Swiat& swiat);

    ~Mlecz() override = default;

    //Trzy próby rozsiania
    void akcja(Swiat& swiat) override;

    char rysowanie() const override;

protected:
    std::shared_ptr<Organizm> utworzSadzonke(int x, int y) override;
};

#endif