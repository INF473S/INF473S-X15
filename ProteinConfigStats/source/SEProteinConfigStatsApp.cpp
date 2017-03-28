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
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <iomanip>

SEProteinConfigStatsApp::SEProteinConfigStatsApp() {

	setGUI(new SEProteinConfigStatsAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEProteinConfigStatsApp::~SEProteinConfigStatsApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEProteinConfigStatsAppGUI* SEProteinConfigStatsApp::getGUI() const { return static_cast<SEProteinConfigStatsAppGUI*>(SBDApp::getGUI()); }

void SEProteinConfigStatsApp::analyse(int numberOfResidues, int step, std::string wpath, std::string rpath) {

	if (!QFileInfo(QString::fromStdString(wpath + "\\" + "CHAINES" + "\\")).exists()) QDir().mkpath(QString::fromStdString(wpath + "\\" + "CHAINES" + "\\"));
	if (!QFileInfo(QString::fromStdString(wpath + "\\" + "DISTANCES" + "\\")).exists()) QDir().mkpath(QString::fromStdString(wpath + "\\" + "DISTANCES" + "\\"));
	if (!QFileInfo(QString::fromStdString(wpath + "\\" + "DAT" + "\\")).exists()) QDir().mkpath(QString::fromStdString(wpath + "\\" + "DAT" + "\\"));

	ofstream** fileArray = new ofstream*[step];
	ofstream logFile(wpath + "\\log.txt", ios::out | ios::app);

	logFile << "Beginning at " << QDateTime::currentDateTime().toString("hh'h'mm '-' MM.dd.yyyy").toStdString() << std::endl;

	for (int s = 1; s < step + 1; s++) {

		std::string path_dat = (wpath + "\\" + "DAT" + "\\" + "Size_" + QString::number(numberOfResidues).toStdString() + "_Step_" + QString::number(s).toStdString() + "_full.dat");
		fileArray[s - 1] = new ofstream(path_dat, ios::out | ios::app);
		(*fileArray[s - 1]) << setprecision(2);

		for (int i = 0; i < numberOfResidues; i++) (*fileArray[s - 1]) << "AA" << i << " ";

		for (int i = 0; i < numberOfResidues; i++) {

			//if (i == numberOfResidues / 2) 
			
			for (int j = 0; j < numberOfResidues; j++) {

				if (j > i) (*fileArray[s - 1]) << "D-" << i << "-" << j << " ";

			}

		}

		(*fileArray[s - 1]) << std::endl;

	}

	QDir dir(QString::fromStdString(rpath));
	QFileInfoList files = dir.entryInfoList();
	foreach(QFileInfo file, files) {

		std::string proteinName = (file.fileName().split(".")[0]).toStdString();
		std::string fileName = (file.filePath()).toStdString();

		// creation of a new layer

		SBLayer* newLayer = new SBDDocumentLayer();
		newLayer->create();

		// create parameters for the pdb importer

		SBList<std::string>* parameters = new SBList<std::string>;
		parameters->push_back("1"); parameters->push_back("0");
		parameters->push_back("0"); parameters->push_back("1");
		parameters->push_back("1"); parameters->push_back("0"); parameters->push_back("0");

		// import in created layer

		SAMSON::disableHolding();
		SAMSON::importFromFile(fileName, parameters, newLayer);
		SAMSON::enableHolding();

		SBNodeIndexer nodeIndexer;
		newLayer->getNodes(nodeIndexer, SBNode::IsType(SBNode::Residue) && SBResidue::IsAminoAcid() && SBResidue::HasCompleteAminoAcidBackbone());

		if (!nodeIndexer.empty()) {

			for (int s = 1; s < step + 1; s++) {

				for (int offset = 0; offset <= (int)nodeIndexer.size() - numberOfResidues*s; offset++) {

					int size = numberOfResidues;

					//std::string path_chain = (wpath + "\\" + "CHAINES" + "\\" + proteinName + "_step_" + QString::number(s).toStdString() + "_offset_" + QString::number(offset).toStdString() + ".png");
					//QString nom_chain = QString::fromStdString(path_chain);
					//QImage image_chain = QImage(size, size, QImage::Format_RGB32);

					//std::string path_dist = (wpath + "\\" + "DISTANCES" + "\\" + proteinName + "_step_" + QString::number(s).toStdString() + "_offset_" + QString::number(offset).toStdString() + ".png");
					//QString nom_dist = QString::fromStdString(path_dist);
					//QImage image_dist = QImage(size, size, QImage::Format_RGB32);

					// check that all residues have the same parent, to avoid jumps in distances

					bool areSiblings = true;
					SBNode* parent = nodeIndexer[offset]->getParent();
					for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s) if (nodeIndexer[A1]->getParent() != parent) areSiblings = false;

					// check that all residues are in the same chain, to avoid jumps in distances

					bool sameChain = true;
#if 0
					std::string chain(static_cast<SBResidue*>(nodeIndexer[offset])->getBackbone()->getAlphaCarbon()->getChain(), static_cast<SBResidue*>(nodeIndexer[offset])->getBackbone()->getAlphaCarbon()->getChainSize());
					for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s) if (std::string(static_cast<SBResidue*>(nodeIndexer[A1])->getBackbone()->getAlphaCarbon()->getChain(), static_cast<SBResidue*>(nodeIndexer[A1])->getBackbone()->getAlphaCarbon()->getChainSize()) != chain) sameChain = false;
#endif
					// check that the difference between the residues indices correspond to what is expected

					bool distanceOK = true;
					int residueSequenceNumber = static_cast<SBResidue*>(nodeIndexer[offset])->getBackbone()->getAlphaCarbon()->getResidueSequenceNumber();
					for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s) if (static_cast<SBResidue*>(nodeIndexer[A1])->getBackbone()->getAlphaCarbon()->getResidueSequenceNumber() - residueSequenceNumber != A1 - offset) distanceOK = false;

					// save the distances

					if (areSiblings&&sameChain&&distanceOK) {

						for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s) {
							(*fileArray[s - 1]) << setfill('0') << setw(2) << static_cast<SBResidue*>(nodeIndexer[A1])->getResidueType() << " ";
						}

						(*fileArray[s - 1]) << "   ";

						int px = 0;

						for (int A1 = offset; A1 < offset + numberOfResidues*s; A1 = A1 + s) {

							SBAtom* carb1 = static_cast<SBResidue*>(nodeIndexer[A1])->getBackbone()->getAlphaCarbon();
							SBPosition3 pos1 = carb1->getPosition();

							int py = 0;

							for (int A2 = offset; A2 < offset + numberOfResidues*s; A2 = A2 + s) {

								SBAtom* carb2 = static_cast<SBResidue*>(nodeIndexer[A2])->getBackbone()->getAlphaCarbon();
								SBPosition3 pos2 = carb2->getPosition();

								SBQuantity::angstrom distance = (pos1 - pos2).norm();

								if (/*(A1 == offset + numberOfResidues / 2 * s) && */ A2 > A1) {

									// output the distance between the first and last residue

									//if (distance > SBQuantity::angstrom(27.0)) logFile << "Distance = " << distance << " for " <<
									//	"protein " << proteinName << ", between " <<
									//	"residue " << static_cast<SBResidue*>(nodeIndexer[A1])->getName() << " and " <<
									//	"residue " << static_cast<SBResidue*>(nodeIndexer[A2])->getName() <<
									//	std::endl;

									(*fileArray[s - 1]) << std::setfill('0') << std::setw(6) << std::fixed << std::setprecision(2) << distance.getValue() << " ";

								}

								//int c_dist1 = (int)distance.getValue();
								//int c_dist2 = (int)(10 * (distance.getValue() - c_dist1));
								//int c_dist3 = (int)(100 * (distance.getValue() - c_dist1 - 0.1*c_dist2));
								//image_dist.setPixel(px, py, qRgb(c_dist1, c_dist2, c_dist3));

								//int c_chain = (int)((static_cast<SBResidue*>(nodeIndexer[A1])->getResidueType()) * 255 / 26);
								//image_chain.setPixel(px, py, qRgb(c_chain, c_chain, c_chain));

								py++;

							}

							px++;

						}

						(*fileArray[s - 1]) << std::endl;

						//image_dist.save(nom_dist, 0, 100);
						//						image_chain.save(nom_chain, 0, 100);

					}

				}

			}

		}

	}

	for (int s = 1; s < step + 1; s++) {

		fileArray[s - 1]->close();

	}

	QString title = "Information";
	QString text = "Computation finished";
	SAMSON::informUser(title, text);

	logFile << "Ending at " << QDateTime::currentDateTime().toString("hh'h'mm '-' MM.dd.yyyy").toStdString() << std::endl;
	logFile.close();

}