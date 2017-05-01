
# All Targets
all: cyber

# Tool invocations
# Executable "cyber" depends on the files Run.o dns.o expert.o pc.o worm.o
cyber: bin/Run.o bin/cyberdns.o bin/cyberexpert.o bin/cyberpc.o bin/cyberworm.o
	@echo 'Building target: cyber'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cyber	bin/Run.o bin/cyberdns.o bin/cyberexpert.o bin/cyberpc.o bin/cyberworm.o
	@echo 'Finished building target: cyber'
	@echo ' '

# Depends on the source and header files
bin/cyberdns.o: src/cyberdns.cpp
	g++ -g -Wall -Weffc++ -c -Linclude -o bin/cyberdns.o src/cyberdns.cpp

# Depends on the source and header files
bin/cyberexpert.o: src/cyberexpert.cpp
	g++ -g -Wall -Weffc++ -c -Linclude -o bin/cyberexpert.o src/cyberexpert.cpp

# Depends on the source and header files
bin/cyberpc.o: src/cyberpc.cpp
	g++ -g -Wall -Weffc++ -c -Linclude -o bin/cyberpc.o src/cyberpc.cpp

# Depends on the source and header files
bin/cyberworm.o: src/cyberworm.cpp
	g++ -g -Wall -Weffc++ -c -Linclude -o bin/cyberworm.o src/cyberworm.cpp
	
# Depends on the source and header files 
bin/Run.o: src/Run.cpp
	g++ -g -Wall -Weffc++ -c -Linclude -o bin/Run.o src/Run.cpp

#Clean the build directory
clean: 
	rm -f bin/*