#include <iostream>
#include <cstring>
#define N 10000



class CObject
{
public:
	virtual void someMethod() {}
	virtual int getCode() { return 0; }
};

class CCircle : public CObject {
private:
	int rad;
public:
	CCircle() {
		rad = 10;
	}
	virtual void someMethod() override
	{
		printf("someMethod() : CCircle");
	}
	virtual int getCode() { return 1; }
};

class CVehicle : public CObject
{
public:
	void someMethod() override
	{
		printf("someMethod() : CVehicle");
	}
	virtual int getCode() { return 20; }
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
	void someMethod() override
	{
		printf("someMethod() : CCar");
	}
	virtual int getCode() { return 21; }
};

class MyObjectFactory
{
public:
	MyObjectFactory() { }

	CObject* createObject(CObject& p)
	{
		CObject* _object;
		if (&p == nullptr) return nullptr;
		switch (p.getCode())
		{
		case 1:
			_object = (new typename CCircle());
			break;
		case 20:
			_object = (new typename CVehicle());
			break;
		case 21:
			_object = (new typename CCar());
			break;
		default:
			_object = (new typename CCar());
			break;
		}
		return _object;
	}
};





class CObjectArray 
{
private:
	int count;
	int emptycount;
	CObject** objects;
public:
	CObjectArray(int count)
	{
		this->emptycount = count;
		this->count = count;
		objects = new CObject * [count];
		for (int i = 0; i < count; i++)
		{
			objects[i] = nullptr;
		}
	}

	CObjectArray(CObjectArray& copy)
	{
		MyObjectFactory factory;
		this->emptycount = copy.count;
		this->count = copy.count;
		objects = new CObject * [count];
		for (int i = 0; i < count; i++)
		{
			objects[i] = factory.createObject(*copy.objects[i]);
		}
	}


	~CObjectArray()
	{
		for (int i = 0; i < this->count; i++)
		{
			if (this->objects[i] != nullptr)
				delete (this->objects[i]);
		}
		delete[] (this->objects);
	}
	void randObject(int index)
	{
		switch (rand() % 3)
		{
		case 0:
			this->setCObject(index, new CCircle());
			break;
		case 1:
			this->setCObject(index, new CVehicle());
			break;
		default:
			this->setCObject(index, new CCar());
			break;
		}
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
			emptycount--;
		}
	}
	
	void addobject(CObject* _object)
	{
		MyObjectFactory factory;
		CObjectArray* tmp = new CObjectArray(*this);

		for (int i = 0; i < this->count; i++)
		{
			if (this->objects[i] != nullptr)
				delete (this->objects[i]);
		}
		delete[](this->objects);

		this->objects = new CObject * [(this->count)+1];
		for (int i = 0; i < this->count; i++)
		{
			this->objects[i] = factory.createObject(*(tmp->objects[i]));
		}
		this->objects[count] = _object;
		this->count++;
		tmp->~CObjectArray();
	}

	CObject* getCObject(int index)
	{
		if (objects[index] != nullptr) return objects[index];
		else std::cout << "Индекс пустой";
	}
	void delCObject(int index)
	{
		if (objects[index] != nullptr)
		{
			delete objects[index];
			objects[index] = nullptr;
			emptycount++;

		}
		
	}
	int getCount()
	{
		return count;
	}
	bool isNullobj(int index)
	{
		if (objects[index] == nullptr) return true;
		else return false;
	}
};



int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	CObjectArray myStorage(N);
	for (int i = 0; i < myStorage.getCount(); i++)
	{
		myStorage.randObject(i);
	}
	
	myStorage.addobject(new CCircle());

	for (int i = 0; i < myStorage.getCount(); i++)
	{
		std::cout << i;
		myStorage.getCObject(i)->someMethod();
		std::cout << std::endl;
		
	}
	std::cout << "\n----------------------------------------------------------------\n";

	for (int i = 0; i < myStorage.getCount()&& (i < N + N/7); i++) {
		//std::cout << i << " ";

		
		switch (rand() % 5)
		{
		
		case 0:
			myStorage.addobject(new CVehicle());
			//myStorage.getCObject(i)->someMethod();
			break;
		case 1:
			myStorage.addobject(new CCar());
			//myStorage.getCObject(i)->someMethod();
			break;
		case 2:
			myStorage.delCObject(i);
			//myStorage.getCObject(i);
			break;
		default:
			myStorage.addobject(new CCircle());
			//myStorage.getCObject(i)->someMethod();
			break;
		}


		//std::cout << std::endl;
	}

	for (int i = 0; i < myStorage.getCount(); i++)
	{
		std::cout << i << " ";
		if (myStorage.isNullobj(i)) myStorage.getCObject(i);
			else myStorage.getCObject(i)->someMethod();
		std::cout << std::endl;

	}


	
	return 0;
}