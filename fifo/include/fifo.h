/*
 * fifo.h
 *
 *  Created on: Sep 9, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_FIFO_H_
#define SRC_FIFO_H_

#include<systemc.h>

template <typename T>
class fifo
{

public:

	fifo();

	~fifo();

	inline void read_b(T& value_);			// blocking read

	inline void write_b(const T& value_); 	// blocking write

	inline bool read_nb(T& value_);			// non-blocking read

	inline bool write_nb(const T& value_);	// non-blocking write

	inline int get_ndata() const;			// gets number of data available in FIFO

	inline void reset();					// resets the content of FIFO to initial state

private:

	bool buffer_read(T& value_);			// reads the top most content of the buffer

	bool buffer_write(const T& value_);		// adds value to buffer

	T* buffer;						// the buffer
	int free;						// number of free spaces in buffer
	int buffer_size;				// size of the buffer
	int index_read;					// index of next read
	int index_write;				// index of next write

	sc_event data_written_event;
	sc_event data_read_event;
};

template <typename T>
fifo<T>::fifo():
	buffer_size(10),
	index_read(0),
	index_write(0),
	free(10)
{
	buffer = new T(10);
}

template <typename T>
fifo<T>::~fifo()
{
	delete [] buffer;
}

// blocking read
template <typename T>
inline void fifo<T>::read_b(T& value_)
{
	while(get_ndata() == 0)
	{
		wait(data_written_event);
	}
	buffer_read(value_);
	data_read_event.notify();
}

// blocking write
template <typename T>
inline void fifo<T>::write_b(const T& value_)
{
	while(free == 0)
	{
		wait(data_read_event);
	}
	buffer_write(value_);
	data_written_event.notify();
}

// non-blocking read
template <typename T>
inline bool fifo<T>::read_nb(T& value_)
{
	if(get_ndata() == 0)
	{
		return false;
	}
	buffer_read(value_);
	data_read_event.notify();

	return true;
}

// non-blocking write
template <typename T>
inline bool fifo<T>::write_nb(const T& value_)
{
	if(free == 0)
	{
		return false;
	}
	buffer_write(value_);
	data_written_event.notify();

	return true;
}

// gets the number of data available in FIFO
template <typename T>
inline int fifo<T>::get_ndata() const
{
	return (buffer_size - free);
}

// resets the content of FIFO to initial state
template <typename T>
inline void fifo<T>::reset()
{
	index_read = 0;
	index_write = 0;
	free = 10;

	for (std::size_t i(0); i < buffer_size; ++i)
	{
		buffer[i] = T();
	}
}

// reads data of buffer
template <typename T>
bool fifo<T>::buffer_read(T& value_)
{
	if(free == buffer_size)
	{
		return false;
	}

	value_ = buffer[index_read];
	buffer[index_read] = T();
	index_read = (index_read + 1) % buffer_size;
	free++;

	return true;
}

// writes data to buffer
template <typename T>
bool fifo<T>::buffer_write(const T& value_)
{
	if(free == 0)
	{
		return 0;
	}

	buffer[index_write] = value_;
	index_write = (index_write + 1) % buffer_size;
	free--;

	return true;
}

#endif /* SRC_FIFO_H_ */
