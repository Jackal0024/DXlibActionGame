#pragma once


class IField
{
public:
	virtual ~IField() {}
	virtual bool Collision() const = 0;
};
