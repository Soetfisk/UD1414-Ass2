#include "maya_includes.h"


MCallbackIdArray gCallbackIds;

void addNodeCallback(MObject nodeObject)
{
	MStatus rs = MS::kSuccess;
	MCallbackId id = MNodeMessage::addAttributeChangedCallback(nodeObject, NULL, &rs);

	
	gCallbackIds.append(id);

	//DERP SJIT

}

void nodeAdded(MObject nodeObject)
{

}



MCallbackId addNodeAddedCallback(MMessage::MNodeFunction func)
{


}


//static MStatus removeCallbacks(MCallbackIdArray &ids)
//{
//
//}


EXPORT MStatus initializePlugin(MObject obj)
{
	MStatus rs = MS::kSuccess;

	MFnPlugin myPlugin(obj, "Maya plugin", "1.0", "Any", &rs);
	if (MFAIL(rs))
	{
		CHECK_MSTATUS(rs);
	}

	MGlobal::displayInfo("Ultrabajsplugin loaded");

	addNodeCallback(obj);


	return rs;
}


EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	MGlobal::displayInfo("Ultrabajsplugin annihilated");


	return MS::kSuccess;
}


