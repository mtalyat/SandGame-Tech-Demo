#ifndef ELEMENT_H
#define ELEMENT_H

#include "Object.h"
#include "Matrix.h"
#include "Time.h"
#include "Random.h"
#include "Temperature.h"

class Element :
	public Object
{
public:
	enum class Type
	{
		Unknown = 0,
		Gas = 1,
		Liquid = 2,
		Solid = 3
	};

	enum class SubType
	{
		Gas,
		Vapor,
		Liquid,
		Powder,
		Particle,
		Solid,
		Conductor
	};

	enum class ID
	{
		Sand = 0,
		Water = 1,
		Bedrock = 2,
		Wood = 3,
		Stone = 4,
		Fire = 5,
		Flame = 6,
		Ash = 7,
		Smoke = 8,
		Molten = 9,
		Steam = 10,
		Oil = 11,
		Glass = 12,
		Gold = 13,
		Ice = 14,
		Iron = 15,
		Copper = 16,
		Dirt = 17,
		Grass = 18,
		Mud = 19,
		Rock = 20,
		Spark = 21,
	};

private:
	//updated and active
	unsigned char state;

	float temperature;
	float deltaTemperature;

protected:
	signed char xVel;
	signed char yVel;

public:
	static const float BASE_TEMP;//average world temp in Kelvin, kinda
	static const int GRAVITY;//how much is gravity?

private:
	//determines what to do with the given element, returns true when a reaction happened
	bool interact(int const xOffset, int const yOffset, Matrix::UpdateData const& data);

	void trySpreadHeat(Element* const other);

protected:

	//				functionality

	//actual individual update functionality for each element
	virtual bool onUpdate(Matrix::UpdateData const &updateData) = 0;

	//determines what to do with the given element, returns true when a reaction happened
	virtual bool reactWith(Element &other, int const xOffset, int const yOffset, Matrix::UpdateData const& data) = 0;

	//check the current temperature of this element and act accordingly
	virtual bool checkTemperature(Matrix::UpdateData const& data) = 0;

	//				helper methods

	//swaps, and updates velocity to match the swap
	bool swap(int const x, int const y, int const targetX, int const targetY, Matrix& matrix);

	//attempts to swap with another element, if this element can
	bool trySwap(int const x, int const y, int const targetX, int const targetY, Matrix& matrix);

public:

	//				constructors

	Element();
	virtual ~Element() {}

	//				element data

	//the unique id number for this element
	virtual ID getID() const = 0;

	//gets the name of this element
	virtual std::string getName() const = 0;

	//gets the basic type for this element (gas, liquid, solid)
	virtual Type getType() const = 0;

	//gets the sub type for this element
	virtual SubType getSubType() const = 0;

	//gets the color as an integer in BGRA format
	virtual int getColor() const = 0;//default 0xffffffff (white)

	//how dense is this material?
	virtual float getDensity() const = 0;

	//how hot is this material (in Celcius... kinda)
	virtual float getBaseTemperature() const = 0;

	//how much will this element apply its own heat to the nearby elements?
	virtual float heatConductivity() const = 0;

	//				functionality

	void init();

	//updates this element, returns true when the element has moved
	bool update(Matrix::UpdateData const& data);

	//can this element swap with the other element?
	virtual bool canSwap(Element* const other, int const xOffset, int const yOffset) { return !other || getType() > other->getType(); }

	//				heat and temperatures

	//what is the current temperature of this element?
	float getTemperature() const { return temperature; }

	//set the temperature for this element
	void setTemperature(float const temp) { temperature = temp; }

	//apply some heat to this element
	void applyHeat(Element const &from);

	//				activation

	//sets this element to active
	void activate() { state = (state & 0b11111101) | (1 << 1); }
	//sets this element to inactive
	void deactivate() { state = (state & 0b11111101); }
	//is this element active?
	bool isActive() const { return (state >> 1) & 0b00000001; }

	//				updating

	//sets the update toggle for this element
	void setUpdateToggle(bool const u) { state = (state & 0b11111110) | (int)u; }
	//gets the update toggle state for this element
	bool getUpdateToggle() const { return state & 0b00000001; }

	//				misc

	std::string toString() const override { return getName() + "(" + std::to_string(isActive()) + ")"; }
};

#endif