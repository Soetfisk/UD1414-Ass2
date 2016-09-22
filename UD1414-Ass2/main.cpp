#include "maya_includes.h"


MCallbackIdArray gCallbackIds;
MCallbackId bajs;


void transformChangedCallback(MObject &transformNode, MDagMessage::MatrixModifiedFlags &modified, void *clientData)
{

}

void nameChangedCallback(MObject &node, const MString &str, void*clientData)
{

	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dagNode(node);
		MGlobal::displayInfo("NewName: " + dagNode.name());
	}
}

//void elapsedTimeCallback(float elapsedTime, float lastTime, void *clientData)
//{
//	static float totalTime = 0;
//	totalTime += elapsedTime;
//
//	MString derp;
//	derp+=(totalTime);
//
//	//MGlobal::displayInfo("time changed!");
//	MGlobal::displayInfo(derp);
//}


void addNodeCallback(MObject &node, void *clientData) //get generic node creation
{
	MStatus rs = MS::kSuccess;

	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dagNode(node);
		MGlobal::displayInfo(dagNode.fullPathName());
		//MGlobal::displayInfo(node.apiTypeStr()); //
	}
	


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


EXPORT MStatus initializePlugin(MObject obj)
{
	MStatus rs = MS::kSuccess;
	MCallbackId callbackId;

	MFnPlugin myPlugin(obj, "Maya plugin", "1.0", "Any", &rs);
	if (MFAIL(rs))
	{
		CHECK_MSTATUS(rs);
	}

	MGlobal::displayInfo("Ultrabajsplugin loaded");
	
	loadScene(rs);
	readScene(rs);




	return rs;
}


EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	MGlobal::displayInfo("Ultrabajskissplugin annihilated");

	MMessage::removeCallbacks(gCallbackIds);

	return MS::kSuccess;
}

MStatus readScene(MStatus &rs)
{
	gCallbackIds.append(MDGMessage::addNodeAddedCallback(addNodeCallback,
		kDefaultNodeType,
		NULL,
		&rs
	));

	//gCallbackIds.append(MTimerMessage::addTimerCallback(5.0f,
	//	elapsedTimeCallback,
	//	NULL,
	//	&rs
	//));

	gCallbackIds.append(MNodeMessage::addNameChangedCallback(
		MObject::kNullObj,
		nameChangedCallback,
		NULL,
		&rs
	));
}

MStatus loadScene(MStatus &rs)
{
	MCallbackId callbackId;

	MItDag dagIt(MItDag::kBreadthFirst, MFn::kTransform, &rs);
	for (; !dagIt.isDone(); dagIt.next())
	{
		if (dagIt.currentItem().hasFn(MFn::kTransform))
		{
			MFnTransform transFn = dagIt.currentItem();

			if (transFn.child(0).hasFn(MFn::kCamera) || transFn.child(0).hasFn(MFn::kMesh))
			{
				MDagPath transDagPath = MDagPath::getAPathTo(transFn.child(0));

				callbackId = MDagMessage::addWorldMatrixModifiedCallback(
					transDagPath,
					transformChangedCallback,
					NULL,
					&rs
				);
				if (rs == MS::kSuccess)
					if (gCallbackIds.append(callbackId) == MS::kSuccess)
					{

					}
					else
					{

					}
				else
				{

				}
			}
		}
	}

}