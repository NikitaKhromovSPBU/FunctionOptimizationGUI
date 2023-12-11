#pragma once
#include "GeneralOptimizer.h"
class FletcherReevesOptimizer : public GeneralOptimizer
{
  protected:
    double _alpha;
    double _beta;
    std::vector<double> _grad_prev, _grad_new, _p;

  public:
    FletcherReevesOptimizer(const GeneralFunction *f, std::vector<double> starting_point, RectangularArea area,
                            const GeneralStopCriterion *sc);

    ~FletcherReevesOptimizer() override = default;

    static const double golden_ratio;

  protected:
    void step() override;
};
