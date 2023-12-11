#pragma once
#include "GeneralOptimizer.h"
#include <random>

/**
 * Implementation of the stohastic method of optimization.
 */
class StohasticOptimizer : public GeneralOptimizer
{
  protected:
    /**
     * Probability of generating a point inside the vicinity of the last point.
     */
    double _p;

    /**
     * Radius of the ball in the Chebyshev metric in which the new point might be generated with probability _p.
     */
    double _delta;
    double _delta0;

    /**
     * _delta reduction rate.
     * \f$ \delta_{i+1} = \alpha \delta_{i}\f$
     */
    double _alpha;

    double _current_function_value;

  private:
    std::mt19937 _generator;

    static std::uniform_real_distribution<> _U01;

  public:
    StohasticOptimizer(const GeneralFunction *f, std::vector<double> starting_point, RectangularArea area,
                       const GeneralStopCriterion *sc, double p = 0.5, double delta = 1, double alpha = 0.5);

    ~StohasticOptimizer() override = default;

  protected:
    void step() override;
};
