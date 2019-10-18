#pragma once


template <typename Type>
class List {
public:
	Type		elem;
	List<Type>* next = nullptr;

	List(const Type & elem) {
		this->elem = elem;
	}
	int Length()
	{
		if (nullptr == next) return 1;
		else return next->Length()+1;
	}

	void Append(const Type & elem) {
		if (next == nullptr)
			next = new List(elem);
		else
			next->Append(elem);

	}

	List<Type>* AddFirst(const Type & elem) {
		List<Type>* first = new List(elem);
		first->next = this;
		return first;
	}

	List<Type>* Remove(const Type & elem) {
		if (this->elem == elem)
		{
			auto SuiteDeListe = next;
			this->next = nullptr;
			delete this;
			if (SuiteDeListe != nullptr)
				return SuiteDeListe->Remove(elem);
			else
				return nullptr;
		}
		else
		{
			if (next) next = next->Remove(elem);
			return this;
		}
	}

	bool Contains(const Type & elem) {
		if (this->elem == elem)
			return true;
		else
			if (next) next->Contains(elem);
		return false;
	}
};

typedef List<int> IntList;