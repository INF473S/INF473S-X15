/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEProteinConfigStatsApp.hpp "SEProteinConfigStatsApp.hpp"
#include "SEProteinConfigStatsApp.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SEProteinConfigStatsApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("SEProteinConfigStatsApp : SAMSON Element generator pro tip: modify me");

#ifdef SB_CLASS_VERSION_NUMBER
	SB_CLASS_VERSION_NUMBER("1.0.0");
#endif

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEProteinConfigStatsApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEProteinConfigStatsApp);

