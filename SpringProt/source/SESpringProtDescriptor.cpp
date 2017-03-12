/// \headerfile SESpringProtInteractionModelDescriptor.hpp "SESpringProtInteractionModelDescriptor.hpp"
#include "SESpringProtInteractionModelDescriptor.hpp"

/// \headerfile SESpringProtInteractionModelPropertiesDescriptor.hpp "SESpringProtInteractionModelPropertiesDescriptor.hpp"
#include "SESpringProtInteractionModelPropertiesDescriptor.hpp"



// Describe the SAMSON Element

// SAMSON Element generator pro tip: modify the information below if necessary
// (for example when a new class is added, when the version number changes, to describe categories more precisely, etc.)

SB_ELEMENT_DESCRIPTION("This app computes springs from images from ProteinConfigStats");
SB_ELEMENT_DOCUMENTATION("Resource/Documentation/doc.html");
#ifdef SB_ELEMENT_VERSION
SB_ELEMENT_VERSION("0.5.0");
#endif

#ifdef SB_ELEMENT_VERSION_NUMBER
SB_ELEMENT_VERSION_NUMBER("0.6.0");
#endif


SB_ELEMENT_CLASSES_BEGIN;

	SB_ELEMENT_CLASS(SESpringProtInteractionModel);
	SB_ELEMENT_CLASS(SESpringProtInteractionModelProperties);

SB_ELEMENT_CLASSES_END;

SB_ELEMENT_CATEGORIES_BEGIN;

	SB_ELEMENT_CATEGORY(SBClass::Category::General);

SB_ELEMENT_CATEGORIES_END;