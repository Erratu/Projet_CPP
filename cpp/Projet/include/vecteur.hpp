class Vecteur {
public:
    float x;
    float y;
    float z;

    Vecteur(float x, float y, float z) : x(x), y(y), z(z) {};

    Vecteur operator+(const Vecteur& v) const;
    Vecteur operator-(const Vecteur& v) const;
    Vecteur operator*(double scalaire) const;

    float produitScalaire(const Vecteur& v) const;

    void afficher() const;
}