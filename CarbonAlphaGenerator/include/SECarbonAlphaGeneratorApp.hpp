#pragma once 

#include "SBDApp.hpp"
#include "SECarbonAlphaGeneratorAppGUI.hpp"


/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SECarbonAlphaGeneratorAppGUI class

class SECarbonAlphaGeneratorApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SECarbonAlphaGeneratorApp();																													///< Constructs an app
	virtual ~SECarbonAlphaGeneratorApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SECarbonAlphaGeneratorAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	void generate(QString chain);
};


SB_REGISTER_TARGET_TYPE(SECarbonAlphaGeneratorApp, "SECarbonAlphaGeneratorApp", "5FF7F0A9-DACC-A869-B8D2-C73ABA52149B");
SB_DECLARE_BASE_TYPE(SECarbonAlphaGeneratorApp, SBDApp);
