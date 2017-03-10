#include "SECarbonAlphaGeneratorApp.hpp"
#include "SECarbonAlphaGeneratorAppGUI.hpp"
#include "SAMSON.hpp"
#include "SBAtom.hpp"
#include "SBBond.hpp"
#include "SBStructuralModel.hpp"
#include "SBRandom.hpp"

SECarbonAlphaGeneratorApp::SECarbonAlphaGeneratorApp() {

	setGUI(new SECarbonAlphaGeneratorAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SECarbonAlphaGeneratorApp::~SECarbonAlphaGeneratorApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SECarbonAlphaGeneratorAppGUI* SECarbonAlphaGeneratorApp::getGUI() const { return static_cast<SECarbonAlphaGeneratorAppGUI*>(SBDApp::getGUI()); }

void SECarbonAlphaGeneratorApp::generate(int numberOfCarbons){

	SBStructuralModel* model = new SBStructuralModel();
	model->setName("Alpha carbon chain");

	unsigned int numberOfAlphaCarbons = numberOfCarbons;
	SBAtom** atomArray = new SBAtom*[numberOfAlphaCarbons];
	SBBond** bondArray = new SBBond*[numberOfAlphaCarbons - 1];

	static SBRandom r;
	double x = 0;
	double y = 0;
	double z = 0;
	for (unsigned int i = 0; i < numberOfAlphaCarbons; i++) {
		x = x + 1+2*r.randDouble1();
		y = y + 1+2*r.randDouble1();
		z = z + 1+2*r.randDouble1();
		atomArray[i] = new SBAtom(SBElement::Carbon, SBPosition3(SBQuantity::angstrom(x), SBQuantity::angstrom(y), SBQuantity::angstrom(z)));
		atomArray[i]->setName("CA");

		model->getStructuralRoot()->addChild(atomArray[i]);

	}

	for (unsigned int i = 1; i < numberOfAlphaCarbons; i++) {

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