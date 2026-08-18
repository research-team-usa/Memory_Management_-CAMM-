# CAMM

Eigenstaendig kompilierbarer CAMM-Kern mit persistentem Content Store, RAM-LRU-Cache,
adaptiver Policy, Metriken, Systembeobachtung, asynchronem Worker und Callback-Adapter.

Der Kern manipuliert keine CUDA-Aufrufe. Die konkrete llama.cpp-Version bindet ihre
State-Export-/Restore-Funktionen ueber `LlamaAdapter::callbacks()` an. Der CUPTI-Observer
ist als sicherer, optionaler Beobachtungsadapter abgegrenzt und standardmaessig aus.

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
./build/camm_demo
```

Alternativ ohne CMake siehe `build.sh`.
