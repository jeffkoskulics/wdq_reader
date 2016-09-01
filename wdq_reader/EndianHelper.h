#pragma once
#include <cstdint>
#include <iostream>

namespace Serial {

	const union {
		int16_t data;
		char bytes[2];
	} EndianTestUnion = {0x0102} ;

	constexpr bool isLittleEndian () {
		return EndianTestUnion.bytes[0] == 0x02 ;
	}

	template <class T> class Primitive {
	public:
		Primitive(T value = 0) : myValue {value} {}
		operator T () const { return myValue; }
		void setValue(T value) { myValue = value; }
		static Primitive<T> read (std::istream& source);
		void write (std::ostream& output) const;
	private:
		T myValue;
	};

	using Byte = Primitive<uint8_t>;
	using Word = Primitive<uint16_t>;
	using DoubleWord = Primitive<uint32_t>;
	using QuadWord = Primitive<uint64_t>;

	template <class T>
	std::istream& operator >> (std::istream& input, Primitive<T>& p) {
		p.read (input);
		return input;
	}

	template <class T>
	std::ostream& operator << (std::ostream& output, Primitive<T>& p) {
		p.write (output);
		return output;
	}

	template <class T>
	T reverseEndian(const T input) {
		union {
			T myT;
			char bytes[sizeof(T)];
		} raw = { input }, reversed;

		for (int i = sizeof(T); i > 0; --i) {
			reversed.bytes[i - 1] = raw.bytes[sizeof(T) - i];
		}

		return reversed.myT;
	}

	template <class T> 
	Primitive<T> Primitive<T>::read(std::istream& source) {
		T tBuffer;
		source.read(reinterpret_cast<char *>(&tBuffer), sizeof(T));

#ifdef ENDIAN_MISMATCH
		tBuffer = reverseEndian(tBuffer);
#endif //ENDIAN_MISMATCH

		return tBuffer;
	}

	template <class T>
	void Primitive<T>::write(std::ostream& output) const {
		T tBuffer = myValue;
#ifdef ENDIAN_MISMATCH
		tBuffer = reverseEndian(tBuffer);
#endif //ENDIAN_MISMATCH
		output.write(reinterpret_cast<char *>(&const_cast<T&>(tBuffer)), sizeof(T));
	}

	template <class T>
	class binary_ostream_iterator : public std::iterator<std::output_iterator_tag, T> {
		std::ostream* out_stream;
		unsigned trailing_bytes;

	public:
		binary_ostream_iterator(std::ostream& s, unsigned padding_bytes = 0) :
			out_stream(&s), 
			trailing_bytes(padding_bytes)
		{}

		binary_ostream_iterator<T>& operator = (const T& value) {
			*out_stream << value;
			for (unsigned i = 0; i < trailing_bytes; ++i)
				*out_stream << Serial::Byte(0);
			return *this;
		}

		binary_ostream_iterator<T>& operator *() { return *this;  }
		binary_ostream_iterator<T>& operator ++() { return *this; }
		binary_ostream_iterator<T>& operator ++(int) { return *this; }
	};
}
