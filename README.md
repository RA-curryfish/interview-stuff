# Interview Prep Basically
Purposely made hard to navigate/find stuff so that it's NoSQL for the brain.

## C++11 features
- thread stuff, concurrency, locking stuff
- smart pointers, chrono, hashmaps
- for each, nullptr, lambdas, auto, move() constructor, lval/rval?
- noexcept tells compiler that it doesn't throw exception
- reference vs pointer, use the latter to represent 'no' object
- benefit of rval is you can recognise that a temp obj was used to call a funciton, so can 'steal resources'
- can overload fns by either specifiying lvals or rvals
- Even if the variable's type is rvalue reference, the expression consisting of its name is an lvalue expression

## Multithreading examples
- mutex, condition_variable, atomic, futures, unique_lock, lock_guard, threads
- https://baptiste-wicht.com/posts/2017/09/cpp11-concurrency-tutorial-futures.html

## Design Patterns
- Singleton: want exactly one instance of the class. use static vars to ensure this. and locks to be thread safe execpt for static decl??
- Observer: pub/sub model. Game sending update to clients 
- Factory: predefined ways to instantiate, abstract factory produce abstract items. BisonBurger,
- Builder: functions for customization, for any type of customizability. BurgerBuilder::AddBun/AddCheese/Sauce
- Visitor: adding virtual funcs to classes without adding them. just need a 'accept' method in the class with a visitor type obj param. Pet<-Cat, Pet::Accept(Visitor V){v->Eat(this);}, Visitor::Eat(Pet p){p->SpecificFood();}
- Decorator: inherit base abstract class, override one function that inturn works on another derived type, and 'add' decoration. Shape<-Circle, Shape<-ColoredShape

## Library Interposing
- Create wrapper lib functions and expose as .so files
- Replace dynamic lib functions by setting LD_PRELOAD=<custom.so> file while executing application
- Can use it to extract stats like malloc size distribution in an application and so on 
