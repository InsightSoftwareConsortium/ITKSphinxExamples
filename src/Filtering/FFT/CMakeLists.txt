add_example( FilterImageInFourierDomain )
compare_to_baseline( FilterImageInFourierDomain Output --tolerance-intensity 5 )
add_example( ComputeImageSpectralDensity )
compare_to_baseline( ComputeImageSpectralDensity Output --tolerance-intensity 5 )
