/*
   This file is part of elemental, a library for distributed-memory dense 
   linear algebra.

   Copyright (C) 2009-2010 Jack Poulson <jack.poulson@gmail.com>

   This program is released under the terms of the license contained in the 
   file LICENSE.
*/
#ifndef ELEMENTAL_DIST_MATRIX_STAR_VC_HPP
#define ELEMENTAL_DIST_MATRIX_STAR_VC_HPP 1

#include "elemental/dist_matrix.hpp"

namespace elemental {

// Partial specialization to A[* ,VC]
//
// The rows of these distributed matrices are spread throughout the 
// process grid in a column-major fashion, while the columns are not 
// distributed.

template<typename T>
class DistMatrixBase<T,Star,VC> : public AbstractDistMatrix<T>
{
protected:
    typedef AbstractDistMatrix<T> ADM;

    DistMatrixBase
    ( int height,
      int width,
      bool constrainedRowAlignment,
      int rowAlignment,
      int rowShift,
      const Grid& g );

    ~DistMatrixBase();

public:
    //------------------------------------------------------------------------//
    // Fulfillments of abstract virtual func's from AbstractDistMatrixBase    //
    //------------------------------------------------------------------------//

    //
    // Non-collective routines
    //

    // (empty)

    //
    // Collective routines
    //

    T Get( int i, int j ) const;
    void Set( int i, int j, T alpha );

    void MakeTrapezoidal
    ( Side side, Shape shape, int offset = 0 );

    void Print( const std::string& s ) const;
    void ResizeTo( int height, int width );
    void SetToIdentity();
    void SetToRandom();

    //------------------------------------------------------------------------//
    // Routines specific to [* ,VC] distribution                              //
    //------------------------------------------------------------------------//

    //
    // Non-collective routines
    //

    // (empty)

    //
    // Collective routines
    //

    // Aligns all of our DistMatrix's distributions that match a distribution
    // of the argument DistMatrix.
    void AlignWith( const DistMatrixBase<T,MC,  MR  >& A );
    void AlignWith( const DistMatrixBase<T,MR,  MC  >& A );
    void AlignWith( const DistMatrixBase<T,MC,  Star>& A );
    void AlignWith( const DistMatrixBase<T,Star,MC  >& A );
    void AlignWith( const DistMatrixBase<T,Star,VC  >& A );
    void AlignWith( const DistMatrixBase<T,VC,  Star>& A );
    void AlignWith( const DistMatrixBase<T,Star,MD  >& A ) {}
    void AlignWith( const DistMatrixBase<T,Star,MR  >& A ) {}
    void AlignWith( const DistMatrixBase<T,Star,VR  >& A ) {}
    void AlignWith( const DistMatrixBase<T,Star,Star>& A ) {}
    void AlignWith( const DistMatrixBase<T,MD,  Star>& A ) {}
    void AlignWith( const DistMatrixBase<T,MR,  Star>& A ) {}
    void AlignWith( const DistMatrixBase<T,VR,  Star>& A ) {}

    // Aligns our column distribution (i.e., Star) with the matching 
    // distribution of the argument. These are no-ops and exist solely to 
    // allow for templating over distribution parameters.
    void AlignColsWith( const DistMatrixBase<T,Star,MC  >& A ) {}
    void AlignColsWith( const DistMatrixBase<T,Star,MD  >& A ) {}
    void AlignColsWith( const DistMatrixBase<T,Star,MR  >& A ) {}
    void AlignColsWith( const DistMatrixBase<T,Star,VC  >& A ) {}
    void AlignColsWith( const DistMatrixBase<T,Star,VR  >& A ) {}
    void AlignColsWith( const DistMatrixBase<T,Star,Star>& A ) {}
    void AlignColsWith( const DistMatrixBase<T,MC,  Star>& A ) {}
    void AlignColsWith( const DistMatrixBase<T,MD,  Star>& A ) {}
    void AlignColsWith( const DistMatrixBase<T,MR,  Star>& A ) {}
    void AlignColsWith( const DistMatrixBase<T,VC,  Star>& A ) {}
    void AlignColsWith( const DistMatrixBase<T,VR,  Star>& A ) {}

    // Aligns our row distribution (i.e., VC) with the matching distribution
    // of the argument. We recognize that a VC distribution can be a subset of 
    // an MC distribution.
    void AlignRowsWith( const DistMatrixBase<T,MC,  MR  >& A );
    void AlignRowsWith( const DistMatrixBase<T,MR,  MC  >& A );
    void AlignRowsWith( const DistMatrixBase<T,MC,  Star>& A );
    void AlignRowsWith( const DistMatrixBase<T,Star,MC  >& A );
    void AlignRowsWith( const DistMatrixBase<T,Star,VC  >& A );
    void AlignRowsWith( const DistMatrixBase<T,VC,  Star>& A );

    // (Immutable) view of a distributed matrix
    void View( DistMatrixBase<T,Star,VC>& A );
    void LockedView( const DistMatrixBase<T,Star,VC>& A );

    // (Immutable) view of a portion of a distributed matrix
    void View
    ( DistMatrixBase<T,Star,VC>& A,
      int i, int j, int height, int width );

    void LockedView
    ( const DistMatrixBase<T,Star,VC>& A,
      int i, int j, int height, int width );

    // (Immutable) view of two horizontally contiguous partitions of a
    // distributed matrix
    void View1x2
    ( DistMatrixBase<T,Star,VC>& AL, DistMatrixBase<T,Star,VC>& AR );

    void LockedView1x2
    ( const DistMatrixBase<T,Star,VC>& AL, 
      const DistMatrixBase<T,Star,VC>& AR );

    // (Immutable) view of two vertically contiguous partitions of a
    // distributed matrix
    void View2x1
    ( DistMatrixBase<T,Star,VC>& AT,
      DistMatrixBase<T,Star,VC>& AB );

    void LockedView2x1
    ( const DistMatrixBase<T,Star,VC>& AT,
      const DistMatrixBase<T,Star,VC>& AB );

    // (Immutable) view of a contiguous 2x2 set of partitions of a
    // distributed matrix
    void View2x2
    ( DistMatrixBase<T,Star,VC>& ATL, DistMatrixBase<T,Star,VC>& ATR,
      DistMatrixBase<T,Star,VC>& ABL, DistMatrixBase<T,Star,VC>& ABR );

    void LockedView2x2
    ( const DistMatrixBase<T,Star,VC>& ATL, 
      const DistMatrixBase<T,Star,VC>& ATR,
      const DistMatrixBase<T,Star,VC>& ABL, 
      const DistMatrixBase<T,Star,VC>& ABR );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,MC,MR>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,MC,Star>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,Star,MR>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,MD,Star>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,Star,MD>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,MR,MC>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,MR,Star>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,Star,MC>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,VC,Star>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,Star,VC>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,VR,Star>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,Star,VR>& A );

    const DistMatrixBase<T,Star,VC>&
    operator=( const DistMatrixBase<T,Star,Star>& A );
};

template<typename R>
class DistMatrix<R,Star,VC> : public DistMatrixBase<R,Star,VC>
{
protected:
    typedef DistMatrixBase<R,Star,VC> DMB;

public:
    DistMatrix
    ( const Grid& g );

    DistMatrix
    ( int height, int width, const Grid& g );

    DistMatrix
    ( bool constrainedRowAlignment, int rowAlignment, const Grid& g );

    DistMatrix
    ( int height, int width,
      bool constrainedRowAlignment, int rowAlignment, const Grid& g );

    DistMatrix
    ( const DistMatrix<R,Star,VC>& A );

    ~DistMatrix();
    
    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,MC,MR>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,MC,Star>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,Star,MR>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,MD,Star>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,Star,MD>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,MR,MC>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,MR,Star>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,Star,MC>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,VC,Star>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,Star,VC>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,VR,Star>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,Star,VR>& A );

    const DistMatrix<R,Star,VC>&
    operator=( const DistMatrixBase<R,Star,Star>& A );

    //------------------------------------------------------------------------//
    // Fulfillments of abstract virtual func's from AbstractDistMatrixBase    //
    //------------------------------------------------------------------------//

    //
    // Non-collective routines
    //

    // (empty)

    //
    // Collective routines
    //

    void SetToRandomHPD();
};

#ifndef WITHOUT_COMPLEX
template<typename R>
class DistMatrix<std::complex<R>,Star,VC> 
: public DistMatrixBase<std::complex<R>,Star,VC>
{
protected:
    typedef DistMatrixBase<std::complex<R>,Star,VC> DMB;

public:
    DistMatrix
    ( const Grid& g );

    DistMatrix
    ( int height, int width, const Grid& g );

    DistMatrix
    ( bool constrainedRowAlignment, int rowAlignment, const Grid& g );

    DistMatrix
    ( int height, int width,
      bool constrainedRowAlignment, int rowAlignment, const Grid& g );

    DistMatrix
    ( const DistMatrix<std::complex<R>,Star,VC>& A );

    ~DistMatrix();
    
    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,MC,MR>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,MC,Star>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,Star,MR>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,MD,Star>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,Star,MD>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,MR,MC>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,MR,Star>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,Star,MC>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,VC,Star>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,Star,VC>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,VR,Star>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,Star,VR>& A );

    const DistMatrix<std::complex<R>,Star,VC>&
    operator=( const DistMatrixBase<std::complex<R>,Star,Star>& A );

    //------------------------------------------------------------------------//
    // Fulfillments of abstract virtual func's from AbstractDistMatrixBase    //
    //------------------------------------------------------------------------//

    //
    // Non-collective routines
    //

    // (empty)

    //
    // Collective routines
    //

    void SetToRandomHPD();

    //------------------------------------------------------------------------//
    // Fulfillments of abstract virtual func's from AbstractDistMatrix        //
    //------------------------------------------------------------------------//

    //
    // Non-collective routines
    //

    // (empty)

    //
    // Collective routines
    //

    R GetReal( int i, int j ) const;
    R GetImag( int i, int j ) const;
    void SetReal( int i, int j, R u );
    void SetImag( int i, int j, R u );
};
#endif // WITHOUT_COMPLEX

//----------------------------------------------------------------------------//
// Implementations begin here                                                 //
//----------------------------------------------------------------------------//

//
// DistMatrixBase[* ,VC]
//

template<typename T>
inline
DistMatrixBase<T,Star,VC>::DistMatrixBase
( int height,
  int width,
  bool constrainedRowAlignment,
  int rowAlignment,
  int rowShift,
  const Grid& g )
: ADM(height,width,false,constrainedRowAlignment,0,rowAlignment,0,rowShift,g)
{ }

template<typename T>
inline
DistMatrixBase<T,Star,VC>::~DistMatrixBase()
{ }

//
// Real DistMatrix[* ,VC]
//

template<typename R>
inline
DistMatrix<R,Star,VC>::DistMatrix
( const Grid& g ) 
: DMB(0,0,false,0,g.VCRank(),g)
{ }

template<typename R>
inline
DistMatrix<R,Star,VC>::DistMatrix
( int height, int width, const Grid& g )
: DMB(height,width,false,0,g.VCRank(),g)
{
#ifndef RELEASE
    PushCallStack("DistMatrix[* ,VC]::DistMatrix");
#endif
    DMB::LocalMatrix().ResizeTo
    ( height, utilities::LocalLength( width, g.VCRank(), g.Size() ) );
#ifndef RELEASE
    PopCallStack();
#endif
}

template<typename R>
inline
DistMatrix<R,Star,VC>::DistMatrix
( bool constrainedRowAlignment, int rowAlignment, const Grid& g )
: DMB(0,0,constrainedRowAlignment,rowAlignment,
      utilities::Shift( g.VCRank(), rowAlignment, g.Size() ),g)
{ }

template<typename R>
inline
DistMatrix<R,Star,VC>::DistMatrix
( int height, int width,
  bool constrainedRowAlignment, int rowAlignment, const Grid& g )
: DMB(height,width,constrainedRowAlignment,rowAlignment,
      utilities::Shift( g.VCRank(), rowAlignment, g.Size() ),g)
{
#ifndef RELEASE
    PushCallStack("DistMatrix[* ,VC]::DistMatrix");
#endif
    DMB::LocalMatrix().ResizeTo
    ( height, utilities::LocalLength( width, DMB::RowShift(), g.Size() ) );
#ifndef RELEASE
    PopCallStack();
#endif
}

template<typename R>
inline
DistMatrix<R,Star,VC>::DistMatrix
( const DistMatrix<R,Star,VC>& A )
: DMB(0,0,false,0,0,A.GetGrid())
{
#ifndef RELEASE
    PushCallStack("DistMatrix[* ,VC]::DistMatrix");
#endif
    if( &A != this )
        *this = A;
    else
        throw std::logic_error
        ( "Attempted to construct a [* ,VC] with itself." );
#ifndef RELEASE
    PopCallStack();
#endif
}

template<typename R>
inline
DistMatrix<R,Star,VC>::~DistMatrix()
{ }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,MC,MR>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,MC,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,Star,MR>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,MD,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,Star,MD>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,MR,MC>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,MR,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,Star,MC>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,VC,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,Star,VC>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,VR,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,Star,VR>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<R,Star,VC>&
DistMatrix<R,Star,VC>::operator=
( const DistMatrixBase<R,Star,Star>& A )
{ DMB::operator=( A ); return *this; }

//
// Complex DistMatrix[* ,VC]
//

#ifndef WITHOUT_COMPLEX
template<typename R>
inline
DistMatrix<std::complex<R>,Star,VC>::DistMatrix
( const Grid& g ) 
: DMB(0,0,false,0,g.VCRank(),g)
{ }

template<typename R>
inline
DistMatrix<std::complex<R>,Star,VC>::DistMatrix
( int height, int width, const Grid& g )
: DMB(height,width,false,0,g.VCRank(),g)
{
#ifndef RELEASE
    PushCallStack("DistMatrix[* ,VC]::DistMatrix");
#endif
    DMB::LocalMatrix().ResizeTo
    ( height, utilities::LocalLength( width, g.VCRank(), g.Size() ) );
#ifndef RELEASE
    PopCallStack();
#endif
}

template<typename R>
inline
DistMatrix<std::complex<R>,Star,VC>::DistMatrix
( bool constrainedRowAlignment, int rowAlignment, const Grid& g )
: DMB(0,0,constrainedRowAlignment,rowAlignment,
      utilities::Shift( g.VCRank(), rowAlignment, g.Size() ),g)
{ }

template<typename R>
inline
DistMatrix<std::complex<R>,Star,VC>::DistMatrix
( int height, int width,
  bool constrainedRowAlignment, int rowAlignment, const Grid& g )
: DMB(height,width,constrainedRowAlignment,rowAlignment,
      utilities::Shift( g.VCRank(), rowAlignment, g.Size() ),g)
{
#ifndef RELEASE
    PushCallStack("DistMatrix[* ,VC]::DistMatrix");
#endif
    DMB::LocalMatrix().ResizeTo
    ( height, utilities::LocalLength( width, DMB::RowShift(), g.Size() ) );
#ifndef RELEASE
    PopCallStack();
#endif
}

template<typename R>
inline
DistMatrix<std::complex<R>,Star,VC>::DistMatrix
( const DistMatrix<std::complex<R>,Star,VC>& A )
: DMB(0,0,false,0,0,A.GetGrid())
{
#ifndef RELEASE
    PushCallStack("DistMatrix[* ,VC]::DistMatrix");
#endif
    if( &A != this )
        *this = A;
    else
        throw std::logic_error
        ( "Attempted to construct a [* ,VC] with itself." );
#ifndef RELEASE
    PopCallStack();
#endif
}

template<typename R>
inline
DistMatrix<std::complex<R>,Star,VC>::~DistMatrix()
{ }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,MC,MR>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,MC,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,Star,MR>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,MD,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,Star,MD>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,MR,MC>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,MR,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,Star,MC>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,VC,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,Star,VC>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,VR,Star>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,Star,VR>& A )
{ DMB::operator=( A ); return *this; }

template<typename R>
inline const DistMatrix<std::complex<R>,Star,VC>&
DistMatrix<std::complex<R>,Star,VC>::operator=
( const DistMatrixBase<std::complex<R>,Star,Star>& A )
{ DMB::operator=( A ); return *this; }
#endif // WITHOUT_COMPLEX

} // elemental

#endif /* ELEMENTAL_DIST_MATRIX_STAR_VC_HPP */

