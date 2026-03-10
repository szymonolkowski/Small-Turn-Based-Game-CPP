#include "WilczeJagody.h"
#include "Swiat.h"
#include "Zwierze.h"
#include <string>

WilczeJagody::WilczeJagody(int x, int y, Swiat& swiat)
    : Roslina(x, y, swiat) {}

void WilczeJagody::akcja(Swiat& swiat) {
    Roslina::akcja(swiat);
}

void WilczeJagody::kolizja(const std::shared_ptr<Organizm>& inny) {
    if (std::dynamic_pointer_cast<Zwierze>(inny)) {
        swiat_.usunOrganizm(inny);
        swiat_.dodajDoLogu("Zwierze zginalo po zjedzeniu wilczych jagod");
    }
    Roslina::kolizja(inny);
}

char WilczeJagody::rysowanie() const {
    return 'J';
}

std::shared_ptr<Organizm> WilczeJagody::utworzSadzonke(int x, int y) {
    return std::make_shared<WilczeJagody>(x, y, swiat_);
}
