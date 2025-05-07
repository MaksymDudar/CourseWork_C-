CXX = clang++
CXXFLAGS = -Wall -std=c++17

course: play.cpp paint_method.cpp structure_of_field.cpp 
	$(CXX) $(CXXFLAGS) -o course play.cpp paint_method.cpp structure_of_field.cpp 