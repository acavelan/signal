#include <list>
#include <functional>

template<typename... Args>
class Signal
{
    private:

        std::list<std::function<void(Args...)> > _calls;

    public:
    
        virtual ~Signal()
        {
            _calls.clear();
        }

        inline void connect(std::function<void(Args...)> fct)
        {
            _calls.push_back(fct);
        }
        
        template<typename Object>
        inline void connect(Object* object, void (Object::*method)(Args...))
        {
            _calls.push_back([object,method](Args... args){(*object.*method)(args...);});
        }
        
        template<typename Object>
        inline void connect(Object* object, void (Object::*method)(Args...) const)
        {
            _calls.push_back([object,method](Args... args){(*object.*method)(args...);});
        }
        
        template<typename Object>
        inline void connect(const Object* object, void (Object::*method)(Args...) const)
        {
            _calls.push_back([object,method](Args... args){(*object.*method)(args...);});
        }

        inline void emit(Args... args)
        {
            for(auto call : _calls)
                call(args...);
        }
};
