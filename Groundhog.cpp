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
                std::cout << "Not enough values" << std::endl;
                exit(84);
            } else {
                std::cout << "Global tendency switched " << _switcher << " times" << std::endl;
                check_weird();
                break;
            }

        }
        if (line.find(',') != std::string::npos) {
            exit(84);
        }
        try {
            std::stod(line);
            _values.push_back(std::stod(line));
            get_increase();
            get_evolution();
            get_deviation();
            check_switch();
        } catch (std::exception &e) {
            exit(84);
        }
    }
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
    for (size_t i = _values.size() - _period; i < _values.size(); i++) {
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
    std::cout << "s=" << std::fixed << std::setprecision(2) << _deviation;
}

void Groundhog::check_switch()
{
    if (_values.size() < _period) {
        return;
    }
    if (_last_evolution < 0 && _evolution >= 0 || _last_evolution >= 0 && _evolution < 0) {
        _switcher += 1;
        std::cout << "\t\ta switch occurs" << std::endl;
    } else
        std::cout << std::endl;
}

double sort_by_diff(const std::pair<double, double>& a, const std::pair<double, double>& b)
{
    return a.second < b.second;
};

std::vector<std::pair<double, double>> calculate_weird_values(const std::vector<double>& _values, int _period)
{
    std::vector<std::pair<double, double>> weird_values;
    for (int i = 0; i < _values.size() - _period + 1; ++i) {
        double mean = 0.0;
        double et = 0.0;
        double ecart = 0.0;
        int index = _period - 1;
        // Calcul de la moyenne mobile
        for (int j = i; j < i + _period; ++j) {
            mean += _values[j];
        }
        mean /= _period;

        // Calcul de l'écart-type
        for (int j = i; j < i + _period; ++j) {
            et += (_values[j] - mean) * (_values[j] - mean);
        }
        et = std::sqrt(et / _period);

        double bb_upper = mean + (2 * et);
        double bb_lower = mean - (2 * et);
        //printf("valeur = %f / moyenne = %f / ecart-type = %f / bb_sup = %f (%f) / bb_inf = %f (%f)\n",_values[i + index], mean, et, bb_upper, bb_upper - _values[i + index], bb_lower, _values[i + index] - bb_lower);

        if (_values[i + index] - bb_lower > (bb_upper - _values[i + index])) {
            ecart = bb_upper - _values[i + index];
        } else {
            ecart = _values[i + index] - bb_lower;
        }

        weird_values.push_back(std::make_pair(_values[i + index], ecart));
    }
    std::sort(weird_values.begin(), weird_values.end(), sort_by_diff);
    return (weird_values);
}

void Groundhog::check_weird()
{
    std::vector<std::pair<double, double>> weird_values;
    weird_values = calculate_weird_values(_values, _period);

    if (weird_values.size() < 5) {
        return;
    }
    std::cout << "5 weirdest values are [";
    for (int i = 0; i < 5 && i < weird_values.size(); ++i) {
        std::cout << std::fixed << std::setprecision(1) << weird_values[i].first;
        if (i < 4) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
