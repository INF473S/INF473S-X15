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
		
		if (chain[i] == QChar('A')){
			newResidue->setName("A");
			newResidue->setResidueType(SBResidue::ALA);
		}

		if (chain[i] == QChar('R')){
			newResidue->setName("R");
			newResidue->setResidueType(SBResidue::ARG);
		}

		if (chain[i] == QChar('N')){
			newResidue->setName("N");
			newResidue->setResidueType(SBResidue::ASN);
		}

		if (chain[i] == QChar('D')){
			newResidue->setName("D");
			newResidue->setResidueType(SBResidue::ASP);
		}

		if (chain[i] == QChar('B')){
			newResidue->setName("B");
			newResidue->setResidueType(SBResidue::ASX);
		}

		if (chain[i] == QChar('C')){
			newResidue->setName("C");
			newResidue->setResidueType(SBResidue::CYS);
		}

		if (chain[i] == QChar('E')){
			newResidue->setName("E");
			newResidue->setResidueType(SBResidue::GLU);
		}

		if (chain[i] == QChar('Q')){
			newResidue->setName("Q");
			newResidue->setResidueType(SBResidue::GLN);
		}
		if (chain[i] == QChar('Z')){
			newResidue->setName("Z");
			newResidue->setResidueType(SBResidue::GLX);
		}

		if (chain[i] == QChar('G')){
			newResidue->setName("G");
			newResidue->setResidueType(SBResidue::GLY);
		}

		if (chain[i] == QChar('H')){
			newResidue->setName("H");
			newResidue->setResidueType(SBResidue::HIS);
		}

		if (chain[i] == QChar('I')){
			newResidue->setName("I");
			newResidue->setResidueType(SBResidue::ILE);
		}

		if (chain[i] == QChar('L')){
			newResidue->setName("L");
			newResidue->setResidueType(SBResidue::LEU);
		}

		if (chain[i] == QChar('K')){
			newResidue->setName("K");
			newResidue->setResidueType(SBResidue::LYS);
		}

		if (chain[i] == QChar('M')){
			newResidue->setName("M");
			newResidue->setResidueType(SBResidue::MET);
		}

		if (chain[i] == QChar('F')){
			newResidue->setName("F");
			newResidue->setResidueType(SBResidue::PHE);
		}
		if (chain[i] == QChar('P')){
			newResidue->setName("P");
			newResidue->setResidueType(SBResidue::PRO);
		}
		if (chain[i] == QChar('S')){
			newResidue->setName("S");
			newResidue->setResidueType(SBResidue::SER);
		}
		if (chain[i] == QChar('T')){
			newResidue->setName("T");
			newResidue->setResidueType(SBResidue::THR);
		}
		if (chain[i] == QChar('W')){
			newResidue->setName("W");
			newResidue->setResidueType(SBResidue::TRP);
		}
		if (chain[i] == QChar('Y')){
			newResidue->setName("Y");
			newResidue->setResidueType(SBResidue::TYR);
		}
		if (chain[i] == QChar('V')){
			newResidue->setName("V");
			newResidue->setResidueType(SBResidue::VAL);
		}

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