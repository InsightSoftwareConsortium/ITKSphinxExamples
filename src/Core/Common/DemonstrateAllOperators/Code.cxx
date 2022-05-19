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
#include <itkNeighborhoodOperator.h>

#include <itkDerivativeOperator.h>
#include <itkForwardDifferenceOperator.h>
#include <itkGaussianDerivativeOperator.h>
#include <itkGaussianOperator.h>
#include <itkImageKernelOperator.h>
#include <itkLaplacianOperator.h>
#include <itkSobelOperator.h>
#include <itkAnnulusOperator.h>
#include <itkBackwardDifferenceOperator.h>

#include <vector>

int
main()
{
  using DerivativeOperatorType = itk::DerivativeOperator<float, 2>;
  using ForwardDifferenceOperatorType = itk::ForwardDifferenceOperator<float, 2>;
  using GaussianDerivativeOperatorType = itk::GaussianDerivativeOperator<float, 2>;
  using GaussianOperatorType = itk::GaussianOperator<float, 2>;
  using ImageKernelOperatorType = itk::ImageKernelOperator<float, 2>;
  using LaplacianOperatorType = itk::LaplacianOperator<float, 2>;
  using SobelOperatorType = itk::SobelOperator<float, 2>;
  using AnnulusOperatorType = itk::AnnulusOperator<float, 2>;
  using BackwardDifferenceOperatorType = itk::BackwardDifferenceOperator<float, 2>;

  std::vector<itk::NeighborhoodOperator<float, 2> *> operators;
  operators.push_back(new DerivativeOperatorType);
  operators.push_back(new ForwardDifferenceOperatorType);
  operators.push_back(new GaussianDerivativeOperatorType);
  operators.push_back(new GaussianOperatorType);
  operators.push_back(new ImageKernelOperatorType);
  operators.push_back(new LaplacianOperatorType);
  operators.push_back(new SobelOperatorType);
  operators.push_back(new AnnulusOperatorType);
  operators.push_back(new BackwardDifferenceOperatorType);

  itk::Size<2> radius;
  radius.Fill(1);

  for (auto & operatorId : operators)
  {
    operatorId->SetDirection(0); // Create the operator for the X axis derivative
    operatorId->CreateToRadius(radius);
    // std::cout << *(operators[operatorId]) << std::endl;
    // operators[operatorId]->Print(std::cout);
    // std::cout << operators[operatorId]->GetNameOfClass() << std::endl;

    for (auto i = -operatorId->GetSize()[0] / 2; i <= operatorId->GetSize()[0] / 2; i++)
    {
      for (auto j = -operatorId->GetSize()[1] / 2; j <= operatorId->GetSize()[1] / 2; j++)
      {
        itk::Offset<2> offset;
        offset[0] = i;
        offset[1] = j;

        unsigned int neighborhoodIndex = operatorId->GetNeighborhoodIndex(offset);
        std::cout << operatorId->GetElement(neighborhoodIndex) << " ";
      }
      std::cout << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
