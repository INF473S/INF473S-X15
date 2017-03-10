/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SESpringProtInteractionModel.hpp "SESpringProtInteractionModel.hpp"
#include "SESpringProtInteractionModel.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SESpringProtInteractionModel);

	SB_CLASS_TYPE(SBCClass::InteractionModelParticleSystem);
	SB_CLASS_DESCRIPTION("SESpringProtInteractionModel : SAMSON Element generator pro tip: modify me");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SESpringProtInteractionModel);
		SB_CONSTRUCTOR_1(SESpringProtInteractionModel, SBParticleSystem*);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SESpringProtInteractionModel);

