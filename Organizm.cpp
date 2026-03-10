#include "Organizm.h"

Organizm::Organizm(int sila, int inicjatywa, int x, int y, Swiat& swiat)
    : sila_{sila}, inicjatywa_{inicjatywa}, x_{x}, y_{y}, wiek_{0}, swiat_{swiat} {}

int Organizm::getSila() const {
    return sila_;
}

int Organizm::getInicjatywa() const {
    return inicjatywa_;
}

int Organizm::getX() const {
    return x_;
}

int Organizm::getY() const {
    return y_;
}

int Organizm::getWiek() const {
    return wiek_;
}

void Organizm::ustawPozycje(int x, int y) {
    x_ = x;
    y_ = y;
}

void Organizm::zwiekszWiek() {
    ++wiek_;
}

void Organizm::zmienSile(int delta) {
    sila_ += delta;
};

