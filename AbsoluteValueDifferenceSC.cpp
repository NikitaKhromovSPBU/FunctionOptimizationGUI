#include "AbsoluteValueDifferenceSC.h"

bool AbsoluteValueDifferenceSC::stop_criterion(const std::vector<std::vector<double>> &trajectory,
                                               const GeneralFunction *function) const
{
    if (!function)
        throw std::exception("A function must be given for this stop criterion.");

    auto iter{trajectory.rbegin()}, last_point{iter};
    for (; iter != trajectory.rend() && *iter == *last_point; ++iter)
    {
    };

    if (iter == trajectory.rend() || (iter - last_point < _iterations_number / 10 &&
                                      function->evaluate(*iter) - function->evaluate(*last_point) >= _precision))
        return false;
    return true;
}
