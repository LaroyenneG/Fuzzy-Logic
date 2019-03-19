
#ifndef LOGIQUEFLOUE_ENGINE_H
#define LOGIQUEFLOUE_ENGINE_H

#include <string>

#define ENGINE_DEFAULT_POWER 0.0
#define ENGINE_DEFAULT_ROTATION 0.0
#define ENGINE_DEFAULT_FRICTION 0.0

/*
2 machines alternatives avaient pour fonction d'actionner les arbres des 2 hélices latérales. D'une hauteur de 10,70 mètres, 19,20 mètres de longueur et d'un poids de 600 tonnes ces machines s'élevaient jusqu'au pont E. Leur puissance était de 15000 cv et accomplissaient 75 révolutions par minute en vitesse de croisière contre 77 en pleine vitesse.
Les machines étaient de 4 cylindriques à triple expansion (un à haute pression à 1,37 mètres de diamètre, un à moyenne pression à 2,13 mètres de diamètre et deux à basse pression à 2,46 et 1,90 mètres de diamètres).
 */

namespace model {

    class Engine {

    private:
        std::string name;

        double rotationSpeed;       // radian / s
        double power;               // [0 - 1] %

        const double friction;            // m / s
        const double propellerDiameter;   // m
        const double propellerWeight;     // kg
        const double maxPower;  // cv

    public:

        explicit Engine(const std::string &_name, double _rotationSpeed, double _power, double _friction,
                        double _propellerDiameter, double _propellerWeight, double _maxPower);

        explicit Engine(const std::string &_name, double _propellerDiameter, double _propellerWeight, double _maxPower);

        double getRotationSpeed() const;

        const std::string &getName() const;

        double getPropulsionStrength() const;

        double getPower() const;

        void setPower(double value);
    };
}

#endif //LOGIQUEFLOUE_ENGINE_H
