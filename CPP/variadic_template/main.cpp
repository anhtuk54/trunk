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
		function<R(Args...)> f = [obj,cb](Args... args)->R {
			return (obj->*cb)(args...);
		};
		CallbackMap<R,Args...>[id] = f;
	}

	template <class R, class ... Args>
	void Callback(string id, Args&& ... args)
	{
		CallbackMap<R,Args...>[id](forward<Args...>(args)...);
	}

private:
	template <class R, class ... Args>
	static unordered_map<string, function<R(Args...)>> CallbackMap;
};

template <class R, class ... Args>
unordered_map<string, function<R(Args...)>> Factory::CallbackMap;


int main(int argc, char **argv)
{
	A a;
	B b;
	Factory f;
	f.RegisterCallback("A",&a,&A::method);
	f.RegisterCallback("B",&b,&B::method);
	f.Callback<void>("A", 10);
	f.Callback<int>("B");
	return 0;
}
