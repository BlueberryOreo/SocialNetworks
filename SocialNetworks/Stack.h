#pragma once

template<typename T>
class Stack
{
private:
	T* stk;
	int idx;
	int memSize;

public:
	Stack() {
		memSize = 8;
		stk = new T[memSize];
		idx = -1;
	}
	~Stack() {
		delete stk;
	}
	void push(T n) {
		if (idx + 1 == memSize) {
			// À©Õ¹ÈÝÁ¿
			memSize *= 2;
			T* newStk = new T[memSize];
			for (int i = 0; i < idx; i ++) {
				newStk[i] = stk[i];
			}
			T* original = stk;
			stk = newStk;
			delete original;
		}
		stk[++idx] = n;
	}
	T top() {
		return stk[idx];
	}
	void pop() {
		if (idx == -1) return;
		idx--;
	}
	int size() {
		return idx + 1;
	}
	bool empty() {
		return idx == -1;
	}
};

