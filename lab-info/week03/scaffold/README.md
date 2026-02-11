# Week 03 Scaffold — Template Classes & Linked Lists

This scaffold provides additional examples and templates to help you understand template classes and linked lists.

## Files in this directory

### Template Examples
- `template_examples.cpp` — Basic template syntax examples
- `linked_list_examples.cpp` — How to use the LinkedList template

### Game Integration Examples
- `inventory_template_usage.cpp` — How Inventory uses LinkedList<Item>
- `enemygroup_template_usage.cpp` — How EnemyGroup uses LinkedList<Enemy>

### Additional Templates
- `Stack.h` — Template-based stack implementation
- `Queue.h` — Template-based queue implementation

## Building Examples

```bash
# Build individual examples
g++ -std=c++17 -I ../../dungeongame/include template_examples.cpp -o template_examples
g++ -std=c++17 -I ../../dungeongame/include linked_list_examples.cpp -o linked_list_examples

# Run examples
./template_examples
./linked_list_examples
```

## Key Template Concepts

### Template Class Declaration
```cpp
template <typename T>
class MyTemplate {
private:
    T data;
public:
    MyTemplate(const T& d) : data(d) {}
    T getData() const { return data; }
};
```

### Template Usage
```cpp
MyTemplate<int> intTemplate(42);
MyTemplate<std::string> stringTemplate("Hello");
```

### Template Iterator Support
```cpp
template <typename T>
class Iterator {
    // Implementation for range-based for loops
};
```

## Linked List vs Arrays

| Operation | Linked List | Array |
|-----------|-------------|-------|
| Access by index | O(n) | O(1) |
| Insert at end | O(1) | O(1) amortized |
| Insert at beginning | O(1) | O(n) |
| Delete at position | O(1) | O(n) |
| Memory usage | Higher (pointers) | Lower |

## Common Template Patterns

1. **Type aliases**: `using StringList = LinkedList<std::string>;`
2. **Template specialization**: Special behavior for specific types
3. **Template metaprogramming**: Compile-time computations
4. **CRTP**: Curiously Recurring Template Pattern for static polymorphism

## Debugging Templates

- **Compilation errors**: Often verbose, focus on the key error message
- **Template instantiation**: Templates are compiled when used
- **Type deduction**: `auto` and `decltype` work well with templates
- **SFINAE**: Substitution Failure is Not An Error

## Performance Considerations

- **Cache locality**: Arrays are better for sequential access
- **Memory allocation**: Linked lists allocate per node
- **Iterator invalidation**: Different rules for different containers
- **Copy operations**: Templates can help avoid unnecessary copies</content>
<parameter name="filePath">/Users/heidiahders/Documents/MendocinoCollege/Class/2026/Spring/CSC222/game/lab-info/week03/scaffold/README.md