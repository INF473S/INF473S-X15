#include "SEProteinConfigStatsApp.hpp"
#include "SEProteinConfigStatsAppGUI.hpp"
#include "SBNodeIndexer.hpp"
#include "SAMSON.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "SBResidue.hpp"
#include "SBBackbone.hpp"
#include "SBDocument.hpp"
#include <qimage.h>


SEProteinConfigStatsApp::SEProteinConfigStatsApp() {

	setGUI(new SEProteinConfigStatsAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEProteinConfigStatsApp::~SEProteinConfigStatsApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEProteinConfigStatsAppGUI* SEProteinConfigStatsApp::getGUI() const { return static_cast<SEProteinConfigStatsAppGUI*>(SBDApp::getGUI()); }

void SEProteinConfigStatsApp::analyse(int numberOfResidues, int step, std::string wpath, std::string rpath){

	for (int num = 1; num < 2; num++){

		std::string proteinName = (QString::number(num).toStdString() + "AF6");
		std::string fileName = (rpath + "\\" + proteinName + ".pdb");

		// creation of a new layer

		SBLayer* newLayer = new SBDDocumentLayer();
		newLayer->create(); // on reparlera de la creation de noeuds
		// create parameters for the pdb importer

		SBList<std::string>* parameters = new SBList<std::string>;
		parameters->push_back("1"); parameters->push_back("0");
		parameters->push_back("0"); parameters->push_back("1");
		parameters->push_back("1"); parameters->push_back("0"); parameters->push_back("0");

		// import in created layer
		SAMSON::importFromFile(fileName, parameters, newLayer);

		SBNodeIndexer nodeIndexer;
		newLayer->getNodes(nodeIndexer, SBNode::IsType(SBNode::Residue));

		for (int s = 1; s < step + 1; s++){

			for (int offset = 0; offset <= nodeIndexer.size() - numberOfResidues*s; offset++){

				std::string path_chain = (wpath + "\\"+"CHAINES" + "\\" + proteinName + "_step" + QString::number(s).toStdString() + "_offset" + QString::number(offset).toStdString() + ".png");
				std::string path_dist = (wpath + "\\" + "IMAGES" + "\\" + proteinName + "_step" + QString::number(s).toStdString() + "_offset" + QString::number(offset).toStdString() + ".png");
				
				QString nom_dist = QString::fromStdString(path_dist);
				QString nom_chain = QString::fromStdString(path_chain);

				int size = numberOfResidues;
				QImage image_dist = QImage(size, size, QImage::Format_RGB32);
				QImage image_chain = QImage(size, size, QImage::Format_RGB32);

				//ofstream fichier(path_chain, ios::out | ios::trunc);
				//fichier << "protein " << proteinName << endl;
				//fichier << "step " << s << endl;
				//fichier << "offset " << offset << endl;

				//for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s){
				//	fichier << static_cast<SBResidue*>(nodeIndexer[A1])->getResidueType() << " ";
				//}

				//fichier << endl;

				int px = 0;
				for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s){
					SBAtom* carb1 = static_cast<SBResidue*>(nodeIndexer[A1])->getBackbone()->getAlphaCarbon();

					SBPosition3 pos1 = carb1->getPosition();
					int py = 0;
					for (int A2 = offset; A2 < offset + numberOfResidues*s; A2 = A2 + s){
						SBAtom* carb2 = static_cast<SBResidue*>(nodeIndexer[A2])->getBackbone()->getAlphaCarbon();

						SBPosition3 pos2 = carb2->getPosition();

						SBQuantity::angstrom distance = (pos1 - pos2).norm();
						//fichier << distance.getValue() << " ";

						int c_dist = (int)distance.getValue();
						int c_chain = (int) ((static_cast<SBResidue*>(nodeIndexer[A1])->getResidueType())*255/26);
						image_dist.setPixel(px, py, qRgb(c_dist,c_dist,c_dist));
						image_dist.setPixel(px, py, qRgb(c_chain, c_chain, c_chain));
						py++;
					}
					//fichier << endl;
					px++;
				}
				//fichier.close();
				image_dist.save(nom_dist,0,100);
				image_chain.save(nom_chain, 0, 100);
			}
		}

	}

	QString title = "Information";
	QString text = "Computation finished";
	SAMSON::informUser( title , text);

}