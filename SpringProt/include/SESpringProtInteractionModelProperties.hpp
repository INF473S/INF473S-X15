#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SESpringProtInteractionModelProperties.h"
#include "SBPointer.hpp"
#include "SESpringProtInteractionModel.hpp"


/// This class implements the GUI of the interaction model

// SAMSON Element generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SESpringProtInteractionModel class

class SESpringProtInteractionModelProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SESpringProtInteractionModelProperties();																								///< Constructs a widget to show the properties of the interaction model
	virtual ~SESpringProtInteractionModelProperties();																						///< Destructs the widget

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const;														///< Returns the widget UUID
	virtual QString												getName() const;														///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const;														///< Returns the widget logo
	int															getFormat() const;														///< Returns the widget format

	//@}

	///\name Settings
	//@{

	void														loadSettings(SBGSettings* settings);									///< Load GUI settings
	void														saveSettings(SBGSettings* settings);									///< Save GUI settings

	//@}

	///\name Setup
	//@{

	virtual bool												setup();																///< Initializes the properties widget
	virtual bool												setup(SBNode* node);													///< Initializes the properties widget

	//@}

	class Observer : public SBCReferenceTarget {

		Observer(SESpringProtInteractionModelProperties* properties);
		virtual ~Observer();

		friend class SESpringProtInteractionModelProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);									///< Base event management
		void														onInteractionEvent(SBInteractionEvent* interactionEvent);				///< Interaction event management

		SESpringProtInteractionModelProperties* properties;

	};

private:

	friend class SESpringProtInteractionModel;
	Ui::SESpringProtInteractionModelPropertiesClass							ui;
	SBPointer<SESpringProtInteractionModel>									interactionModel;

	void														updateEnergies();
	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SESpringProtInteractionModelProperties, "SESpringProtInteractionModelProperties", "968CC320-5296-6D51-BDC3-46E0DEDDDFAC");
