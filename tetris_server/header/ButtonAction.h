#pragma once
class ButtonAction {
private:
	void (*_action)();
public:
	ButtonAction() {};
	ButtonAction(void(*action)()):_action(action) {};
	ButtonAction(const ButtonAction& object) {};
	ButtonAction(const ButtonAction* object) {};
	virtual void action() { cout << "button click!"; };
	virtual ButtonAction* newObject()const {
		return new ButtonAction(this);
	}
};