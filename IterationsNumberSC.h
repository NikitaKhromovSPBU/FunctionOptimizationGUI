#pragma once
#include "GeneralStopCriterion.h"

/**
 * Implements a stopping criterion based on the number of iterations.
 */
class IterationsNumberSC : public GeneralStopCriterion
{
  public:
    explicit IterationsNumberSC(size_t iterations_number = 1000)
        : GeneralStopCriterion(StopCriterionType::IterationsNumber, iterations_number){};

    IterationsNumberSC(const IterationsNumberSC& sc) = default;

    ~IterationsNumberSC() override = default;

  protected:
    /**
     * Implements a stopping criterion based on the number of iterations.
     *
     * \param trajectory Trajectory of the optimization process.
     * \param function Is not used in this criterion.
     * \return true if the optimization process should be stopped, false otherwise.
     */
    bool stop_criterion(const std::vector<std::vector<double>> &trajectory,
                        const GeneralFunction *function = nullptr) const override
    {
        return false;
    };
};
