#ifndef PORTULAN_AS_OPEN_CL_STRUCT

#pragma once

#include "structure.h"


/**
* Информация об астероидах в звёздной системе.
*/
namespace portulan {
    namespace world {
        namespace dungeoncrawl {
            namespace starsystem {
                namespace l0 {
#endif


/**
* @see #Соглашения для 'aboutStar_t'.
*/
typedef struct __attribute__ ((packed)) {
    /**
    * Астероид взаимодействует с другими элементами звёздной системы.
    */
    bool live;

    /**
    * Масса астероида, кг.
    */
    real_t mass;

    /**
    * Размеры астероида по XYZ, м.
    */
    real3_t size;

    /**
    * Координаты астероида в звёздной системе, XYZ, м.
    */
    big3d_t coord;

    /**
    * Наклон астероида по XYZ.
    */
    real3_t rotation;

    /**
    * Скорость движения астероида в звёздной системе, XYZ, м/с.
    */
    real3_t velocity;


    /**
    * Плотность, кг / м3.
    */
    real_t density;


    /**
    * Температура, C.
    *
    * # Указываем в Цельсиях, более привычно.
    * @todo optimize Перед расчётами переводить т. в Кельвины.
    *
    * @copy Проект 'v3d', файл struct.h.
    * @info Физическая температура лежит в диапазоне ~ (0; 1.42e32) Кельвинов.
    * @info Температура замерзания гелия ~ 1 К.
    * @info Температура замерзания водорода ~ 13 К.
    * @info Темпераутра базальтовой лавы ~ 1 500 К.
    * @info Температура на поверхности Солнца ~ 6 Кило К.
    * @info Температура на поверхности Сириуса А ~ 10 Кило К.
    * @info Температура при вспышке Новой звезды ~ 10 Мега К.
    * @info Температура при вспышке Сверхновой звезды ~ 10 Гига К.
    * @info Температура при вспышке Сверхновой звезды ~ 10 Тера К.
    * @info Температура в первую секунду после Большого взрыва ~ 10 Тера К.
    * @info Температура тяжёлой ядерной реакции в Большом адронном коллайдере ~ 10 Эта (10^18) К.
    * @info Температура тёмной материи в ядре активной галактики ~ 1 Зета (10^21) К.
    * @see more http://en.wikipedia.org/wiki/Orders_of_magnitude_%28temperature%29
    */
    real_t temperature;


    /**
    * Геометрическое альбедо.
    */
    real_t albedo;


    /**
    * Температура плавления, К.
    */
    real_t meltingPoint;


    /**
    * Температура кипения, К.
    */
    real_t boilingPoint;


    /**
    * Удельная теплоёмкость, Дж / (кг * К).
    *
    * @see http://ru.wikipedia.org/wiki/%D0%A3%D0%B4%D0%B5%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D1%82%D0%B5%D0%BF%D0%BB%D0%BE%D1%91%D0%BC%D0%BA%D0%BE%D1%81%D1%82%D1%8C
    */
    real_t heatCapacity;


    /**
    * Удельная теплота плавления, Дж / кг.
    */
    real_t enthalpyFusion;


    /**
    * Удельная теплота испарения (парообразования), Дж / кг.
    */
    real_t enthalpyVaporization;

} characteristicAsteroid_t;




typedef struct __attribute__ ((packed)) {
    /**
    * Идентификатор астероида.
    */
    uid_t uid;

    /**
    * Характеристика астероида: сейчас и для след. пульса.
    */
    characteristicAsteroid_t today;
    characteristicAsteroid_t future;

    /**
    * События, выпущенные астероидом за 1 пульс.
    */
    emitterEvent_t emitterEvent;

    /**
    * Все усвоенные астероидом модели поведения.
    *
    * #i Добавлено, чтобы протестировать портулан для живых организмов,
    *    не создавая новых элементов звёздной системы или новых портуланов.
    */
    memoryModel_t memoryModel;

    /**
    * Модели поведения, которые будут выполняться астероидом через
    * определённые промежутки времени.
    */
    frequencyMemoryModel_t  frequencyMemoryModel;

} aboutAsteroid_t;




/**
* Астероиды в области звёздной системы.
*
* # Если тело отсутствует - разрушено, вышло за границу звёздной системы
*   и т.п. - его масса = 0.
* # Отсутствующий астероид - сигнал конца списка.
*/
typedef aboutAsteroid_t*  asteroidContent_t;
typedef struct __attribute__ ((packed)) {
    asteroidContent_t content;
} asteroid_t;




#ifndef PORTULAN_AS_OPEN_CL_STRUCT
                } // l0
            } // starsystem
        } // dungeoncrawl
    } // world
} // portulan
#endif
