CXX = arm-linux-gnueabi-g++
CXXFLAGS = -Wall -O
CXXFLAGS += -static
EXEC = reach

OBJ = src/getData.o src/main.o src/MPU9250.o src/searchFilePath.o

$(EXEC): $(OBJ)
	$(LINK.cpp) $^ -o $@ $(CXXFLAGS)
# ménage
clean:
	$(RM) *~ $(OBJ)

mrproper: clean
	$(RM) $(EXEC)

# dépendances
src/getData.o: includes/getData.h
src/getData.o: includes/MPU9250.h
src/main.o: includes/getData.h
src/main.o: includes/MPU9250.h
src/main.o: includes/searchFilePath.h
src/MPU9250.o: includes/MPU9250.h
src/searchFilePath.o: includes/searchFilePath.h
