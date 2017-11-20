#include <iostream>

//using namespace std;
template <typename Key, typename Value>
class SList;

template <typename Key, typename Value>
class SListItr;

template <typename Key, typename Value>
void interleave(const SList<Key, Value>& first1, int fcount, const SList<Key, Value>& second, int scount, SList<Key, Value>& result);


template <typename Key, typename Value>
class SListNode{
	SListNode(const Key& key = Key(), const Value& value = Value(), SListNode * n = NULL)
		: keyElement(key), valueElement(value), next(n){}

	Key keyElement;
	Value valueElement;
	SListNode *next;

	friend class SList<Key, Value>;
	friend class SListItr<Key, Value>;
};


template <typename Key, typename Value>
class SListItr{
	public:
		SListItr(): current (NULL){}

		bool isValid () const{
			return current != NULL;
		}

		void advance(){
			if (isValid())
				current = current->next;
		}

		const Key& getKey() const{
			if (isValid())
				return current->keyElement;
		}

		const Value& getValue() const{
			if (isValid())
				return current->valueElement;
		}


	private:
		SListNode<Key, Value> *current;

		SListItr(SListNode<Key, Value> *n): current(n){}

	friend class SList<Key, Value>;
};


template <typename Key, typename Value>
class SList{
	public:
		SList();
		SList(const SList& rhs);
		~SList();

		SListItr<Key, Value> zero() const;
		SListItr<Key, Value> first() const;
		bool isEmpty() const;
		void print() const;
		SListItr<Key, Value> findKey (const Key& x) const;
		SListItr<Key, Value> findPreviousKey (const Key& x) const;
		SListItr<Key, Value> findBack() const;
		void removeAll();
		void removeKey(const Key& k);
		bool keyExist(const Key& k);
		void addAfter(const Key& k, const Value& v, const Key& previousKey);
		void addAfter(const Key& k, const Value& v, const SListItr<Key, Value> &previousNode);
		void pushFront(const Key& k, const Value& v);
		void pushBack(const Key& k, const Value& v);
		void removeFront();
		void removeBack();
		SList & operator=(const SList& rhs);
		int size();

	private:
		SListNode<Key, Value> *head;
};


int main()
{
    SList<int, int> l1;
    l1.pushBack(1,100);
    l1.pushBack(1,101);
    l1.pushBack(1,102);
    l1.pushBack(1,103);
    l1.removeBack();
    l1.pushFront(2,100);
    l1.pushFront(3,100);
    l1.addAfter(4,100,2);
//    l1.removeKey(3);
    SList<int, int> l2, l3;
    l2 = l1;
    std::cout << (int)l1.keyExist(4) << std::endl;

    interleave(l1,1,l2,1,l3);
    l3.print();
    std::cin.get();
    return 0;
}


template <typename Key, typename Value>
SList<Key, Value>::SList(){
	head = new SListNode<Key, Value>;
}

template <typename Key, typename Value>
SList<Key, Value>::SList(const SList<Key, Value>& rhs){
	head = new SListNode<Key, Value>;
	*this = rhs;
}

template <typename Key, typename Value>
SList<Key, Value>::~SList(){
	removeAll();
	delete head;
}

template <typename Key, typename Value>
SListItr<Key, Value> SList<Key, Value>::zero() const{
	return SListItr<Key, Value>(head);
}

template <typename Key, typename Value>
SListItr<Key, Value> SList<Key, Value>::first() const{
	return SListItr<Key, Value>(head->next);
}

template <typename Key, typename Value>
bool SList<Key, Value>::isEmpty() const{
	return head->next == NULL;
}

template <typename Key, typename Value>
void SList<Key, Value>::print() const{
	if(isEmpty())
		std::cout << "Empty list" << std::endl;
	else{
		SListNode<Key, Value> *p = head->next;
		for( ; p; p = p->next)
			std::cout << p->keyElement << '\t' << p->valueElement << std::endl;
	}
}

template <typename Key, typename Value>
SListItr<Key, Value> SList<Key, Value>::findKey(const Key& k) const{
	SListNode<Key, Value> *p = head->next;
	while(p != NULL && p->keyElement != k)
		p = p->next;

	return SListItr<Key, Value>(p);
}

template <typename Key, typename Value>
SListItr<Key, Value> SList<Key, Value>::findPreviousKey(const Key& k) const{
	SListNode<Key, Value> *p = head;
	while(p->next != NULL && p->next->keyElement != k)
		p = p->next;

	return SListItr<Key, Value>(p);
}

template <typename Key, typename Value>
SListItr<Key, Value> SList<Key, Value>::findBack() const{
	SListNode<Key, Value> *p = head;
	while(p->next != NULL)
		p = p->next;

	return SListItr<Key, Value>(p);
}

template <typename Key, typename Value>
void SList<Key, Value>::removeAll(){
	while(!isEmpty())
		removeFront();
}

template <typename Key, typename Value>
void SList<Key, Value>::removeKey(const Key& k){
	SListNode<Key, Value> *p = head->next;
	SListNode<Key, Value> *q = head;

	for( ; p; p = p->next){
		if(p->keyElement == k){
//			SListNode<Key, Value> *oldNode = p->next;
			q->next = p->next;
			delete p;
			p = q;
		}else
			q = p;
	}

}

template <typename Key, typename Value>
bool SList<Key, Value>::keyExist(const Key& k){
	return findKey(k).current != NULL;
}

template <typename Key, typename Value>
void SList<Key, Value>::addAfter(const Key& k, const Value& v, const Key& previousKey){
	SListNode<Key, Value> *p = findKey(previousKey).current;
	if(p)
		p->next = new SListNode<Key, Value>(k, v, p->next);
}
template <typename Key, typename Value>
void SList<Key, Value>::addAfter(const Key& k, const Value& v, const SListItr<Key, Value> &previousNode){
	if(previousNode.current != NULL)
		previousNode.current->next = new SListNode<Key, Value> (k, v, previousNode.current->next);
}

template <typename Key, typename Value>
void SList<Key, Value>::pushFront(const Key& k, const Value& v){
	head->next = new SListNode<Key, Value>(k, v, head->next);
}

template <typename Key, typename Value>
void SList<Key, Value>::pushBack(const Key& k, const Value& v){
	SListNode<Key, Value> *p = head;
	while(p->next != NULL)
		p = p->next;

	p->next = new SListNode<Key, Value>(k, v);
}

template <typename Key, typename Value>
void SList<Key, Value>::removeFront(){
	if(head->next){
		SListNode<Key, Value> *oldNode = head->next;
		head->next = oldNode->next;
		delete oldNode;
	}
}

template <typename Key, typename Value>
void SList<Key, Value>::removeBack(){
	SListNode<Key, Value> *p = head;
	while(p->next->next != NULL)
		p = p->next;

	SListNode<Key, Value> *oldNode = p->next;
	p->next = NULL;
	delete oldNode;
}

template <typename Key, typename Value>
SList<Key, Value> & SList<Key, Value>::operator=(const SList<Key, Value>& rhs){
	if (this != &rhs){
		removeAll();

		SListItr<Key, Value> rItr = rhs.first();
		SListItr<Key, Value> itr = zero();
		for ( ; rItr.isValid(); rItr.advance(), itr.advance())
			addAfter(rItr.getKey(), rItr.getValue(), itr);
	}
}

template <typename Key, typename Value>
int SList<Key, Value>::size(){
	int i = 0;
	SListNode<Key, Value> *p = head->next;
	for ( ; p; p = p->next)
		i++;

	return i;
}


template <typename Key, typename Value>
void interleave(const SList<Key, Value>& first1, int fcount, const SList<Key, Value>& second, int scount, SList<Key, Value>& result){
	if(!result.isEmpty())
		result.removeAll();

	SListItr<Key, Value> rItr = result.zero();
	SListItr<Key, Value> fItr = first1.first();
	SListItr<Key, Value> sItr = second.first();

	while (fItr.isValid() && sItr.isValid()){
		for (int i = 0; i < fcount && fItr.isValid(); i++, rItr.advance(), fItr.advance())
			result.addAfter(fItr.getKey(), fItr.getValue(), rItr);
		for (int i = 0; i < scount && sItr.isValid(); i++, rItr.advance(), sItr.advance())
			result.addAfter(sItr.getKey(), sItr.getValue(), rItr);
	}
}
