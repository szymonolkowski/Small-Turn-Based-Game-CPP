#ifndef WILCZEJAGODY_H
#define WILCZEJAGODY_H

#include "Roslina.h"
#include <memory>

class WilczeJagody : public Roslina {
public:
    // siła=99, inicjatywa=0
    WilczeJagody(int x, int y, Swiat& swiat);

    ~WilczeJagody() override = default;

    void akcja(Swiat& swiat) override;

    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    char rysowanie() const override;

protected:
    // tworzy nowe wilcze jagody
    std::shared_ptr<Organizm> utworzSadzonke(int x, int y) override;
};

#endif
