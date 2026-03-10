#ifndef ORGANIZM_H
#define ORGANIZM_H


#include <memory>

class Swiat;

class Organizm : public std::enable_shared_from_this<Organizm> {
public:
    Organizm(int sila, int inicjatywa, int x, int y, Swiat& swiat);
    virtual ~Organizm() = default;

    // gettery
    int getSila() const;
    int getInicjatywa() const;
    int getX() const;
    int getY() const;
    int getWiek() const;

    void ustawPozycje(int x, int y);
    void zwiekszWiek();
    void zmienSile(int delta);

    virtual void akcja(Swiat& swiat) = 0;
    virtual void kolizja(const std::shared_ptr<Organizm>& inny) = 0;
    virtual char rysowanie() const = 0;

protected:
    int sila_;
    int inicjatywa_;
    int x_;
    int y_;
    int wiek_;
    Swiat& swiat_;
};

#endif