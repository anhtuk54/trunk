#pragma once

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(uint16_t size=1000);
    CircularBuffer(T *buffer, uint16_t size);
    ~CircularBuffer();

    void reset(CircularBuffer<T>* cbuf=nullptr);
    void put(T data);
    int put2(T data);
    T get();
    bool empty();
    bool full();
    uint16_t capacity();
    uint16_t size();

private:
    void advance_pointer();
    void retreat_pointer();

private:
    T *mBuffer=nullptr;
    uint16_t mHead=0;
    uint16_t mTail=0;
    uint16_t mMax=0;
    bool mLocalInit=false;
};

template <typename T>
CircularBuffer<T>::CircularBuffer(uint16_t size)
:mMax(size)
{
    mBuffer = new T[mMax+1];
    mLocalInit = true;
}

template <typename T>
CircularBuffer<T>::CircularBuffer(T *buffer, uint16_t size)
:mBuffer(buffer), mMax(size-1)
{
}

template <typename T>
CircularBuffer<T>::~CircularBuffer()
{
    if (mLocalInit) {
        delete [] mBuffer;
    }
}

template <typename T>
void CircularBuffer<T>::reset(CircularBuffer<T> * cbuf)
{
    if(cbuf==nullptr) {
        mHead = mTail = 0;
    }
    else {
        mBuffer = cbuf->mBuffer;
        mHead = cbuf->mHead;
        mTail = cbuf->mTail;
    }
}

template <typename T>
void CircularBuffer<T>::put(T data)
{
    mBuffer[mHead] = data;
    advance_pointer();
}

template <typename T>
int CircularBuffer<T>::put2(T data)
{
    int r = -1;
    if(!this->full()) {
        mBuffer[mHead] = data;
        advance_pointer();
        r = 0;
    }

    return r;
}

template <typename T>
T CircularBuffer<T>::get()
{
    T r;
    if(!this->empty()) {
        r = mBuffer[mTail];
        retreat_pointer();
    }

    return r;
}

template <typename T>
bool CircularBuffer<T>::empty()
{
    return mHead == mTail;
}

template <typename T>
bool CircularBuffer<T>::full()
{
    uint16_t head = mHead+1;
    if (head==mMax) {
        head = 0;
    }
    return head == mTail;
}

template <typename T>
uint16_t CircularBuffer<T>::capacity()
{
    return mMax;
}

template <typename T>
uint16_t CircularBuffer<T>::size()
{
    uint16_t size = mMax;
    if (!this->full()) {
        if(mHead >= mTail) {
            size = mHead - mTail;
        }
        else {
            size = mMax + mHead - mTail;
        }
    }
    return size;
}

template <typename T>
void CircularBuffer<T>::advance_pointer()
{
	if(this->full()) {
		if (++mTail == mMax) { 
			mTail = 0;
		}
	}

	if (++mHead == mMax) { 
		mHead = 0;
	}
}

template <typename T>
void CircularBuffer<T>::retreat_pointer()
{
	if (++mTail == mMax) { 
		mTail = 0;
	}
}
