#include <inttypes.h>
#include <string.h>

//this shit is bad, but I don't know yet how to get rid of it
constexpr auto N = 44100 * 3;
constexpr auto NFFT = 4096;

template <class T, int32_t size>
class cyclicBuffer {
	T buffer[size];
	T orderedArray[size];
	int32_t pivot;
public:
	cyclicBuffer(T value) : pivot(-1) {
		for (int32_t i = 0; i < size; ++i) {
			memcpy(&buffer[i], &value, sizeof(T));
		}
	};

	void put() {
		if (++pivot == size) pivot = 0;
	}

	void put(T value) {
		if (++pivot == size) pivot = 0;
		memcpy(&buffer[pivot], &value, sizeof(T));
	}

	void put(const T* array, size_t arraySize) {
		if (pivot + 1 + arraySize <= size) {
			memcpy(&buffer[pivot + 1], array, sizeof(T) * arraySize);
			pivot += arraySize;
		}
		else {
			memcpy(&buffer[pivot + 1], array, sizeof(T) * (size - pivot));
			memcpy(&buffer, &array[size - pivot], sizeof(T) * (arraySize - (size - pivot)));
			pivot = arraySize - (size - pivot);
		}
	}

	T* get(int32_t index) {
		if (index >= size) return nullptr;
		return &buffer[index];
	}

	T* show(int32_t index) {
		if (pivot + index + 1 < size) return &buffer[pivot + index + 1];
		else return &buffer[pivot + index - size];
	}

	T* getLast() {
		if(pivot >= 0)	return &buffer[pivot];
		else return nullptr;
	}

	T* getNext() {
		if (pivot + 1 < size) return &buffer[pivot + 1];
		else return &buffer[0];
	}

	T* getFFTBuffer() {
		memcpy(&orderedArray[size - NFFT], &buffer[pivot], sizeof(T) * NFFT);
		return &orderedArray[size - NFFT];
	}

	T* getBuffer() {
		if (pivot == -1) return nullptr;
		if(pivot < size - 1)
			memcpy(orderedArray, &buffer[pivot + 1], sizeof(T) * (size - pivot - 1));
		memcpy(&orderedArray[size - pivot - 1], buffer, sizeof(T) * (pivot + 1));
		return orderedArray;
	}

	size_t getSize() {
		return size;
	}
};
