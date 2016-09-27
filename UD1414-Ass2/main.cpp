#include "maya_includes.h"


MCallbackIdArray gCallbackIds;
MCallbackId bajs;

void elapsedTimeCallback(float elapsedTime, float lastTime, void *clientData)
{
	MStatus temp = MS::kSuccess;

	static float totalTime = 0;
	totalTime += elapsedTime;

	MString derp;
	derp += (totalTime);

	//MGlobal::displayInfo("time changed!");
	MGlobal::displayInfo(derp);
}

void vertexChangedCallback(MNodeMessage::AttributeMessage msg, MPlug & plug, MPlug & otherPlug, void* clientData)
{

	//if ((msg & MNodeMessage::kAttributeEval)) //entire mesh
	//{
	//	MGlobal::displayInfo(plug.name());

	//}

	if (msg & MNodeMessage::kAttributeSet && !plug.isArray()) //separate vertex
	{
		MGlobal::displayInfo(plug.name() + " Changed");
	}
	
	//other
	//plug.attribute.kChanged

}

void transformChangedCallback(MObject &transformNode, MDagMessage::MatrixModifiedFlags &modified, void *clientData)
{
	MFnTransform transFn(transformNode);

	MGlobal::displayInfo(transFn.name() + " Transform changed");
}

void nameChangedCallback(MObject &node, const MString &str, void*clientData)
{

	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dagNode(node);
		MGlobal::displayInfo("NewName: " + dagNode.name());
	}
}


void transCallback(MFnTransform &transFn, MStatus &rs)
{
	MCallbackId callbackId;

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
				//transform callback added
			}
			else
			{
				//transform callback failed
				MGlobal::displayInfo("Adding transformChange callback failed");
			}
		else
		{
			MGlobal::displayInfo("Creating transformChange callback failed");
		}
	}
}

void vertCallback(MObject &node, MStatus &rs)
{
	MCallbackId callbackId;

	
	MGlobal::displayInfo("STUFF");


	callbackId = MNodeMessage::addAttributeChangedCallback(node,
		vertexChangedCallback,
		NULL,
		&rs);

	if (rs == MS::kSuccess)
		if (gCallbackIds.append(callbackId) == MS::kSuccess)
		{
			//transform callback added
		}
		else
		{
			//transform callback failed
			MGlobal::displayInfo("Adding vertChange callback failed");
		}
	else
	{
		MGlobal::displayInfo("Creating vertChange callback failed");
	}

}




void addNodeCallback(MObject &node, void *clientData) //get generic node creation
{
	MStatus rs = MS::kSuccess;

	MCallbackId callbackId;

	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dagNode(node);
		MGlobal::displayInfo(dagNode.fullPathName());
	}

	if (node.hasFn(MFn::kTransform))
	{
		MFnTransform transFn(node);
		transCallback(transFn, rs);
	}

	if (node.hasFn(MFn::kMesh))
	{
		//MFnMesh meshFn(node);
		vertCallback(node, rs);
	}	
}


void readCallbacks(MStatus &rs)
{
	MCallbackId callbackId;

	callbackId = MTimerMessage::addTimerCallback(5, elapsedTimeCallback, NULL, &rs);

	callbackId = MDGMessage::addNodeAddedCallback(addNodeCallback,
		kDefaultNodeType,
		NULL,
		&rs
	);

	if (rs == MS::kSuccess)
		if (gCallbackIds.append(callbackId) == MS::kSuccess)
		{
			//transform callback added
		}
		else
		{
			//transform callback failed
			MGlobal::displayInfo("Adding NodeAdded callback failed");
		}
	else
	{
		MGlobal::displayInfo("Creating NodeAdded callback failed");
	}


	callbackId = MNodeMessage::addNameChangedCallback(
		MObject::kNullObj,
		nameChangedCallback,
		NULL,
		&rs
	);
	if (rs == MS::kSuccess)
		if (gCallbackIds.append(callbackId) == MS::kSuccess)
		{
			//transform callback added
		}
		else
		{
			//transform callback failed
			MGlobal::displayInfo("Adding NameChange callback failed");
		}
	else
	{
		MGlobal::displayInfo("Creating NameChange callback failed");
	}




}

void loadCallbacks(MStatus &rs)
{
	MCallbackId callbackId;

	MItDag dagIt(MItDag::kBreadthFirst, MFn::kDagNode, &rs);
	for (; !dagIt.isDone(); dagIt.next())
	{
		if (dagIt.currentItem().hasFn(MFn::kTransform))
		{
			MFnTransform transFn = dagIt.currentItem();
			transCallback(transFn, rs);
		}
		
		if (dagIt.currentItem().hasFn(MFn::kMesh))
		{
			// meshFn(dagIt.currentItem());
			vertCallback(dagIt.currentItem(), rs);
		}
		
	}

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

	loadCallbacks(rs);
	readCallbacks(rs);


	

	return rs;
}


EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	MGlobal::displayInfo("Ultrabajspasnoppenplugin annihilated");

	MMessage::removeCallbacks(gCallbackIds);

	return MS::kSuccess;
}