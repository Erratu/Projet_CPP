class Particule {
public:
    float x, y, z; // Position
    float vx, vy, vz; // Vitesse
    float masse; // Masse
    int id; // Identifiant unique
    const char* type; // Catégorie de la particule
    float forceX, forceY, forceZ; // Force appliquée à la particule
    void afficher();

    Particule(float x, float y, float z, float vx, float vy, float vz, float masse, int id, const char* type, float forceX, float forceY, float forceZ) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
        this->masse = masse;
        this->id = id;
        this->type = type;
        this->forceX = forceX;
        this->forceY = forceY;
        this->forceZ = forceZ;
    }
};