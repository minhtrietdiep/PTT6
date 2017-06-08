lib-target:
	cd sharedlibs; make lib-target
	cd HAL; make lib-target
	cd BusinessLayer; make lib-target
	cd API; make lib-target
	cd UI; make lib-target

lib-host:
	cd sharedlibs; make lib-host
	cd HAL; make lib-host
	cd BusinessLayer; make lib-host
	cd API; make lib-host
	cd UI; make lib-host

target:
	make lib-target
	cd HAL; make target
	cd BusinessLayer; make target
	cd API; make target
	cd UI; make target

host:
	make lib-host
	cd HAL; make host
	cd BusinessLayer; make host
	cd API; make host
	cd UI; make host

test:
	make lib-host
	cd HAL; make test
	cd BusinessLayer; make test
	cd API; make test
	cd UI; make test

test-run:
	cd HAL; make test-run
	cd BusinessLayer; make test-run
	cd API; make test-run
	cd UI; make test-run

test-clean:
	cd HAL; make test-clean
	cd BusinessLayer; make test-clean
	cd API; make test-clean
	cd UI; make test-clean

copy:
	cd BusinessLayer; make copy
	cd API; make copy

all:
	make lib-host
	make host
	make lib-target
	make target
	make test

clean:
	cd sharedlibs; make clean
	cd BusinessLayer; make clean
	cd API; make clean
	cd HAL; make clean
	cd UI; make clean