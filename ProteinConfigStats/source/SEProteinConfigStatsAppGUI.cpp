#include "SEProteinConfigStatsAppGUI.hpp"
#include "SEProteinConfigStatsApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"
#include <qfiledialog.h>
#include "SBAtom.hpp"
#include "SBBond.hpp"
#include "SBStructuralModel.hpp"

SEProteinConfigStatsAppGUI::SEProteinConfigStatsAppGUI(SEProteinConfigStatsApp* t) : SBGApp(t) {

	ui.setupUi(this);

}

SEProteinConfigStatsAppGUI::~SEProteinConfigStatsAppGUI() {

}

SEProteinConfigStatsApp* SEProteinConfigStatsAppGUI::getApp() const { return static_cast<SEProteinConfigStatsApp*>(SBGApp::getApp()); }

void SEProteinConfigStatsAppGUI::loadSettings(SBGSettings *settings) {

	if (settings == NULL) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	ui.spinBox_NR->setValue(settings->loadIntValue("numberOfResidues", 10));
	ui.spinBox_S->setValue(settings->loadIntValue("step", 1));
	ui.lineEdit_w->setText(settings->loadQStringValue("w_path"));
	ui.lineEdit_r->setText(settings->loadQStringValue("r_path"));
}

void SEProteinConfigStatsAppGUI::saveSettings(SBGSettings *settings) {

	if (settings == NULL) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	settings->saveValue("numberOfResidues", ui.spinBox_NR->value());
	settings->saveValue("step", ui.spinBox_S->value());
	settings->saveValue("r_path", ui.lineEdit_r->text());
	settings->saveValue("w_path", ui.lineEdit_w->text());
}

SBCContainerUUID SEProteinConfigStatsAppGUI::getUUID() const { return SBCContainerUUID("EB7333E9-4BFE-2CE1-1EFA-674BD48BFE02"); }

QPixmap SEProteinConfigStatsAppGUI::getLogo() const {

	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEProteinConfigStatsAppIcon.png"));

}

QString SEProteinConfigStatsAppGUI::getName() const {

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "SEProteinConfigStatsApp";

}

int SEProteinConfigStatsAppGUI::getFormat() const {

	// SAMSON Element generator pro tip: modify these default settings if you want more options (see the documentation of SBGWindow)

	return (SBGWindow::Savable | SBGWindow::Resizable);

}

void SEProteinConfigStatsAppGUI::onAnalyse() {
	getApp()->analyse(ui.spinBox_NR->value(), ui.spinBox_S->value(), ui.lineEdit_w->text().toStdString(), ui.lineEdit_r->text().toStdString());
}

void SEProteinConfigStatsAppGUI::on_w_Browse() {
	QString dossier = QFileDialog::getExistingDirectory(this);
	ui.lineEdit_w->setText(dossier);
}

void SEProteinConfigStatsAppGUI::on_r_Browse() {
	QString dossier = QFileDialog::getExistingDirectory(this);
	ui.lineEdit_r->setText(dossier);
}

void SEProteinConfigStatsAppGUI::onGenerateModel() {

	SBStructuralModel* model = new SBStructuralModel();
	model->setName("Alpha carbon chain");

	unsigned int numberOfAlphaCarbons = 35;
	SBAtom** atomArray = new SBAtom*[numberOfAlphaCarbons];
	SBBond** bondArray = new SBBond*[numberOfAlphaCarbons - 1];

	for (unsigned int i = 0; i < numberOfAlphaCarbons; i++) {

		atomArray[i] = new SBAtom(SBElement::Carbon, SBPosition3(SBQuantity::angstrom(3 * i), SBQuantity::angstrom::zero, SBQuantity::angstrom::zero));
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
