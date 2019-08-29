#ifndef itkExampleCostFunction_h
#define itkExampleCostFunction_h

#include "itkMultipleValuedCostFunction.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"
#include <cmath>
#include <vector>

namespace itk
{
class ExampleCostFunction : public MultipleValuedCostFunction
{
public:
  /** Standard class type alias. */
  using Self = ExampleCostFunction;
  using Superclass = MultipleValuedCostFunction;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ExampleCostFunction, MultipleValuedCostFunction);

  // The equation we're fitting is y=C*e^(K*x)
  // The free parameters which we're trying to fit are C and K
  // Therefore, there are two parameters
  unsigned int
  GetNumberOfParameters() const override
  {
    return 2;
  }

  // We will take a curve with concrete values for C and K,
  // which has been corrupted by Gaussian noise, and sample
  // it at 100 points on the interval [0,1].  Each of these
  // points will produce a residual with the expected value.
  // Therefore, there are 100 values (aka residuals).
  unsigned int
  GetNumberOfValues() const override
  {
    return 100;
  }

  // Calculate the residual array, given a set of parameters.
  // We take parameters[0] to be C and parameters[1] to be K.
  // Therefore, this is a matter of calculating the value of y
  // at each of the sampled points, given the provided guesses
  // for C and K, and returning the difference from the data.
  MeasureType
  GetValue(const ParametersType & parameters) const override
  {
    MeasureType residual(this->GetNumberOfValues());
    double      predictedC = parameters[0];
    double      predictedK = parameters[1];
    for (unsigned int i = 0; i < 100; ++i)
    {
      double position = double(i) / 100;
      double prediction = predictedC * exp(position * predictedK);
      residual[i] = prediction - y[i];
    }
    return residual;
  }

  // The "derivative" is the Jacobian, which takes the derivative
  // of each residual with respect to each parameter.  Since this
  // class does not provide a derivative, any optimizer using this
  // cost function must be told explicitly not to ask for derivative,
  // otherwise an exception will the thrown.
  void
  GetDerivative(const ParametersType & /*parameters*/, DerivativeType & /*derivative*/) const override
  {
    throw ExceptionObject(__FILE__, __LINE__, "No derivative available.");
  }

protected:
  ExampleCostFunction()
  {
    // Create some data
    // Take the curve y = C*e^(K*x), add noise, and sample at 100 points on [0,1]
    // C and K are our parameters
    // In the actual data, these parameters are 5.5 and 0.5
    using GeneratorType = itk::Statistics::MersenneTwisterRandomVariateGenerator;
    GeneratorType::Pointer randomEngine = GeneratorType::New();
    double                 actualC = 5.5;
    double                 actualK = 0.5;
    for (unsigned int i = 0; i < 100; ++i)
    {
      double position = double(i) / 100;
      this->x.push_back(position);
      this->y.push_back(actualC * exp(position * actualK) + randomEngine->GetUniformVariate(0.0, 0.5));
    }
  };
  ~ExampleCostFunction() override = default;
  ;

private:
  ExampleCostFunction(const Self &) = delete; // purposely not implemented
  void
  operator=(const Self &) = delete; // purposely not implemented

  // The x and y positions of the data, created in the constructor
  std::vector<double> x;
  std::vector<double> y;
};

} // end namespace itk

#endif
