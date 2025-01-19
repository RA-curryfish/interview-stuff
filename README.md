# Interview Prep Basically

## C++11 features
- thread stuff, concurrency, locking stuff
- smart pointers, chrono, hashmaps
- for each, nullptr, lambdas, auto, move() constructor

## Multithreading examples
- mutex, condition_variable, atomic, futures, unique_lock, lock_guard, threads
- https://baptiste-wicht.com/posts/2017/09/cpp11-concurrency-tutorial-futures.html

## Design Patterns
- Singleton: want exactly one instance of the class. use static vars to ensure this. and locks to be thread safe execpt for static decl??
- Observer: pub/sub model
- Factory: predefined ways to instantiate
- Builder: functions for customization, for any type of customizability

## Library Interposing
- Create wrapper lib functions and expose as .so files
- Replace dynamic lib functions by setting LD_PRELOAD=<custom.so> file while executing application
- Can use it to extract stats like malloc size distribution in an application and so on 
