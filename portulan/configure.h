#pragma once


namespace portulan {


/*
* Соглашения при работе с проектом
*   # Все перечисления enum заканчиваются элементом вида SHORT_last,
*     где SHORT - сокращённое название перечисления.
*   # См. др. соглашения, отмеченные символом "#" в коде проекта.
*/




/**
* Используются типы данных из библиотеки OpenCL.
* (!) Не все классы проекта будут доступны при отсутствии этой декларации.
*/
#define OPENCL_PORTULAN


/**
* Какой мир (набор структур) использовать.
*/
#define DUNGEON_CRAWL_WORLD_PORTULAN




/**
* Разрешает использовать тип 'double' в портуланах.
* Без этой директивы движки стараются поместиться в 'float'.
* 
* #! Не все видеокарты поддерживают 'double' для OpenCL.
*
* @see typedef real_t
* @see porte::PERMIT_DOUBLE_ENGINE_PORTE
*/
#define PERMIT_DOUBLE_ENGINE_PORTULAN




/**
* Размер буфера (количество записей-пульсов) при ведении статистики портулана.
*
* @see world::*::Portulan::statistics_t
*/
static const size_t STATISTICS_BUFFER_COUNT = 200000;


} // portulan
