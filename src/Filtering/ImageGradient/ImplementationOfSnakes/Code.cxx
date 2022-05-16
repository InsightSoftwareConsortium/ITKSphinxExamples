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
#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkGradientRecursiveGaussianImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"
#include "itkImageFileReader.h"

#include "itkMath.h"
#include <vnl/vnl_matrix.h>
#include "vnl/algo/vnl_determinant.h"
#include "vnl/algo/vnl_matrix_inverse.h"
#include <vnl/vnl_vector.h>

#include <iostream>

namespace
{
using ImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
using IndexType = ImageType::IndexType;
using OutputPixelType = itk::CovariantVector<float, 2>;
using OutputImageType = itk::Image<OutputPixelType, 2>;
using FilterType = itk::GradientRecursiveGaussianImageFilter<FloatImageType, OutputImageType>;
using GradMagfilterType = itk::GradientMagnitudeImageFilter<ImageType, FloatImageType>;
} // namespace

vnl_vector<double>
generateCircle(double cx, double cy, double rx, double ry, int n);
void
createImage(ImageType::Pointer image, int w, int h, double cx, double cy, double rx, double ry);
vnl_matrix<double>
computeP(double alpha, double beta, double gamma, double N) throw();
vnl_vector<double>
sampleImage(vnl_vector<double> x, vnl_vector<double> y, OutputImageType::Pointer gradient, int position);

int
main(int argc, char * argv[])
{
  // Image dimensions
  int                w = 300;
  int                h = 300;
  ImageType::Pointer image;
  if (argc < 7)
  {
    std::cout << "Usage " << argv[0] << " points alpha beta gamma sigma iterations [image]" << std::endl;
    return EXIT_FAILURE;
  }
  else if (argc < 8)
  {
    // Synthesize the image
    image = ImageType::New();
    createImage(image, w, h, 150, 150, 50, 50);
  }
  else if (argc == 8)
  {
    try
    {
      image = itk::ReadImage<ImageType>(argv[7]);
      w = image->GetLargestPossibleRegion().GetSize()[0];
      h = image->GetLargestPossibleRegion().GetSize()[1];
    }
    catch (const itk::ExceptionObject & err)
    {
      std::cerr << "Caught unexpected exception " << err;
      return EXIT_FAILURE;
    }
  }

  // Snake parameters
  double alpha = 0.001;
  double beta = 0.4;
  double gamma = 100;
  double iterations = 1;
  int    nPoints = 20;
  double sigma;

  nPoints = std::stoi(argv[1]);
  alpha = std::stod(argv[2]);
  beta = std::stod(argv[3]);
  gamma = std::stod(argv[4]);
  sigma = std::stod(argv[5]);
  iterations = std::stoi(argv[6]);

  // Temporal variables
  vnl_matrix<double> P;
  vnl_vector<double> v;
  double             N;

  // Generate initial snake circle
  v = generateCircle(130, 130, 50, 50, nPoints);

  // Compute P matrix.
  N = v.size() / 2;
  try
  {
    P = computeP(alpha, beta, gamma, N);
  }
  catch (...)
  {
    return EXIT_FAILURE;
  }

  // Compute the magnitude gradient
  GradMagfilterType::Pointer gradientMagnitudeFilter = GradMagfilterType::New();
  gradientMagnitudeFilter->SetInput(image);
  gradientMagnitudeFilter->Update();

  // Compute the gradient of the gradient magnitude
  FilterType::Pointer gradientFilter = FilterType::New();
  gradientFilter->SetInput(gradientMagnitudeFilter->GetOutput());
  gradientFilter->SetSigma(sigma);
  gradientFilter->Update();

  // Loop
  vnl_vector<double> x(N);
  vnl_vector<double> y(N);

  std::cout << "Initial snake" << std::endl;
  for (int i = 0; i < N; ++i)
  {
    x[i] = v[2 * i];
    y[i] = v[2 * i + 1];
    std::cout << "(" << x[i] << ", " << y[i] << ")" << std::endl;
  }

  for (int i = 0; i < iterations; ++i)
  {
    vnl_vector<double> fex;
    vnl_vector<double> fey;
    fex = sampleImage(x, y, gradientFilter->GetOutput(), 0);
    fey = sampleImage(x, y, gradientFilter->GetOutput(), 1);

    x = (x + gamma * fex).post_multiply(P);
    y = (y + gamma * fey).post_multiply(P);
  }

  // Display the answer
  std::cout << "Final snake after " << iterations << " iterations" << std::endl;
  vnl_vector<double> v2(2 * N);
  for (int i = 0; i < N; ++i)
  {
    v2[2 * i] = x[i];
    v2[2 * i + 1] = y[i];
    std::cout << "(" << x[i] << ", " << y[i] << ")" << std::endl;
  }

  return EXIT_SUCCESS;
}

vnl_vector<double>
generateCircle(double cx, double cy, double rx, double ry, int n)
{
  vnl_vector<double> v(2 * (n + 1));

  for (int i = 0; i < n; ++i)
  {
    v[2 * i] = cx + rx * cos(2 * itk::Math::pi * i / n);
    v[2 * i + 1] = cy + ry * sin(2 * itk::Math::pi * i / n);
  }
  v[2 * n] = v[0];
  v[2 * n + 1] = v[1];
  return v;
}

void
createImage(ImageType::Pointer image, int w, int h, double cx, double cy, double rx, double ry)
{
  itk::Size<2> size;
  size[0] = w;
  size[1] = h;

  itk::RandomImageSource<ImageType>::Pointer randomImageSource = itk::RandomImageSource<ImageType>::New();
  randomImageSource->SetNumberOfWorkUnits(1); // to produce non-random results
  randomImageSource->SetSize(size);
  randomImageSource->SetMin(200);
  randomImageSource->SetMax(255);
  randomImageSource->Update();

  image->SetRegions(randomImageSource->GetOutput()->GetLargestPossibleRegion());
  image->Allocate();

  IndexType index;

  // Draw oval
  for (int i = 0; i < w; ++i)
  {
    for (int j = 0; j < h; ++j)
    {
      index[0] = i;
      index[1] = j;
      if (((i - cx) * (i - cx) / (rx * rx) + (j - cy) * (j - cy) / (ry * ry)) < 1)
      {
        image->SetPixel(index, randomImageSource->GetOutput()->GetPixel(index) - 100);
      }
      else
      {
        image->SetPixel(index, randomImageSource->GetOutput()->GetPixel(index));
      }
    }
  }
}

vnl_matrix<double>
computeP(double alpha, double beta, double gamma, double N) throw()
{

  double a = gamma * (2 * alpha + 6 * beta) + 1;
  double b = gamma * (-alpha - 4 * beta);
  double c = gamma * beta;

  vnl_matrix<double> P(N, N);

  P.fill(0);

  // Fill diagonal
  P.fill_diagonal(a);

  // Fill next two diagonals
  for (int i = 0; i < N - 1; ++i)
  {
    P(i + 1, i) = b;
    P(i, i + 1) = b;
  }
  // Moreover
  P(0, N - 1) = b;
  P(N - 1, 0) = b;

  // Fill next two diagonals
  for (int i = 0; i < N - 2; ++i)
  {
    P(i + 2, i) = c;
    P(i, i + 2) = c;
  }
  // Moreover
  P(0, N - 2) = c;
  P(1, N - 1) = c;
  P(N - 2, 0) = c;
  P(N - 1, 1) = c;

  if (vnl_determinant(P) == 0.0)
  {
    std::cerr << "Singular matrix. Determinant is 0." << std::endl;
    throw;
  }

  // Compute the inverse of the matrix P
  vnl_matrix<double> Pinv;
  Pinv = vnl_matrix_inverse<double>(P);

  return Pinv.transpose();
}

vnl_vector<double>
sampleImage(vnl_vector<double> x, vnl_vector<double> y, OutputImageType::Pointer gradient, int position)
{
  int size;
  size = x.size();
  vnl_vector<double> ans(size);

  IndexType index;
  for (int i = 0; i < size; ++i)
  {
    index[0] = x[i];
    index[1] = y[i];
    ans[i] = gradient->GetPixel(index)[position];
  }
  return ans;
}
