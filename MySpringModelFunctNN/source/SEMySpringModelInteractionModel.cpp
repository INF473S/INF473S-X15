#include "SEMySpringModelInteractionModel.hpp"
#include "SAMSON.hpp"
#include "SBResidue.hpp"
#include "SBBackbone.hpp"
#include "SBRandom.hpp"
#include <qdir.h>

double Size_32_Step_10_D_16_17(double AA0, double  AA1, double AA2, double AA3, double AA4, double AA5, double AA6, double AA7, double AA8, double AA9, double AA10, double  AA11, double AA12, double AA13, double AA14, double AA15, double AA16, double AA17, double AA18, double AA19, double AA20, double AA21, double AA22, double AA23, double AA24, double AA25, double AA26, double AA27, double AA28, double AA29, double AA30, double AA31);

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

#ifdef SB_ELEMENT_VERSION
	// 0.5.0
	particleIndex = (*particleSystem)->getStructuralParticleIndex();
#else
	particleIndex = (*particleSystem)->getStructuralParticleIndexer();
#endif

	unsigned int nParticles = particleIndex->size();

	//initialize vectors
	springLengthVector = new SBVector < SBQuantity::length > ;
	springAtomIVector = new SBVector < SBAtom* > ;
	springAtomJVector = new SBVector < SBAtom* > ;

	////get the list of bonds in the model
	//SBNodePredicate* nodePredicate = SAMSON::makeNodePredicate("node.type bond");
	SBNodeIndexer nodeIndexer;

	SB_FOR(SBStructuralParticle* particle, *particleIndex) if ((SBNode::IsType(SBNode::Atom) && SBAtom::HasName() && (SBAtom::GetName() == std::string("CA")))(particle)) nodeIndexer.addNode(particle);
	
	//SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom) && SBAtom::HasName() && (SBAtom::GetName() == std::string("CA")));

	SBRandom r(SAMSON::getTime());

	for (int i = 0; i < nodeIndexer.size() - 320; i++){
		SBAtom* carbi = static_cast<SBAtom*>(nodeIndexer[i + 160]);
		SBAtom* carbj = static_cast<SBAtom*>(nodeIndexer[i + 170]);

		SBQuantity::length distance = SBQuantity::angstrom(Size_32_Step_10_D_16_17(
			static_cast<SBResidue*>(nodeIndexer[i]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 10]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 20]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 30]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 40]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 50]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 60]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 70]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 80]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 90]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 100]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 110]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 120]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 130]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 140]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 150]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 160]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 170]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 180]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 190]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 200]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 210]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 220]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 230]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 240]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 250]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 260]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 270]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 280]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 290]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 300]->getParent()->getParent())->getResidueType(),
			static_cast<SBResidue*>(nodeIndexer[i + 310]->getParent()->getParent())->getResidueType()
			));

		//distance *= 1.0 + 1.9*(r.randDouble1() - 0.5); // add randomness to test robustness
		springAtomIVector->push_back(carbi);
		springAtomJVector->push_back(carbj);
		springLengthVector->push_back(distance);

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

#ifdef SB_ELEMENT_VERSION
	// 0.5.0
	particleIndex = (*particleSystem)->getStructuralParticleIndex();
#else
	particleIndex = (*particleSystem)->getStructuralParticleIndexer();
#endif

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


double Size_32_Step_10_D_16_17(double AA0, double  AA1, double AA2, double AA3, double AA4, double AA5, double AA6, double AA7, double AA8, double AA9, double AA10, double  AA11, double AA12, double AA13, double AA14, double AA15, double AA16, double AA17, double AA18, double AA19, double AA20, double AA21, double AA22, double AA23, double AA24, double AA25, double AA26, double AA27, double AA28, double AA29, double AA30, double AA31){
	double scaled_AA0 = 2 * (AA0 - 1) / (25 - 1) - 1;
	double scaled_AA1 = 2 * (AA1 - 1) / (25 - 1) - 1;
	double scaled_AA2 = 2 * (AA2 - 1) / (25 - 1) - 1;
	double scaled_AA3 = 2 * (AA3 - 1) / (25 - 1) - 1;
	double scaled_AA4 = 2 * (AA4 - 1) / (25 - 1) - 1;
	double scaled_AA5 = 2 * (AA5 - 1) / (25 - 1) - 1;
	double scaled_AA6 = 2 * (AA6 - 1) / (25 - 1) - 1;
	double scaled_AA7 = 2 * (AA7 - 1) / (25 - 1) - 1;
	double scaled_AA8 = 2 * (AA8 - 1) / (25 - 1) - 1;
	double scaled_AA9 = 2 * (AA9 - 1) / (25 - 1) - 1;
	double scaled_AA10 = 2 * (AA10 - 1) / (25 - 1) - 1;
	double scaled_AA11 = 2 * (AA11 - 1) / (25 - 1) - 1;
	double scaled_AA12 = 2 * (AA12 - 1) / (25 - 1) - 1;
	double scaled_AA13 = 2 * (AA13 - 1) / (25 - 1) - 1;
	double scaled_AA14 = 2 * (AA14 - 1) / (20 - 1) - 1;
	double scaled_AA15 = 2 * (AA15 - 1) / (20 - 1) - 1;
	double scaled_AA16 = 2 * (AA16 - 1) / (20 - 1) - 1;
	double scaled_AA17 = 2 * (AA17 - 1) / (20 - 1) - 1;
	double scaled_AA18 = 2 * (AA18 - 1) / (20 - 1) - 1;
	double scaled_AA19 = 2 * (AA19 - 1) / (20 - 1) - 1;
	double scaled_AA20 = 2 * (AA20 - 1) / (20 - 1) - 1;
	double scaled_AA21 = 2 * (AA21 - 1) / (20 - 1) - 1;
	double scaled_AA22 = 2 * (AA22 - 1) / (20 - 1) - 1;
	double scaled_AA23 = 2 * (AA23 - 1) / (20 - 1) - 1;
	double scaled_AA24 = 2 * (AA24 - 1) / (20 - 1) - 1;
	double scaled_AA25 = 2 * (AA25 - 1) / (20 - 1) - 1;
	double scaled_AA26 = 2 * (AA26 - 1) / (20 - 1) - 1;
	double scaled_AA27 = 2 * (AA27 - 1) / (20 - 1) - 1;
	double scaled_AA28 = 2 * (AA28 - 1) / (20 - 1) - 1;
	double scaled_AA29 = 2 * (AA29 - 1) / (20 - 1) - 1;
	double scaled_AA30 = 2 * (AA30 - 1) / (20 - 1) - 1;
	double scaled_AA31 = 2 * (AA31 - 1) / (20 - 1) - 1;
	double y_1_1 = tanh(-0.38367 - 0.924601*scaled_AA0 - 2.57477*scaled_AA1 + 0.460334*scaled_AA2 - 2.5386*scaled_AA3 - 1.08321*scaled_AA4 - 1.24545*scaled_AA5 - 1.99591*scaled_AA6 + 0.216117*scaled_AA7 + 0.13532*scaled_AA8 + 1.98332*scaled_AA9 - 0.0535492*scaled_AA10 - 0.711181*scaled_AA11 - 0.0541116*scaled_AA12 + 2.12953*scaled_AA13 + 1.26609*scaled_AA14 + 1.67178*scaled_AA15 + 0.20171*scaled_AA16 - 0.876384*scaled_AA17 - 1.16911*scaled_AA18 + 1.0733*scaled_AA19 - 0.305686*scaled_AA20 - 0.696599*scaled_AA21 - 0.33267*scaled_AA22 + 0.909584*scaled_AA23 - 2.19223*scaled_AA24 - 0.310584*scaled_AA25 - 1.23246*scaled_AA26 + 0.685551*scaled_AA27 + 0.713103*scaled_AA28 - 0.925223*scaled_AA29 + 0.228664*scaled_AA30 - 0.736128*scaled_AA31);
	double y_1_2 = tanh(-1.57981 + 1.14064*scaled_AA0 + 1.05282*scaled_AA1
		- 2.52094*scaled_AA2 - 0.00670856*scaled_AA3
		+ 0.207727*scaled_AA4 - 1.42357*scaled_AA5
		- 0.792585*scaled_AA6 - 1.80976*scaled_AA7
		+ 1.02348*scaled_AA8 - 0.67478*scaled_AA9
		+ 0.818449*scaled_AA10
		+ 2.01672*scaled_AA11
		+ 0.280675*scaled_AA12
		- 0.0552483*scaled_AA13
		- 0.142991*scaled_AA14
		+ 2.20591*scaled_AA15
		- 0.240463*scaled_AA16
		- 1.29935*scaled_AA17
		- 0.835291*scaled_AA18
		+ 0.534475*scaled_AA19
		+ 1.44157*scaled_AA20
		- 1.64093*scaled_AA21
		+ 0.09349*scaled_AA22
		- 1.15784*scaled_AA23
		- 0.550415*scaled_AA24
		- 1.16544*scaled_AA25
		+ 0.0971009*scaled_AA26
		- 0.455174*scaled_AA27
		- 0.795005*scaled_AA28
		- 0.317224*scaled_AA29
		- 0.59532*scaled_AA30
		+ 1.41016*scaled_AA31);
	double y_1_3 = tanh(0.587399
		+ 2.14562*scaled_AA0
		+ 1.86811*scaled_AA1
		+ 2.48591*scaled_AA2
		+ 0.431556*scaled_AA3
		+ 1.01404*scaled_AA4
		+ 1.69016*scaled_AA5
		+ 0.603131*scaled_AA6
		- 0.638956*scaled_AA7
		- 0.303118*scaled_AA8
		- 0.848011*scaled_AA9
		- 1.2121*scaled_AA10
		+ 2.39869*scaled_AA11
		- 0.275645*scaled_AA12
		- 0.0800632*scaled_AA13
		+ 0.822362*scaled_AA14
		+ 1.42579*scaled_AA15
		+ 1.0506*scaled_AA16
		- 0.149057*scaled_AA17
		+ 0.0725882*scaled_AA18
		+ 1.2068*scaled_AA19
		+ 0.292597*scaled_AA20
		+ 0.220894*scaled_AA21
		- 0.397568*scaled_AA22
		- 0.702097*scaled_AA23
		+ 2.99359*scaled_AA24
		- 0.0648737*scaled_AA25
		- 2.17638*scaled_AA26
		- 0.794631*scaled_AA27
		- 0.740555*scaled_AA28
		+ 0.0600667*scaled_AA29
		- 1.56341*scaled_AA30
		+ 0.609231*scaled_AA31);
	double y_1_4 = tanh(0.675907
		+ 0.593603*scaled_AA0
		+ 0.944076*scaled_AA1
		- 0.964342*scaled_AA2
		- 1.72873*scaled_AA3
		- 0.045172*scaled_AA4
		+ 0.0708639*scaled_AA5
		- 0.75061*scaled_AA6
		+ 1.08458*scaled_AA7
		+ 0.986166*scaled_AA8
		+ 1.50139*scaled_AA9
		- 0.793083*scaled_AA10
		+ 1.01869*scaled_AA11
		- 0.393448*scaled_AA12
		+ 0.562483*scaled_AA13
		+ 0.141709*scaled_AA14
		+ 0.509575*scaled_AA15
		- 0.413578*scaled_AA16
		- 0.319964*scaled_AA17
		- 0.697135*scaled_AA18
		+ 1.04714*scaled_AA19
		- 0.797962*scaled_AA20
		- 0.371764*scaled_AA21
		+ 1.21355*scaled_AA22
		- 0.154672*scaled_AA23
		- 1.23665*scaled_AA24
		+ 0.274124*scaled_AA25
		+ 1.03278*scaled_AA26
		+ 0.0652955*scaled_AA27
		- 1.21785*scaled_AA28
		- 0.428225*scaled_AA29
		- 1.3418*scaled_AA30
		+ 1.6469*scaled_AA31);
	double y_1_5 = tanh(-0.702418
		+ 0.0882194*scaled_AA0
		- 1.36627*scaled_AA1
		- 2.12665*scaled_AA2
		+ 1.3491*scaled_AA3
		- 1.45824*scaled_AA4
		- 0.785255*scaled_AA5
		+ 0.191153*scaled_AA6
		+ 0.539833*scaled_AA7
		- 0.103782*scaled_AA8
		+ 0.623289*scaled_AA9
		- 0.196835*scaled_AA10
		- 1.31104*scaled_AA11
		+ 0.153002*scaled_AA12
		- 0.631874*scaled_AA13
		+ 1.1097*scaled_AA14
		+ 0.0229927*scaled_AA15
		+ 1.00142*scaled_AA16
		- 0.88874*scaled_AA17
		- 1.58115*scaled_AA18
		- 0.484705*scaled_AA19
		- 0.501745*scaled_AA20
		+ 0.851471*scaled_AA21
		- 0.242699*scaled_AA22
		+ 0.293571*scaled_AA23
		+ 0.907861*scaled_AA24
		- 0.616137*scaled_AA25
		+ 0.763881*scaled_AA26
		- 1.35884*scaled_AA27
		- 1.40557*scaled_AA28
		+ 1.15204*scaled_AA29
		+ 1.17431*scaled_AA30
		- 0.331503*scaled_AA31);
	double y_1_6 = tanh(0.306036
		- 0.235516*scaled_AA0
		- 0.645451*scaled_AA1
		+ 0.418058*scaled_AA2
		+ 0.197159*scaled_AA3
		- 1.39046*scaled_AA4
		- 0.321999*scaled_AA5
		+ 0.00651898*scaled_AA6
		+ 1.75337*scaled_AA7
		+ 0.553963*scaled_AA8
		+ 0.901643*scaled_AA9
		+ 0.350106*scaled_AA10
		- 0.643437*scaled_AA11
		- 0.105598*scaled_AA12
		- 0.656461*scaled_AA13
		+ 0.568889*scaled_AA14
		+ 0.291627*scaled_AA15
		- 0.0894702*scaled_AA16
		+ 0.980243*scaled_AA17
		- 0.467474*scaled_AA18
		- 0.826546*scaled_AA19
		- 0.673947*scaled_AA20
		- 1.07797*scaled_AA21
		- 1.10009*scaled_AA22
		+ 0.910213*scaled_AA23
		- 2.07205*scaled_AA24
		+ 1.13527*scaled_AA25
		+ 0.232418*scaled_AA26
		- 0.0515844*scaled_AA27
		+ 0.882809*scaled_AA28
		- 0.0466832*scaled_AA29
		- 0.575343*scaled_AA30
		- 0.365195*scaled_AA31);
	double y_1_7 = tanh(1.30204
		- 0.405407*scaled_AA0
		+ 1.88972*scaled_AA1
		- 0.295887*scaled_AA2
		- 2.45987*scaled_AA3
		+ 1.29234*scaled_AA4
		+ 1.83854*scaled_AA5
		- 2.4344*scaled_AA6
		+ 0.112584*scaled_AA7
		- 0.0640261*scaled_AA8
		- 0.00798415*scaled_AA9
		+ 0.952802*scaled_AA10
		+ 0.81611*scaled_AA11
		+ 0.0479887*scaled_AA12
		- 0.892862*scaled_AA13
		+ 0.256779*scaled_AA14
		- 0.076995*scaled_AA15
		- 0.51576*scaled_AA16
		- 0.278696*scaled_AA17
		- 1.02929*scaled_AA18
		+ 2.75046*scaled_AA19
		+ 0.229055*scaled_AA20
		+ 1.33591*scaled_AA21
		+ 0.687591*scaled_AA22
		+ 0.402845*scaled_AA23
		- 1.19297*scaled_AA24
		- 0.223916*scaled_AA25
		- 0.905841*scaled_AA26
		- 1.55617*scaled_AA27
		+ 0.716273*scaled_AA28
		+ 2.00988*scaled_AA29
		- 1.02739*scaled_AA30
		+ 0.199129*scaled_AA31);
	double y_1_8 = tanh(0.157754
		+ 1.73969*scaled_AA0
		+ 0.197036*scaled_AA1
		- 0.454274*scaled_AA2
		- 1.07747*scaled_AA3
		- 1.78724*scaled_AA4
		- 1.35302*scaled_AA5
		- 0.173988*scaled_AA6
		- 1.79656*scaled_AA7
		+ 0.947838*scaled_AA8
		+ 0.927206*scaled_AA9
		- 0.80576*scaled_AA10
		+ 1.29059*scaled_AA11
		- 1.79408*scaled_AA12
		- 1.07454*scaled_AA13
		- 0.649633*scaled_AA14
		- 0.00450743*scaled_AA15
		+ 1.44878*scaled_AA16
		+ 0.61753*scaled_AA17
		- 1.29727*scaled_AA18
		- 0.110802*scaled_AA19
		- 0.663859*scaled_AA20
		+ 0.460542*scaled_AA21
		+ 1.00211*scaled_AA22
		+ 0.816957*scaled_AA23
		- 0.305934*scaled_AA24
		+ 0.404725*scaled_AA25
		- 0.607636*scaled_AA26
		- 0.528281*scaled_AA27
		+ 0.0439876*scaled_AA28
		+ 1.30458*scaled_AA29
		- 0.637049*scaled_AA30
		- 0.0108024*scaled_AA31);
	double y_1_9 = tanh(-0.979982
		- 1.1535*scaled_AA0
		+ 1.19006*scaled_AA1
		- 0.723918*scaled_AA2
		- 0.52316*scaled_AA3
		+ 1.30621*scaled_AA4
		+ 1.93537*scaled_AA5
		- 0.261367*scaled_AA6
		- 0.139701*scaled_AA7
		- 0.449011*scaled_AA8
		- 3.12295*scaled_AA9
		+ 0.486014*scaled_AA10
		- 0.480145*scaled_AA11
		+ 0.30783*scaled_AA12
		- 0.361828*scaled_AA13
		+ 2.32366*scaled_AA14
		- 0.579032*scaled_AA15
		- 0.509198*scaled_AA16
		+ 0.579386*scaled_AA17
		+ 2.15539*scaled_AA18
		- 0.770737*scaled_AA19
		+ 1.04425*scaled_AA20
		- 1.18584*scaled_AA21
		+ 0.874048*scaled_AA22
		+ 0.66949*scaled_AA23
		- 0.564283*scaled_AA24
		- 1.03959*scaled_AA25
		+ 0.117298*scaled_AA26
		+ 0.645375*scaled_AA27
		+ 0.67759*scaled_AA28
		- 1.2066*scaled_AA29
		- 1.05245*scaled_AA30
		+ 0.115484*scaled_AA31);
	double y_1_10 = tanh(1.84371
		- 0.386842*scaled_AA0
		- 1.31535*scaled_AA1
		- 1.89528*scaled_AA2
		- 1.28735*scaled_AA3
		- 0.10915*scaled_AA4
		+ 1.16111*scaled_AA5
		+ 1.77845*scaled_AA6
		- 0.0955927*scaled_AA7
		+ 2.43182*scaled_AA8
		+ 1.08891*scaled_AA9
		+ 3.05162*scaled_AA10
		- 1.86078*scaled_AA11
		- 0.14211*scaled_AA12
		+ 0.86512*scaled_AA13
		+ 1.6646*scaled_AA14
		- 1.14335*scaled_AA15
		+ 0.649746*scaled_AA16
		+ 0.733204*scaled_AA17
		- 0.0129794*scaled_AA18
		- 1.33703*scaled_AA19
		+ 1.17942*scaled_AA20
		- 2.20604*scaled_AA21
		- 0.292178*scaled_AA22
		+ 0.791061*scaled_AA23
		- 0.336544*scaled_AA24
		+ 0.65963*scaled_AA25
		+ 0.871384*scaled_AA26
		- 0.166553*scaled_AA27
		- 0.346617*scaled_AA28
		+ 2.28051*scaled_AA29
		- 0.985281*scaled_AA30
		+ 0.861253*scaled_AA31);
	double y_1_11 = tanh(-0.805401
		+ 1.87062*scaled_AA0
		- 0.341784*scaled_AA1
		+ 0.785556*scaled_AA2
		- 0.680056*scaled_AA3
		+ 0.585985*scaled_AA4
		+ 2.23438*scaled_AA5
		+ 0.902425*scaled_AA6
		+ 0.561691*scaled_AA7
		+ 0.621681*scaled_AA8
		+ 0.154213*scaled_AA9
		- 1.05434*scaled_AA10
		- 0.141513*scaled_AA11
		+ 0.379722*scaled_AA12
		- 0.00590647*scaled_AA13
		- 0.330465*scaled_AA14
		+ 1.07936*scaled_AA15
		- 1.33719*scaled_AA16
		+ 1.21791*scaled_AA17
		+ 0.671771*scaled_AA18
		+ 0.367185*scaled_AA19
		- 0.798256*scaled_AA20
		- 0.0200456*scaled_AA21
		+ 1.31865*scaled_AA22
		+ 1.36459*scaled_AA23
		+ 1.23224*scaled_AA24
		+ 1.04017*scaled_AA25
		- 0.0999806*scaled_AA26
		+ 0.391758*scaled_AA27
		+ 0.763726*scaled_AA28
		+ 0.0682785*scaled_AA29
		+ 1.39693*scaled_AA30
		+ 0.22537*scaled_AA31);
	double y_1_12 = tanh(1.22828
		+ 1.68227*scaled_AA0
		+ 0.234893*scaled_AA1
		- 0.890044*scaled_AA2
		- 0.159532*scaled_AA3
		- 0.411383*scaled_AA4
		+ 3.55646*scaled_AA5
		- 0.774145*scaled_AA6
		- 0.045758*scaled_AA7
		+ 0.110905*scaled_AA8
		+ 0.105504*scaled_AA9
		- 0.454415*scaled_AA10
		- 0.137397*scaled_AA11
		+ 0.395107*scaled_AA12
		- 0.333761*scaled_AA13
		+ 0.338306*scaled_AA14
		+ 0.309047*scaled_AA15
		- 0.39094*scaled_AA16
		+ 0.300845*scaled_AA17
		- 0.422912*scaled_AA18
		- 0.913508*scaled_AA19
		- 1.57715*scaled_AA20
		- 0.73896*scaled_AA21
		- 0.211349*scaled_AA22
		+ 0.818594*scaled_AA23
		- 0.98393*scaled_AA24
		- 0.508603*scaled_AA25
		- 0.908032*scaled_AA26
		- 0.631461*scaled_AA27
		+ 0.518581*scaled_AA28
		+ 1.06298*scaled_AA29
		+ 1.00192*scaled_AA30
		+ 0.42808*scaled_AA31);
	double y_1_13 = tanh(2.52975
		+ 0.670979*scaled_AA0
		+ 2.16779*scaled_AA1
		- 0.280982*scaled_AA2
		+ 0.525688*scaled_AA3
		+ 0.439959*scaled_AA4
		- 0.661242*scaled_AA5
		+ 0.46016*scaled_AA6
		+ 1.04281*scaled_AA7
		- 1.55556*scaled_AA8
		- 1.21849*scaled_AA9
		+ 0.786991*scaled_AA10
		+ 0.494911*scaled_AA11
		+ 0.242391*scaled_AA12
		- 0.0295633*scaled_AA13
		- 0.122531*scaled_AA14
		+ 0.246787*scaled_AA15
		- 1.13624*scaled_AA16
		- 1.29991*scaled_AA17
		- 0.84939*scaled_AA18
		+ 0.125689*scaled_AA19
		- 0.125041*scaled_AA20
		- 0.16629*scaled_AA21
		- 0.149577*scaled_AA22
		+ 0.387235*scaled_AA23
		+ 1.50021*scaled_AA24
		- 0.253915*scaled_AA25
		+ 0.364329*scaled_AA26
		+ 1.22051*scaled_AA27
		+ 1.13281*scaled_AA28
		- 0.301789*scaled_AA29
		+ 0.845729*scaled_AA30
		- 2.13357*scaled_AA31);
	double y_1_14 = tanh(1.7814
		- 1.4325*scaled_AA0
		+ 0.751002*scaled_AA1
		+ 0.183491*scaled_AA2
		+ 0.551758*scaled_AA3
		- 0.0826868*scaled_AA4
		- 1.03708*scaled_AA5
		+ 2.0651*scaled_AA6
		+ 1.55264*scaled_AA7
		+ 0.85724*scaled_AA8
		- 0.363697*scaled_AA9
		- 1.18569*scaled_AA10
		+ 1.80183*scaled_AA11
		- 0.00115098*scaled_AA12
		+ 1.0108*scaled_AA13
		- 2.70475*scaled_AA14
		+ 0.745769*scaled_AA15
		+ 0.826763*scaled_AA16
		+ 0.885942*scaled_AA17
		+ 0.64351*scaled_AA18
		- 1.58388*scaled_AA19
		- 2.11404*scaled_AA20
		+ 0.430298*scaled_AA21
		- 0.533825*scaled_AA22
		- 1.29411*scaled_AA23
		- 0.653186*scaled_AA24
		- 1.83657*scaled_AA25
		+ 0.716411*scaled_AA26
		+ 1.0538*scaled_AA27
		+ 1.67901*scaled_AA28
		+ 0.420142*scaled_AA29
		+ 1.26857*scaled_AA30
		- 1.42796*scaled_AA31);
	double y_1_15 = tanh(-0.0660131
		- 0.540398*scaled_AA0
		+ 0.0143006*scaled_AA1
		- 0.833536*scaled_AA2
		- 0.960968*scaled_AA3
		- 1.03186*scaled_AA4
		+ 0.195414*scaled_AA5
		- 0.919482*scaled_AA6
		+ 0.471274*scaled_AA7
		+ 0.776106*scaled_AA8
		+ 0.799401*scaled_AA9
		- 0.19199*scaled_AA10
		- 0.897965*scaled_AA11
		+ 0.671849*scaled_AA12
		+ 2.10961*scaled_AA13
		- 0.485644*scaled_AA14
		- 0.466106*scaled_AA15
		+ 0.202713*scaled_AA16
		- 1.15192*scaled_AA17
		- 0.0125904*scaled_AA18
		+ 0.299098*scaled_AA19
		+ 0.04461*scaled_AA20
		- 0.487826*scaled_AA21
		- 0.869344*scaled_AA22
		- 1.04697*scaled_AA23
		- 0.34108*scaled_AA24
		+ 0.0623663*scaled_AA25
		- 0.433282*scaled_AA26
		+ 0.368927*scaled_AA27
		+ 0.750425*scaled_AA28
		+ 0.114101*scaled_AA29
		+ 0.340046*scaled_AA30
		+ 0.0671671*scaled_AA31);
	double y_1_16 = tanh(-1.14125
		- 0.663256*scaled_AA0
		- 1.3253*scaled_AA1
		- 0.481399*scaled_AA2
		+ 1.07769*scaled_AA3
		+ 1.00084*scaled_AA4
		- 0.4355*scaled_AA5
		+ 0.0351362*scaled_AA6
		- 0.946771*scaled_AA7
		+ 0.517733*scaled_AA8
		- 0.348584*scaled_AA9
		- 0.423917*scaled_AA10
		- 0.602031*scaled_AA11
		- 1.1049*scaled_AA12
		- 0.408243*scaled_AA13
		+ 0.669634*scaled_AA14
		- 0.333355*scaled_AA15
		+ 0.668059*scaled_AA16
		- 0.948946*scaled_AA17
		+ 0.565736*scaled_AA18
		- 0.922853*scaled_AA19
		- 0.180224*scaled_AA20
		- 0.0502969*scaled_AA21
		- 0.928757*scaled_AA22
		+ 0.566961*scaled_AA23
		- 0.0874855*scaled_AA24
		+ 0.817171*scaled_AA25
		- 2.01661*scaled_AA26
		+ 1.07248*scaled_AA27
		+ 1.31252*scaled_AA28
		+ 1.54336*scaled_AA29
		+ 0.0848288*scaled_AA30
		- 0.786854*scaled_AA31);
	double y_1_17 = tanh(0.515066
		- 0.57659*scaled_AA0
		- 2.00642*scaled_AA1
		- 0.111378*scaled_AA2
		- 0.703025*scaled_AA3
		- 1.22214*scaled_AA4
		- 1.55063*scaled_AA5
		- 1.9258*scaled_AA6
		- 0.268664*scaled_AA7
		+ 1.38893*scaled_AA8
		+ 0.989087*scaled_AA9
		- 0.0509312*scaled_AA10
		- 0.264297*scaled_AA11
		- 0.230456*scaled_AA12
		+ 1.41108*scaled_AA13
		- 0.682601*scaled_AA14
		+ 1.92305*scaled_AA15
		- 0.58933*scaled_AA16
		+ 0.671691*scaled_AA17
		+ 0.109772*scaled_AA18
		+ 0.0841118*scaled_AA19
		- 0.535571*scaled_AA20
		+ 0.430213*scaled_AA21
		+ 0.272723*scaled_AA22
		+ 1.55321*scaled_AA23
		- 1.27824*scaled_AA24
		+ 0.198906*scaled_AA25
		+ 0.147194*scaled_AA26
		+ 0.932138*scaled_AA27
		+ 1.02706*scaled_AA28
		- 0.0951503*scaled_AA29
		+ 0.0772982*scaled_AA30
		- 1.25265*scaled_AA31);
	double y_1_18 = tanh(-0.296138
		+ 0.354094*scaled_AA0
		+ 0.719297*scaled_AA1
		- 1.42877*scaled_AA2
		+ 0.836894*scaled_AA3
		+ 0.758008*scaled_AA4
		- 1.84227*scaled_AA5
		+ 2.21294*scaled_AA6
		- 0.61111*scaled_AA7
		+ 0.482943*scaled_AA8
		- 1.7152*scaled_AA9
		+ 0.629847*scaled_AA10
		+ 0.744879*scaled_AA11
		- 0.217323*scaled_AA12
		- 0.865559*scaled_AA13
		+ 0.82103*scaled_AA14
		+ 0.685779*scaled_AA15
		- 0.358319*scaled_AA16
		+ 0.53872*scaled_AA17
		+ 1.0494*scaled_AA18
		+ 1.00117*scaled_AA19
		- 1.02263*scaled_AA20
		- 0.0607694*scaled_AA21
		+ 0.960108*scaled_AA22
		+ 2.00771*scaled_AA23
		- 1.41976*scaled_AA24
		- 0.556189*scaled_AA25
		+ 2.69764*scaled_AA26
		- 0.338427*scaled_AA27
		- 1.58599*scaled_AA28
		- 0.792303*scaled_AA29
		+ 0.290763*scaled_AA30
		- 0.189699*scaled_AA31);
	double y_1_19 = tanh(1.56874
		+ 0.0524635*scaled_AA0
		- 1.16941*scaled_AA1
		+ 0.592956*scaled_AA2
		+ 0.169462*scaled_AA3
		- 0.985642*scaled_AA4
		- 0.39375*scaled_AA5
		- 0.134438*scaled_AA6
		- 1.20469*scaled_AA7
		- 0.0484668*scaled_AA8
		+ 1.72952*scaled_AA9
		+ 0.44884*scaled_AA10
		+ 1.41396*scaled_AA11
		- 1.26035*scaled_AA12
		- 1.90598*scaled_AA13
		+ 1.11453*scaled_AA14
		+ 1.09465*scaled_AA15
		+ 1.49699*scaled_AA16
		- 1.68353*scaled_AA17
		- 1.89484*scaled_AA18
		- 1.09866*scaled_AA19
		- 1.53365*scaled_AA20
		- 0.677096*scaled_AA21
		+ 2.34367*scaled_AA22
		+ 2.19387*scaled_AA23
		- 0.34894*scaled_AA24
		+ 0.261921*scaled_AA25
		- 1.22277*scaled_AA26
		+ 1.68111*scaled_AA27
		- 2.02455*scaled_AA28
		+ 1.87061*scaled_AA29
		- 2.05997*scaled_AA30
		+ 0.20444*scaled_AA31);
	double y_1_20 = tanh(-0.614755
		+ 0.602754*scaled_AA0
		+ 1.41465*scaled_AA1
		+ 0.128908*scaled_AA2
		+ 0.189378*scaled_AA3
		- 0.426494*scaled_AA4
		- 0.28037*scaled_AA5
		+ 3.0255*scaled_AA6
		- 0.0913488*scaled_AA7
		- 0.430412*scaled_AA8
		- 0.72015*scaled_AA9
		- 1.67095*scaled_AA10
		- 1.07154*scaled_AA11
		- 1.2828*scaled_AA12
		+ 0.264823*scaled_AA13
		- 0.420374*scaled_AA14
		+ 1.05549*scaled_AA15
		+ 0.32812*scaled_AA16
		- 1.47345*scaled_AA17
		- 0.563366*scaled_AA18
		+ 1.01724*scaled_AA19
		- 0.0533428*scaled_AA20
		+ 1.4343*scaled_AA21
		- 0.403311*scaled_AA22
		- 2.48888*scaled_AA23
		+ 1.64254*scaled_AA24
		+ 2.18414*scaled_AA25
		+ 0.106234*scaled_AA26
		- 1.03562*scaled_AA27
		- 0.508683*scaled_AA28
		+ 0.270999*scaled_AA29
		- 1.03987*scaled_AA30
		- 1.20837*scaled_AA31);
	double y_1_21 = tanh(0.457027
		- 0.882054*scaled_AA0
		- 0.208906*scaled_AA1
		- 0.509259*scaled_AA2
		+ 1.73342*scaled_AA3
		+ 1.44033*scaled_AA4
		+ 2.75953*scaled_AA5
		- 0.67234*scaled_AA6
		+ 2.59642*scaled_AA7
		- 0.705493*scaled_AA8
		- 0.68462*scaled_AA9
		+ 0.682489*scaled_AA10
		- 0.782133*scaled_AA11
		+ 1.25906*scaled_AA12
		+ 1.17072*scaled_AA13
		+ 0.52174*scaled_AA14
		- 0.437364*scaled_AA15
		- 1.05634*scaled_AA16
		- 1.2292*scaled_AA17
		+ 0.495109*scaled_AA18
		- 0.360922*scaled_AA19
		+ 1.41576*scaled_AA20
		- 0.754064*scaled_AA21
		+ 0.319299*scaled_AA22
		- 0.792612*scaled_AA23
		+ 0.150099*scaled_AA24
		- 0.142619*scaled_AA25
		+ 0.157732*scaled_AA26
		+ 1.26102*scaled_AA27
		+ 0.0135477*scaled_AA28
		- 1.65797*scaled_AA29
		+ 1.25397*scaled_AA30
		+ 0.348309*scaled_AA31);
	double y_1_22 = tanh(-2.11433
		- 1.28431*scaled_AA0
		+ 2.11755*scaled_AA1
		- 0.844341*scaled_AA2
		- 1.27394*scaled_AA3
		+ 0.658054*scaled_AA4
		+ 1.89583*scaled_AA5
		- 0.502685*scaled_AA6
		+ 2.30804*scaled_AA7
		- 1.07306*scaled_AA8
		+ 0.442547*scaled_AA9
		- 0.587118*scaled_AA10
		- 0.57992*scaled_AA11
		- 0.97638*scaled_AA12
		- 0.489346*scaled_AA13
		- 2.15358*scaled_AA14
		- 0.239364*scaled_AA15
		+ 0.152437*scaled_AA16
		- 0.7131*scaled_AA17
		- 0.168149*scaled_AA18
		- 1.46776*scaled_AA19
		+ 1.24265*scaled_AA20
		- 0.974301*scaled_AA21
		- 3.13617*scaled_AA22
		- 1.05536*scaled_AA23
		+ 0.727415*scaled_AA24
		- 2.25588*scaled_AA25
		- 0.733387*scaled_AA26
		- 1.42773*scaled_AA27
		+ 0.732385*scaled_AA28
		- 0.187058*scaled_AA29
		- 0.824322*scaled_AA30
		+ 0.100755*scaled_AA31);
	double y_1_23 = tanh(1.63405
		- 0.992335*scaled_AA0
		+ 0.82463*scaled_AA1
		+ 2.06514*scaled_AA2
		- 0.762521*scaled_AA3
		- 0.022265*scaled_AA4
		+ 0.86269*scaled_AA5
		+ 0.434599*scaled_AA6
		+ 0.0923638*scaled_AA7
		- 0.360329*scaled_AA8
		+ 3.78934*scaled_AA9
		+ 0.0095005*scaled_AA10
		+ 0.672773*scaled_AA11
		- 1.31398*scaled_AA12
		- 0.901679*scaled_AA13
		- 0.546385*scaled_AA14
		+ 1.13046*scaled_AA15
		- 2.06428*scaled_AA16
		+ 0.775699*scaled_AA17
		+ 2.17871*scaled_AA18
		+ 1.39633*scaled_AA19
		+ 0.912038*scaled_AA20
		- 1.90096*scaled_AA21
		+ 0.812581*scaled_AA22
		- 1.96697*scaled_AA23
		+ 1.18118*scaled_AA24
		- 1.15739*scaled_AA25
		- 1.1759*scaled_AA26
		+ 1.50715*scaled_AA27
		- 0.146875*scaled_AA28
		+ 1.25573*scaled_AA29
		+ 0.266416*scaled_AA30
		+ 3.01748*scaled_AA31);
	double y_1_24 = tanh(1.48182
		+ 0.495248*scaled_AA0
		+ 1.10944*scaled_AA1
		- 0.320625*scaled_AA2
		- 1.61544*scaled_AA3
		+ 2.73073*scaled_AA4
		- 0.136102*scaled_AA5
		- 1.27566*scaled_AA6
		- 0.263333*scaled_AA7
		- 0.564363*scaled_AA8
		+ 0.127636*scaled_AA9
		+ 1.44629*scaled_AA10
		+ 0.825178*scaled_AA11
		+ 1.95175*scaled_AA12
		- 1.36052*scaled_AA13
		+ 0.68083*scaled_AA14
		+ 0.0713077*scaled_AA15
		- 0.911343*scaled_AA16
		+ 1.14754*scaled_AA17
		- 0.841876*scaled_AA18
		+ 1.23228*scaled_AA19
		- 0.178404*scaled_AA20
		- 0.0850459*scaled_AA21
		- 0.167296*scaled_AA22
		- 1.23871*scaled_AA23
		- 1.9737*scaled_AA24
		+ 0.377178*scaled_AA25
		+ 0.124122*scaled_AA26
		- 0.792285*scaled_AA27
		- 0.764675*scaled_AA28
		+ 0.923057*scaled_AA29
		+ 0.0839092*scaled_AA30
		- 0.185917*scaled_AA31);
	double y_1_25 = tanh(-1.72355
		+ 0.868459*scaled_AA0
		- 0.600455*scaled_AA1
		- 0.259065*scaled_AA2
		- 0.309944*scaled_AA3
		+ 0.200663*scaled_AA4
		+ 0.368486*scaled_AA5
		+ 0.412707*scaled_AA6
		- 1.6817*scaled_AA7
		- 0.380711*scaled_AA8
		- 0.573961*scaled_AA9
		+ 1.14258*scaled_AA10
		- 1.15699*scaled_AA11
		+ 1.28031*scaled_AA12
		+ 1.45962*scaled_AA13
		- 0.203784*scaled_AA14
		+ 0.0176344*scaled_AA15
		+ 1.03629*scaled_AA16
		- 0.274199*scaled_AA17
		- 0.842236*scaled_AA18
		- 0.965916*scaled_AA19
		+ 0.573961*scaled_AA20
		- 1.47132*scaled_AA21
		+ 0.132235*scaled_AA22
		- 0.531581*scaled_AA23
		+ 0.432787*scaled_AA24
		- 2.14609*scaled_AA25
		- 0.775805*scaled_AA26
		- 0.795462*scaled_AA27
		- 1.17145*scaled_AA28
		+ 0.293289*scaled_AA29
		+ 0.153667*scaled_AA30
		+ 0.248337*scaled_AA31);
	double y_1_26 = tanh(2.28
		+ 1.72972*scaled_AA0
		+ 0.707177*scaled_AA1
		+ 0.463595*scaled_AA2
		+ 0.896424*scaled_AA3
		+ 3.08076*scaled_AA4
		- 0.529889*scaled_AA5
		- 0.539022*scaled_AA6
		- 0.337041*scaled_AA7
		- 0.523583*scaled_AA8
		- 1.10451*scaled_AA9
		+ 0.862394*scaled_AA10
		+ 0.322061*scaled_AA11
		- 0.160353*scaled_AA12
		+ 0.122138*scaled_AA13
		+ 0.727626*scaled_AA14
		- 1.879*scaled_AA15
		- 2.06941*scaled_AA16
		+ 0.2338*scaled_AA17
		- 0.380944*scaled_AA18
		- 0.819091*scaled_AA19
		+ 1.43956*scaled_AA20
		+ 0.451204*scaled_AA21
		+ 0.8626*scaled_AA22
		- 0.246136*scaled_AA23
		- 0.81436*scaled_AA24
		- 2.20147*scaled_AA25
		+ 3.47853*scaled_AA26
		- 0.827105*scaled_AA27
		- 0.14487*scaled_AA28
		- 1.19907*scaled_AA29
		- 0.580629*scaled_AA30
		+ 0.657691*scaled_AA31);
	double y_1_27 = tanh(0.964948
		+ 1.37341*scaled_AA0
		- 0.952507*scaled_AA1
		- 1.94333*scaled_AA2
		+ 0.103642*scaled_AA3
		- 0.288942*scaled_AA4
		- 0.0893883*scaled_AA5
		- 1.7792*scaled_AA6
		- 0.556965*scaled_AA7
		- 1.61349*scaled_AA8
		- 1.5935*scaled_AA9
		+ 1.65298*scaled_AA10
		- 0.975349*scaled_AA11
		+ 1.35234*scaled_AA12
		- 4.01453*scaled_AA13
		+ 1.22782*scaled_AA14
		+ 1.07971*scaled_AA15
		- 0.658546*scaled_AA16
		- 0.556035*scaled_AA17
		+ 0.469816*scaled_AA18
		+ 0.119253*scaled_AA19
		- 0.251838*scaled_AA20
		+ 0.381757*scaled_AA21
		+ 2.02225*scaled_AA22
		- 1.81065*scaled_AA23
		- 0.610974*scaled_AA24
		+ 0.576075*scaled_AA25
		- 0.8875*scaled_AA26
		- 2.25273*scaled_AA27
		- 1.47385*scaled_AA28
		+ 1.43251*scaled_AA29
		+ 1.20647*scaled_AA30
		- 0.930274*scaled_AA31);
	double y_1_28 = tanh(-1.54001
		- 0.382655*scaled_AA0
		- 0.806673*scaled_AA1
		+ 1.3406*scaled_AA2
		+ 0.124639*scaled_AA3
		- 0.839301*scaled_AA4
		+ 0.481139*scaled_AA5
		+ 1.31789*scaled_AA6
		+ 0.375071*scaled_AA7
		- 1.27657*scaled_AA8
		+ 1.65354*scaled_AA9
		- 0.885083*scaled_AA10
		+ 0.432173*scaled_AA11
		+ 0.0877337*scaled_AA12
		- 0.174436*scaled_AA13
		+ 0.929993*scaled_AA14
		- 2.51801*scaled_AA15
		- 0.162206*scaled_AA16
		- 0.373694*scaled_AA17
		- 0.350186*scaled_AA18
		+ 0.687881*scaled_AA19
		+ 0.0581993*scaled_AA20
		+ 0.826387*scaled_AA21
		+ 1.23491*scaled_AA22
		- 1.42138*scaled_AA23
		- 0.860981*scaled_AA24
		- 0.2219*scaled_AA25
		+ 0.239877*scaled_AA26
		- 1.55656*scaled_AA27
		+ 0.528984*scaled_AA28
		+ 0.107247*scaled_AA29
		+ 0.314603*scaled_AA30
		+ 1.32737*scaled_AA31);
	double y_1_29 = tanh(2.97466
		+ 1.27706*scaled_AA0
		+ 0.525191*scaled_AA1
		+ 0.468008*scaled_AA2
		+ 1.27363*scaled_AA3
		+ 2.03308*scaled_AA4
		+ 0.330588*scaled_AA5
		- 0.0683298*scaled_AA6
		- 0.485581*scaled_AA7
		- 0.451478*scaled_AA8
		- 0.638752*scaled_AA9
		+ 0.360334*scaled_AA10
		- 0.531782*scaled_AA11
		- 0.0438395*scaled_AA12
		+ 1.01062*scaled_AA13
		- 1.27812*scaled_AA14
		+ 1.93734*scaled_AA15
		+ 0.169833*scaled_AA16
		+ 0.825077*scaled_AA17
		+ 1.00608*scaled_AA18
		- 0.355606*scaled_AA19
		- 0.00458756*scaled_AA20
		- 0.259484*scaled_AA21
		- 0.493047*scaled_AA22
		+ 1.78477*scaled_AA23
		+ 1.24203*scaled_AA24
		- 1.15202*scaled_AA25
		+ 0.440657*scaled_AA26
		+ 0.584465*scaled_AA27
		- 1.89093*scaled_AA28
		+ 0.0566401*scaled_AA29
		- 0.448007*scaled_AA30
		+ 0.0907209*scaled_AA31);
	double y_1_30 = tanh(-1.11571
		- 0.19277*scaled_AA0
		+ 0.0240157*scaled_AA1
		- 0.542775*scaled_AA2
		+ 1.21967*scaled_AA3
		- 0.675694*scaled_AA4
		+ 1.37805*scaled_AA5
		- 0.935155*scaled_AA6
		+ 1.09017*scaled_AA7
		+ 0.632971*scaled_AA8
		- 1.18303*scaled_AA9
		+ 1.55202*scaled_AA10
		- 0.574013*scaled_AA11
		+ 0.931365*scaled_AA12
		+ 0.736799*scaled_AA13
		+ 0.0986305*scaled_AA14
		+ 0.0889212*scaled_AA15
		+ 0.304599*scaled_AA16
		- 1.4212*scaled_AA17
		- 0.230676*scaled_AA18
		- 1.50572*scaled_AA19
		+ 2.41796*scaled_AA20
		- 0.133414*scaled_AA21
		- 0.423299*scaled_AA22
		+ 0.309392*scaled_AA23
		- 1.57711*scaled_AA24
		- 1.68131*scaled_AA25
		+ 0.960832*scaled_AA26
		+ 0.879255*scaled_AA27
		- 0.235791*scaled_AA28
		- 1.99497*scaled_AA29
		- 0.0223396*scaled_AA30
		- 0.296995*scaled_AA31);
	double y_1_31 = tanh(0.52819
		+ 1.13707*scaled_AA0
		+ 1.22761*scaled_AA1
		- 1.70042*scaled_AA2
		+ 0.19669*scaled_AA3
		+ 0.239693*scaled_AA4
		- 0.23538*scaled_AA5
		+ 1.95623*scaled_AA6
		+ 2.22756*scaled_AA7
		- 0.881823*scaled_AA8
		- 0.0469446*scaled_AA9
		- 1.211*scaled_AA10
		- 0.0430677*scaled_AA11
		- 1.58974*scaled_AA12
		- 0.343793*scaled_AA13
		- 1.92868*scaled_AA14
		+ 0.75036*scaled_AA15
		- 0.540318*scaled_AA16
		+ 1.54417*scaled_AA17
		+ 0.553761*scaled_AA18
		- 0.642154*scaled_AA19
		+ 1.70283*scaled_AA20
		+ 0.568921*scaled_AA21
		+ 0.202514*scaled_AA22
		+ 1.05694*scaled_AA23
		+ 1.41329*scaled_AA24
		- 0.0871563*scaled_AA25
		- 1.25616*scaled_AA26
		- 2.50994*scaled_AA27
		+ 0.408209*scaled_AA28
		+ 0.0482232*scaled_AA29
		+ 0.862203*scaled_AA30
		- 0.516845*scaled_AA31);
	double y_1_32 = tanh(-0.547057
		+ 0.561137*scaled_AA0
		- 1.66222*scaled_AA1
		- 1.32283*scaled_AA2
		- 1.54067*scaled_AA3
		+ 1.8379*scaled_AA4
		+ 0.932973*scaled_AA5
		- 1.08425*scaled_AA6
		+ 0.670916*scaled_AA7
		+ 0.947171*scaled_AA8
		- 1.8083*scaled_AA9
		+ 0.806627*scaled_AA10
		- 1.23367*scaled_AA11
		+ 0.00245888*scaled_AA12
		+ 0.237312*scaled_AA13
		- 1.16033*scaled_AA14
		- 0.652016*scaled_AA15
		- 0.0554361*scaled_AA16
		+ 2.2955*scaled_AA17
		- 0.970359*scaled_AA18
		+ 0.852221*scaled_AA19
		+ 1.07795*scaled_AA20
		+ 0.643779*scaled_AA21
		+ 0.226204*scaled_AA22
		- 0.138028*scaled_AA23
		- 0.469189*scaled_AA24
		- 0.769774*scaled_AA25
		+ 0.371973*scaled_AA26
		+ 2.27869*scaled_AA27
		- 0.03692*scaled_AA28
		+ 1.87066*scaled_AA29
		+ 0.213476*scaled_AA30
		+ 0.843197*scaled_AA31);
	double y_1_33 = tanh(-1.09204
		+ 0.216028*scaled_AA0
		- 0.518267*scaled_AA1
		- 0.524455*scaled_AA2
		+ 0.806723*scaled_AA3
		+ 0.352117*scaled_AA4
		- 0.184052*scaled_AA5
		- 0.196242*scaled_AA6
		- 1.11692*scaled_AA7
		+ 2.28921*scaled_AA8
		+ 0.66006*scaled_AA9
		- 0.903175*scaled_AA10
		- 0.696079*scaled_AA11
		- 0.997078*scaled_AA12
		- 0.677074*scaled_AA13
		+ 0.576078*scaled_AA14
		- 0.253976*scaled_AA15
		+ 1.20739*scaled_AA16
		- 2.04749*scaled_AA17
		- 1.14649*scaled_AA18
		- 0.91077*scaled_AA19
		+ 2.23672*scaled_AA20
		+ 1.70539*scaled_AA21
		+ 0.83812*scaled_AA22
		+ 1.41521*scaled_AA23
		- 0.814198*scaled_AA24
		- 0.684468*scaled_AA25
		- 1.27223*scaled_AA26
		- 0.433311*scaled_AA27
		+ 0.879679*scaled_AA28
		- 2.61939*scaled_AA29
		+ 0.746282*scaled_AA30
		+ 0.763296*scaled_AA31);
	double y_1_34 = tanh(0.874196
		+ 2.31095*scaled_AA0
		+ 0.975569*scaled_AA1
		- 0.792628*scaled_AA2
		+ 0.640608*scaled_AA3
		+ 0.760455*scaled_AA4
		+ 1.97479*scaled_AA5
		- 1.83167*scaled_AA6
		+ 0.279057*scaled_AA7
		- 1.34529*scaled_AA8
		- 1.10246*scaled_AA9
		- 0.231642*scaled_AA10
		- 2.75802*scaled_AA11
		- 0.0765523*scaled_AA12
		+ 0.167799*scaled_AA13
		+ 0.820181*scaled_AA14
		- 1.23896*scaled_AA15
		+ 0.614203*scaled_AA16
		- 0.65988*scaled_AA17
		+ 0.575437*scaled_AA18
		- 0.422005*scaled_AA19
		- 0.417225*scaled_AA20
		+ 0.845934*scaled_AA21
		- 1.59599*scaled_AA22
		+ 0.255961*scaled_AA23
		- 0.316813*scaled_AA24
		- 2.17302*scaled_AA25
		- 0.735466*scaled_AA26
		+ 0.474959*scaled_AA27
		+ 0.298054*scaled_AA28
		+ 0.844135*scaled_AA29
		+ 0.566882*scaled_AA30
		+ 0.680496*scaled_AA31);
	double y_1_35 = tanh(-0.800849
		- 2.03709*scaled_AA0
		- 0.0152054*scaled_AA1
		- 1.33413*scaled_AA2
		+ 0.982455*scaled_AA3
		- 0.64057*scaled_AA4
		- 1.10612*scaled_AA5
		- 1.04919*scaled_AA6
		+ 0.445592*scaled_AA7
		+ 0.928482*scaled_AA8
		- 0.204387*scaled_AA9
		+ 0.501333*scaled_AA10
		+ 2.69558*scaled_AA11
		- 0.246285*scaled_AA12
		- 2.12125*scaled_AA13
		- 1.35634*scaled_AA14
		+ 1.30925*scaled_AA15
		+ 0.632278*scaled_AA16
		- 0.384445*scaled_AA17
		- 1.0699*scaled_AA18
		- 1.47697*scaled_AA19
		- 0.386243*scaled_AA20
		- 0.154902*scaled_AA21
		- 0.547502*scaled_AA22
		+ 1.71979*scaled_AA23
		+ 0.892853*scaled_AA24
		- 0.251404*scaled_AA25
		- 1.59673*scaled_AA26
		+ 0.0805834*scaled_AA27
		- 2.06357*scaled_AA28
		- 0.23307*scaled_AA29
		- 1.3777*scaled_AA30
		- 0.788977*scaled_AA31);
	double y_1_36 = tanh(-0.506956
		+ 0.840163*scaled_AA0
		+ 0.983018*scaled_AA1
		+ 1.87751*scaled_AA2
		+ 0.252509*scaled_AA3
		- 0.335696*scaled_AA4
		+ 0.0653784*scaled_AA5
		+ 2.07613*scaled_AA6
		- 0.835671*scaled_AA7
		+ 1.20226*scaled_AA8
		- 1.40638*scaled_AA9
		+ 0.564115*scaled_AA10
		- 1.12896*scaled_AA11
		- 0.970246*scaled_AA12
		+ 2.10169*scaled_AA13
		- 1.32406*scaled_AA14
		- 2.2234*scaled_AA15
		- 1.9177*scaled_AA16
		+ 0.199272*scaled_AA17
		- 0.970244*scaled_AA18
		- 2.02345*scaled_AA19
		- 1.98292*scaled_AA20
		- 0.723396*scaled_AA21
		+ 1.46314*scaled_AA22
		+ 0.0738394*scaled_AA23
		- 0.0215431*scaled_AA24
		- 0.984345*scaled_AA25
		+ 1.14082*scaled_AA26
		+ 0.54494*scaled_AA27
		- 1.09077*scaled_AA28
		+ 0.142092*scaled_AA29
		+ 0.712451*scaled_AA30
		+ 2.25681*scaled_AA31);
	double y_1_37 = tanh(-1.18125
		- 1.20979*scaled_AA0
		- 1.99828*scaled_AA1
		- 1.12871*scaled_AA2
		+ 0.363756*scaled_AA3
		+ 1.01283*scaled_AA4
		+ 2.55754*scaled_AA5
		- 0.32782*scaled_AA6
		+ 1.56451*scaled_AA7
		- 1.1533*scaled_AA8
		- 0.751063*scaled_AA9
		+ 0.50977*scaled_AA10
		- 0.160936*scaled_AA11
		+ 0.0832993*scaled_AA12
		+ 0.353606*scaled_AA13
		- 1.19262*scaled_AA14
		- 0.0388728*scaled_AA15
		- 2.05076*scaled_AA16
		- 0.355603*scaled_AA17
		- 1.09303*scaled_AA18
		+ 1.0437*scaled_AA19
		- 1.42979*scaled_AA20
		- 0.880789*scaled_AA21
		- 1.86279*scaled_AA22
		+ 0.866668*scaled_AA23
		+ 1.22257*scaled_AA24
		+ 0.812896*scaled_AA25
		- 0.938532*scaled_AA26
		+ 0.201259*scaled_AA27
		- 0.111514*scaled_AA28
		- 0.340633*scaled_AA29
		+ 0.968314*scaled_AA30
		+ 0.244209*scaled_AA31);
	double y_1_38 = tanh(-0.68556
		+ 1.58326*scaled_AA0
		- 0.164205*scaled_AA1
		+ 0.659611*scaled_AA2
		- 0.455668*scaled_AA3
		+ 0.437157*scaled_AA4
		+ 1.90882*scaled_AA5
		+ 0.855802*scaled_AA6
		+ 0.597103*scaled_AA7
		+ 0.635014*scaled_AA8
		- 0.0287655*scaled_AA9
		- 1.03308*scaled_AA10
		- 0.0888507*scaled_AA11
		+ 0.277714*scaled_AA12
		+ 0.0182516*scaled_AA13
		- 0.134373*scaled_AA14
		+ 1.05456*scaled_AA15
		- 1.05389*scaled_AA16
		+ 1.07757*scaled_AA17
		+ 0.510181*scaled_AA18
		+ 0.284278*scaled_AA19
		- 0.461317*scaled_AA20
		+ 0.0572229*scaled_AA21
		+ 1.06021*scaled_AA22
		+ 1.05811*scaled_AA23
		+ 1.03325*scaled_AA24
		+ 0.936629*scaled_AA25
		- 0.0246648*scaled_AA26
		+ 0.335271*scaled_AA27
		+ 0.678075*scaled_AA28
		+ 0.0742623*scaled_AA29
		+ 1.19527*scaled_AA30
		+ 0.133649*scaled_AA31);
	double y_1_39 = tanh(-1.03814
		+ 1.57859*scaled_AA0
		- 0.936591*scaled_AA1
		- 0.770083*scaled_AA2
		+ 0.675991*scaled_AA3
		+ 2.02355*scaled_AA4
		+ 0.555844*scaled_AA5
		+ 0.361074*scaled_AA6
		+ 1.87489*scaled_AA7
		+ 1.06119*scaled_AA8
		+ 2.6129*scaled_AA9
		- 2.40616*scaled_AA10
		- 1.05911*scaled_AA11
		+ 0.387587*scaled_AA12
		- 0.176345*scaled_AA13
		+ 0.141653*scaled_AA14
		+ 0.551876*scaled_AA15
		+ 1.10966*scaled_AA16
		- 0.126615*scaled_AA17
		- 2.19842*scaled_AA18
		- 0.587398*scaled_AA19
		- 0.0305814*scaled_AA20
		- 2.12018*scaled_AA21
		- 1.98458*scaled_AA22
		+ 0.697893*scaled_AA23
		+ 0.136541*scaled_AA24
		- 1.94737*scaled_AA25
		- 1.23303*scaled_AA26
		+ 1.4449*scaled_AA27
		- 0.316712*scaled_AA28
		+ 0.424226*scaled_AA29
		- 2.04826*scaled_AA30
		- 0.0855144*scaled_AA31);
	double y_1_40 = tanh(-1.27876
		- 1.08978*scaled_AA0
		- 1.44663*scaled_AA1
		+ 1.49972*scaled_AA2
		+ 0.714571*scaled_AA3
		- 2.78323*scaled_AA4
		+ 0.218161*scaled_AA5
		+ 1.7546*scaled_AA6
		+ 1.77051*scaled_AA7
		- 1.111*scaled_AA8
		- 1.17192*scaled_AA9
		+ 2.28437*scaled_AA10
		- 0.671376*scaled_AA11
		+ 0.930215*scaled_AA12
		- 0.932835*scaled_AA13
		- 1.3198*scaled_AA14
		+ 0.0966387*scaled_AA15
		- 0.463986*scaled_AA16
		- 0.161386*scaled_AA17
		- 0.711096*scaled_AA18
		+ 0.780809*scaled_AA19
		- 0.0878112*scaled_AA20
		+ 0.121616*scaled_AA21
		- 0.889942*scaled_AA22
		+ 0.312522*scaled_AA23
		+ 0.904255*scaled_AA24
		+ 0.791388*scaled_AA25
		- 1.51576*scaled_AA26
		- 0.590789*scaled_AA27
		+ 0.869867*scaled_AA28
		+ 1.53866*scaled_AA29
		+ 0.463832*scaled_AA30
		- 0.0405398*scaled_AA31);
	double scaled_D_16_17 = (-0.101198
		- 0.186028*y_1_1
		- 0.161543*y_1_2
		+ 0.14867*y_1_3
		+ 0.186105*y_1_4
		+ 0.178279*y_1_5
		+ 0.183183*y_1_6
		- 0.173076*y_1_7
		+ 0.197778*y_1_8
		+ 0.184199*y_1_9
		- 0.138135*y_1_10
		+ 1.27824*y_1_11
		+ 0.18822*y_1_12
		+ 0.17363*y_1_13
		- 0.132876*y_1_14
		+ 0.242522*y_1_15
		+ 0.191448*y_1_16
		+ 0.237119*y_1_17
		+ 0.164116*y_1_18
		- 0.171682*y_1_19
		+ 0.143737*y_1_20
		+ 0.221043*y_1_21
		+ 0.151261*y_1_22
		+ 0.14761*y_1_23
		+ 0.150632*y_1_24
		+ 0.200938*y_1_25
		+ 0.155015*y_1_26
		- 0.158809*y_1_27
		+ 0.21291*y_1_28
		+ 0.194386*y_1_29
		- 0.181106*y_1_30
		- 0.154366*y_1_31
		+ 0.175486*y_1_32
		+ 0.153863*y_1_33
		- 0.161259*y_1_34
		+ 0.187454*y_1_35
		- 0.153313*y_1_36
		- 0.16556*y_1_37
		- 1.36196*y_1_38
		- 0.168659*y_1_39
		+ 0.174411*y_1_40);
	return (0.5*(scaled_D_16_17 + 1.0)*(34.12 - 3.88) + 3.88);
}