# Lab 06 — Abstract Shape Hierarchy

## Overview

In this lab you will design and implement an abstract base class for geometric shapes and then derive specific shape classes from it. The classes will demonstrate inheritance, virtual methods, constructors, and polymorphism.

The UML diagram for the required classes is provided in the assignment instructions:

![Shape UML](./shape_uml.png) <!-- refer to the attached image if needed -->

## Requirements

### Abstract Base Class: `Shape`

- **Access specifier**: `protected` for attributes
- **Attributes**:
  - `double height` &ndash; represents the height of the shape
  - `double width` &ndash; represents the width of the shape

- **Methods**:
  - `void show_dimensions()` &ndash; prints the height and width of the shape
  - `std::string to_String()` &ndash; returns a string description of the shape

- **Virtual methods** (pure virtual / abstract):
  - `double getArea() = 0;`
  - `double getPerimeter() = 0;`

- **Constructors**:
  - `Shape()` &ndash; default; sets both height and width to `0`
  - `Shape(double ht, double wd)` &ndash; initializes `height` to `ht` and `width` to `wd`

### Derived Class: `Triangle`

- Inherits from `Shape` (public inheritance)
- **Additional attribute**:
  - `std::string style` &ndash; e.g. "right", "isosceles" etc.

- **Methods**:
  - Getters/setters as needed for `style` (and height/width if desired)
  - overrides for virtual methods
    - `double getArea()` &ndash; compute area using `height` and `width` as appropriate (base)
    - `double getPerimeter()` &ndash; for this lab simply return a constant value
  - `std::string to_String()` may be overridden to include style

- **Constructors**:
  - `Triangle()` &ndash; calls `Shape()`
  - `Triangle(double h, double b, std::string s)` &ndash; sets height (`h`), width (`b`), and `style` (`s`)

### Derived Class: `Rectangle`

- Inherits from `Shape`
- **Additional attribute**:
  - `bool square` &ndash; `true` when the rectangle is a square

- **Methods**:
  - Getters/setters for `square` and possibly override base class methods
  - `double getArea()` &ndash; `height * width`
  - `double getPerimeter()` &ndash; `2 * (height + width)`

- **Constructors**:
  - `Rectangle()` &ndash; calls `Shape()`
  - `Rectangle(double h, double w)` &ndash; sets height and width and computes `square` accordingly

### Tester Program

- Instantiate multiple `Triangle` and `Rectangle` objects to exercise all constructors and methods.
- Call `show_dimensions()`, `to_String()`, `getArea()`, and `getPerimeter()` on each object.
- Demonstrate polymorphic behavior using pointers or references to `Shape`.

## Submission

- Place all class definitions and implementations in appropriate header/source files (e.g., `Shape.h`, `Triangle.h`, `Rectangle.h`, etc.)
- Provide the tester program source (e.g., `lab06_test.cpp`)
- Ensure the UML diagram image is available in the directory or referenced correctly.

---

> This markdown file describes the lab assignment and can be used as the README for Lab 06.
