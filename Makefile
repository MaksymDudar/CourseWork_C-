CXX = clang++
CXXFLAGS = -Wall -std=c++17

course: task25.cpp global_state.cpp paint_method.cpp field.cpp cell.cpp instuction.cpp
	$(CXX) $(CXXFLAGS) -o course task25.cpp global_state.cpp paint_method.cpp field.cpp cell.cpp instuction.cpp