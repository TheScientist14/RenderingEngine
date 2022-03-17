//
// Created by ewakeford on 17/03/2022.
//

#pragma once



class ModelLoader {

public:
    const class aiScene* scene;
    char* pFile;

    const aiScene* import(char* pFile);


};