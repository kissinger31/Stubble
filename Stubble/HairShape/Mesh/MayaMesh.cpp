#include "MayaMesh.hpp"
#include "HairShape\UserInterface\HairShape.hpp"

#include <maya\MIntArray.h>
#include <maya\MFnMesh.h>
#include <maya\MItMeshPolygon.h>
#include <maya\MPointArray.h>
#include <maya\MFnDagNode.h>
#include <maya\MDagPathArray.h>

namespace Stubble
{

namespace HairShape
{

MayaMesh::MayaMesh(MObject & aMesh, const MString & aUVSet): 
	mUVSet( aUVSet )
{
	// creating acceleration structure
	mMayaMesh = new MFnMesh( aMesh );
	mMeshIntersector = new MMeshIntersector();

	MStatus status = mMeshIntersector->create( aMesh, HairShape::getActiveObject()->getCurrentInclusiveMatrix() );

	MItMeshPolygon iter( aMesh ); // Polygon iterator
	MFnMesh fnMesh( aMesh ); // Mesh functions

	unsigned __int32 * localVerticesIndices = new unsigned __int32[ fnMesh.numVertices() ]; // Global to local indices
	unsigned __int32 polygonID = 0;

	while ( !iter.isDone() )
	{
		// Get local vertices indices
		for( unsigned __int32 i = 0; i < iter.polygonVertexCount(); ++i )
		{
			localVerticesIndices[ iter.vertexIndex( i ) ] = i;
		}
		int count; // Number of triangles
		iter.numTriangles( count ); // Get new triangles count
		for ( int i = 0; i < count; ++i ) // For each triangle in polygon
		{
			MIntArray trianglePointsIndices; 
			MPointArray trianglePoints;
			// Select triangle
			iter.getTriangle( i, trianglePoints, trianglePointsIndices, MSpace::kWorld );

			// mTriangles.push_back( Triangle() ); // New triangle in our storage
			// Triangle & triangle = *mTriangles.rbegin(); // Our triangle storage

			MeshPoint triangleMeshPoints[3];

			for ( unsigned __int32 j = 0; j < 3 ; ++j ) // For each vertex in triangle
			{
				// Select texture coordinates
				float2 uv;
				iter.getUV( localVerticesIndices[ trianglePointsIndices[ j ] ], uv, &aUVSet );
				// Select normal
				MVector normal;
				iter.getNormal( localVerticesIndices[ trianglePointsIndices[ j ] ], normal, MSpace::kWorld );
				// Select tangent
				MVector tangent;
				fnMesh.getFaceVertexTangent( polygonID, trianglePointsIndices[ j ], tangent, MSpace::kWorld, &aUVSet );
				iter.getNormal( localVerticesIndices[ trianglePointsIndices[ j ] ], normal, MSpace::kWorld );

				triangleMeshPoints[j] = MeshPoint( Vector3D<Real> ( trianglePoints [ j ] ), // Position
					Vector3D< Real > ( normal ), // Normal
					Vector3D< Real > ( tangent ), // Tangent
					static_cast< Real >( uv[ 0 ] ), // U Coordinate
					static_cast< Real >( uv[ 1 ] )); // V Coordinate

				// Update bounding box
				mRestPose.mBoundingBox.expand( Vector3D< Real > ( trianglePoints[ j ] ) );
			}

			mRestPose.mTriangles.push_back( Triangle( triangleMeshPoints[0], triangleMeshPoints[1], triangleMeshPoints[2] ) );

			// Set maya triangle IDs for fast access to updated triangle
			mMayaTriangles.push_back( MayaTriangle( polygonID, localVerticesIndices[ trianglePointsIndices[ 0 ] ],
				localVerticesIndices[ trianglePointsIndices[ 1 ] ],
				localVerticesIndices[ trianglePointsIndices[ 2 ] ] ) );
		}

		++polygonID; // Next polygon ID
		iter.next();
	}
}

MeshPoint MayaMesh::getMeshPoint( const UVPoint &aPoint ) const
{

	// First select full barycentric coordinates
	double u = aPoint.getU();
	double v = aPoint.getV();
	double w = 1 - u - v;

	// Get triangle
	const MayaTriangle & triangle = mMayaTriangles [ aPoint.getTriangleID() ];

	// Get vertices indices
	int3 indices;
	MIntArray vertices;
	mMayaMesh->getPolygonVertices( triangle.getFaceID(), vertices );
	indices[ 0 ] = vertices[ triangle.getLocalVertex1() ];
	indices[ 1 ] = vertices[ triangle.getLocalVertex2() ];
	indices[ 2 ] = vertices[ triangle.getLocalVertex3() ];

	// Calculate position of point
	MPoint point, tmpPoint;
	mMayaMesh->getPoint( indices[ 0 ], point, MSpace::kWorld );
	mMayaMesh->getPoint( indices[ 1 ], tmpPoint, MSpace::kWorld );
	point = point * u + tmpPoint * v;
	mMayaMesh->getPoint( indices[ 2 ], tmpPoint, MSpace::kWorld );
	point += tmpPoint * w;

	// Calculate normal
	MVector normal1, normal2, normal3;
	mMayaMesh->getFaceVertexNormal( triangle.getFaceID(), indices[ 0 ], normal1, MSpace::kWorld );
	mMayaMesh->getFaceVertexNormal( triangle.getFaceID(), indices[ 1 ], normal2, MSpace::kWorld );
	mMayaMesh->getFaceVertexNormal( triangle.getFaceID(), indices[ 2 ], normal3, MSpace::kWorld );
	MVector normal = normal1 * u + normal2 * v + normal3 * w;
	normal.normalize();

	// Calculate tangent
	MVector tangent1, tangent2, tangent3;
	mMayaMesh->getFaceVertexTangent( triangle.getFaceID(), indices[ 0 ], tangent1, MSpace::kWorld, &mUVSet );
	mMayaMesh->getFaceVertexTangent( triangle.getFaceID(), indices[ 1 ], tangent2, MSpace::kWorld, &mUVSet );
	mMayaMesh->getFaceVertexTangent( triangle.getFaceID(), indices[ 2 ], tangent3, MSpace::kWorld, &mUVSet );
	MVector tangent = tangent1 * u + tangent2 * v + tangent3 * w;

	// Orthonormalize tangent to normal
	tangent -= normal * ( tangent * normal ); 
	tangent.normalize();

	// Calculate texture coordinates
	double textU, textV;
	float tmpU, tmpV;
	mMayaMesh->getPolygonUV( triangle.getFaceID(), triangle.getLocalVertex1(), tmpU, tmpV, &mUVSet);
	textU = tmpU * u;
	textV = tmpV * u;
	mMayaMesh->getPolygonUV( triangle.getFaceID(), triangle.getLocalVertex2(), tmpU, tmpV, &mUVSet);
	textU += tmpU * v;
	textV += tmpV * v;
	mMayaMesh->getPolygonUV( triangle.getFaceID(), triangle.getLocalVertex3(), tmpU, tmpV, &mUVSet);
	textU += tmpU * ( 1 - u - v );
	textV += tmpV * ( 1 - u - v );

	// Return PointOnMesh
	return MeshPoint( point, normal, tangent, textU, textV );
}

inline const Triangle MayaMesh::getTriangle( unsigned __int32 aID) const
{
	// Get triangle
	const MayaTriangle & triangle = mMayaTriangles [ aID ];

	// points store variables
	int3 indices;
	int3 local_indices;
	float3 textU, textV;
	MPoint points[ 3 ];
	MVector normals[ 3 ];
	MVector tangents[ 3 ];
	MeshPoint meshPoints[ 3 ];

	MIntArray vertices;
	mMayaMesh->getPolygonVertices( triangle.getFaceID(), vertices );
	indices[ 0 ] = vertices[ triangle.getLocalVertex1() ];
	indices[ 1 ] = vertices[ triangle.getLocalVertex2() ];
	indices[ 2 ] = vertices[ triangle.getLocalVertex3() ];
	local_indices[ 0 ] = triangle.getLocalVertex1();
	local_indices[ 1 ] = triangle.getLocalVertex2();
	local_indices[ 2 ] = triangle.getLocalVertex3();

	for( unsigned __int32 i = 0; i < 3; ++i)
	{
		mMayaMesh->getPoint( indices[ i ], points [ i ], MSpace::kWorld );
		mMayaMesh->getFaceVertexNormal( triangle.getFaceID(), indices[ i ], normals[ i ], MSpace::kWorld );
		mMayaMesh->getFaceVertexTangent( triangle.getFaceID(), indices[ i ], tangents[ i ], MSpace::kWorld, &mUVSet );
		mMayaMesh->getPolygonUV( triangle.getFaceID(), local_indices[ i ], textU [ i ], textV [ i ], &mUVSet);

		meshPoints [ i ] = MeshPoint(Vector3D < Real > ( points[ i ] ), Vector3D < Real > ( normals[ i ] ),
			Vector3D < Real > ( tangents[ i ] ), static_cast< Real >(textU[ i ]), static_cast < Real >(textV[ i ] ));
	}

	return Triangle( meshPoints[0], meshPoints[1], meshPoints[2] );
}

inline unsigned __int32 MayaMesh::getTriangleCount() const
{
	return static_cast< unsigned __int32 >( mMayaTriangles.size() );
}

void MayaMesh::meshUpdate( MObject & aUpdatedMesh, const MString & aUVSet )
{
	// updating acceleration structure
	MStatus status = mMeshIntersector->create( aUpdatedMesh, HairShape::getActiveObject()->getCurrentInclusiveMatrix() );

	delete mMayaMesh;
	mMayaMesh = new MFnMesh( aUpdatedMesh );
	mUVSet = aUVSet;
}

void MayaMesh::serialize( std::ostream & aOutputStream ) const
{
	mRestPose.exportMesh( aOutputStream );		
}

void MayaMesh::deserialize( std::istream & aInputStream  )
{
	mRestPose.importMesh( aInputStream );	
}

MayaMesh::~MayaMesh()
{
	delete mMayaMesh;
	delete mMeshIntersector;
}

void MayaMesh::getTriangles( Triangles & aResult ) const
{
	aResult.clear();
	aResult.reserve( mMayaTriangles.size() );
	for ( unsigned __int32 i = 0; i < aResult.size(); ++i )
	{
		aResult.push_back( getTriangle( i ) );
	}
}

} // namespace HairShape

} // namespace Stubble