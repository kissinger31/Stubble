#include "GenericTool.hpp"
#include "../ToolShapes/CircleToolShape/CircleToolShape.hpp"
#include "../ToolShapes/TextureToolShape/TextureToolShape.hpp"

// Command parameter names and shortcuts
const char *toolScaleFlag = "-ts";
const char *toolScaleLongFlag = "-toolScale";
const char *toolShapeFlag = "-tsh";
const char *toolShapeLongFlag = "-toolShape";
const char *brushModeChoiceFlag = "-bmc";
const char *brushModeChoiceLongFlag = "-brushModeChoice";
const char *brushSensitivityFlag = "-bse"; // :)
const char *brushSensitivityLongFlag = "-brushSensitivity";
const char *brushFalloffFlag = "-bfo";
const char *brushFalloffLongFlag = "-brushFalloff";
const char *brushCollisionFlag = "-bco";
const char *brushCollisionLongFlag = "-brushCollision";

namespace Stubble
{

namespace Toolbox
{

GenericTool::GenericTool() :
	mShape(0), mScale(1.0)
{
}

GenericTool::GenericTool(ToolShape *aToolShape) :
	mShape(aToolShape), mScale(1.0)
{
}

M3dView* GenericTool::getActiveView()
{
	mView = M3dView::active3dView();
	return &mView;
}

void GenericTool::drawToolShape( short aScreenCoords[ 2 ], QEvent::Type aEventType )
{
	mShape->draw( getActiveView(), aScreenCoords, aEventType );
}

void GenericTool::drawHapticToolShape( MVector &aHapticProxyPosition, MVector &aHapticProxyRotation, double &aHapticProxyRotationAngle )
{
	mShape->draw( getActiveView(), aHapticProxyPosition, aHapticProxyRotation, aHapticProxyRotationAngle );
}

ToolShape *GenericTool::getToolShape()
{
	return mShape;
}

double GenericTool::getToolScale()
{
	return mScale;
}

void GenericTool::changeToolShape(MString aShapeName)
{
	if( aShapeName == "Circle Tool Shape" ) 
	{
		delete mShape;
		mShape = new CircleToolShape();
	}
	if( aShapeName == "Texture Tool Shape" )
	{
		delete mShape;
		mShape = new TextureToolShape();
	}
}
GenericToolCommand::GenericToolCommand()
{
}

GenericToolCommand::~GenericToolCommand()
{
}

MStatus	GenericToolCommand::appendSyntax()
{
	MSyntax syn = syntax();
	
	syn.addFlag( brushModeChoiceFlag, brushModeChoiceLongFlag, MSyntax::kLong );

	syn.addFlag( toolScaleFlag, toolScaleLongFlag, MSyntax::kDouble );

	syn.addFlag( toolShapeFlag, toolShapeLongFlag, MSyntax::kString );

	syn.addFlag( brushSensitivityFlag, brushSensitivityLongFlag, MSyntax::kDouble );

	syn.addFlag( brushFalloffFlag, brushFalloffLongFlag, MSyntax::kBoolean );

	syn.addFlag( brushCollisionFlag, brushCollisionLongFlag, MSyntax::kBoolean );

	return MS::kSuccess;
}

} // namespace Toolbox

} // namespace Stubble
