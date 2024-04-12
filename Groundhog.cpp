/*
** EPITECH PROJECT, 2024
** Groundhog
** File description:
** groundhog
*/

#include "Groundhog.hpp"

Groundhog::Groundhog()
{
    _period = 0;
    _switcher = 0;
    _increase = 0;
    _evolution = 0;
    _deviation = 0;
    _last_evolution = 0;
}

Groundhog::~Groundhog()
{
}

void Groundhog::setPeriod(int period)
{
    _period = period;
}

void Groundhog::loop()
{
    std::string line;
    while (1) {
        getline(std::cin, line);
        if (line == "STOP") {
            if (_values.size() < _period) {
                std::cout << "Global tendency switched " << _switcher << " times" << std::endl;
                exit(84);
            } else {
                break;
            }
        }
        try {
            std::stod(line);
            _values.push_back(std::stod(line));
            get_increase();
            get_evolution();
            get_deviation();
            chek_switch();
        } catch (std::exception &e) {
            exit(84);
        }
    }
    std::cout << "Global tendency switched " << _switcher << " times" << std::endl;
}

void Groundhog::get_increase()
{
    double sumIncrease = 0;
    int countIncrease = 0;
    _increase = 0;

    if (_values.size() < _period + 1) {
        std::cout << "g=nan\t\t";
        return;
    }
    for (size_t i = _values.size() - _period; i < _values.size(); ++i) {
        if (_values[i] > _values[i - 1]) {
            sumIncrease += _values[i] - _values[i - 1];
        }
    }
    _increase = sumIncrease / _period;
    std::cout << "g=" << std::setprecision(2) << _increase << "\t\t";
}

void Groundhog::get_evolution()
{
    int size = _values.size();
    _last_evolution = _evolution;
    if (_values.size() < _period + 1) {
        std::cout << "r=nan%\t\t";
        return;
    }
    _evolution = (_values[size - 1] - _values[size - _period - 1]) / _values[size - _period - 1] * 100.0;
    int evolution = round(_evolution);
    std::cout << "r=" << std::setprecision(1) << evolution << "%\t\t";
}

void Groundhog::get_deviation()
{
    double sum = 0;
    double mean = 0;

    if (_values.size() < _period) {
        std::cout << "s=nan" << std::endl;
        return;
    }
    for (size_t i = _values.size() - _period; i < _values.size(); ++i) {
        sum += _values[i];
    }
    mean = sum / _period;
    sum = 0;
    for (size_t i = _values.size() - _period; i < _values.size(); ++i) {
        sum += pow(_values[i] - mean, 2);
    }
    _deviation = sqrt(sum / _period);
    std::cout << "s=" << std::fixed << std::setprecision(2) << _deviation <<"\t";
}

void Groundhog::chek_switch()
{
    if (_values.size() < _period) {
        return;
    }
    if (_last_evolution < 0 && _evolution > 0 || _last_evolution > 0 && _evolution < 0) {
        _switcher += 1;
        std::cout << "\ta switch occurs" << std::endl;
    } else
        std::cout << std::endl;
}

// Créer une fonction qui prédit la prochaine valeur en fonction de la tendance actuelle
// Stocker la valeur prédite dans un attribut de la classe
// Faire la différence entre la valeur prédite et la valeur réelle
// stocker dans un std::pair la valeur donner et la différence
// Trier les valeurs dans l'ordre décroissant en fonction de la différence
// Afficher les 5 premières valeurs après le tri