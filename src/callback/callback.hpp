#ifndef __CALLBACK_HPP
#define __CALLBACK_HPP

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
			if(m_callback)
				(*m_callback)();
		}

		Callback0()
		{
			m_callback=0;
		}

		template <typename O>
		void set(O* object,void (O::*func)())
		{
			m_callback=new CallbackMem0<O>(object,func);
		}

		void set(void (*func)())
		{
			m_callback=new CallbackFun0(func);
		}
		
	private:
		void free()
		{
			if(m_callback)
			{
				delete m_callback;
				m_callback=0;
			}			
		}

		CallbackBase0* m_callback;
};


#endif
