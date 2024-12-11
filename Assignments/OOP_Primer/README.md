------

**Abstract Classes and Interfaces:**

- Abstract classes can have both abstract methods (without implementation) and concrete methods (with implementation).
- They cannot be instantiated.
- Interfaces only define method declarations, with no implementations.
- Classes that implement an interface must provide the method implementations.

// Abstract class with one abstract method and one concrete method
class Shape {
public:
    virtual void draw() = 0; // Abstract method
    void move() { /* Move logic */ } // Concrete method
};

// Derived class implementing the abstract method
class Circle : public Shape {
public:
    void draw() override {
        // Implementation of draw
    }
};


------

**Abstraction:**

- Abstraction hides complex implementation details and exposes only the necessary functionality to the user.

class Car {
public:
    void start() { /* Code to start car */ }
    void stop() { /* Code to stop car */ }
};

class User {
public:
    void operateCar(Car& car) {
        car.start(); // User only interacts with abstraction
    }
};


------

**Access Modifiers:**

- **Public:** Accessible from anywhere.
- **Private:** Accessible only within the same class.
- **Protected:** Accessible within the class and its subclasses.

class Example {
public:
    int publicVar; // Accessible everywhere
private:
    int privateVar; // Accessible only within the class
protected:
    int protectedVar; // Accessible within class and derived classes
};


------

**Attributes / Properties:**

- Attributes represent the state of an object and are typically defined as variables within a class.

class Person {
public:
    string name; // Attribute
    int age;     // Attribute
};


------

**Class Variable:**

- Class variables are shared across all instances of a class.

class MyClass {
public:
    static int counter; // Class variable
};

// Initialize static variable
int MyClass::counter = 0;

------

**Classes and Objects:**

- A class is a blueprint for creating objects, and an object is an instance of a class.

class Dog {
public:
    void bark() { std::cout << "Woof!" << std::endl; }
};

int main() {
    Dog myDog; // Creating an object of the Dog class
    myDog.bark(); // Calling a method of the object
}


------

**Collections and Iterators:**

- Collections are data structures that hold multiple elements.
- Iterators allow you to traverse through these elements.

#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4};
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << " "; // Using iterator to traverse
    }
}


------

**Composition:**

- Composition is a design principle where one object contains another object, allowing complex objects to be constructed from simpler ones.

class Engine {
public:
    void start() { std::cout << "Engine started" << std::endl; }
};

class Car {
private:
    Engine engine; // Car contains an Engine object
public:
    void start() { engine.start(); }
};


------

**Constructors and Destructors:**

- Constructors initialize an object’s state.
- Destructors handle cleanup when an object is no longer in use.

class MyClass {
public:
    MyClass() { std::cout << "Constructor called" << std::endl; } // Constructor
    ~MyClass() { std::cout << "Destructor called" << std::endl; } // Destructor
};

int main() {
    MyClass obj; // Constructor called when object is created
}


------

**Encapsulation:**

- Encapsulation is the bundling of data and methods that operate on the data within a class, often using access modifiers to hide data from outside interference.

class Account {
private:
    double balance; // Encapsulated data

public:
    void deposit(double amount) { balance += amount; } // Method to modify data
    double getBalance() { return balance; } // Method to access data
};


------

**Exception Handling:**

- Exception handling in OOP allows developers to manage runtime errors gracefully, preventing crashes and unexpected behavior.

#include <iostream>
#include <stdexcept>

void testFunction() {
    throw std::runtime_error("An error occurred");
}

int main() {
    try {
        testFunction();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}


------

**File I/O in OOP:**

- File I/O allows for reading and writing to files, often used for persistent storage of data.

#include <fstream>
#include <iostream>

int main() {
    std::ofstream outfile("example.txt");
    outfile << "Hello, File!" << std::endl;
    outfile.close();
}


------

**Friends (C++):**

- A friend function or class in C++ allows access to the private and protected members of another class.

class MyClass {
private:
    int secret;

public:
    MyClass() : secret(42) {}

    friend void revealSecret(MyClass& obj); // Friend function declaration
};

void revealSecret(MyClass& obj) {
    std::cout << "Secret: " << obj.secret << std::endl; // Accessing private member
}


------

**Generics and Templates:**

- Generics in Java and templates in C++ enable the creation of methods and classes that can work with any data type.

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << std::endl; // Works with integers
    std::cout << add(3.5, 4.5) << std::endl; // Works with doubles
}

------

**Inheritance:**

- Inheritance allows a class to inherit properties and behaviors from another class.

class Animal {
public:
    void speak() { std::cout << "Animal speaks" << std::endl; }
};

class Dog : public Animal {
public:
    void speak() { std::cout << "Woof!" << std::endl; } // Overriding base class method
};

![Inheritance Graphic](Assignments/OOP_Primer/images/download-1.jpg)

------

**Instance and Member Variables:**

- Instance variables are unique to each instance of a class.
- Member variables belong to the class and are used to store data.

class MyClass {
public:
    int instanceVar; // Instance variable
    static int classVar; // Static (class) variable
};

int MyClass::classVar = 0; // Initialize class variable


------

**Memory Management:**

- Memory management in OOP involves allocating and deallocating memory.
- This can be automatic (garbage collection in Java) or manual (using pointers in C++).

class MyClass {
public:
    int* data;

    MyClass() {
        data = new int(10); // Manual memory allocation
    }

    ~MyClass() {
        delete data; // Manual memory deallocation
    }
};

------

**Method Overloading:**

- Method overloading allows multiple methods with the same name but different parameters, providing flexibility in how methods are called.

class Calculator {
public:
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
};


------

**Multithreading:**

- Multithreading enables concurrent execution of multiple threads, which is useful for CPU-bound tasks.

#include <iostream>
#include <thread>

void printMessage() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(printMessage);
    t.join(); // Wait for thread to finish
}

![Multithreading Graphic](Assignments/OOP_Primer/images/download-2.png)

------

**Object Relationships (Association, Aggregation, Composition):**

- **Association:** A relationship between two classes where one class has an object of another class.
- **Aggregation:** A special form of association where one class can exist independently of the other.
- **Composition:** A form of association where one class owns another, and the owned class cannot exist without the owning class.

// Association Example
class Engine {};
class Car {
    Engine engine; // Car has an Engine
};

// Aggregation Example
class Engine {};
class Car {
    Engine* engine; // Car has a pointer to Engine, but Engine can exist independently
};

// Composition Example
class Engine {
public:
    void start() { std::cout << "Engine started" << std::endl; }
};

class Car {
private:
    Engine engine; // Car owns Engine; Engine can't exist without Car
public:
    void start() { engine.start(); }
};

------

Object-Oriented Design Principles:
- Object-Oriented Design Principles are guidelines that help in designing object-oriented systems, focusing on how to organize classes, objects, and their relationships effectively.

! [Object-Oriented Design Principles Graphic](Assignments/OOP_Primer/images/download.jpg)
------

Operator Overloading:
- Operator overloading allows you to define custom behavior for operators (e.g., +, -, *, etc.) when applied to instances of a class, making operators work with user-defined types.

class Complex {
public:
    int real, imag;

    Complex operator + (const Complex& other) {
        Complex temp;
        temp.real = real + other.real;
        temp.imag = imag + other.imag;
        return temp;
    }
};


------

Overloading:
- Overloading refers to defining multiple methods or operators with the same name but different parameters, allowing the same operation to be performed on different data types or numbers of arguments.

------

Polymorphism:
- Polymorphism allows objects of different classes to be treated as objects of a common superclass, with methods behaving differently based on the object type. It can be achieved through method overriding and interfaces.

![Polymorphism Graphic](Assignments/OOP_Primer/images/download-1.png)



------

Public / Private / Protected:
- Public: Accessible from anywhere in the program.
- Private: Accessible only within the same class.
- Protected: Accessible within the class and its subclasses.

------

SOLID Principles:
- SOLID is an acronym for five design principles in object-oriented programming:
  - S: Single Responsibility Principle
  - O: Open/Closed Principle
  - L: Liskov Substitution Principle
  - I: Interface Segregation Principle
  - D: Dependency Inversion Principle

  ! [SOLID Princples Graphic](Assignments/OOP_Primer/images/download.png)

  ------

Static (Methods and Variables):
- Static Methods/Variables: Static methods and variables belong to the class itself rather than instances of the class, meaning they are shared across all instances.

------

Testing in OOP (Unit Testing, Test-Driven Development):
- Unit Testing: A software testing method where individual units of code (usually functions or methods) are tested in isolation.
- Test-Driven Development (TDD): A software development approach where tests are written before the code is developed, guiding the design process.

------

UML Diagrams and Modeling:
- UML Diagrams: Unified Modeling Language (UML) diagrams are visual representations of a system’s structure and behavior, helping to document and communicate the design of object-oriented systems.
- Modeling: Involves creating an abstract representation of a system, showing relationships, processes, and interactions between components.

![UML Diagrams and Modeling Graphic](Assignments/OOP_Primer/images/3_uml.webp)


------

Virtual:
- Virtual Methods: A virtual method is a method in a base class that can be overridden by a derived class, allowing for dynamic method dispatch (polymorphism) at runtime.

class Base {
public:
    virtual void speak() { std::cout << "Base class speaking" << std::endl; }
};

class Derived : public Base {
public:
    void speak() override { std::cout << "Derived class speaking" << std::endl; }
};


