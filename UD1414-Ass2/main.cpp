#include <iostream>

#include "maya_includes.h"


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

