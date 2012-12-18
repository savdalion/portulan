#pragma once


namespace portulan {
    namespace test {

/**
* Варианты движков для моделирования звёздной системы.
*
* # Допустимо выбрать только один движок.
*
* #! OpenCL не работает с double на NVIDIA GeForce 8800GTS.
*/
// Движок на параллельном OpenCL.
//#define OPENCL_STARSYSTEM_L0_ENGINE_PORTE
// Для движка на OpenCL: указание использовать CPU.
//#define ONLY_CPU_OPENCL_STARSYSTEM_L0_ENGINE_PORTE

// Движок на линейном CPU.
#define CPU_STARSYSTEM_L0_ENGINE_PORTE


    } // test

} // portulan
