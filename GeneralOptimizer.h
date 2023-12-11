#pragma once
#include <limits>
#include <vector>

#include "AbsoluteValueDifferenceSC.h"
#include "ExpModulatedSin.h"
#include "HimmelblauFunction.h"
#include "IterationsNumberSC.h"
#include "LeviFunction.h"
#include "RectangularArea.h"
#include "RelativeDifferenceSC.h"
#include "RosenbrockFunction.h"

/**
 * Abstract class for implementing a set of optimization processes.
 */
class GeneralOptimizer
{
  protected:
    /**
     * Function to optimize.
     */
    const GeneralFunction *_function;
    /**
     * Trajectory of the optimization process.
     */
    std::vector<std::vector<double>> _trajectory;
    /**
     * Stop criterion.
     */
    const GeneralStopCriterion *_sc;
    /**
     * Area in which the function is optimized.
     */
    RectangularArea _area;
    /**
     * Value of the function on the last point of the optimization process.
     */
    double _result_function_value;

  public:
    GeneralOptimizer(const GeneralFunction *f, const std::vector<double> &starting_point, RectangularArea area,
                     const GeneralStopCriterion *sc);

    /**
     * Performs the optimization process.
     *
     * \return Value of the function on the last point of the optimization process.
     */
    double optimize();

    /**
     * Only usable after the optimization process, otherwise returns NaN.
     *
     * \return Value of the function on the last point of the optimization process.
     */
    double get_optimized_value() const
    {
        return _result_function_value;
    };

    /**
     * Only usable after the optimization process, otherwise returns the starting point.
     *
     * \return Last point of the optimization process.
     */
    std::vector<double> get_optimizing_point() const
    {
        return *_trajectory.rbegin();
    };

    size_t trajectory_size() const
    {
        return _trajectory.size();
    };

    virtual ~GeneralOptimizer(){};

  protected:
    /**
     * Performs transition from \f$ x_{n} \f$ to \f$ x_{n+1} \f$.
     */
    virtual void step() = 0;
};
