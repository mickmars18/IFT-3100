#pragma once
#include "../Domain/Object.h"
#include "../Helper/Log.h"
#include <stack>
#include <utility>
#include "../Tools/InputController.h"

using namespace std;

class UndoRedo {
public:
	void action(std::vector<Object*> activeObjects);
	void undo();
	void redo();
	void keyReleased(int key);
private:
	stack<vector<pair<Object*, Transform>>> m_undoStack;
	stack<vector<pair<Object*, Transform>>> m_redoStack;
};