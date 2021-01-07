<div align="center">
    <h1>Simulation of a distributed synchronization using a central Coordinator</h1>
    <h4>Simulation einer verteilten Synchronisation mit einem zentralen Koordinator</h4>
    <h3>fischer_project_1</h3>
</div>

<div align="center">

[![License](https://img.shields.io/badge/License-Boost%201.0-blue.svg)](https://www.boost.org/LICENSE_1_0.txt)
[![time tracker](https://wakatime.com/badge/github/konstfish/fischer_project_1.svg)](https://wakatime.com/badge/github/konstfish/fischer_project_1)

</div>

<a href="https://s.konst.fish/fischer_projekt_1">Live-Demo</a>

## Short Summary

The goal of this assignment was to create a Simulation of a distributed synchronization using a central Coordinator. The number of Nodes should be defined using a command-line argument.

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

## Example Output

```
[2021-01-04 20:01:54.449] [info] Node 3: Preparing to enter critical section (4s)
[2021-01-04 20:01:54.449] [info] Node 0: Preparing to enter critical section (4.68s)
[2021-01-04 20:01:54.449] [info] Node 1: Preparing to enter critical section (3.89s)
[2021-01-04 20:01:54.449] [info] Node 2: Preparing to enter critical section (3.48s)
[2021-01-04 20:01:54.449] [info] Node 4: Preparing to enter critical section (4.89s)
[2021-01-04 20:01:57.932] [info] Node 2: REQ to enter critical section
[2021-01-04 20:01:57.932] [info] Coord : OK to Node 2
[2021-01-04 20:01:57.932] [info] Node 2: Entering critical section
[2021-01-04 20:01:58.337] [info] Node 1: REQ to enter critical section
[2021-01-04 20:01:58.453] [info] Node 3: REQ to enter critical section
[2021-01-04 20:01:59.132] [info] Node 0: REQ to enter critical section
[2021-01-04 20:01:59.340] [info] Node 4: REQ to enter critical section
[2021-01-04 20:02:01.935] [info] Node 2: REL critical section
[2021-01-04 20:02:01.935] [info] Node 2: Preparing to enter critical section (4.4s)
[2021-01-04 20:02:02.353] [info] Coord : OK to Node 1
[2021-01-04 20:02:02.353] [info] Node 1: Entering critical section
^C
[2021-01-04 20:02:03.353] [critical] Interrupt signal (2) recieved!
Final Stats:
+-----------------------+--------------------+-------------------------+--------------------------+
| No. of Admitted Nodes | Maximum Queue Size | Failed Nodes/Recoveries | Total Time Spent Running |
+-----------------------+--------------------+-------------------------+--------------------------+
| 2                     | 4                  | 0/0                     | 8s                       |
+-----------------------+--------------------+-------------------------+--------------------------+
```
