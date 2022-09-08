
#define PrintVector(vector) \
	std::cout << "Vector: " << vector.x << ", " << vector.y << ", " << vector.z << std::endl;
#define PrintMatrix(matrix) \
	std::cout << "Matrix:" << std::endl;for (int i = 0; i < 4; i++){for (int j = 0; j < 4; j++){std::cout << matrix[i][j] << ", ";}std::cout << std::endl;}
#define Print(x) \
	std::cout << x << std::endl;