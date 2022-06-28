#pragma once

#include "../MessageSystem/MessageSystemNode.h"

class RenderSystem : public MessageSystemNode
{
public:
	RenderSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	~RenderSystem() {};

private:
	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};