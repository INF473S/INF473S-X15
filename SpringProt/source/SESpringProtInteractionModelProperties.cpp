#include "SESpringProtInteractionModelProperties.hpp"
#include "SESpringProtInteractionModel.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SESpringProtInteractionModelProperties::SESpringProtInteractionModelProperties() {

	interactionModel = 0;
	ui.setupUi( this );
	observer = new Observer(this);

}

SESpringProtInteractionModelProperties::~SESpringProtInteractionModelProperties() {

	if (!interactionModel.isValid()) return;

	interactionModel->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SESpringProtInteractionModelProperties::Observer::onBaseEvent));
	interactionModel->disconnectInteractionSignalFromSlot(observer(), SB_SLOT(&SESpringProtInteractionModelProperties::Observer::onInteractionEvent));

}

void SESpringProtInteractionModelProperties::loadSettings( SBGSettings *settings ) {

	if ( settings == 0 ) return;
	
	// SAMSON Element generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

void SESpringProtInteractionModelProperties::saveSettings( SBGSettings *settings ) {

	if ( settings == 0 ) return;

	// SAMSON Element generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

SBCContainerUUID SESpringProtInteractionModelProperties::getUUID() const { return SBCContainerUUID( "E061A253-E207-BD96-A1FF-9341B0024A38" );}

QPixmap SESpringProtInteractionModelProperties::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your interaction model.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/Icons/SESpringProtInteractionModelPropertiesIcon.png"));

}

QString SESpringProtInteractionModelProperties::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your interaction model inside SAMSON

	return "SESpringProtInteractionModel properties window"; 

}

int SESpringProtInteractionModelProperties::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings if you want more options (see the documentation of SBGWindow)
	
	return (SBGWindow::Lockable);

}

bool SESpringProtInteractionModelProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode* node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SESpringProtInteractionModel") && SBNode::GetElement() == std::string("SESpringProt") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		interactionModel = static_cast<SESpringProtInteractionModel*>((nodeIndexer)[0]);
		interactionModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SESpringProtInteractionModelProperties::Observer::onBaseEvent));
		interactionModel->connectInteractionSignalToSlot(observer(), SB_SLOT(&SESpringProtInteractionModelProperties::Observer::onInteractionEvent));

		updateEnergies();

		return true;

	}

	return false;

}

bool SESpringProtInteractionModelProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SESpringProtInteractionModel") return false;
	if (node->getProxy()->getElement() != "SESpringProt") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	interactionModel = static_cast<SESpringProtInteractionModel*>(node);
	interactionModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SESpringProtInteractionModelProperties::Observer::onBaseEvent));
	interactionModel->connectInteractionSignalToSlot(observer(), SB_SLOT(&SESpringProtInteractionModelProperties::Observer::onInteractionEvent));

	updateEnergies();

	return true;

}

void SESpringProtInteractionModelProperties::updateEnergies() {

	ui.labelTotalEnergy->setText(QString(tr("Total energy: ")) + QString::fromStdString(SBQuantity::eV(interactionModel->getEnergy()).toStdString()));

}

SESpringProtInteractionModelProperties::Observer::Observer(SESpringProtInteractionModelProperties* properties) { this->properties = properties; }
SESpringProtInteractionModelProperties::Observer::~Observer() {}

void SESpringProtInteractionModelProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();

}

void SESpringProtInteractionModelProperties::Observer::onInteractionEvent(SBInteractionEvent* interactionEvent) {

	if (interactionEvent->getType() == SBInteractionEvent::InteractionModelChanged) properties->updateEnergies();

}
