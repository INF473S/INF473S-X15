#include "SECarbonAlphaGeneratorAppGUI.hpp"
#include "SECarbonAlphaGeneratorApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SECarbonAlphaGeneratorAppGUI::SECarbonAlphaGeneratorAppGUI( SECarbonAlphaGeneratorApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SECarbonAlphaGeneratorAppGUI::~SECarbonAlphaGeneratorAppGUI() {

}

SECarbonAlphaGeneratorApp* SECarbonAlphaGeneratorAppGUI::getApp() const { return static_cast<SECarbonAlphaGeneratorApp*>(SBGApp::getApp()); }

void SECarbonAlphaGeneratorAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	ui.textEdit->setText(settings->loadQStringValue("chain"));

}

void SECarbonAlphaGeneratorAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	settings->saveValue("chain", ui.textEdit->toPlainText());

}

SBCContainerUUID SECarbonAlphaGeneratorAppGUI::getUUID() const { return SBCContainerUUID( "0A341852-FD73-CA6F-236A-0BE920203130" );}

QPixmap SECarbonAlphaGeneratorAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SECarbonAlphaGeneratorAppIcon.png"));

}

QString SECarbonAlphaGeneratorAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "SECarbonAlphaGeneratorApp"; 

}

int SECarbonAlphaGeneratorAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings if you want more options (see the documentation of SBGWindow)
	
	return (SBGWindow::Savable | SBGWindow::Resizable);

}

void SECarbonAlphaGeneratorAppGUI::onGenerate() {
	getApp()->generate(ui.textEdit->toPlainText());
}
