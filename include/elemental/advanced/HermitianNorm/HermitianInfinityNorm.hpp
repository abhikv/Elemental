/*
   Copyright (c) 2009-2011, Jack Poulson
   All rights reserved.

   This file is part of Elemental.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

    - Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    - Neither the name of the owner nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

// The operator L1 and Linf norms for Hermitian matrices are identical. The 
// former is the maximum column L1 norm and the latter is the maximum row L1 
// norm. Hermiticity implies their equivalence.

template<typename R> // representation of a real number
inline R
elemental::advanced::internal::HermitianInfinityNorm
( UpperOrLower uplo, const Matrix<R>& A )
{
#ifndef RELEASE
    PushCallStack("advanced::internal::HermitianInfinityNorm");
#endif
    R maxRowSum = advanced::internal::HermitianOneNorm( uplo, A );
#ifndef RELEASE
    PopCallStack();
#endif
    return maxRowSum;
}

template<typename R> // representation of a real number
inline R
elemental::advanced::internal::HermitianInfinityNorm
( UpperOrLower uplo, const Matrix<std::complex<R> >& A )
{
#ifndef RELEASE
    PushCallStack("advanced::internal::HermitianInfinityNorm");
#endif
    R maxRowSum = advanced::internal::HermitianOneNorm( uplo, A );
#ifndef RELEASE
    PopCallStack();
#endif
    return maxRowSum;
}

template<typename R> // representation of a real number
inline R
elemental::advanced::internal::HermitianInfinityNorm
( UpperOrLower uplo, const DistMatrix<R,MC,MR>& A )
{
#ifndef RELEASE
    PushCallStack("advanced::internal::HermitianInfinityNorm");
#endif
    R maxRowSum = advanced::internal::HermitianOneNorm( uplo, A );
#ifndef RELEASE
    PopCallStack();
#endif
    return maxRowSum;
}

template<typename R> // representation of a real number
inline R
elemental::advanced::internal::HermitianInfinityNorm
( UpperOrLower uplo, const DistMatrix<std::complex<R>,MC,MR>& A )
{
#ifndef RELEASE
    PushCallStack("advanced::internal::HermitianInfinityNorm");
#endif
    R maxRowSum = advanced::internal::HermitianOneNorm( uplo, A );
#ifndef RELEASE
    PopCallStack();
#endif
    return maxRowSum;
}
