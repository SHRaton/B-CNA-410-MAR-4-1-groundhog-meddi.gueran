/*
** EPITECH PROJECT, 2024
** Groundhog
** File description:
** groundhong
*/

#ifndef GROUNDHOG_HPP_
#define GROUNDHOG_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

class Groundhog {
    public:
        Groundhog();
        ~Groundhog();
        void loop();
        void setPeriod(int period);
        void get_increase();
        void get_evolution();
        void get_deviation();
        void check_switch();
        void check_weird();
        void get_predict();
    protected:
    private:
        int _period;
        int _switcher;
        std::vector<int> _weird;
        std::vector<double> _values;
        double _increase;
        double _evolution;
        double _deviation;
        double _last_evolution;
        std::pair<double, double> _predict;
};



#endif /* !GROUNDHONG_HPP_ */
