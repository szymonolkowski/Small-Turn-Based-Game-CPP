#ifndef CYBEROWCA_H
#define CYBEROWCA_H

#include "Owca.h"
#include "BarszczSosnowskiego.h"
#include <memory>
#include <limits>
#include <cmath>

class CyberOwca : public Owca {
public:
    // Konstruktor: siła=10, inicjatywa=4
    CyberOwca(int x, int y, Swiat& swiat);
    virtual ~CyberOwca() = default;

    // Akcja: eksterminacja barszczu sosnowskiego lub zwyczajny ruch owcy
    void akcja(Swiat& swiat) override;

    // Symbol rysowany na planszy
    char rysowanie() const override;

protected:
    // Tworzy potomka Cyber-owcy
    std::shared_ptr<Organizm> utworzPotomka(int x, int y) override;
};

#endif // CYBEROWCA_H
