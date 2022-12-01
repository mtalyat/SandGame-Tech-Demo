#include "Matrix.h"
#include "Element.h"
#include <string>

#define CHUNK_SIZE 8

int Matrix::positionToChunkIndex(int const x, int const y) const
{
	return ((y / CHUNK_SIZE) * (width / CHUNK_SIZE) + (x / CHUNK_SIZE));
}

Matrix::Matrix(int const w, int const h, SDL_Renderer* renderer)
	: width(w), height(h), size(w* h), chunks(new Chunk[(w / CHUNK_SIZE) * (h / CHUNK_SIZE)]), elements(new Element* [w * h]), updateToggle(true)
{
	//initialize elements to null
	std::memset(elements, NULL, sizeof(Element*) * w * h);

	//initialize texture
	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_BGRA8888,
		SDL_TEXTUREACCESS_STREAMING,
		w, h);
}

Matrix::~Matrix()
{
	//delete chunks

	delete[] chunks;

	//delete elements
	for (int i = 0; i < size; i++)
	{
		if (elements[i])
		{
			delete elements[i];
		}
	}

	delete[] elements;

	//delete texture
	SDL_DestroyTexture(texture);
}

void Matrix::updateAll()
{
	Element* e;

	UpdateData ud(this, updateToggle);

	//delete old elements
	for (int i = static_cast<int>(elementsToDestroy.size()) - 1; i >= 0; i--)
	{
		if (elementsToDestroy.at(i))
			delete elementsToDestroy.at(i);
	}

	elementsToDestroy.clear();

	if (updateToggle)
	{
		//update all
		for (int y = height - 1; y >= 0; y--)
		{
			ud.y = y;

			for (int x = 0; x < width; x++)
			{
				ud.x = x;

				e = getElement(x, y);

				if (e)
				{
					e->update(ud);
				}
			}
		}
	}
	else
	{
		//update all
		for (int y = height - 1; y >= 0; y--)
		{
			ud.y = y;

			for (int x = width - 1; x >= 0; x--)
			{
				ud.x = x;

				e = getElement(x, y);

				if (e)
				{
					e->update(ud);
				}
			}
		}
	}

	updateToggle = !updateToggle;
}

void Matrix::updateTexture()
{
	//lock texture for updating
	int* pixels;
	int pitch;
	SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch);

	Element* e;

	for (int i = 0; i < size; i++)
	{
		e = elements[i];

		if (e)
		{
			//there is an element, color to its color
			//if (e->isActive())
			//	pixels[i] = e->getColor();
			//else
			//	pixels[i] = 0xFFFFFFFF;
			pixels[i] = e->getColor();
		}
		else
		{
			//there is no element, color black
			pixels[i] = 0;
		}
	}

	//we are done, unlock the texture
	SDL_UnlockTexture(texture);
}

SDL_Texture* Matrix::getTexture() const
{
	return texture;
}

Element* Matrix::getElement(int const x, int const y) const
{
	//bounds check
	if (!contains(x, y))
	{
		return nullptr;
	}

	return elements[positionToIndex(x, y)];
}

void Matrix::findEmptyElement(int const xPos, int const yPos, int& targetX, int& targetY)
{
	Element* thisElement = getElement(xPos, yPos);

	if (!thisElement)
	{
		//hmm.. no element?
		return;
	}

	//go in a line, stop once something is hit
	int dx = targetX - xPos;
	int dy = targetY - yPos;

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

	x = xPos;
	y = yPos;

	int oldX = xPos;
	int oldY = yPos;

	int newX, newY;

	for (int i = 0; i < steps; i++)
	{
		x += xInc;
		y += yInc;

		newX = static_cast<int>(round(x));
		newY = static_cast<int>(round(y));

		if (newX == xPos && newY == yPos)
		{
			continue;
		}

		//if out of bounds, or an element in the way
		if (!contains(newX, newY) || !thisElement->canSwap(getElement(newX, newY), newX - xPos, newY - yPos))
		{
			//if there was an element, return with current x and y
			targetX = oldX;
			targetY = oldY;
			return;
		}

		oldX = newX;
		oldY = newY;
	}

	targetX = oldX;
	targetY = oldY;
}

bool Matrix::setElement(int const x, int const y, Element* const element)
{
	int index = positionToIndex(x, y);

	//if nothing and now something, or vice versa, mark it with chunk
	Element* old = elements[index];

	if (!old && element)
	{
		chunks[positionToChunkIndex(x, y)].activate();
	}
	else if (old && !element)
	{
		chunks[positionToChunkIndex(x, y)].deactivate();
	}

	if (element)
	{
		element->init();
		element->activate();
	}
	
	elements[index] = element;

	return true;
}

void Matrix::activateSurrounding(int const x, int const y)
{
	tryActivate(x, y + 1);
	tryActivate(x, y - 1);
	tryActivate(x + 1, y);
	tryActivate(x - 1, y);
}

void Matrix::destroyElement(int const x, int const y)
{
	if (contains(x, y))
	{
		//within the matrix
		int index = positionToIndex(x, y);

		Element* e = elements[index];

		if (e)
		{
			e->deactivate();
			elementsToDestroy.push_back(e);
			setElement(x, y, nullptr);
		}
	}
}

void Matrix::destroyElements(int const x, int const y, int const width)
{
	for (int yy = y - width / 2; yy <= y + width / 2; yy++)
	{
		for (int xx = x - width / 2; xx <= x + width / 2; xx++)
		{
			destroyElement(xx, yy);
		}
	}
}

void Matrix::swap(int const index1, int const index2)
{
	//swap the elements
	Element* temp = elements[index1];
	elements[index1] = elements[index2];
	elements[index2] = temp;

	//make sure both are activated
	if (elements[index1])
		elements[index1]->activate();

	if (elements[index2])
		elements[index2]->activate();
}

bool Matrix::swap(int const x1, int const y1, int const x2, int const y2)
{
	if (!contains(x1, y1) || !contains(x2, y2))
	{
		//do not swap if trying to move outside the matrix... for now
		return false;
	}

	//same spot...
	if (x1 == x2 && y1 == y2)
	{
		return false;
	}

	swap(positionToIndex(x1, y1), positionToIndex(x2, y2));

	return true;
}

void Matrix::replaceElement(int const x, int const y, Element* const newElement, bool const destroy)
{
	Element* oldElement = getElement(x, y);

	//destroy old
	if (oldElement && destroy)
	{
		destroyElement(x, y);
	}

	setElement(x, y, newElement);
}

void Matrix::convertElement(int const x, int const y, Element* const newElement, bool const destroy)
{
	Element* oldElement = getElement(x, y);

	//destroy old
	if (oldElement && destroy)
	{
		destroyElement(x, y);
	}

	setElement(x, y, newElement);

	//take heat of old since converting
	if (oldElement)
	{
		newElement->setTemperature(oldElement->getTemperature());
	}
}

int Matrix::positionToIndex(int const x, int const y) const
{
	return y * width + x;
}

void Matrix::activateSurrounding(int const x, int const y, int const width)
{
	int const halfWidth = width / 2;

	//go around the borders
	for (int yy = y - halfWidth; yy <= y + halfWidth; yy++)
	{
		tryActivate(x - halfWidth - 1, yy);
		tryActivate(x + halfWidth + 1, yy);
	}

	for (int xx = x - halfWidth; xx <= x + halfWidth; xx++)
	{
		tryActivate(xx, y + halfWidth + 1);
		tryActivate(xx, y - halfWidth - 1);
	}
}

void Matrix::clear()
{
	Element* e;

	//clear elements
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			e = getElement(x, y);

			if (e)
			{
				delete e;
				elements[positionToIndex(x, y)] = nullptr;
			}
		}
	}

	//clear chunks
	for (int y = 0; y < (height / CHUNK_SIZE); y++)
	{
		for (int x = 0; x < (width / CHUNK_SIZE); x++)
		{
			chunks[y * (width / CHUNK_SIZE) + x] = Chunk();
		}
	}

	//reset
	updateToggle = true;
}

bool Matrix::tryActivate(int const x, int const y)
{
	Element* e = getElement(x, y);

	if (e)
	{
		e->activate();
		return true;
	}

	return false;
}