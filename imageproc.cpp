#include <string>
#include<iostream>
#include"imageproc.h"
#include<fstream>

int** readFile(string fileName, int& rows, int& cols, int& max){
    ifstream fin;
    fin.open(fileName.c_str());
    int **myArr = NULL;
    string myValue = "";

    if(fin){
        cout << "File found"<< endl;
        fin >> myValue;
        fin >> rows;
        myArr = new int*[rows];
        fin >> cols;
        for(int i = 0; i < rows; ++i){
            myArr[i] = new int[cols];
        }
        fin >> max;
        int i = 0, j = 0;
        for(i = 0; i < rows; ++i){
            for(j = 0; j < cols; ++j){
                fin  >> myArr[i][j];
            }
        }
    }
    else {
        cout << "File not found ";
    }
    fin.close();
    return myArr;
};
void writeFile(string fileName, int** image, int rows, int cols, int max){
    ofstream fout;
        cout << fileName << endl;
        fout.open(fileName.c_str());
        if(fout){
            fout << "P2\n";
            fout << rows << " " << cols << endl << max << endl;
            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j){
                        fout << image[i][j] << " ";
                }
                fout << endl;
            }
        }
        else {
            cout << "File not opened";
        }
        fout.close();
}; // called from each of the following functions, to create a new file: see document for naming of new file
void invertColors(string fileName, int** image, int rows, int cols, int max){
    int **myArr = NULL;
    myArr = new int*[rows];
    int i, j;
    for(i = 0; i < rows; ++i){
        myArr[i] = new int[cols];
    }
    for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
            myArr[i][j] = 255 - image[i][j];
            if(myArr[i][j] < 0){
                myArr[i][j] *= -1;
            }
        }
    }
    writeFile("invertColors.pgm",myArr,rows,cols,max);
    cout << "Created invertColors.pgm"<< endl;
    deallocate(myArr, rows);
}; // makes brighter dark, and vice versa (see sample image)
void shrink2x(string fileName, int** image, int rows, int cols, int max){
    int **shrinkArray = NULL,
        newCols = cols/2,
        newRows = rows/2,
        i = 0, j = 0,
        cC = 0, rC = 0;
    shrinkArray = new int*[newRows];
    for(i = 0; i < newRows; ++i){
        shrinkArray[i] = new int[newCols];
    }
    for(i = 0; i < rows; i += 2){
        cC = 0;
        for(j = 0; j < cols; j+=2){
            shrinkArray[rC][cC] = image[i][j];
            cC++;
        }
        rC++;
    }
    writeFile("shrink2x.pgm",shrinkArray,newRows,newCols,max);
    cout << "Created shrink2x.pgm"<< endl;
    deallocate(shrinkArray, newRows);
};  // makes the image half the size
void enlarge2x(string fileName, int** image, int rows, int cols, int max){
    int **enlargeArray = NULL,
        newCols = cols*2,
        newRows = rows*2,
        i = 0, j = 0,
        cC = 0, rC = 0;
    enlargeArray = new int*[newRows];
    for(i = 0; i < newRows; ++i){
        enlargeArray[i] = new int[newCols];
    }
    for(i = 0; i < newRows; i++){
        cC = 0;
        if((i%2) == 0 && i > 0){
            rC++;
        }
        for(j = 0; j < newCols; j++){
            if((j%2) == 0 && j > 0){
                cC++;
            }
            enlargeArray[i][j] = (image[rC][cC]);
        }
    }
    writeFile("enlarge2x.pgm",enlargeArray,newRows,newCols,max);
    cout << "Created enlarge2x.pgm"<< endl;
    deallocate(enlargeArray, newRows);
}; // makes the image twice the size
void brighten(string fileName, int** image, int rows, int cols, int max){
    int **myArr = NULL;
    myArr = new int*[rows];
    int i, j;
    for(i = 0; i < rows; ++i){
        myArr[i] = new int[cols];
    }
    for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
            if((image[i][j] + (image[i][j] * 0.10)) <= 255){
                myArr[i][j] = (image[i][j] + (image[i][j] * 0.10));
            }
            else {
                myArr[i][j] = 255;
            }
        }
    }
    writeFile("birghten.pgm",myArr,rows,cols,max);
    cout << "Created birghten.pgm"<< endl;
    deallocate(myArr, rows);
};  // brightens the image by 10%
void darken(string fileName, int** image, int rows, int cols, int max){
    int **myArr = NULL;
    myArr = new int*[rows];
    int i, j;
    for(i = 0; i < rows; ++i){
        myArr[i] = new int[cols];
    }
    for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
            if((image[i][j] - (image[i][j] * 0.10)) >= 0){
                myArr[i][j] = (image[i][j] - (image[i][j] * 0.10));
            }else {
                myArr[i][j] = 0;
            }
        }
    }
    writeFile("darken.pgm",myArr,rows,cols,max);
    cout << "Created darken.pgm"<< endl;
    deallocate(myArr, rows);
};    // darkens the image by 10%
void crop(string fileName, int** image, int rows, int cols, int max, int x1, int y1, int x2, int y2){
    int **cropArray = NULL,
    newRows = 0, newCols = 0,
    i = 0, j = 0,
    cC = 0, rC = 0;
    newRows = x2 - x1;
    newCols = y2 - y1;
    cropArray = new int*[newRows];
    for(int i = 0; i < newRows; ++i){
        cropArray[i] = new int[newCols];
    }
    for(i = x1; i < x2; i++){
        cC = 0;
        for(j = y1; j < y2; j++){
            cropArray[rC][cC] = image[i][j];
            cC++;
        }
        rC++;
    }
    writeFile("crop.pgm",cropArray,newRows,newCols,max);
    cout << "Created crop.pgm"<< endl;
    deallocate(cropArray, newRows);
};
void deallocate(int** image, int rows){
    for(int i = 0; i < rows; ++i){
        delete [] image[i];
    }}
