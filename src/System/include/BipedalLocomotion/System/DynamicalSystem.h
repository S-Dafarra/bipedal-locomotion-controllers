/**
 * @file DynamicalSystem.h
 * @authors Giulio Romualdi
 * @copyright 2020 Istituto Italiano di Tecnologia (IIT). This software may be modified and
 * distributed under the terms of the GNU Lesser General Public License v2.1 or any later version.
 */

#ifndef BIPEDAL_LOCOMOTION_SYSTEM_DYNAMICAL_SYSTEM_H
#define BIPEDAL_LOCOMOTION_SYSTEM_DYNAMICAL_SYSTEM_H

#include <memory>
#include <tuple>

#include <BipedalLocomotion/GenericContainer/TemplateHelpers.h>
#include <BipedalLocomotion/ParametersHandler/IParametersHandler.h>

namespace BipedalLocomotion
{
namespace System
{

/**
 * DynamicalSystem defines a continuous time dynamical system, i.e. \f$\dot{x}=f(x, u, t)\f$. Please
 * inherit publicly from this class in order to define your custom dynamical system.
 * @tparam State type used for describing the state (i.e. it has to be a std::tuple vectors/matrices
 * or in general classes).
 * @tparam StateDerivative type used for describing the state derivative (i.e. it has to be a
 * std::tuple of vectors/matrices or in general classes).
 * @tparam Input type used for describing the input (i.e. it has to be a std::tuple of
 * vectors/matrices or in general classes).
 */
template <typename State, typename StateDerivative, typename Input>
class DynamicalSystem
{
    static_assert(is_specialization<State, std::tuple>::value,
                  "The State type must be a specialization of the std::tuple. E.g. "
                  "std::tuple<iDyntree::Position, iDynTree::Rotation>");

    static_assert(is_specialization<StateDerivative, std::tuple>::value,
                  "The StateDerivative type must be a specialization of the std::tuple. E.g. "
                  "std::tuple<iDyntree::Vector3, iDynTree::Vector3>");

    static_assert(is_specialization<Input, std::tuple>::value,
                  "The Input type must be a specialization of the std::tuple. E.g. "
                  "std::tuple<iDyntree::Vector3, iDynTree::Vector3>");

public:
    using StateType = State; /**< State space type */
    using StateDerivativeType = StateDerivative; /**< State space derivative type */
    using InputType = Input; /**< Input type */

protected:
    InputType m_controlInput; /**< Value of the control input */
    StateType m_state; /**< Value of the current state of the system */

public:

    /**
     * Initialize the Dynamical system.
     * @param handler pointer to the parameter handler.
     * @return true in case of success/false otherwise.
     */
    virtual bool initalize(std::weak_ptr<ParametersHandler::IParametersHandler> handler);

    /**
     * Set the state of the dynamical system.
     * @note In principle, there is no need to override this method. This value is stored in an
     * internal buffer.
     * @param state tuple containing a const reference to the state elements.
     * @return true in case of success, false otherwise.
     */
    virtual bool setState(const StateType& state);

    /**
     * Get the state to the dynamical system.
     * @return the current state of the dynamical system
     */
    const StateType & getState() const;

    /**
     * Set the control input to the dynamical system.
     * @note In principle, there is no need to override this method. This value is stored in an
     * internal buffer.
     * @param controlInput the value of the control input used to compute the system dynamics.
     * @return true in case of success, false otherwise.
     */
    virtual bool setControlInput(const InputType& controlInput);

    /**
     * Computes the system dynamics. It return \f$f(x, u, t)\f$.
     * @note The control input and the state have to be set separately with the methods
     * setControlInput and setState.
     * @param time the time at witch the dynamics is computed.
     * @param stateDynamics tuple containing a reference to the element of the state derivative
     * @warning Please implement the function in your custom dynamical system.
     * @return true in case of success, false otherwise.
     */
    virtual bool dynamics(const double& time, StateDerivativeType& stateDerivative) = 0;

    /**
     * Destructor
     */
    ~DynamicalSystem() = default;
};

} // namespace System
} // namespace BipedalLocomotion

#include <BipedalLocomotion/System/DynamicalSystem.tpp>

#endif // BIPEDAL_LOCOMOTION_SYSTEM_DYNAMICAL_SYSTEM_H
