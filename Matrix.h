#ifndef MATRIX_H
#define MATRIX_H

#include <SDL.h>
#include <vector>
#include "Object.h"
#include "Math.h"

#include <iostream>

class Element;

class Matrix :
	public Object
{
public:
	struct UpdateData
	{
		int x;
		int y;
		Matrix* const matrix;
		bool const updateToggle;

		UpdateData(Matrix* const m, bool const toggle)
			:x(0), y(0), matrix(m), updateToggle(toggle)
		{

		}
	};

private:
	struct Chunk
	{
		//hold the amount of active elements in the chunk
		unsigned char activeCount;

		Chunk()
			: activeCount(0)//, nextHeat(0.0f), nextHeatCount(0), heat(0.0f)
		{

		}

		void activate(int const amount = 1)
		{
			activeCount += amount;
		}
		void deactivate(int const amount = 1)
		{
			activeCount = std::max(0, activeCount - amount);
		}
		bool isActive() const { return activeCount > 0; }
	};

private:
	int const width;
	int const height;
	int const size;

	Element** elements;
	Chunk* chunks;

	std::vector<Element*> elementsToDestroy;

	SDL_Texture* texture;

	bool updateToggle;

private:
	int positionToChunkIndex(int const x, int const y) const;

public:
	Matrix(int const w, int const h, SDL_Renderer* renderer);
	~Matrix();

	void updateAll();

	void updateTexture();
	SDL_Texture* getTexture() const;

	bool contains(int const x, int const y) const { return x >= 0 && x < width&& y >= 0 && y < height; }

	//Element* getElement(int const index) const;
	Element* getElement(int const x, int const y) const;

	void findEmptyElement(int const xPos, int const yPos, int& targetX, int& targetY);

	bool setElement(int const x, int const y, Element* const element);

	//replaces the element at the given position with the given element
	void replaceElement(int const x, int const y, Element* const newElement, bool const destroy = true);

	//converts the element at the given position to the given element. Preserves heat
	void convertElement(int const x, int const y, Element* const newElement, bool const destroy = true);

	//void destroyElement(int const index);
	void destroyElement(int const x, int const y);
	void destroyElements(int const x, int const y, int const width);

	template <class T>
	bool trySetElement(int const x, int const y)
	{
		if (!contains(x, y))
		{
			//out of bounds
			return false;
		}

		//if there is nothing there, set it
		if (!getElement(x, y))
		{
			setElement(x, y, new T());

			return true;
		}

		return false;
	}

	template <class T>
	bool trySetElements(int const x, int const y, int const width)
	{
		//set a square of elements
		int xCorner = x - width / 2;
		int yCorner = y - width / 2;

		bool anyElementSet = false;

		for (int xx = 0; xx < width; xx++)
		{
			for (int yy = 0; yy < width; yy++)
			{
				anyElementSet = trySetElement<T>(xCorner + xx, yCorner + yy) || anyElementSet;
			}
		}

		return anyElementSet;
	}

	template<class T>
	bool trySetElements(int const x1, int const y1, int const x2, int const y2)
	{
		//if not even a line, just set the element
		if (x1 == x2 && y1 == y2)
		{
			return trySetElement<T>(x1, y2);
		}

		//https://www.tutorialspoint.com/computer_graphics/line_generation_algorithm.htm

		int dx = x2 - x1;
		int dy = y2 - y1;

		float x, y;

		int steps;

		if (abs(dx) >= abs(dy))
		{
			steps = abs(dx);
		}
		else
		{
			steps = abs(dy);
		}

		float xInc = dx / static_cast<float>(steps);
		float yInc = dy / static_cast<float>(steps);

		x = x1;
		y = y1;

		bool anyElementSet = false;

		for (int i = 0; i < steps; i++)
		{
			x += xInc;
			y += yInc;

			anyElementSet = trySetElement<T>(static_cast<int>(floor(x)), static_cast<int>(floor(y))) || anyElementSet;
		}

		return anyElementSet;
	}

	template<class T>
	bool trySetElements(int const x1, int const y1, int const x2, int const y2, int const width)
	{
		return trySetElements<T>(x2, y2, width);

		//draw a line from p1 to p2, of varying thickness

		//if x1 == x2, just move straight

		int x1Side = sign(x1 - x2);
		int y1Side = sign(y1 - y2);
		int x1Corner = x1 + width / 2 * x1Side;
		int y1Corner = y1 + width / 2 * y1Side;
		int x2Corner = x2 + width / 2 * -x1Side;
		int y2Corner = y2 + width / 2 * -y1Side;

		if (x1 == x2)
		{
			//straight up/down
		}
		else {
			//get slope
			float slope = (float)(y2 - y1) / (x2 - x1);
			float inverseSlope = -1.0f / slope;

			float inverseAngle = atan(inverseSlope);

			//y = mx + b
			//b = y - mx
			float b = y1 - slope * x1;
			float inverseB = y1 - inverseSlope * x1;

			//get offsets
			float offsetX = width / 2 * sin(M_PI / 2 - inverseAngle);
			float offsetY = width / 2 * sin(inverseAngle);

			//fill in between the two points
			if (x1 < x2)
			{

			}
		}
	}

	bool tryActivate(int const x, int const y);
	void activateSurrounding(int const x, int const y);
	void activateSurrounding(int const x, int const y, int const width);

	void swap(int const index1, int const index2);
	bool swap(int const x1, int const y1, int const x2, int const y2);

	void clear();

	int positionToIndex(int const x, int const y) const;
};

#endif
