<div align="center">
    <h1>Simulation einer verteilten Synchronisation mit einem zentralen Koordinator</h1>
    <h3>fischer_project_1</h3>
    <a href="https://s.konst.fish/fischer_projekt_1">Live-Demo</a>
    <br>
</div>

<div align="center">

[![License](https://img.shields.io/badge/License-Boost%201.0-blue.svg)](https://www.boost.org/LICENSE_1_0.txt)
[![time tracker](https://wakatime.com/badge/github/konstfish/fischer_project_1.svg)](https://wakatime.com/badge/github/konstfish/fischer_project_1)

</div>

## Usage

```
Simulation of a distributed Synchronisation using a central Coordinator
Usage: ./distsync [OPTIONS] number

Positionals:
  number INT:Range is limited to sensible values REQUIRED
                              Number of Nodes to create

Options:
  -h,--help                   Print this help message and exit
  -o,--outage-simulation      Randomly forces nodes to fail, causing a deadlock
  -d,--outage-detection Needs: --outage-simulation
                              Detect failing nodes & remove them from the queue
  -r,--requests               Use requests to communicate (Limits Nodes to a maximum of 10)
```

## Compile

`mkdir build && cd build && meson .. && ninja`

