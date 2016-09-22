//MItDag meshIt(MItDag::kBreadthFirst, MFn::kTransform, &res);
//
//for (; !meshIt.isDone(); meshIt.next())
//{
//	MFnTransform trans = meshIt.currentItem();
//	
//	if (trans.child(0).hasFn(MFn::kCamera) || trans.child(0).hasFn(MFn::kMesh))
//	{
//		MDagPath meshDag = MDagPath::getAPathTo(trans.child(0));
//		MCallbackId newId = MDagMessage::addWorldMatrixModifiedCallback(meshDag, WorldMatrixModified, NULL, &loopResults);
//		
//		if (loopResults == MS::kSuccess)
//		{
//			if (myCallbackArray.append(newId) == MS::kSuccess)
//				MGlobal::displayInfo("added worldmatrix for " + trans.name());
//			else
//				MGlobal::displayInfo("failed to add worldmatrix callback");
//		
//		}
//		else
//		{
//			MGlobal::displayInfo("failed to connect");
//		}
//	}
//}