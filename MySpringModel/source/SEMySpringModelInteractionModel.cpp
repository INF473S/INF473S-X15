#include "SEMySpringModelInteractionModel.hpp"
#include "SAMSON.hpp"
#include "SBResidue.hpp"
#include "SBBackbone.hpp"
#include "SBRandom.hpp"
#include <qdir.h>


SEMySpringModelInteractionModel::SEMySpringModelInteractionModel() : SBMInteractionModelParticleSystem(0) {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.


}

SEMySpringModelInteractionModel::SEMySpringModelInteractionModel(SBParticleSystem* particleSystem) : SBMInteractionModelParticleSystem(particleSystem) {

	// SAMSON Element generator pro tip: implement this function if you want your interaction model to be applied to a particle system (the general case).
	// You might want to connect to various signals and handle the corresponding events (for example to erase this interaction model when the dynamical model it is applied to is erased).

}

SEMySpringModelInteractionModel::~SEMySpringModelInteractionModel() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

}

void SEMySpringModelInteractionModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer) const {

	SBMInteractionModelParticleSystem::serialize(serializer, nodeIndexer);

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to serialize your interaction model.

}

void SEMySpringModelInteractionModel::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer) {

	SBMInteractionModelParticleSystem::unserialize(serializer, nodeIndexer);

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to unserialize your interaction model.

}

void SEMySpringModelInteractionModel::eraseImplementation() {

	// SAMSON Element generator pro tip: modify this function when you need to perform special tasks when your interaction model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SEMySpringModelInteractionModel::initializeInteractions() {

	particleIndex = (*particleSystem)->getStructuralParticleIndex();
	unsigned int nParticles = particleIndex->size();

	//initialize vectors
	springLengthVector = new SBVector<SBQuantity::length>;
	springAtomIVector = new SBVector<SBAtom*>;
	springAtomJVector = new SBVector<SBAtom*>;

	////get the list of bonds in the model
	//SBNodePredicate* nodePredicate = SAMSON::makeNodePredicate("node.type bond");
	SBNodeIndexer nodeIndexer;
	//SAMSON::getActiveDocument()->getNodes(nodeIndexer, *nodePredicate);

	//SAMSON::setStatusMessage(QString::number(nodeIndexer.size()),0);

	//SB_FOR(SBNode* node, nodeIndexer) {

	//	SBBond* bond = static_cast<SBBond*>(node);

	//	SBAtom* atomI = bond->getLeftAtom();
	//	SBAtom* atomJ = bond->getRightAtom();

	//	unsigned int atomIIndex = particleIndex->getIndex(atomI);
	//	unsigned int atomJIndex = particleIndex->getIndex(atomJ);
	//	
	//	//add the atoms to the atoms Vectors
	//	springAtomIVector->push_back(atomI);
	//	springAtomJVector->push_back(atomJ);

	//	//SBQuantity::length 	distance = bond->getLength();
	//	//add the equilibrium lengthd to the springLength vector
	//	SBQuantity::length distance = ((*particleSystem)->getPosition(atomIIndex) -
	//		(*particleSystem)->getPosition(atomJIndex)).norm();
	//	springLengthVector->push_back(distance);
	//}

	//MODIFS ROMAIN
	nodeIndexer.clear();
	SB_FOR(SBStructuralParticle* particle, *particleIndex) if ((SBNode::IsType(SBNode::Atom) && SBAtom::HasName() && (SBAtom::GetName() == std::string("CA")))(particle)) nodeIndexer.addNode(particle);
	//SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom) && SBAtom::HasName() && (SBAtom::GetName() == std::string("CA")));

	//QDir dir("C:\\Stephane\\Enseignement\\Polytechnique\\2016-2017\\INF473S\\Git\\Tests\\DISTANCES");
	QDir dir("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\TESTS\\DISTANCES");

	QString title = "/!\\ Attention /!\\";
	QString text = "Bien verifier que le \"QDir\" a la ligne 98 du SEMySpringModelInteractionModel.cpp est le bon. C'est le repertoire ou on doit aller chercher les images de distances.";
	SAMSON::informUser(title, text);

	SBRandom r(SAMSON::getTime());

	QFileInfoList files = dir.entryInfoList();
	foreach(QFileInfo file, files) {
		if (!file.isDir()) {
			QImage image(file.filePath());

			int size = image.width();

			QString name = file.fileName().split(".")[0];
			int step = (name.split("_")[2]).toInt();
			int offset = (name.split("_")[4]).toInt();

			for (int i = 0; i < size - 1; i++) {

				SBAtom* carbi = static_cast<SBAtom*>(nodeIndexer[offset + i*step]);
				if (!carbi) continue;

				for (int j = i + 1; j < size; j++) {

					SBAtom* carbj = static_cast<SBAtom*>(nodeIndexer[offset + j*step]);
					if (!carbj) continue;

					SBQuantity::length distance = SBQuantity::angstrom(image.pixelColor(QPoint(i, j)).red());

					//distance *= 1.0 + 1.9*(r.randDouble1() - 0.5); // add randomness to test robustness

					springAtomIVector->push_back(carbi);
					springAtomJVector->push_back(carbj);
					springLengthVector->push_back(distance);

				}
			}
		}
	}
	//FIN MODIFS ROMAIN

	//initialize energy and forces
	*energy = SBQuantity::energy(0.0);
	SBQuantity::energy currentEnergy(0.0);
	for (unsigned int i = 0; i < nParticles; ++i)
		setForce(i, SBForce3(SBQuantity::force(0)));

	unsigned int nSprings = springLengthVector->size();
	for (unsigned int i = 0; i < nSprings; ++i) {

		SBAtom* leftAtom = (*springAtomIVector)[i];
		SBAtom* rightAtom = (*springAtomJVector)[i];

		unsigned int  leftAtomIndex = particleIndex->getIndex(leftAtom);
		unsigned int rightAtomIndex = particleIndex->getIndex(rightAtom);

		const SBPosition3& leftAtomPosition =
			(*particleSystem)->getPosition(leftAtomIndex);
		const SBPosition3& rightAtomPosition =
			(*particleSystem)->getPosition(rightAtomIndex);

		//the force intensity depends on the shift respect to the equilibrium
		SBQuantity::length forceIntensity = (rightAtomPosition - leftAtomPosition).norm()
			- (*springLengthVector)[i];
		SBQuantity::forcePerLength forceFactor(5);

		SBForce3  force = forceFactor * forceIntensity *
			(rightAtomPosition - leftAtomPosition).normalizedVersion();

		SBForce3 forceI = getForce(leftAtomIndex) + force;
		SBForce3 forceJ = getForce(rightAtomIndex) - force;

		setForce(leftAtomIndex, forceI);
		setForce(rightAtomIndex, forceJ);
		currentEnergy += 0.5 * forceFactor * forceIntensity * forceIntensity;
	}
	*energy = currentEnergy;



	changed();
}

void SEMySpringModelInteractionModel::updateInteractions() {

	particleIndex = (*particleSystem)->getStructuralParticleIndex();
	unsigned int nParticles = particleIndex->size();

	//initialize energy and forces
	//*energy = SBQuantity::energy(0.0);
	SBQuantity::energy currentEnergy(0.0);
	for (unsigned int i = 0; i < nParticles; ++i)
		setForce(i, SBForce3(SBQuantity::force(0)));

	unsigned int nSprings = springLengthVector->size();
	for (unsigned int i = 0; i < nSprings; ++i) {

		SBAtom* leftAtom = (*springAtomIVector)[i];
		SBAtom* rightAtom = (*springAtomJVector)[i];

		unsigned int  leftAtomIndex = particleIndex->getIndex(leftAtom);
		unsigned int rightAtomIndex = particleIndex->getIndex(rightAtom);

		const SBPosition3& leftAtomPosition =
			(*particleSystem)->getPosition(leftAtomIndex);
		const SBPosition3& rightAtomPosition =
			(*particleSystem)->getPosition(rightAtomIndex);

		//the force intensity depends on the shift respect to the equilibrium
		SBQuantity::length forceIntensity = (rightAtomPosition - leftAtomPosition).norm()
			- (*springLengthVector)[i];
		SBQuantity::forcePerLength forceFactor(5);

		SBForce3  force = forceFactor * forceIntensity *
			(rightAtomPosition - leftAtomPosition).normalizedVersion();

		SBForce3 forceI = getForce(leftAtomIndex) + force;
		SBForce3 forceJ = getForce(rightAtomIndex) - force;

		setForce(leftAtomIndex, forceI);
		setForce(rightAtomIndex, forceJ);

		currentEnergy += 0.5 * forceFactor * forceIntensity * forceIntensity;
	}
	*energy = currentEnergy;

	changed();
}

void SEMySpringModelInteractionModel::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	unsigned int nSprings = springLengthVector->size();

	float* positionData = new float[6 * nSprings];
	unsigned int* indexData = new  unsigned int[2 * nSprings];
	unsigned int* flagData = new  unsigned int[2 * nSprings];
	float* colorData = new float[8 * nSprings];

	for (unsigned int i = 0; i < nSprings; ++i) {

		SBAtom* carbi = (*springAtomIVector)[i];
		SBAtom* carbj = (*springAtomJVector)[i];

		indexData[2 * i + 0] = 2 * i + 0;
		indexData[2 * i + 1] = 2 * i + 1;

		flagData[2 * i + 0] = getInheritedFlags();
		flagData[2 * i + 1] = getInheritedFlags();

		SBPosition3 positioni = carbi->getPosition();
		positionData[6 * i + 0] = (float)positioni.v[0].getValue();
		positionData[6 * i + 1] = (float)positioni.v[1].getValue();
		positionData[6 * i + 2] = (float)positioni.v[2].getValue();

		SBPosition3 positionj = carbj->getPosition();
		positionData[6 * i + 3] = (float)positionj.v[0].getValue();
		positionData[6 * i + 4] = (float)positionj.v[1].getValue();
		positionData[6 * i + 5] = (float)positionj.v[2].getValue();

		SBQuantity::length currentLength = (positioni - positionj).norm();

		if (currentLength <= (*springLengthVector)[i]) {

			float lambda = (float)(currentLength / (*springLengthVector)[i]).getValue();

			// from blue (too short) to green (equilibrium)

			colorData[8 * i + 0] = 0.0f;
			colorData[8 * i + 1] = lambda;
			colorData[8 * i + 2] = 1.0f - lambda;
			colorData[8 * i + 3] = 1.0f;

			colorData[8 * i + 4] = 0.0f;
			colorData[8 * i + 5] = lambda;
			colorData[8 * i + 6] = 1.0f - lambda;
			colorData[8 * i + 7] = 1.0f;

		}
		else {

			float lambda = min(2.0f, (float)(currentLength / (*springLengthVector)[i]).getValue()) - 1.0f;

			// from green (equilibrium) to red (too long)

			colorData[8 * i + 0] = lambda;
			colorData[8 * i + 1] = 1.0f - lambda;
			colorData[8 * i + 2] = 0.0f;
			colorData[8 * i + 3] = 1.0f;

			colorData[8 * i + 4] = lambda;
			colorData[8 * i + 5] = 1.0f - lambda;
			colorData[8 * i + 6] = 0.0f;
			colorData[8 * i + 7] = 1.0f;

		}

	}

#ifdef SB_ELEMENT_VERSION_NUMBER
	SAMSON::displayLines(nSprings, 2 * nSprings, indexData, positionData, colorData, flagData);
#else
	SAMSON::displayLines(nSprings, 2 * nSprings, indexData, positionData, colorData);
#endif

	delete[] positionData;
	delete[] indexData;
	delete[] colorData;
	delete[] flagData;

}

void SEMySpringModelInteractionModel::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function if your interaction model displays things in viewports, so that your interaction model can cast shadows
	// to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SEMySpringModelInteractionModel::displayForSelection() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to perform object picking.
	// Instead of rendering colors, your interaction model is expected to write the index of a data graph node (obtained with getIndex()).
	// Implement this function so that your interaction model can be selected (if you render its own index) or can be used to select other objects (if you render 
	// the other objects' indices), for example thanks to the utility functions provided by SAMSON (e.g. displaySpheresSelection, displayTrianglesSelection, etc.)
	// This should be implemented if your interaction model displays something in viewports (and you want the user to be able to select your interaction model
	// by picking its visual representation in viewports). 

}

void SEMySpringModelInteractionModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the interaction model. 
	// This should be implemented if your interaction model displays something in viewports. 

}

void SEMySpringModelInteractionModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

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

void SEMySpringModelInteractionModel::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle base events

}

void SEMySpringModelInteractionModel::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SEMySpringModelInteractionModel::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle dynamical events 

}

void SEMySpringModelInteractionModel::onStructuralEvent(SBStructuralEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle structural events

}
