#ifndef STUBBLE_SEGMENTS_UG_HPP
#define STUBBLE_SEGMENTS_UG_HPP

#include "HairShape\HairComponents\GuidePosition.hpp"
#include "HairShape\HairComponents\Segments.hpp"
#include "HairShape\HairComponents\SelectedGuides.hpp"

namespace Stubble
{

namespace HairShape
{

namespace HairComponents
{

///-------------------------------------------------------------------------------------------------
/// Guides segments uniform grid
///-------------------------------------------------------------------------------------------------
class SegmentsUG
{
public:

	///-------------------------------------------------------------------------------------------------
	/// Default constructor. 
	///-------------------------------------------------------------------------------------------------
	SegmentsUG();

	///-------------------------------------------------------------------------------------------------
	/// Finaliser. 
	///-------------------------------------------------------------------------------------------------
	~SegmentsUG();

	///-------------------------------------------------------------------------------------------------
	/// Builds the uniform grid. 
	///
	/// \param	aGuidesCurrentPositions	the guides current positions. 
	/// \param	aFrameSegments			the guides segments in current frame. 
	///-------------------------------------------------------------------------------------------------
	void build( const GuidesCurrentPositions & aGuidesCurrentPositions, 
		const FrameSegments & aFrameSegments );

	///-------------------------------------------------------------------------------------------------
	/// Selects the guides using selection mask. 
	///
	/// \param	aSelectionMask	the selection mask. 
	/// \param [in,out]	aResult	the selected guides. 
	///-------------------------------------------------------------------------------------------------
	void select( const SelectionMask & aSelectionMask, SelectedGuides & aResult );

	///-------------------------------------------------------------------------------------------------
	/// Rebuilds the part of uniform grid holding the selected guides. 
	///
	/// \param	aSelectedGuides	the selected guides. 
	///-------------------------------------------------------------------------------------------------
	void rebuild( const SelectedGuides & aSelectedGuides );

	///-------------------------------------------------------------------------------------------------
	/// Sets the dirty bit. 
	///-------------------------------------------------------------------------------------------------
	inline void setDirty();

	///-------------------------------------------------------------------------------------------------
	/// Query if this object is dirty. 
	///
	/// \return	true if dirty, false if not. 
	///-------------------------------------------------------------------------------------------------
	inline bool isDirty() const;

private:
	bool mDirtyBit; ///< true to dirty bit
};

// inline functions implementation

inline void SegmentsUG::setDirty()
{
	mDirtyBit = true;
}

inline bool SegmentsUG::isDirty() const
{
	return mDirtyBit;
}

} // namespace HairComponents

} // namespace HairShape

} // namespace Stubble

#endif // STUBBLE_SEGMENTS_UG_HPP