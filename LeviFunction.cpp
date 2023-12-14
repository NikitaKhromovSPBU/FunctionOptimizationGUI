#include "LeviFunction.h"
#include <stdexcept>

double LeviFunction::evaluate(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::logic_error("Wrong number of parameters");
    return sin(3 * PI * parameters[0]) * sin(3 * PI * parameters[0]) +
           (parameters[0] - 1) * (parameters[0] - 1) * (1 + sin(3 * PI * parameters[1]) * sin(3 * PI * parameters[1])) +
           (parameters[1] - 1) * (parameters[1] - 1) * (1 + sin(2 * PI * parameters[1]) * sin(2 * PI * parameters[1]));
}

std::vector<double> LeviFunction::get_gradient(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::logic_error("Wrong number of parameters");
    return std::vector<double>{2 * (parameters[0] - 1) *
                                       (1 + sin(3 * PI * parameters[1]) * sin(3 * PI * parameters[1])) +
                                   6 * PI * sin(3 * PI * parameters[0]) * cos(3 * PI * parameters[0]),
                               3 * PI * (parameters[0] - 1) * (parameters[0] - 1) * sin(6 * PI * parameters[1]) +
                                   2 * PI * (parameters[1] - 1) * (parameters[1] - 1) * sin(4 * PI * parameters[1]) -
                                   (parameters[1] - 1) * (cos(4 * PI * parameters[1]) - 3)};
}

const double LeviFunction::PI = acos(-1);
