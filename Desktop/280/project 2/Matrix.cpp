#include <cassert>
#include "Matrix.h"
#include <cstring>
#include <string>

using namespace std;


// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
void Matrix_init(Matrix* mat, int width, int height) {
    assert(0<width && width <= MAX_MATRIX_WIDTH);
    assert(0<height && height <= MAX_MATRIX_WIDTH);
    
    mat->width = width;
    mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    os << mat->width << " " << mat->height << endl;
//    for (int i = 1; i < mat->height; ++i)
//    {
//        for (int j = 1; j< mat->width; ++j)
//        {
//            os << mat->data[i*j-1] << " " << endl;
//        }
//        
//    }
    
    for (int i = 0; i<(mat->width * mat->height); i+=mat->width)
    {
        for(int j = 0; j< mat->width; ++j)
        {
            os << mat->data[i+j]<< " ";
        }
        os << endl;
    }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat)
{
    return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat)
{
    return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr)
{
    int index = ptr - mat->data;
    int row = (index/mat->width);
    return row;
    // find the index of whatever number you're looking for
    // then divide it by the number of columns and round down
    // this gives you row #
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    int row = Matrix_row(mat,ptr);
    int FirstElementIndex = row * mat->width;
    int ptrIndex = ptr - mat->data;
    int column = ptrIndex - FirstElementIndex;
    return column;
//multiply row number of the ptr by width (which gives you the the index of the first number in that row, subtract the index of that first number from the index of the ptr to get the column number
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    int index = (row*mat->width)+column;
    int *ptr = mat->data;
    ptr = ptr + index;
    return ptr;
    //row 1 column 3 is actually row 2 and column 4, so its 2 * 4 -1
    // index = (row + 1)*(col + 1) -1
    // ptr = ptr + index
    //return ptr;
 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    int index = (row*mat->width)+column;
    const int *ptr = mat->data;
    ptr = ptr + index; // just changing the position
    return ptr;

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    
    for (int i = 0; i<(mat->width * mat->height); i+=mat->width)
    {
        for(int j = 0; j< mat->width; ++j)
        {
            mat->data[i+j] = value;
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value)
{
    for (int i = 0; i<(mat->width); ++i) // top
    {
        mat->data[i] = value;
    }
    
    for (int i = 0; i<(mat->width); ++i) // bottom
    {
        int *ptr;
        ptr = Matrix_at(mat,mat->height-1,i);
        *ptr = value;
    }
    
    for (int i = 1; i<(mat->height-2); ++i) // left
    {
        int *ptr;
        ptr = Matrix_at(mat,i,0);
        *ptr = value;
    }
    
    for (int i = 1; i<(mat->height-2); ++i) // right
    {
        int *ptr;
        ptr = Matrix_at(mat,i,mat->width-1);
        *ptr = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
// MAX ISNT WORKING :(
int Matrix_max(const Matrix* mat) {
        int max = 0;
        int index_of_max = 0;
        const int *cursor = mat->data; //start at first index of data array
    
        while(*cursor != '\0') // until the end of data array
        {
            if (*cursor > max)//mat->data[index_of_max]) // if the max is less than the value at cursor
            {
                index_of_max = (cursor - (mat->data)); // finding the index of cursor aka new max
                max = *cursor; // the value at cursor becomes the new max
                
            }
            cout << "current index is " << cursor - mat->data << endl;
            ++cursor; // moving cursor 
        }
    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end)
{
    int min = 0;
    int index_of_min = 0;
   //start at first index of data array
    const int *cursor = Matrix_at(mat,row,column_start);
    while (cursor < Matrix_at(mat,row,column_end)) // until the end of data array
    {
        if (*cursor < mat->data[index_of_min]) // if the max is less than the value at cursor
        {
            min = *cursor; // the value at cursor becomes the new max
            index_of_min = (cursor - (mat->data)); // finding the index of cursor aka new max
            
        }
        ++cursor; // moving cursor
    }
    
    return Matrix_column(mat,cursor);
    
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
    int min = 0;
    int index_of_min = 0;
    //start at first index of data array
    const int *cursor = Matrix_at(mat,row,column_start);
    while (cursor < Matrix_at(mat,row,column_end)) // until the end of data array
    {
        if (*cursor < mat->data[index_of_min]) // if the max is less than the value at cursor
        {
            min = *cursor; // the value at cursor becomes the new max
            index_of_min = (cursor - (mat->data)); // finding the index of cursor aka new max
            
        }
        ++cursor; // moving cursor
    }
    
    return min;
    
}
