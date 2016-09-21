#include "maya_includes.h"


MCallbackIdArray gCallbackIds;
MCallbackId bajs;




void addNodeCallback(MObject &node, void *clientData) //get generic node creation
{
	MStatus rs = MS::kSuccess;
	MFnDagNode dagNode(node);
	//MGlobal::displayInfo(node.apiTypeStr()); //

	MGlobal::displayInfo(dagNode.fullPathName());


	//if (node.hasFn(MFn::kMesh))
	//{
	//	MFnMesh mesh(node);							//here's the meshimesh 
	//	//MGlobal::displayInfo("MESH GET");
	//	//mesh.dagPath().fullPathName()
	//}

	//if (node.hasFn(MFn::kTransform))
	//{
	//	MFnTransform transform(node);				//heres the transiformiform
	//	
	//	//MGlobal::displayInfo("TRANSFORM GET name: " + transform.name());
	//}
 	
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
	
	gCallbackIds.append(MDGMessage::addNodeAddedCallback(addNodeCallback,
		kDefaultNodeType,
		NULL,
		NULL
	));



	

	return rs;
}


EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	MGlobal::displayInfo("Ultrabajskissplugin annihilated");

	MMessage::removeCallbacks(gCallbackIds);

	return MS::kSuccess;
}


