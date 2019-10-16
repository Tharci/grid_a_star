#ifndef GRID_H
#define GRID_H

#include <vector>

template<class T>
class Grid
{
public:
    Grid(int width, int height);
    ~Grid();

    T* get(int x, int y);
    void set(int x, int y, T value);
    int getWidth();
    int getHeight();
    bool checkXY(int x, int y);

private:
    std::vector<T> data;

    int width, height;
};


//definitions
template<class T>
Grid<T>::Grid(int width, int height)
{
    this->width = width;
    this->height = height;

    data.resize(width * height);
}

template<class T>
Grid<T>::~Grid()
{
    delete data;
}


template<class T>
void Grid<T>::set(int x, int y, T value)
{
    data[y * width + x] = value;
}


template<class T>
T* Grid<T>::get(int x, int y)
{
    return &data[y * width + x];
}

template<class T>
int Grid<T>::getWidth()
{
    return width;
}

template<class T>
int Grid<T>::getHeight()
{
    return height;
}

template<class T>
bool Grid<T>::checkXY(int x, int y)
{
    return (x >= 0 && x < width && y >= 0 && y < height);
}


#endif
