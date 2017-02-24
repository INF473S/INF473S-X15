#include "SEProteinConfigStatsApp.hpp"
#include "SEProteinConfigStatsAppGUI.hpp"
#include "SBNodeIndexer.hpp"
#include "SAMSON.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "SBResidue.hpp"
#include "SBBackbone.hpp"

SEProteinConfigStatsApp::SEProteinConfigStatsApp() {

	setGUI(new SEProteinConfigStatsAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEProteinConfigStatsApp::~SEProteinConfigStatsApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEProteinConfigStatsAppGUI* SEProteinConfigStatsApp::getGUI() const { return static_cast<SEProteinConfigStatsAppGUI*>(SBDApp::getGUI()); }

void SEProteinConfigStatsApp::analyse(int numberOfResidues, int step, std::string wpath){

	SBNodeIndexer nodeIndexer;
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Residue));

	for (int s = 1; s < step + 1; s++){

		for (int offset = 0; offset < nodeIndexer.size() - numberOfResidues*s; offset++){

			std::string n = (wpath + "\\step" + QString::number(s).toStdString() + "_offset" + QString::number(offset).toStdString() + ".txt");
			ofstream fichier(n, ios::out | ios::trunc);

			fichier << "step " << s << endl;
			fichier << "offset " << offset << endl;

			for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s){
				fichier << static_cast<SBResidue*>(nodeIndexer[A1])->getResidueType() << " ";
			}

			fichier << endl; 

			for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s){
				SBAtom* carb1 = static_cast<SBResidue*>(nodeIndexer[A1])->getBackbone()->getAlphaCarbon();

				SBPosition3 pos1 = carb1->getPosition();

				for (int A2 = A1 + s; A2 < offset + numberOfResidues*s; A2 = A2 + s){
					SBAtom* carb2 = static_cast<SBResidue*>(nodeIndexer[A2])->getBackbone()->getAlphaCarbon();

					SBPosition3 pos2 = carb2->getPosition();

					SBQuantity::angstrom distance = (pos1 - pos2).norm();
					fichier << distance.getValue() << " ";
				}
				fichier << endl;
			}
			fichier.close();
		}

	}

	QString title = "Information";
	QString text = "Computation finished";
	SAMSON::informUser( title , text);
}