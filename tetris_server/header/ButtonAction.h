#pragma once
class ButtonAction {
public:
	void virtual action() { return; };
};

class DefaultButtonAction : public ButtonAction {
public:
	void action() override {
		cout << "button click!";
	}
};