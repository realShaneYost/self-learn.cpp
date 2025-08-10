## What is a Factory Pattern?

Think of a Factory Pattern like a droid workshop on Tatooine. I can walk into Watto's shop and say
"Hey, I need a protocol droid.". Watto goes in the back, assembles one, and gives me a C-3PO unit.
Next day I ask for a astromech and out comes RD-D2.

I didn't build the droids myself. I just ask for the type I want and Watto handles the parts and 
circuits behind the scenes. That's what a Factory does in C++. It builds the right object for me
based on what I ask for. I don't need to know how to construct it. I just say give me a type of 
droid and out comes a droid object. 

In my own words I can then conclude the Factory pattern is a design pattern used to create objects
without specifying the exact class of the object being created. In C++, it might look like ...

- A static method (often in a class like DroidFactory) that returns a `std::unique_ptr`
- The method (which often is called a Factory method) checks input (string, enum)
- It then instantiates the correct subclass behind the scenes based on input

## What are some OOP concepts in a Factory Pattern?

#### Polymorphism

A droid could have a base class with a `virtual void speak()` method. Classes like AstromechDroid
and ProtocolDroid could then override that method with their own behavior.

The factory method returns a `std::unique_ptr<Droid>`, but at runtime, the actual object could be
a ProtocolDroid or AstromechDroid. This lets me call it as such `droid->speak()`. 

#### Inheritance

ProtocolDroid and AstromechDroid inherit from Droid. This gives them access to any public or 
protected members of Device and enforces that they implement the virtual functions, like `speak()`.

Inheritance forms the backbone of polymorphism I could say. It allows a pointer/reference to a 
`Droid` to actually point to any type of subclass (type of droid).

#### Encapsulation

There generally is a `Factory` class that implements the factory method. It hides the logic of
object creation. Users of the factory don't see `new ProtocolDroid`, `std::make_unique`, or which
headers or dependencies are required. 

Instead, the client just calls `DroidFactory::create("ProtocolDroid")` and gets back a working
droid object. Creation details are hidden behind the factory interface.

#### Abstraction __"Trust in the interface, not the details"__

I like this saying whether it breaks down or not. Not only is it an easy star wars saying to 
remember but abstraction is about defining behavior without knowing the specific implementation.

The base droid class acts as an abstract interface via the pure virtual method we might specify.
So like `virtual void speak() = 0;`. The client code relies only on a Droid class. This allows
different concrete implementations of droid types to plug into the same architecture.

```Cpp
std::unique_ptr<Droid> d = DroidFactory::create("ProtocolDroid");
d->speak();
```

## What are the building blocks to a Factory Pattern?

#### Abstract Base Class

This defines the interface (pure virtual methods) that all concrete types must implement. This 
enables polymorphism. It is our `Droid` class.

#### Concrete Subclasses

Real implementations of the base class. These are the actual types created by the factory that 
override methods from the Abstract Base Class. It is our classes like `ProtocolDroid`.

#### Factory Method

Can vary in implementation but often a static method that takes input (e.g. "ProtocolDroid") and
returns the appropriate concrete object wrapped in a smart pointer.

