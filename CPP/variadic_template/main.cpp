#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <utility>

using namespace std;

class A
{
public:
	A(){}
	~A()=default;
	void method(int v)
	{
		cout << "[" << __PRETTY_FUNCTION__<< "]" << " value: " << v << endl;
	}

};

class B
{
public:
	B(){}
	~B()=default;
	int method()
	{
		cout << "[" << __PRETTY_FUNCTION__<< "]" << endl;
		return 11;
	}

};

template <class R, class T, class ... Args>
struct _FP
{
	T * obj;
	R(T::*fp)(Args...);
};

class Factory
{
public:
	Factory()
	{}

	~Factory()
	{}

	template <class R, class T, class ... Args>
	void RegisterCallback(string id, T *obj, R(T::*cb)(Args...))
	{
		CallbackMap<R,T,Args...>[id] = _FP<R,T,Args...>{obj,cb};
	}

	template <class R, class T, class ... Args>
	void Callback(string id, Args&& ... args)
	{
		auto v = CallbackMap<R,T,Args...>[id];
		(v.obj->*(v.fp))(forward<Args...>(args)...);
	}

private:
	template <class R, class T, class ... Args>
	static unordered_map<string, _FP<R,T,Args...>> CallbackMap;
};

template <class R, class T, class ... Args>
unordered_map<string, _FP<R,T,Args...>> Factory::CallbackMap;


int main(int argc, char **argv)
{
	A a;
	B b;
	Factory f;
	f.RegisterCallback("A",&a,&A::method);
	f.RegisterCallback("B",&b,&B::method);
	f.Callback<void,A>("A", 10);
	f.Callback<int,B>("B");
	return 0;
}
