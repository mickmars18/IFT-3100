#include "UndoRedo.h"

void UndoRedo::action(std::vector<Object*> activeObjects) {
	vector<pair<Object*, Transform>> states;
	for (size_t i = 0; i < activeObjects.size(); i++) {
		pair<Object*, Transform> pair = std::make_pair(activeObjects[i], activeObjects[i]->getTransform());
		states.push_back(pair);
	}
	m_undoStack.push(states);
	while (!m_redoStack.empty()) {
		m_redoStack.pop();
	}
}

void UndoRedo::undo() {
	if (m_undoStack.empty())
		return;

	vector<pair<Object*, Transform>> actions = m_undoStack.top();
	m_undoStack.pop();

	vector<pair<Object*, Transform>> states;
	for (size_t i = 0; i < actions.size(); i++) {
		pair<Object*, Transform> pair = std::make_pair(actions[i].first, actions[i].first->getTransform());
		states.push_back(pair);
		actions[i].first->setTransform(actions[i].second);
	}
	m_redoStack.push(states);
}

void UndoRedo::redo() {
	if (m_redoStack.empty())
		return;

	vector<pair<Object*, Transform>> actions = m_redoStack.top();
	m_redoStack.pop();

	vector<pair<Object*, Transform>> states;
	for (size_t i = 0; i < actions.size(); i++) {
		pair<Object*, Transform> pair = std::make_pair(actions[i].first, actions[i].first->getTransform());
		states.push_back(pair);
		actions[i].first->setTransform(actions[i].second);
	}
	m_undoStack.push(states);
}

void UndoRedo::keyReleased(int key) {
	if (InputController::isKeyDown(KEY::CTRL) && key == 26) {
		undo();
	}
	else if (InputController::isKeyDown(KEY::CTRL) && key == 25) {
		redo();
	}
}

