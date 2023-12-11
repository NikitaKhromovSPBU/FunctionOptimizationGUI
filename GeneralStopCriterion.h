#pragma once
#include "GeneralFunction.h"
#include <vector>

/**
 * Abstract class for optimization processes stopping criteria.
 */
class GeneralStopCriterion
{
  public:
    enum class StopCriterionType
    {
        AbsoluteValueDifference,
        RelativeDifference,
        IterationsNumber,
    };

  protected:
    size_t _iterations_number;

    StopCriterionType _sc_type;

  public:
    GeneralStopCriterion(StopCriterionType sc_type, size_t iterations_number = 1000)
        : _iterations_number(iterations_number), _sc_type(sc_type){};

    /**
     * Checks whether to stop the optimization process based on the given trajectory.
     *
     * \param trajectory Trajectory of the optimization process.
     * \param function A function being optimized. Is nullptr if not needed.
     * \return true if the optimization process should be stopped, false otherwise.
     */
    bool stop(const std::vector<std::vector<double>> &trajectory, const GeneralFunction *function = nullptr) const
    {
        return (trajectory.size() >= _iterations_number) || stop_criterion(trajectory, function);
    };

    void set_iterations_number(size_t iterations_number)
    {
        _iterations_number = iterations_number;
    };

    size_t get_iterations_number() const
    {
        return _iterations_number;
    };

    StopCriterionType get_stop_criterion_type() const { return _sc_type; };

    virtual ~GeneralStopCriterion() = default;

  protected:
    virtual bool stop_criterion(const std::vector<std::vector<double>> &trajectory,
                                const GeneralFunction *function = nullptr) const = 0;
};
