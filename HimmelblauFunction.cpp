#include "HimmelblauFunction.h"
#include <stdexcept>

double HimmelblauFunction::evaluate(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::logic_error("Wrong number of parameters");
    return (parameters[0] * parameters[0] + parameters[1] - 11) * (parameters[0] * parameters[0] + parameters[1] - 11) +
           (parameters[0] + parameters[1] * parameters[1] - 7) * (parameters[0] + parameters[1] * parameters[1] - 7);
}

std::vector<double> HimmelblauFunction::get_gradient(const std::vector<double> &parameters) const
{
    if (parameters.size() != get_dimensions())
        throw std::logic_error("Wrong number of parameters");
    return std::vector<double>{4 * parameters[0] * (parameters[0] * parameters[0] + parameters[1]) -
                                   42 * parameters[0] + 2 * parameters[1] * parameters[1] - 14,
                               4 * parameters[1] * (parameters[1] * parameters[1] + parameters[0]) -
                                   26 * parameters[1] + 2 * parameters[0] * parameters[0] - 22};
}
