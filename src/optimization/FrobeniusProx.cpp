/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"

// The Frobenius norm prox returns the solution to
//     arg min || A ||_F + tau/2 || A - A0 ||_F^2
//        A

namespace El {

template<typename F>
void FrobeniusProx( Matrix<F>& A, Base<F> tau )
{
    DEBUG_ONLY(CallStackEntry cse("FrobeniusProx"))
    const Base<F> frobNorm = FrobeniusNorm( A );
    if( frobNorm > 1/tau )
        Scale( 1-1/(tau*frobNorm), A );
    else
        Zero( A );
}

template<typename F>
void FrobeniusProx( AbstractDistMatrix<F>& A, Base<F> tau )
{
    DEBUG_ONLY(CallStackEntry cse("FrobeniusProx"))
    const Base<F> frobNorm = FrobeniusNorm( A );
    if( frobNorm > 1/tau )
        Scale( 1-1/(tau*frobNorm), A );
    else
        Zero( A );
}

#define PROTO(F) \
  template void FrobeniusProx( Matrix<F>& A, Base<F> tau ); \
  template void FrobeniusProx( AbstractDistMatrix<F>& A, Base<F> tau );

PROTO(float)
PROTO(double)
PROTO(Complex<float>)
PROTO(Complex<double>)

} // namespace El