# Containers in the C++ Standard Library

Containers are the backbone of the C++ Standard Library. They are:
- **template-based data structures** that store collections of objects, called elements; thus can store built-in types like `int`, `double` to custom classes.
- provide standardized interfaces for insertion, deletion, traversal, and access.
- **Homogenous**: store objects of only one type
- **Heterogenous**: use `std::any`, `std::variant` or create a class that has multiple derived classes and wrap the object with derived class

    <u>*Note*</u>: The C++ standard defines interfaces for containers and algorithms, not implementations. Vendors may optimize freely, but must meet specified performance guarantees.  

<u>**Important**: Familiarization with the available data structures is important to be able to choose the most appropriate one for a given task.  </u>

All containers reside in the `std` namespace and are designed for **performance, safety, and flexibility**.

---

## Categories of Containers

C++ containers fall into three broad categories:

- **Sequence Containers**: Maintain the order of elements.
- **Associative Containers**: Store elements in sorted or hashed structures.
- **Container Adapters**: Provide restricted interfaces built on other containers.

---

## Sequence Containers

### `std::vector`
- Dynamic array with contiguous storage.
- Fast random access and amortized constant-time insertion at the end.
- Ideal for most general-purpose use cases.
- [Vector](vector.md)

### `std::list`
- Doubly-linked list.
- Fast insertion and deletion anywhere, but no random access.
- Useful when frequent middle insertions are needed.

### `std::deque`
- Double-ended queue.
- Fast insertion/removal at both ends.
- Slightly more overhead than `vector`.

---

## Associative Containers

### `std::set`
- Stores unique elements in sorted order.
- Backed by a balanced binary tree (usually red-black).
- Fast lookup, insertion, and deletion.

### `std::map`
- Stores key-value pairs with unique keys, sorted by key.
- Also tree-based, with logarithmic time operations.

### `std::unordered_map`
- Stores key-value pairs with unique keys, but **not sorted**.
- Backed by a hash table for average constant-time access.

---

## Container Adapters

### `std::stack`
- LIFO structure built on `deque` or `vector`.
- Only allows access to the top element.

### `std::queue`
- FIFO structure built on `deque`.
- Access only to front and back.

### `std::priority_queue`
- Max-heap by default.
- Retrieves the largest element efficiently.

---

## Common Container Operations

| Operation       | Method(s)                  | Applies To                   |
|-----------------|----------------------------|------------------------------|
| Insert element  | `push_back`, `insert`      | All containers               |
| Remove element  | `pop_back`, `erase`        | All containers               |
| Access element  | `[]`, `at()`, `front()`    | `vector`, `deque`, `map`     |
| Size            | `size()`                   | All containers               |
| Check empty     | `empty()`                  | All containers               |
| Clear contents  | `clear()`                  | All containers               |
| Iterate         | `begin()`, `end()`         | All containers               |

---

## Choosing the Right Container

| Use Case                         | Recommended Container     |
|----------------------------------|---------------------------|
| Fast random access               | `vector`                  |
| Frequent insertions/removals     | `list`, `deque`           |
| Sorted unique elements           | `set`                     |
| Key-value mapping (sorted)       | `map`                     |
| Key-value mapping (fast lookup)  | `unordered_map`           |
| Stack behavior                   | `stack`                   |
| Queue behavior                   | `queue`, `deque`          |
| Priority-based retrieval         | `priority_queue`          |

---

## Best Practices

- Prefer `vector` unless you have a specific reason to use another container.
- Use `unordered_map` for fast key-based access, but be aware of hash collisions.
- Avoid `list` unless you need constant-time insertion/removal in the middle.
- Always consider iterator validity when modifying containers.

---
