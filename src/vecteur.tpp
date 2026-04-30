// Constructors
template<int D>
Vecteur<D>::Vecteur() {
    for (int i = 0; i < D; ++i) coords[i] = 0.0;
}

template<int D>
Vecteur<D>::Vecteur(const double val[D]) {
    for (int i = 0; i < D; ++i) coords[i] = val[i];
}

template<int D>
Vecteur<D>::Vecteur(std::initializer_list<double> vals) {
    int i = 0;
    for (double v : vals) {
        if (i < D) coords[i++] = v;
    }
    for (; i < D; ++i) coords[i] = 0.0;
}

template<int D>
Vecteur<D>::Vecteur(const Vecteur& v) {
    for (int i = 0; i < D; ++i) coords[i] = v.coords[i];
}

// Member assignment operators
template<int D>
Vecteur<D>& Vecteur<D>::operator=(const Vecteur<D>& autre) {
    if (this != &autre) {
        for (int i = 0; i < D; ++i) coords[i] = autre.coords[i];
    }
    return *this;
}

template<int D>
Vecteur<D>& Vecteur<D>::operator+=(const Vecteur<D>& autre) {
    for (int i = 0; i < D; ++i) coords[i] += autre.coords[i];
    return *this;
}

template<int D>
Vecteur<D>& Vecteur<D>::operator-=(const Vecteur<D>& autre) {
    for (int i = 0; i < D; ++i) coords[i] -= autre.coords[i];
    return *this;
}

template<int D>
Vecteur<D>& Vecteur<D>::operator*=(double scalaire) {
    for (int i = 0; i < D; ++i) coords[i] *= scalaire;
    return *this;
}

// Unary minus
template<int D>
Vecteur<D> Vecteur<D>::operator-() const {
    Vecteur<D> resultat;
    for (int i = 0; i < D; ++i) resultat.coords[i] = -this->coords[i];
    return resultat;
}

// Binary operators
template<int D>
Vecteur<D> operator+(Vecteur<D> v1, const Vecteur<D>& v2) {
    v1 += v2;
    return v1;
}

template<int D>
Vecteur<D> operator-(Vecteur<D> v1, const Vecteur<D>& v2) {
    v1 -= v2;
    return v1;
}

template<int D>
Vecteur<D> operator*(Vecteur<D> v, double scalaire) {
    v *= scalaire;
    return v;
}

template<int D>
Vecteur<D> operator*(double scalaire, Vecteur<D> v) {
    return v * scalaire;
}

// I/O stream operators
template<int D>
std::ostream& operator<<(std::ostream& os, const Vecteur<D>& v) {
    os << "(";
    for (int i = 0; i < D; ++i) {
        os << v.coords[i] << (i < D - 1 ? ", " : "");
    }
    os << ")";
    return os;
}

template<int D>
std::istream& operator>>(std::istream& is, Vecteur<D>& v) {
    for (int i = 0; i < D; ++i) {
        is >> v.coords[i];
    }
    return is;
}