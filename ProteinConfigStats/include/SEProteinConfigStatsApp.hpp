#pragma once 

#include "SBDApp.hpp"
#include "SEProteinConfigStatsAppGUI.hpp"


/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEProteinConfigStatsAppGUI class

class SEProteinConfigStatsApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEProteinConfigStatsApp();																													///< Constructs an app
	virtual ~SEProteinConfigStatsApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEProteinConfigStatsAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	void analyse(int numberOfResidues, int step, std::string wpath, std::string rpath);

};


SB_REGISTER_TARGET_TYPE(SEProteinConfigStatsApp, "SEProteinConfigStatsApp", "392424CC-EC4E-8D4A-9683-C562D9DD9B83");
SB_DECLARE_BASE_TYPE(SEProteinConfigStatsApp, SBDApp);
