/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkAmoebaOptimizer.h"
#include "ExampleCostFunction.h"

namespace
{
// Typedef the optimizer and cost function, for convenience
using OptimizerType = itk::AmoebaOptimizer;
using CostType = itk::ExampleCostFunction2;
} // namespace

int
main()
{

  // Instantiate the optimizer
  OptimizerType::Pointer optimizer = OptimizerType::New();

  // Set properties pertinent to convergence
  optimizer->SetMaximumNumberOfIterations(100);
  optimizer->SetParametersConvergenceTolerance(0.01);
  optimizer->SetFunctionConvergenceTolerance(0.01);

  // Instantiate the cost function
  // The cost function is a 2D paraboloid in the x-y plane
  // with the equation f(x,y) = (x+5)^2+(y-7)^2 + 5
  // and a global minimum at (x,y) = (-5, 7)
  CostType::Pointer cost = CostType::New();

  // Assign the cost function to the optimizer
  optimizer->SetCostFunction(cost.GetPointer());

  // Set the initial parameters of the cost function
  OptimizerType::ParametersType initial(2);
  initial[0] = 123;
  initial[1] = -97.4;
  optimizer->SetInitialPosition(initial);

  // Begin the optimization!
  optimizer->StartOptimization();

  // Print out some information about the optimization
  std::cout << "Position: " << optimizer->GetCurrentPosition() << std::endl;
  std::cout << "Value: " << optimizer->GetValue() << std::endl;

  // As expected, the position is near to (-5, 7) and the value to 5
  // Position: [-5.003825599641884, 6.998563761340231]
  // Value: 5.00002
  return EXIT_SUCCESS;
}
