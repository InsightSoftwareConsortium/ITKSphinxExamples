//
// Created by Mathew Seng on 2019-06-03.
//
#ifndef ExampleCostFunction_h
#define ExampleCostFunction_h

#include "itkSingleValuedCostFunction.h"

namespace itk
{
class ExampleCostFunction2 : public SingleValuedCostFunction
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ExampleCostFunction2);
  /** Standard class typedefs. */
  typedef ExampleCostFunction2     Self;
  typedef SingleValuedCostFunction Superclass;
  typedef SmartPointer<Self>       Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ExampleCostFunction2, SingleValuedCostfunction);

  unsigned int
  GetNumberOfParameters() const override
  {
    return 2;
  } // itk::CostFunction

  MeasureType
  GetValue(const ParametersType & parameters) const override
  {
    return pow(parameters[0] + 5, 2) + pow(parameters[1] - 7, 2) + 5;
  }

  void
  GetDerivative(const ParametersType &, DerivativeType & /*derivative*/) const override
  {
    throw itk::ExceptionObject(__FILE__, __LINE__, "No derivative is available for this cost function.");
  }

protected:
  ExampleCostFunction2() = default;
  ~ExampleCostFunction2() override = default;
};

} // end namespace itk

#endif
