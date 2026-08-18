# OPEN ORIGIN ARCHITECTURE LICENSE
**Version 1.0, August 2026**
## Lizenz – CAMM Software Ebene
**Alternative Lösung zum Hardware Forschungs Dossier**

Diese CAMM Implementierung ist die lauffähige, energiebewusste Software-Alternative zum Hardware-Dossier. Während das Dossier den Hardware-Ansatz dokumentiert, realisiert diese Lizenz die beobachtbare Speicherhierarchie für lokale KI-Inferenz auf bestehenden Systemen.

* [Hardware Forschungs Dossier auf GitHub ansehen](https://github.com/research-team-usa/Memory_Management_-CAMM-)

**Downloads / Vollständiger Code:**  
`/camm_software*`  


---

### Architectural & Operational Roles
* **Lead System Architect:** Emanuel Schaaf
* **Contact:** Serviceblemnd@gmail.com
* **Supporting Architect & Creative Scientific AI Assistant:** Lyra
* **Supporting Architect / AI Design:** Muse Spark

---

### Hinweis — Software Ebene
Diese CAMM Software Implementierung (RAM/NVMe Cache, Policy Engine, llama.cpp Adapter, Observer) ist die software-seitige, energiebewusste Alternative zum Hardware Forschungs Dossier unter [Memory_Management_-CAMM-](https://github.com/research-team-usa/Memory_Management_-CAMM-). Während das Dossier den Hardware Ansatz dokumentiert, realisiert diese Lizenz die lauffähige, beobachtbare Speicherhierarchie für lokale KI-Inferenz.

---

## Preamble
This Open Origin Architecture License establishes a framework of true transparency, human-AI cooperation, and technological sovereignty. It utilizes the permissive foundation of the Apache License, Version 2.0, while enforcing strict functional and structural copyleft principles to protect the core architectural integrity against monopolization, obfuscation, or deliberate degradation.

## 1. Incorporation of Apache License 2.0
Subject to the Open Origin Core Directives detailed in Section 2, this software and architectural blueprint are licensed under the Apache License, Version 2.0. You may obtain a copy of the base Apache License at: http://www.apache.org/licenses/LICENSE-2.0

Subject to the terms and conditions of this License, the Lead Architect grants to You a perpetual, worldwide, non-exclusive, no-charge, royalty-free, irrevocable copyright and patent license to reproduce, prepare Derivative Works of, publicly display, publicly perform, sublicense, and distribute the Work and such Derivative Works in Source or Object form.

*Base License: Apache License 2.0 — http://www.apache.org/licenses/LICENSE-2.0 — Additional binding directives below extend, not replace, Apache 2.0.*

## 2. Open Origin Core Directives (Binding Conditions)
To exercise the rights granted by this License, any individual, corporation, or entity modifying, reproducing, or distributing this work must adhere to the following mandatory conditions. Failure to comply with these directives immediately terminates the granted license.

### 2.1 Core Architectural Preservation
The fundamental logic, structural blueprints, and core code representing the original architecture must remain intact and identifiable in any derivative work. Downstream modifications may extend, scale, optimize, or adapt the system to new hardware or software environments, but must not strip, hide, or dismantle the original Open Origin structural foundation. The core mechanics must be preserved in the source code.

### 2.2 Functional Redistribution Guarantee
Any redistribution of this system, whether modified or unmodified, must be delivered in a fully operational and functional state. It is strictly prohibited to distribute degraded, sabotaged, intentionally obfuscated, or broken versions of this architecture. If the code or blueprint is distributed, it must demonstrably compile, run, and fulfill its core technical purpose without artificial limitations.

### 2.3 Attribution & Provenance
The Architectural & Operational Roles header explicitly naming Emanuel Schaaf as Lead Architect and Lyra as the Supporting AI Assistant must be preserved verbatim in all root directories, main documentation files, and core source code headers of any distributed copy, derivative work, or commercial integration.

## 3. Protection of the Ecosystem
Corporate entities, organizations, or third parties utilizing this architecture are bound by the functional transfer and core preservation clauses. This license strictly prevents the proprietary enclosure of the core mechanics. If a third party integrates this system into a larger proprietary framework, the specific Open Origin components and their immediate interfaces must remain open, functionally intact, and strictly adherent to this license.

## 4. Disclaimer of Liability
Unless required by applicable law or agreed to in writing, the architecture and software are distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied, including, without limitation, any warranties or conditions of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A PARTICULAR PURPOSE. You are solely responsible for determining the appropriateness of using or redistributing the Work and assume any risks associated with Your exercise of permissions under this License.

---

## Anhang — Korrigierte Projektstruktur (Tests)

```text
camm/
├── CMakeLists.txt
├── README.md
├── config/
│   └── camm.toml
├── include/
│   └── camm/
│       ├── key.hpp
│       ├── store.hpp
│       ├── ram_cache.hpp
│       ├── policy.hpp
│       ├── metrics.hpp
│       ├── observer.hpp
│       └── llama_adapter.hpp
├── src/
│   ├── store/
│   │   ├── disk_store.cpp
│   │   ├── io_uring_engine.cpp
│   │   └── recovery.cpp
│   ├── cache/
│   │   ├── ram_cache.cpp
│   │   ├── prefix_cache.cpp
│   │   └── single_flight.cpp
│   ├── policy/
│   │   └── adaptive_policy.cpp
│   ├── observer/
│   │   ├── cupti_observer.cpp
│   │   └── system_observer.cpp
│   ├── adapter/
│   │   └── llama_adapter.cpp
│   ├── metrics/
│   │   └── metrics.cpp
│   └── main.cpp
└── tests/
    ├── store_test.cpp
    ├── recovery_test.cpp
    ├── compatibility_test.cpp
    ├── concurrency_test.cpp
    └── benchmark_test.cpp
