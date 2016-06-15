#pragma once

#include"IField.h"
#include"DxLib.h"

class Field : public IField
{
public:
	Field(int modelhandle);
	bool Collision() const override;
	void Draw() const;

private:
	int mModelHandle;
};
