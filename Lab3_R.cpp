#include <iostream>
#define N 100
class CObject
{
public:
	virtual void someMethod() {}
};

class CObjectArray {
private:
	int count;
	CObject** objects;
public:
	CObjectArray(int count)
	{
		this->count = count;
		objects = new CObject * [count];
		for (int i = 0; i < count; i++)
		{
			objects[i] = nullptr;
		}
	}
	~CObjectArray()
	{
		for (int i = 0; i < count; i++)
		{
			if (objects[i] != nullptr)
				delete (objects[i]);
		}
		delete[] objects;
	}
	void setCObject(int index, CObject* _object)
	{
		if (objects[index] != nullptr)
		{
			delete (objects[index]);
			objects[index] = _object;
		}
		else
		{
			objects[index] = _object;
		}
	}
	CObject* getCObject(int index)
	{
		return objects[index];
	}
	void delCObject(int index)
	{
		if (objects[index] != nullptr)
			delete objects[index];
	}
	int getCount()
	{
		return count;
	}
};

class CCicle : public CObject
{
private:
	int rad;
public:
	CCicle()
	{
		rad = 10;
	}
	virtual void someMethod() override
	{
		printf("\nsomeMethod() : CCicle");
	}
};

class CVehicle : public CObject
{
public:
	virtual void someMethod() override
	{
		printf("\nsomeMethod() : CVehicle");
	}
};

class CCar : public CVehicle
{
private:
	const char* mark;
	int age;
public:
	CCar()
	{
		mark = "Opel";
		age = 4;
	}
	virtual void someMethod() override
	{
		printf("\nsomeMethod() : CCar");
	}
};
int main()
{
	setlocale(LC_ALL, "");

	CObjectArray myStorage(N);
	for (int i = 0; i < myStorage.getCount(); i++)
	{
		switch (rand() % 3)
		{
		case 0:
			myStorage.setCObject(i, new CCicle());
			break;
		case 1:
			myStorage.setCObject(i, new CVehicle());
			break;
		default:
			myStorage.setCObject(i, new CCar());
			break;
		}
	}
	for (int i = 0; i < myStorage.getCount(); i++) {
		myStorage.getCObject(i)->someMethod();
	}


	printf("\n");
	return 0;
}