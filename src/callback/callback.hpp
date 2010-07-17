#ifndef __CALLBACK_HPP
#define __CALLBACK_HPP

#include <tr1/memory>

class CallbackBase0
{
	public:
		virtual void operator()()=0;
};

class CallbackFun0: public CallbackBase0
{
	public:
		void operator()()
		{
			(*function)();
		};

		CallbackFun0(void (*func)())
		{
			function=func;
		};
	
	private:
		void (*function)();

};

template <class T>
class CallbackMem0: public CallbackBase0
{
	public:
		void operator()()
		{
			(*object.*function)();
		};

		CallbackMem0(T* obj,void (T::*func)())
		{
			object=obj;
			function=func;
		};
	
	private:
		T* object;
		void (T::*function)();
};

class Callback0
{
	public:
		void operator()()
		{
			if(m_callback.get())
				(*m_callback)();
		}

		Callback0()
		{

		}

		template <typename O>
		Callback0(O* object,void (O::*func)())
		{
			m_callback.reset(new CallbackMem0<O>(object,func));
		}

		Callback0(void (*func)())
		{
			m_callback.reset(new CallbackFun0(func));
		}
		
	private:
		std::tr1::shared_ptr<CallbackBase0> m_callback;
};


#endif
