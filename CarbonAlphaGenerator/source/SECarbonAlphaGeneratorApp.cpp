#include "SECarbonAlphaGeneratorApp.hpp"
#include "SECarbonAlphaGeneratorAppGUI.hpp"
#include "SAMSON.hpp"
#include "SBAtom.hpp"
#include "SBBond.hpp"
#include "SBStructuralModel.hpp"
#include "SBRandom.hpp"
#include "SBResidue.hpp"
#include "SBMStructuralModelNodeBackbone.hpp"

SECarbonAlphaGeneratorApp::SECarbonAlphaGeneratorApp() {

	setGUI(new SECarbonAlphaGeneratorAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SECarbonAlphaGeneratorApp::~SECarbonAlphaGeneratorApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SECarbonAlphaGeneratorAppGUI* SECarbonAlphaGeneratorApp::getGUI() const { return static_cast<SECarbonAlphaGeneratorAppGUI*>(SBDApp::getGUI()); }

void SECarbonAlphaGeneratorApp::generate(QString chain){

	int numberOfCarbons = chain.length();

	SBStructuralModel* model = new SBStructuralModel();
	model->setName("Alpha carbon chain");

	SBAtom** atomArray = new SBAtom*[numberOfCarbons];
	SBBond** bondArray = new SBBond*[numberOfCarbons - 1];

	static SBRandom r;
	double x = - numberOfCarbons;
	double y = - numberOfCarbons;
	double z = - numberOfCarbons;
	for (unsigned int i = 0; i < numberOfCarbons; i++) {
		x = x + 1+2*r.randDouble1();
		y = y + 1+2*r.randDouble1();
		z = z + 1+2*r.randDouble1();
		atomArray[i] = new SBAtom(SBElement::Carbon, SBPosition3(SBQuantity::angstrom(x), SBQuantity::angstrom(y), SBQuantity::angstrom(z)));
		atomArray[i]->setName("CA");

		SBResidue* newResidue = new SBResidue();
		newResidue->setName("A");
		newResidue->setResidueType(SBResidue::ALA);
		SBMStructuralModelNodeBackbone* newBackbone = new SBMStructuralModelNodeBackbone();
		newResidue->addChild(newBackbone);
		newBackbone->addChild(atomArray[i]);

		model->getStructuralRoot()->addChild(newResidue);

	}

	for (unsigned int i = 1; i < numberOfCarbons; i++) {

		bondArray[i - 1] = new SBBond(atomArray[i - 1], atomArray[i], SBQuantity::dimensionless(1.0));
		model->getStructuralRoot()->addChild(bondArray[i - 1]);

	}

	delete[] atomArray;
	delete[] bondArray;

	SAMSON::beginHolding("Add alpha carbon chain");
	model->create();
	SAMSON::getActiveLayer()->addChild(model);
	SAMSON::endHolding();
}