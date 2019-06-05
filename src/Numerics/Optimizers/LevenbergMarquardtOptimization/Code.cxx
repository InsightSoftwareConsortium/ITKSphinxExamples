/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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
// Include the Levenberg-Marquardt optimizer and a custom cost function
#include "itkLevenbergMarquardtOptimizer.h"
#include "itkExampleCostFunction.h"

// Typedef the optimizer and cost function, for convenience
using OptimizerType = itk::LevenbergMarquardtOptimizer;
using CostType = itk::ExampleCostFunction;

int main(int, char *[])
{

    // Instantiate the cost function and optimizer
    CostType::Pointer cost = CostType::New();
    OptimizerType::Pointer optimizer = OptimizerType::New();

    optimizer->SetNumberOfIterations( 100 );
    optimizer->UseCostFunctionGradientOff();
    optimizer->SetCostFunction( cost.GetPointer());

    // This is the initial guess for the parameter values, which we set to one
    CostType::ParametersType p(cost->GetNumberOfParameters());
    p.Fill( 1 );
    optimizer->SetInitialPosition(p);
    optimizer->StartOptimization();

    // Print out some information about the optimization
    // The parameters come out to be near to, but not exactly [5.5, 0.5]
    std::cout << "Position: " << optimizer->GetCurrentPosition() << std::endl;
    std::cout << "Value: " << optimizer->GetValue() << std::endl;

    return EXIT_SUCCESS;

}
