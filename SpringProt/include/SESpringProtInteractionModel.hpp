#pragma once 

#include "SBMInteractionModelParticleSystem.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBStructuralEvent.hpp"


/// This class implements an interaction model

class SESpringProtInteractionModel : public SBMInteractionModelParticleSystem {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SESpringProtInteractionModel();																													///< Builds an interaction model					
	SESpringProtInteractionModel(SBParticleSystem* particleSystem);																					///< Builds an interaction model 
	virtual ~SESpringProtInteractionModel();																											///< Destructs the interaction model

	//@}

	/// \name Serialization
	//@{

	virtual void												serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer) const;		///< Serializes the node
	virtual void												unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer);			///< Unserializes the node

	//@}

	/// \name Topology
	//@{

	virtual	void												eraseImplementation();																///< Erases the interaction model

	//@}

	/// \name Interactions									
	//@{

	virtual void												initializeInteractions();												///< Initializes the interaction model
	virtual void												updateInteractions();													///< Updates the interaction model

	//@}

	/// \name Rendering
	//@{

	virtual void												display();																///< Displays the interaction model
	virtual void												displayForShadow();														///< Displays the interaction model for shadow purposes
	virtual void												displayForSelection();													///< Displays the interaction model for selection purposes

	virtual void												expandBounds(SBIAPosition3& bounds) const;								///< Expands the bounds to make sure the interaction model fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData);		///< To collect ambient occlusion data

	//@}

	/// \name Events
	//@{

	virtual void												onBaseEvent(SBBaseEvent* baseEvent);									///< Handles base events
	virtual void												onDynamicalEvent(SBDynamicalEvent* dynamicalEvent);						///< Handles dynamical events
	virtual void												onDocumentEvent(SBDocumentEvent* documentEvent);						///< Handles document events
	virtual void												onStructuralEvent(SBStructuralEvent* documentEvent);					///< Handles structural events

	//@}

};


SB_REGISTER_TARGET_TYPE(SESpringProtInteractionModel, "SESpringProtInteractionModel", "CC11AEB7-9F79-5A2A-1E7A-0A7437B94454");
SB_DECLARE_BASE_TYPE(SESpringProtInteractionModel, SBMInteractionModelParticleSystem);
