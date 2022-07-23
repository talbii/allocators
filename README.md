# Allocators

Just some experimants with allocators. **Do not use this in production!** (unless?)

Compile with C++20 compilers (except `clang` which for some reason has yet to implement execution policies...)

This repository is accompanied by a [blog post](https://blog.tal.bi/posts/experiments-with-allocators)!

## Results

Below are the results of running on my laptop (Apple M1 Pro), allocating `1e5` integers:

```
std::allocator<int>:
    Average: 0.227592ms (N = 10000)
      Total: 2275.92ms
        Min: 0.212ms
        Max: 0.677ms


aggressive_allocator<int, 65,536>:
    Average: 0.228791ms (N = 10000)
      Total: 2287.91ms
        Min: 0.211ms
        Max: 0.364ms


static_allocator<int, 32MB>:
    Average: 0.226384ms (N = 10000)
      Total: 2263.84ms
        Min: 0.21ms
        Max: 0.322ms
```

