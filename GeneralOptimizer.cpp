#include "GeneralOptimizer.h"

GeneralOptimizer::GeneralOptimizer(const GeneralFunction *f, const std::vector<double> &starting_point,
                                   RectangularArea area, const GeneralStopCriterion *sc)
    : _area(std::move(area)), _function(f), _sc(sc), _trajectory({starting_point}),
      _result_function_value(std::numeric_limits<double>::quiet_NaN())
{
    if (!_area.contains(starting_point))
        throw std::exception("Starting point must be within the given rectangular area.");
}

double GeneralOptimizer::optimize()
{
    while (!_sc->stop(_trajectory, _function))
    {
        step();
    }
    return _result_function_value = _function->evaluate(*_trajectory.rbegin());
}
