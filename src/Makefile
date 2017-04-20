lib-target:
	cd sharedlibs; make lib-target
	cd BusinessLayer; make lib-target
	cd API; make lib-target
	cd HAL; make lib-target
	cd UI; make lib-target

lib-host:
	cd sharedlibs; make lib-host
	cd BusinessLayer; make lib-host
	cd API; make lib-host
	cd HAL; make lib-host
	cd UI; make lib-host

target:
	cd BusinessLayer; make target
	cd API; make target
	cd HAL; make target
	cd UI; make target

host:
	cd BusinessLayer; make host
	cd API; make host
	cd HAL; make host
	cd UI; make host

test:
	cd BusinessLayer; make test
	cd API; make test
	cd HAL; make test
	cd UI; make test

all:
	make lib-host
	make lib-target
	make host
	make target
	make test

clean:
	cd BusinessLayer; make clean
	cd API; make clean
	cd HAL; make clean
	cd UI; make clean