#include "ExpModulatedSin.h"
#include <stdexcept>

double ExpModulatedSin::evaluate(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::logic_error("Wrong number of parameters");
    return exp(parameters[0]) * sin(parameters[1]);
}

std::vector<double> ExpModulatedSin::get_gradient(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::logic_error("Wrong number of parameters");
    return std::vector<double>{evaluate(parameters), exp(parameters[0]) * cos(parameters[1])};
}
