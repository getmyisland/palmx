#pragma once

#include "../MessageSystem/MessageSystemNode.h"

class RenderSystem : public MessageSystemNode
{
public:
	// Constructor with MessageSystemNode
	RenderSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	// Destructor
	~RenderSystem() {};

private:
	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};