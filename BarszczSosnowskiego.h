#ifndef BARSZCZSOSNOWSKIEGO_H
#define BARSZCZSOSNOWSKIEGO_H

#include "Roslina.h"
#include <memory>

// Klasa BarszczSosnowskiego: zabija wszystkie zwierzęta w sąsiedztwie poza CyberOwca
class BarszczSosnowskiego : public Roslina {
public:
    // Konstruktor: siła=10, inicjatywa=0
    BarszczSosnowskiego(int x, int y, Swiat& swiat);

    ~BarszczSosnowskiego() override = default;

    // Akcja: eksterminacja zwierząt wokół (poza cyber-owcą)
    void akcja(Swiat& swiat) override;

    // Kolizja: zwierzę zjadające ginie (CyberOwca odporna)
    void kolizja(const std::shared_ptr<Organizm>& inny) override;

    // Symbol rośliny na planszy
    char rysowanie() const override;

protected:
    // Tworzy sadzonkę Barszczu Sosnowskiego
    std::shared_ptr<Organizm> utworzSadzonke(int x, int y) override;
};

#endif // BARSZCZSOSNOWSKIEGO_H
