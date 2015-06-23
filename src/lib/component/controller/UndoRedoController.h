#ifndef UNDO_REDO_CONTROLLER_H
#define UNDO_REDO_CONTROLLER_H

#include <deque>

#include "utility/messaging/MessageBase.h"
#include "utility/messaging/MessageListener.h"
#include "utility/messaging/type/MessageActivateEdge.h"
#include "utility/messaging/type/MessageActivateFile.h"
#include "utility/messaging/type/MessageActivateNode.h"
#include "utility/messaging/type/MessageGraphNodeBundleSplit.h"
#include "utility/messaging/type/MessageGraphNodeExpand.h"
#include "utility/messaging/type/MessageGraphNodeMove.h"
#include "utility/messaging/type/MessageLoadProject.h"
#include "utility/messaging/type/MessageLoadSource.h"
#include "utility/messaging/type/MessageRedo.h"
#include "utility/messaging/type/MessageSearch.h"
#include "utility/messaging/type/MessageUndo.h"

#include "component/controller/Controller.h"

class UndoRedoView;

class UndoRedoController
	: public Controller
	, public MessageListener<MessageActivateEdge>
	, public MessageListener<MessageActivateFile>
	, public MessageListener<MessageActivateNode>
	, public MessageListener<MessageGraphNodeBundleSplit>
	, public MessageListener<MessageGraphNodeExpand>
	, public MessageListener<MessageGraphNodeMove>
	, public MessageListener<MessageLoadProject>
	, public MessageListener<MessageLoadSource>
	, public MessageListener<MessageRedo>
	, public MessageListener<MessageSearch>
	, public MessageListener<MessageUndo>
{
public:
	UndoRedoController();
	virtual ~UndoRedoController();

	UndoRedoView* getView();

private:
	struct Command
	{
		Command(std::shared_ptr<MessageBase> message, size_t order);

		std::shared_ptr<MessageBase> message;
		size_t order;
	};

	virtual void handleMessage(MessageActivateEdge* message);
	virtual void handleMessage(MessageActivateFile* message);
	virtual void handleMessage(MessageActivateNode* message);
	virtual void handleMessage(MessageGraphNodeBundleSplit* message);
	virtual void handleMessage(MessageGraphNodeExpand* message);
	virtual void handleMessage(MessageGraphNodeMove* message);
	virtual void handleMessage(MessageLoadProject* message);
	virtual void handleMessage(MessageLoadSource* message);
	virtual void handleMessage(MessageRedo* message);
	virtual void handleMessage(MessageSearch* message);
	virtual void handleMessage(MessageUndo* message);

	void processCommand(const Command& command);
	void processNormalCommand(const Command& command);
	void processRedoCommand(const Command& command);
	void processUndoCommand(const Command& command);

	void clear();

	Command m_lastCommand;

	std::deque<Command> m_undo;
	std::deque<Command> m_redo;
};

#endif // UNDO_REDO_CONTROLLER_H
