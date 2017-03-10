#include "SESpringProtInteractionModel.hpp"
#include "SAMSON.hpp"


SESpringProtInteractionModel::SESpringProtInteractionModel() : SBMInteractionModelParticleSystem(0) {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.


}

SESpringProtInteractionModel::SESpringProtInteractionModel(SBParticleSystem* particleSystem) : SBMInteractionModelParticleSystem(particleSystem) {

	// SAMSON Element generator pro tip: implement this function if you want your interaction model to be applied to a particle system (the general case).
	// You might want to connect to various signals and handle the corresponding events (for example to erase this interaction model when the dynamical model it is applied to is erased).

}

SESpringProtInteractionModel::~SESpringProtInteractionModel() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

}

 void SESpringProtInteractionModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer) const {

	SBMInteractionModelParticleSystem::serialize(serializer, nodeIndexer);

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to serialize your interaction model.

}

void SESpringProtInteractionModel::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer) {

	SBMInteractionModelParticleSystem::unserialize(serializer, nodeIndexer);
	
	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to unserialize your interaction model.

}

void SESpringProtInteractionModel::eraseImplementation() {

	// SAMSON Element generator pro tip: modify this function when you need to perform special tasks when your interaction model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SESpringProtInteractionModel::initializeInteractions() {

	//particleindex = (*particlesystem)->getstructuralparticleindex();
	//unsigned int nparticles = particleindex->size();

	////initialize vectors
	//springlengthvector = new sbvector<sbquantity::length>;
	//springatomivector = new sbvector<sbatom*>;
	//springatomjvector = new sbvector<sbatom*>;

	////get the list of bonds in the model
	//sbnodepredicate* nodepredicate = samson::makenodepredicate("node.type bond");
	//sbnodeindexer nodeindexer;
	//samson::getactivedocument()->getnodes(nodeindexer, *nodepredicate);

	//samson::setstatusmessage(qstring::number(nodeindexer.size()), 0);

	//sb_for(sbnode* node, nodeindexer) {

	//	sbbond* bond = static_cast<sbbond*>(node);

	//	sbatom* atomi = bond->getleftatom();
	//	sbatom* atomj = bond->getrightatom();

	//	unsigned int atomiindex = particleindex->getindex(atomi);
	//	unsigned int atomjindex = particleindex->getindex(atomj);

	//	//add the atoms to the atoms vectors
	//	springatomivector->push_back(atomi);
	//	springatomjvector->push_back(atomj);

	//	//sbquantity::length 	distance = bond->getlength();
	//	//add the equilibrium lengthd to the springlength vector
	//	sbquantity::length distance = ((*particlesystem)->getposition(atomiindex) -
	//		(*particlesystem)->getposition(atomjindex)).norm();
	//	springlengthvector->push_back(distance);
	//}

	////initialize energy and forces
	//*energy = sbquantity::energy(0.0);
	//for (unsigned int i = 0; i < nparticles; ++i)
	//	setforce(i, sbforce3(sbquantity::force(0)));

	//unsigned int nsprings = springlengthvector->size();
	//for (unsigned int i = 0; i < nsprings; ++i) {

	//	sbatom* leftatom = (*springatomivector)[i];
	//	sbatom* rightatom = (*springatomjvector)[i];

	//	unsigned int  leftatomindex = particleindex->getindex(leftatom);
	//	unsigned int rightatomindex = particleindex->getindex(rightatom);

	//	const sbposition3& leftatomposition =
	//		(*particlesystem)->getposition(leftatomindex);
	//	const sbposition3& rightatomposition =
	//		(*particlesystem)->getposition(rightatomindex);

	//	//the force intensity depends on the shift respect to the equilibrium
	//	sbquantity::length forceintensity = (rightatomposition - leftatomposition).norm()
	//		- (*springlengthvector)[i];
	//	sbquantity::forceperlength forcefactor(100);

	//	sbforce3  force = forcefactor * forceintensity *
	//		(rightatomposition - leftatomposition).normalizedversion();

	//	sbforce3 forcei = getforce(leftatomindex) + force;
	//	sbforce3 forcej = getforce(rightatomindex) - force;

	//	setforce(leftatomindex, forcei);
	//	setforce(rightatomindex, forcej);
	//}

	//changed();
}

void SESpringProtInteractionModel::updateInteractions() {

	//particleIndex = (*particleSystem)->getStructuralParticleIndex();
	//unsigned int nParticles = particleIndex->size();

	////initialize energy and forces
	////*energy = SBQuantity::energy(0.0);
	//SBQuantity::energy currentEnergy(0.0);
	//for (unsigned int i = 0; i < nParticles; ++i)
	//	setForce(i, SBForce3(SBQuantity::force(0)));

	//unsigned int nSprings = springLengthVector->size();
	//for (unsigned int i = 0; i < nSprings; ++i) {

	//	SBAtom* leftAtom = (*springAtomIVector)[i];
	//	SBAtom* rightAtom = (*springAtomJVector)[i];

	//	unsigned int  leftAtomIndex = particleIndex->getIndex(leftAtom);
	//	unsigned int rightAtomIndex = particleIndex->getIndex(rightAtom);

	//	const SBPosition3& leftAtomPosition =
	//		(*particleSystem)->getPosition(leftAtomIndex);
	//	const SBPosition3& rightAtomPosition =
	//		(*particleSystem)->getPosition(rightAtomIndex);

	//	//the force intensity depends on the shift respect to the equilibrium
	//	SBQuantity::length forceIntensity = (rightAtomPosition - leftAtomPosition).norm()
	//		- (*springLengthVector)[i];
	//	SBQuantity::forcePerLength forceFactor(100);

	//	SBForce3  force = forceFactor * forceIntensity *
	//		(rightAtomPosition - leftAtomPosition).normalizedVersion();

	//	SBForce3 forceI = getForce(leftAtomIndex) + force;
	//	SBForce3 forceJ = getForce(rightAtomIndex) - force;

	//	setForce(leftAtomIndex, forceI);
	//	setForce(rightAtomIndex, forceJ);

	//	currentEnergy += 0.5 * forceFactor * forceIntensity * forceIntensity;
	//}
	//*energy = currentEnergy;

	//changed();
}

void SESpringProtInteractionModel::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SESpringProtInteractionModel::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function if your interaction model displays things in viewports, so that your interaction model can cast shadows
	// to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SESpringProtInteractionModel::displayForSelection() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to perform object picking.
	// Instead of rendering colors, your interaction model is expected to write the index of a data graph node (obtained with getIndex()).
	// Implement this function so that your interaction model can be selected (if you render its own index) or can be used to select other objects (if you render 
	// the other objects' indices), for example thanks to the utility functions provided by SAMSON (e.g. displaySpheresSelection, displayTrianglesSelection, etc.)
	// This should be implemented if your interaction model displays something in viewports (and you want the user to be able to select your interaction model
	// by picking its visual representation in viewports). 

}

void SESpringProtInteractionModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the interaction model. 
	// This should be implemented if your interaction model displays something in viewports. 

}

void SESpringProtInteractionModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine your model's influence on ambient occlusion (in case your interaction model displays something in viewports).
	// Implement this function if you want your interaction model to occlude other objects in ambient occlusion calculations.
	//
	// The ambientOcclusionData represents a nCellsX x nCellsY x nCellsZ grid of occlusion densities over the spatial region (boxOrigin, boxSize).
	// If your model represents geometry at position (x, y, z), then the occlusion density in corresponding grid nodes should be increased.
	//
	// Assuming x, y and z are given in length units (SBQuantity::length, SBQuantity::angstrom, etc.), the grid coordinates are:
	// SBQuantity::dimensionless xGrid = nCellsX * (x - boxOrigin.v[0]) / boxSize.v[0];
	// SBQuantity::dimensionless yGrid = nCellsY * (x - boxOrigin.v[1]) / boxSize.v[1];
	// SBQuantity::dimensionless zGrid = nCellsZ * (x - boxOrigin.v[2]) / boxSize.v[2];
	//
	// The corresponding density can be found at ambientOcclusionData[((int)zGrid.getValue() + 0)*nCellsY*nCellsX + ((int)yGrid.getValue() + 0)*nCellsX + ((int)xGrid.getValue() + 0)] (beware of grid bounds).
	// For higher-quality results, the influence of a point can be spread over neighboring grid nodes.

}

void SESpringProtInteractionModel::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle base events

}

void SESpringProtInteractionModel::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SESpringProtInteractionModel::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle dynamical events 

}

void SESpringProtInteractionModel::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Element generator pro tip: implement this function if you need to handle structural events

}
