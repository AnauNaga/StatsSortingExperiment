//Sorting Class with 5 sorting algorithms that can sort arrays
//Compiled in Visual Studio 2013 but should work on any C++ compiler with a few tweaks.

//Incase you need som info on sorting algorithms
//https://en.wikipedia.org/wiki/Sorting_algorithm

// Algorithms in this class
// 1 Boubble Sort
// 2 Merge Sort
// 3 Selection Sort
// 4 Insertion Sort
// 5 Shell Sort

//See more of my projects
//https://gist.github.com/DreamVB/

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

#include <chrono>

// ...

using namespace std::chrono;
milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());


class TSort {
private:
	template <typename T>
	void merge_split(T* data, size_t l, size_t m, size_t r) {
		//Used to split a source array into two halfs and sort each set
		int n1 = (m - l + 1);
		int n2 = (r - m);

		size_t x = 0;
		size_t y = 0;
		size_t z = 0;

		T* L;
		T* R;
		//Create arrays
		L = new T[n1]; // Left
		R = new T[n2]; // Right
		//Copy data to left array
		while (x < n1) {
			L[x] = data[l + x];
			x++;
		}
		//Copy data to right array
		while (y < n2) {
			R[y] = data[m + 1 + y];
			y++;
		}
		//Reset variables for next loops
		x = 0;
		y = 0;
		//Set z to left
		z = l;

		while (x < n1 && y < n2) {
			//Compare left array to right array
			if (L[x] <= R[y]) {
				//Set data
				data[z] = L[x];
				x++;
			}
			else {
				//Set data
				data[z] = R[y];
				y++;
			}
			z++;
		}
		//Copy any remaining left array back to data array
		while (x < n1) {
			//Set data array with left array data
			data[z] = L[x];
			x++;
			z++;
		}
		//Copy any remaining right array back to data array
		while (y < n2) {
			//Set data array with right array data
			data[z] = R[y];
			y++;
			z++;
		}
		//Delete left and right arrays.
		delete[]L;
		delete[]R;
	}
public:
	//Merge sort algorithm
	template <typename T>
	void merge_sort(T* data, size_t l, size_t r) {

		if (l >= r) {
			return;
		}
		//Get middle of data array
		int mid = l + (r - l) / 2;
		//Merge left side
		merge_sort(data, l, mid);
		//Merge right side
		merge_sort(data, mid + 1, r);
		merge_split(data, l, mid, r);
	}

	//Bobble sort algorithm
	template <typename T>
	void bubble_sort(T* data, const size_t r) {
		T temp;
		bool swapped;
		for (size_t x = 0; x < r; x++) {
			swapped = false;
			for (size_t y = x + 1; y < r; y++) {
				//Compare data x to data y
				if (data[x] >= data[y]) {
					//Swap data
					temp = data[y];
					data[y] = data[x];
					data[x] = temp;
					//Tell us the data have been swaped.
					swapped = true;
				}
			}
			if (!swapped) {
				break;
			}
		}
	}

	//Insertion Sort
	template <typename T>
	void insertion_sort(T* data, const size_t size) {
		size_t x;
		size_t y;
		T key;

		for (x = 1; x < size; x++) {
			//get data
			key = data[x];

			y = (x - 1);

			while (y >= 0 && data[y] > key) {
				//Set data y+1 to data y
				data[y + 1] = data[y];
				//DEC y
				y--;
			}
			//Set data with key
			data[y + 1] = key;
		}
	}
	//Shell sort
	template <typename T>
	void shell_sort(T* data, const size_t size) {
		T da;
		size_t x;
		size_t y;
		int interval = 1;

		while (interval <= size / 3) {
			interval *= (3 + 1);
		}

		while (interval > 0) {

			for (x = interval; x < size; x++) {
				//Get data
				da = data[x];
				//Set y to x
				y = x;
				//Do the sorting
				while (y > interval - 1 && data[y - interval] >= da) {
					data[y] = data[y - interval];
					y -= interval;
				}
				//Set data to da
				data[y] = da;
			}
			interval += (-1 * 3);
		}
	}

	//Selection sort algorithm
	template <typename T>
	void selection_sort(T* data, const size_t size) {
		T temp;
		size_t min;

		for (size_t x = 0; x < size - 1; x++) {
			//Get minimum element
			min = x;
			for (int y = x + 1; y < size; y++) {
				//Compare data
				if (data[y] <= data[min]) {
					//Set minimum element to y
					min = y;
				}
			}
			//Do swap
			temp = data[x];
			data[x] = data[min];
			data[min] = temp;
		}
	}
};

template <typename T>
void Display(T* data, const size_t size) {
	size_t x = 0;
	//Just display the elements in a array
	while (x < size) {
		std::cout << data[x] << " ";
		x++;
	}
	std::cout << std::endl;
}

int main() {
	//Tests
	int size = 0;
	int arraySize = 10000;
	int* nums1 = new int[arraySize];
	int* nums2 = new int[arraySize];
	int* nums3 = new int[arraySize];
	int* nums4 = new int[arraySize];
	int* nums5 = new int[arraySize];
	TSort sort;

	bool firstTime = true;
	//list of tests, each test has a list of algorithms used, each algorithm has a list of observations for that algorithm
	int*** observationsList = new int** [100];

	for (int i = 0; i < 100; i++) {
		observationsList[i] = new int* [5];
		for (int j = 0; j < 5; j++) {
			observationsList[i][j] = new int[50];
			for (int k = 0; k < 50; k++) {
				observationsList[i][j][k] = 0;
			}
		}
	}

	firstTime = false;

	//Make some random numbers and store them in nums array
	for (int currNumber = 1; currNumber < 101; currNumber++) {
		size = currNumber * 100;
		for (int observation = 0; observation < 50; observation++) {

			srand(time(NULL));
			for (int i = 0; i < size; i++) {
				//Set random value 0..1000
				nums1[i] = rand() % 1001;
				nums2[i] = nums1[i];
				nums3[i] = nums1[i];
				nums4[i] = nums1[i];
				nums5[i] = nums1[i];
			}


			std::cout << "observation: " << observation << "  currSize: " << size << "\n";

			milliseconds timeStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());



			//std::cout << "Merge Sort::" << std::endl;
			//Merge sort the nums array
			sort.merge_sort<int>(nums1, 0, (size - 1));

			milliseconds timeEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			//std::cout << "\n" << (timeEnd - timeStart).count() << " ms\n";
			observationsList[currNumber - 1][0][observation] = (int)(timeEnd - timeStart).count();
			timeStart = timeEnd;



			//std::cout << std::endl << "Bubble Sort::" << std::endl;
			sort.bubble_sort<int>(nums2, size);

			timeEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			//std::cout << "\n" << (timeEnd - timeStart).count() << " ms\n";
			observationsList[currNumber - 1][1][observation] = (int)(timeEnd - timeStart).count();
			timeStart = timeEnd;



			//std::cout << std::endl << "Selection Sort::" << std::endl;
			sort.selection_sort<int>(nums3, size);

			timeEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			//std::cout << "\n" << (timeEnd - timeStart).count() << " ms\n";
			observationsList[currNumber - 1][2][observation] = (int)(timeEnd - timeStart).count();
			timeStart = timeEnd;


			//std::cout << std::endl << "insertion Sort::" << std::endl;
			sort.insertion_sort<int>(nums4, size);

			timeEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			//std::cout << "\n" << (timeEnd - timeStart).count() << " ms\n";

			observationsList[currNumber - 1][3][observation] = (int)(timeEnd - timeStart).count();
			timeStart = timeEnd;



			//std::cout << std::endl << "Shell Sort::" << std::endl;
			sort.shell_sort<int>(nums5, size);

			timeEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			//std::cout << "\n" << (timeEnd - timeStart).count() << " ms\n";
			observationsList[currNumber - 1][4][observation] = (int)(timeEnd - timeStart).count();
			timeStart = timeEnd;
		}
	}
	ofstream currfile;
	for (int i = 0; i < 100; i++) {
		string filename = "Test";
		string filenum = std::to_string(i);
		string extention = ".txt";
		string columns = "\"m\" \"b\" \"s\" \"i\" \"h\"\n";
		currfile.open(filename + filenum + extention);
		currfile.write(columns.c_str(), columns.length());
		for (int j = 0; j < 50; j++) {
			string currNumber;
			std::cout << observationsList[i][0][j] << ", ";
			std::cout << observationsList[i][1][j] << ", ";
			std::cout << observationsList[i][2][j] << ", ";
			std::cout << observationsList[i][3][j] << ", ";
			std::cout << observationsList[i][4][j] << "\n";

			currNumber = std::to_string(observationsList[i][0][j]) + " ";
			currfile.write(currNumber.c_str(), currNumber.length());

			currNumber = std::to_string(observationsList[i][1][j]) + " ";
			currfile.write(currNumber.c_str(), currNumber.length());

			currNumber = std::to_string(observationsList[i][2][j]) + " ";
			currfile.write(currNumber.c_str(), currNumber.length());

			currNumber = std::to_string(observationsList[i][3][j]) + " ";
			currfile.write(currNumber.c_str(), currNumber.length());

			currNumber = std::to_string(observationsList[i][4][j]) + "\n";
			currfile.write(currNumber.c_str(), currNumber.length());
		}
		currfile.close();
	}
	//Clear nums array
	delete[]nums1;
	delete[]nums2;
	delete[]nums3;
	delete[]nums4;
	delete[]nums5;
	system("pause");
	return EXIT_SUCCESS;
}