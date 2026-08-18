<img width="1920" height="1280" alt="Download" src="https://github.com/user-attachments/assets/0b2e0b61-5009-4f3b-9255-a8ff5dbb1318" />
<img width="1920" height="1280" alt="Download (1)" src="https://github.com/user-attachments/assets/0a3ed7c9-b644-4311-a2fa-993c46db13a0" />

---

# CAMM

Eigenstaendig kompilierbarer CAMM-Kern mit persistentem Content Store, RAM-LRU-Cache,
adaptiver Policy, Metriken, Systembeobachtung, asynchronem Worker und Callback-Adapter.

Der Kern manipuliert keine CUDA-Aufrufe. Die konkrete llama.cpp-Version bindet ihre
State-Export-/Restore-Funktionen ueber `LlamaAdapter::callbacks()` an. Der CUPTI-Observer
ist als sicherer, optionaler Beobachtungsadapter abgegrenzt und standardmaessig aus.

Dokumentation der Architektur
[Camm](https://stellular-scone-9e503f.netlify.app)

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
./build/camm_demo
```

Alternativ ohne CMake siehe `build.sh`.
