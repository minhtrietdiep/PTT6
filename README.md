PTT6 Proftaak
-------------------------------------------------------------------------------

Project to design and implement a plate changer device for a Philips medical
device, while working using AGILE.

[Sprint Trello board](https://trello.com/b/5ZWiUzMG/ptt6-2)  
[Backlog Trello board](https://trello.com/b/j1JP8Bcz/ptt6-2-backlog)

## Building

There are different build configs for different purposes. Generally this should
do the trick:

```sh
cd ./src
make all
```

This builds the host version, builds the target version and builds the unit
tests (for the host system).

If you need to build a specific something, there are the following options
from `./src`:

* `lib-target`
* `lib-host`
* `lib-host-gcov`
* `target`
* `host`
* `host-gcov`
* `test`
* `test-run`
* `test-clean`
* `copy`
* `all`
* `clean`

It should be pretty clear what it stands for. Each system has its own 
library rules. The `-gcov` rules are to generate coverage results when running
unit tests, though unit tests can also be built and run with the non-gcov 
rules. 

The `copy` rule simply copies the (built!) binaries to the target. These are:

* `./src/BusinessLayer/bl.out`
* `./src/API/CommunicationServer/communication.out`

## CI

Check `.gitlab-ci.yml` for what's happening when things go through the GitLab
Runners. GitLab Runner requirements:

* `g++`
* `arm-linux-gnueabihf-g++`
* `libgtest-dev`
* `gcovr`
* `cpplint`

### CI Pipeline

Steps:

* Build host: host-gcov and host-lib-gcov
    * Save host build artifacts
* Build target
* Build test and test-run
    * Depend on host build
    * Save test build and test-run artifacts
* Run coverage check
    * Depend on host build
    * Depend on unit test build and run
* Run linter

Some steps have been taken to make the build process faster, by taking
advantage of GitLab's CI rules. Near the end phase this saved some 6-7 minutes
build time.

Build and run results are __not__ cached between subsequent pipeline triggers.

## Running

Simply run the following in any order:

Target:
* `bl.out`
* `communication.out`

Host:
* `bl-host.out`
* `communication-host.out`


This starts the server-side. 

On a Client machine, start the C# Client application to start communicating.

