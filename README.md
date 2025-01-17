# Interview Prep Basically
## Multithreading examples
- mutex
- condition_variable
- atomic
- future
- unique_lock
- lock_guard
- thread
- https://baptiste-wicht.com/posts/2017/09/cpp11-concurrency-tutorial-futures.html

## Design Patterns
- Singleton: want exactly one instance of the class. use static vars to ensure this. and locks to be thread safe execpt for static decl??
- Observer: pub/sub model
- Factory: predefined ways to instantiate
- Builder: functions for customization, for any type of customizability
