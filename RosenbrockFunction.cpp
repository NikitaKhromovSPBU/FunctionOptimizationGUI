#include "RosenbrockFunction.h"

double RosenbrockFunction::evaluate(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::exception("Wrong number of parameters");
    return 100 * (parameters[1] - parameters[0] * parameters[0]) * (parameters[1] - parameters[0] * parameters[0]) +
           (parameters[0] - 1) * (parameters[0] - 1) +
           100 * (parameters[2] - parameters[1] * parameters[1]) * (parameters[2] - parameters[1] * parameters[1]) +
           (parameters[1] - 1) * (parameters[1] - 1);
}

std::vector<double> RosenbrockFunction::get_gradient(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::exception("Wrong number of parameters");
    return std::vector<double>{
        2 * (200 * parameters[0] * (parameters[0] * parameters[0] - parameters[1]) + parameters[0] - 1),
        2 * (200 * parameters[1] * (parameters[1] * parameters[1] - parameters[2]) -
             100 * parameters[0] * parameters[0] + 101 * parameters[1] - 1),
        200 * (parameters[2] - parameters[1] * parameters[1])};
}
