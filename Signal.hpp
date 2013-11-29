/*
razlock/Signal (https://github.com/razlock/signal) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

        void connect(std::function<void(Args...)> fct)
        {
            _calls.push_back(fct);
        }
        
        template<typename Object>
        void connect(Object* object, void (Object::*method)(Args...))
        {
            _calls.push_back([object,method](Args... args){(*object.*method)(args...);});
        }
        
        template<typename Object>
        void connect(Object* object, void (Object::*method)(Args...) const)
        {
            _calls.push_back([object,method](Args... args){(*object.*method)(args...);});
        }
        
        template<typename Object>
        void connect(const Object* object, void (Object::*method)(Args...) const)
        {
            _calls.push_back([object,method](Args... args){(*object.*method)(args...);});
        }

        void emit(Args... args)
        {
            for(auto it = _calls.begin() ; it!=_calls.end() ; it++)
                (*it)(args...);
        }
};
