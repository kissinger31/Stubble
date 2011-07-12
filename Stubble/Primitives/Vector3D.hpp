#ifndef STUBBLE_VECTOR_3D_HPP
#define STUBBLE_VECTOR_3D_HPP

#include <sstream>

#ifdef MAYA
#include <maya/MVector.h>
#include <maya/MPoint.h>
#endif

namespace Stubble
{

///----------------------------------------------------------------------------------------------------
/// Representation of 3D Vector. 
///----------------------------------------------------------------------------------------------------
template < typename Type >
class Vector3D
{ 
public:

	///----------------------------------------------------------------------------------------------------
	/// Creates vector (0,0,0). 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D();

	///----------------------------------------------------------------------------------------------------
	/// Creates fully defined vector. 
	///
	/// \param	aX	The x coordinate. 
	/// \param	aY	The y coordinate. 
	/// \param	aZ	The z coordinate. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D( Type aX, Type aY, Type aZ );

	///----------------------------------------------------------------------------------------------------
	/// Creates a vector with direction given by 2 points. 
	///
	/// \param	aStart	Start point. 
	/// \param	aEnd	End point. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D( const Vector3D & aStart, const Vector3D & aEnd );

	///----------------------------------------------------------------------------------------------------
	/// Gets the size of the vector. 
	///
	/// \return	Size of the vector. 
	///----------------------------------------------------------------------------------------------------
	inline Type size() const;

	///----------------------------------------------------------------------------------------------------
	/// Gets the size of the vector powered by 2.
	///
	/// \return	Size of the vector powered by 2. 
	///----------------------------------------------------------------------------------------------------
	inline Type sizePwr2() const;

	///----------------------------------------------------------------------------------------------------
	/// Const array indexer operator. 
	///
	/// \param	aIndex	Zero-based index of a. 
	///
	/// \return	The indexed value. 
	///----------------------------------------------------------------------------------------------------
	inline Type operator[] ( unsigned int aIndex ) const;

	///----------------------------------------------------------------------------------------------------
	/// Array indexer operator. 
	///
	/// \param	aIndex	Zero-based index of a. 
	///
	/// \return	The indexed value. 
	///----------------------------------------------------------------------------------------------------
	inline Type & operator[] ( unsigned int aIndex );

	///----------------------------------------------------------------------------------------------------
	/// Addition assignment operator. 
	///
	/// \param	aVector	The added vector. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline const Vector3D & operator+= ( const Vector3D & aVector ); 

	///----------------------------------------------------------------------------------------------------
	/// Subtraction assignment operator. 
	///
	/// \param	aVector	The subtracted vector. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline const Vector3D & operator-= ( const Vector3D & aVector ); 
	
	///----------------------------------------------------------------------------------------------------
	/// Multiplication assignment operator. 
	///
	/// \param	aValue	a scalar value. 
	///----------------------------------------------------------------------------------------------------
	inline const Vector3D & operator*= ( Type aValue ); 

	///----------------------------------------------------------------------------------------------------
	/// Division assignment operator. 
	///
	/// \param	aValue	a scalar value. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline const Vector3D & operator/= ( Type aValue ); 
	
	///----------------------------------------------------------------------------------------------------
	/// Equality operator. 
	///
	/// \param	aVector	compared vector. 
	///
	/// \return	true if the vectors are equivalent. 
	///----------------------------------------------------------------------------------------------------
	inline bool operator== ( const Vector3D & aVector ) const;

	///----------------------------------------------------------------------------------------------------
	/// Inequality operator. 
	///
	/// \param	aVector	compared vector. 
	///
	/// \return	true if the vectors are not equivalent. 
	///----------------------------------------------------------------------------------------------------
	inline bool operator!= ( const Vector3D & aVector ) const; 

	///----------------------------------------------------------------------------------------------------
	/// Addition operator. 
	///
	/// \param	aVector	a vector. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D operator+ ( const Vector3D & aVector ) const; 

	///----------------------------------------------------------------------------------------------------
	/// Subtraction operator. 
	///
	/// \param	aVector	a vector. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D operator-( const Vector3D & aVector ) const; 

	///----------------------------------------------------------------------------------------------------
	/// Negation operator. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D operator-() const;
	
	///----------------------------------------------------------------------------------------------------
	/// Multiplication operator between vector and scalar. 
	///
	/// \param	aScalar	a scalar. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D operator* ( Type aScalar ) const; 

	///----------------------------------------------------------------------------------------------------
	/// Division operator between vector and scalar. 
	///
	/// \param	aScalar	a scalar. 
	///
	/// \return	The result of the operation. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D operator/ ( Type aScalar ) const; 

	///----------------------------------------------------------------------------------------------------
	/// Sets vector coordinates . 
	///
	/// \param	aX	The x coordinate. 
	/// \param	aY	The y coordinate. 
	/// \param	aZ	The z coordinate. 
	///----------------------------------------------------------------------------------------------------
	inline void set( Type aX, Type aY, Type aZ );
	
	///----------------------------------------------------------------------------------------------------
	/// Normalizes this vector. 
	///
	/// \return	Normalized vector. 
	///----------------------------------------------------------------------------------------------------

	inline Vector3D & normalize(); 
	
#ifdef MAYA

	///----------------------------------------------------------------------------------------------------
	/// Constructor - converts maya vector to stubble vector 
	///
	/// \param	aMayaVector	The maya vector. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D( const MVector & aMayaVector );

	///----------------------------------------------------------------------------------------------------
	/// Constructor - converts maya point to stubble vector 
	///
	/// \param	aMayaPoint	The maya point. 
	///----------------------------------------------------------------------------------------------------
	inline Vector3D( const MPoint & aMayaPoint );

	///----------------------------------------------------------------------------------------------------
	/// Converts this object to a maya vector. 
	///
	/// \return	This object as a MVector. 
	///----------------------------------------------------------------------------------------------------
	inline MVector toMayaVector() const;

	///----------------------------------------------------------------------------------------------------
	/// Converts this object to a maya point. 
	///
	/// \return	This object as a MPoint. 
	///----------------------------------------------------------------------------------------------------
	inline MPoint toMayaPoint() const;

#endif

	///----------------------------------------------------------------------------------------------------
	/// Normalizes the given vector. 
	///
	/// \param	aVector	a vector. 
	///
	/// \return	Normalized vector. 
	///----------------------------------------------------------------------------------------------------
	inline static Vector3D normalize( const Vector3D & aVector ); 

	///----------------------------------------------------------------------------------------------------
	/// Dot product. 
	///
	/// \param	aVector1	The first vector. 
	/// \param	aVector2	The second vector. 
	///
	/// \return	Scalar. 
	///----------------------------------------------------------------------------------------------------
	inline static Type dotProduct( const Vector3D & aVector1, const Vector3D & aVector2 ); 

	///----------------------------------------------------------------------------------------------------
	/// Cross product. 
	///
	/// \param	aVector1	The first vector. 
	/// \param	aVector2	The second vector. 
	///
	/// \return	Vector. 
	///----------------------------------------------------------------------------------------------------
	inline static Vector3D crossProduct( const Vector3D & aVector1, const Vector3D & aVector2 ); 

	Type x; ///< The x coordinate

	Type y; ///< The y coordinate
	
	Type z; ///< The z coordinate
};

///----------------------------------------------------------------------------------------------------
/// Put vector into stream 
///
/// \param [in,out]	aStreamOut	a stream out. 
/// \param	aVector				a vector. 
///
/// \return	The updated stream. 
///----------------------------------------------------------------------------------------------------

template < typename Type >
inline std::ostream & operator<<( std::ostream & aStreamOut, const Vector3D< Type > & aVector );

///----------------------------------------------------------------------------------------------------
/// Pull vector from stream 
///
/// \param [in,out]	aStreamIn	a stream in. 
/// \param [in,out]	aVector		a vector. 
///
/// \return	The updated stream. 
///----------------------------------------------------------------------------------------------------

template < typename Type >
inline std::istream & operator>>( std::istream & aStreamIn, Vector3D< Type > & aVector );

// inline functions implementation
template < typename Type >
inline Vector3D< Type >::Vector3D():
	x( 0 ),
	y( 0 ),
	z( 0 )
{
}

template < typename Type >
inline Vector3D< Type >::Vector3D( Type aX, Type aY, Type aZ ):
	x( aX ),
	y( aY ),
	z( aZ ) 
{
}

template < typename Type >
inline Vector3D< Type >::Vector3D( const Vector3D & aStart, const Vector3D & aEnd ): 
	x( aEnd.x - aStart.x ), 
	y( aEnd.y - aStart.y ), 
	z( aEnd.z - aStart.z ) 
{
}	

template < typename Type >
inline Type Vector3D< Type >::size() const
{ 
	return sqrt( x * x  +  y * y  +  z * z );
}

template < typename Type >
inline Type Vector3D< Type >::sizePwr2() const 
{
	return x * x  +  y * y  +  z * z;
}

template < typename Type >
inline Type Vector3D< Type >::operator[] ( unsigned int aIndex ) const
{
	if ( aIndex == 0 )
		return x;

	if ( aIndex == 1 )
		return y;

	return z;
}

template < typename Type >
inline Type & Vector3D< Type >::operator[] ( unsigned int aIndex )
{
	if ( aIndex == 0 ) return x;
	if ( aIndex == 1 ) return y;
	return z;
}

template < typename Type >
inline const Vector3D< Type > & Vector3D< Type >::operator+= ( const Vector3D & aVector ) 
{
	x += aVector.x;
	y += aVector.y;
	z += aVector.z;
	return *this;
}

template < typename Type >
inline const Vector3D< Type > & Vector3D< Type >::operator-= ( const Vector3D & aVector ) 
{
	x -= aVector.x;
	y -= aVector.y;
	z -= aVector.z;
	return *this;
}

template < typename Type >
inline const Vector3D< Type > & Vector3D< Type >::operator*= ( Type aValue ) 
{
	x *= aValue;
	y *= aValue;
	z *= aValue;
	return *this;
}

template < typename Type >
inline const Vector3D< Type > & Vector3D< Type >::operator/= ( Type aValue ) 
{
	x /= aValue;
	y /= aValue;
	z /= aValue;
	return *this;
}

template < typename Type >
inline bool Vector3D< Type >::operator== ( const Vector3D & aVector ) const
{
	return x == aVector.x && y == aVector.y && z == aVector.z;
}

template < typename Type >
inline bool Vector3D< Type >::operator!= ( const Vector3D & aVector ) const
{
	return x != aVector.x || y != aVector.y || z != aVector.z;
}

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::operator+ ( const Vector3D & aVector ) const 
{
	return Vector3D( x + aVector.x, y + aVector.y, z + aVector.z );
}

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::operator-( const Vector3D & aVector ) const 
{
	return Vector3D( x - aVector.x, y - aVector.y, z - aVector.z );
}

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::operator-() const 
{
	return Vector3D( -x, -y, -z );
}

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::operator* ( Type aScalar ) const 
{
	return Vector3D( x * aScalar, y * aScalar, z * aScalar );
}

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::operator/ ( Type aScalar ) const 
{
	return Vector3D( x / aScalar, y / aScalar, z / aScalar );
}

template < typename Type >
inline void Vector3D< Type >::set( Type aX, Type aY, Type aZ )
{
	x = aX;
	y = aY;
	z = aZ;
}
	
template < typename Type >
inline Vector3D< Type > & Vector3D< Type >::normalize() 
{
	if ( x == 0 && y == 0 && z == 0 ) 
	{
		return *this;
	}

	*this /= size();

	return *this;
}

	
#ifdef MAYA
template < typename Type >
inline Vector3D< Type >::Vector3D( const MVector & aMayaVector ):
	x( aMayaVector.x ),
	y( aMayaVector.y ),
	z( aMayaVector.z )
{
}

template < typename Type >
inline Vector3D< Type >::Vector3D( const MPoint & aMayaPoint ):
	x( aMayaPoint.x ),
	y( aMayaPoint.y ),
	z( aMayaPoint.z )
{
}

template < typename Type >
inline MVector Vector3D< Type >::toMayaVector() const
{
	return MVector( x, y, z );
}

template < typename Type >
inline MPoint Vector3D< Type >::toMayaPoint() const
{
	return MPoint( x, y, z );
}

#endif

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::normalize( const Vector3D & aVector ) 
{
	if ( aVector.x == 0 && aVector.y == 0 && aVector.z == 0 ) 
	{
		return aVector;
	}

	return aVector / aVector.size();
}

template < typename Type >
inline Type Vector3D< Type >::dotProduct( const Vector3D & aVector1, const Vector3D & aVector2 ) 
{
	return aVector1.x * aVector2.x  +  aVector1.y * aVector2.y  +  aVector1.z * aVector2.z;
}

template < typename Type >
inline Vector3D< Type > Vector3D< Type >::crossProduct( const Vector3D & aVector1, const Vector3D & aVector2 ) 
{
	return Vector3D( aVector1.y * aVector2.z - aVector1.z * aVector2.y,
					 aVector1.z * aVector2.x - aVector1.x * aVector2.z,
					 aVector1.x * aVector2.y - aVector1.y * aVector2.x );
}

template < typename Type >
inline std::ostream & operator<<( std::ostream & aStreamOut, const Vector3D< Type > & aVector )
{
	return aStreamOut << aVector.x << " " << aVector.y << " " << aVector.z;
}

template < typename Type >
inline std::istream & operator>>( std::istream & aStreamIn, Vector3D< Type > & aVector )
{
	return aStreamIn >> aVector.x >> aVector.y >> aVector.z;
}

} //namespace Stubble

#endif //STUBBLE_VECTOR_3D_HPP