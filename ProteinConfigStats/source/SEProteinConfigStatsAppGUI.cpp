#include "SEProteinConfigStatsAppGUI.hpp"
#include "SEProteinConfigStatsApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"
#include <qfiledialog.h>

SEProteinConfigStatsAppGUI::SEProteinConfigStatsAppGUI( SEProteinConfigStatsApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SEProteinConfigStatsAppGUI::~SEProteinConfigStatsAppGUI() {

}

SEProteinConfigStatsApp* SEProteinConfigStatsAppGUI::getApp() const { return static_cast<SEProteinConfigStatsApp*>(SBGApp::getApp()); }

void SEProteinConfigStatsAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next
	
	ui.spinBox_NR->setValue(settings->loadIntValue("numberOfResidues", 10));
	ui.spinBox_S->setValue(settings->loadIntValue("step", 1));
	ui.lineEdit->setText(settings->loadQStringValue("path"));

}

void SEProteinConfigStatsAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	settings->saveValue("numberOfResidues", ui.spinBox_NR->value());
	settings->saveValue("step", ui.spinBox_S->value());
	settings->saveValue("path", ui.lineEdit->text());

}

SBCContainerUUID SEProteinConfigStatsAppGUI::getUUID() const { return SBCContainerUUID( "EB7333E9-4BFE-2CE1-1EFA-674BD48BFE02" );}

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

void SEProteinConfigStatsAppGUI::onAnalyse(){
	getApp()->analyse(ui.spinBox_NR->value(), ui.spinBox_S->value(), ui.lineEdit->text().toStdString());
}

void SEProteinConfigStatsAppGUI::onBrowse(){
	QString dossier = QFileDialog::getExistingDirectory(this);
	ui.lineEdit->setText(dossier);
}
