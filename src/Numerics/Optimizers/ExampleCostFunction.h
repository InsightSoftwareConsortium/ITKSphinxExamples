//
// Created by Mathew Seng on 2019-06-03.
//
#ifndef ExampleCostFunction_h
#define ExampleCostFunction_h

#include "../../../../ITK/Modules/Numerics/Optimizers/include/itkSingleValuedCostFunction.h"

namespace itk
{
    class ExampleCostFunction2 :
            public SingleValuedCostFunction
    {
    public:
        /** Standard class typedefs. */
        typedef ExampleCostFunction2      Self;
        typedef SingleValuedCostFunction  Superclass;
        typedef SmartPointer<Self>        Pointer;
        typedef SmartPointer<const Self>  ConstPointer;

        /** Method for creation through the object factory. */
        itkNewMacro(Self);

        /** Run-time type information (and related methods). */
        itkTypeMacro(ExampleCostFunction2, SingleValuedCostfunction);

        unsigned int GetNumberOfParameters(void) const { return 2; } // itk::CostFunction

        MeasureType GetValue(const ParametersType & parameters) const {
            return pow(parameters[0]+5, 2)+pow(parameters[1]-7, 2)+5;
        }

        void GetDerivative(const ParametersType &,
                           DerivativeType & derivative ) const {
            throw itk::ExceptionObject( __FILE__, __LINE__, "No derivative is available for this cost function.");
        }

    protected:
        ExampleCostFunction2(){};
        ~ExampleCostFunction2(){};

    private:
        ExampleCostFunction2(const Self &); //purposely not implemented
        void operator = (const Self &); //purposely not implemented
    };

} // end namespace itk

#endif