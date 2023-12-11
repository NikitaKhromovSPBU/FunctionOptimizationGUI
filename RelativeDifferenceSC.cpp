#include "RelativeDifferenceSC.h"

bool RelativeDifferenceSC::stop_criterion(const std::vector<std::vector<double>> &trajectory,
                                          const GeneralFunction *function) const
{
    if (!function)
        throw std::exception("A function must be given for this stop criterion.");

    auto iter{trajectory.rbegin()}, last_point{iter};
    for (; iter != trajectory.rend() && *iter == *last_point; ++iter)
    {
    };

    double previous_function_value;
    if (iter == trajectory.rend() ||
        (iter - last_point < _iterations_number / 10 &&
         ((previous_function_value = function->evaluate(*iter)) - function->evaluate(*last_point)) /
                 abs(previous_function_value) >= _precision))
        return false;
    return true;
}
