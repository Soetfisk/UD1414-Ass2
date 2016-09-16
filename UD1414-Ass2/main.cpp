#include <iostream>

#include <maya/MSimple.h>
#include <maya/MIOStream.h>
#include <maya/MArgList.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>

#include <maya/MCallbackIdArray.h>


MCallbackIdArray gCallbackIds;

DeclareSimpleCommand(HelloWorld, "Autodesk", "2016");

void addNodeCallback(MObject nodeObject)
{
	MStatus st = MS::kSuccess;
	MCallbackId  id = 


}

MStatus HelloWorld::doIt(const MArgList&)
{
	printf("poop\n");
	std::cout << "also poop\n" << std::endl;
	return MS::kSuccess;
}

