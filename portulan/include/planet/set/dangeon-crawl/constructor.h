#pragma once

#include "structure.h"
#include "component.h"
#include "living.h"
#include <silhouette/silhouette.h>
#include <typelib/typelib.h>
#include <boost/assign.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/function.hpp>


/**
* Базовый набор команд для создания карты планеты.
* Упрощает инициализацию planet::Topology начальными данными.
*
* @see planet::set::* для подробного пояснения смысла параметров.
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace consructor {

/**
* Заполняет структуру с общей информацией об области планеты.
*
* @param radius* Радиусы планеты и атмосферы, км.
* @param mass* Массы планеты и атмосферы, кг.
* @param component* Содержание компонентов в атмосфере, % / 100.
*        Диапазон [ 0.0; 1.0 ]. Сумма всех равна 1.0.
*/
void aboutPlanet(
    portulan::planet::structure::aboutPlanet_t&,
    double radiusPlanet,  double massPlanet,      
    const std::map< portulan::planet::structure::CODE_COMPONENT, double >&  componentPlanet,
    double radiusAtmosphere,  double massAtmosphere,  
    const std::map< portulan::planet::structure::CODE_COMPONENT, double >&  componentAtmosphere
);





/**
* Конструктор для заполнения структуры aboutOneComponent_t.
*/
portulan::planet::structure::aboutOneComponent_t aoc(
    double density,
    double meltingPoint,    double boilingPoint,
    double enthalpyFusion,  double enthalpyVaporization,
    double heatCapacity
);




/**
* Заполняет структуру с информацией о компонентах, встречающихся в области
* планеты. UID компонентов согласованы с COMPONENT_CODE.
*/
void aboutComponent(
    portulan::planet::structure::aboutComponent_t&
);





/**
* Создаёт образ информации о расположении компонентов в области планеты.
*
* @param aboutPlanet Информация о планете.
* @param fn Функция, заполняющая массовые доли компонентов в зависимости от
*        ячейки 'typelib::coord_t' и информации из 'aboutPlanet'.
*/
void component(
    portulan::planet::structure::component_t&,
    const portulan::planet::structure::aboutPlanet_t&  aboutPlanet,
    const boost::function< void(
        portulan::planet::structure::componentCell_t&,
        const typelib::coord_t&,
        const portulan::planet::structure::aboutPlanet_t&
    ) >&  fn
);





/**
* Конструктор для заполнения структуры aboutOneLiving_t.
*/
portulan::planet::structure::aboutOneLiving_t aol(
);




/**
* Заполняет структуру с информацией об особях живого мира,
* встречающихся в области планеты. UID особей согласованы
* с LIVING_CODE.
*/
void aboutLiving(
    portulan::planet::structure::aboutLiving_t&
);





#if 0

/**
* Создаёт образ атмосферы планеты.
*
* @param mass Масса атмосферы, кг.
* @param innerRadius Внутренний радиус атмосферы (== радиусу планеты), км.
* @param depth Толщина атмосферы, км.
* @param chemicalSubstance Содержание portulan::planet::Topology::CHEMICAL_SUBSTANCE
*        хим. элементов в атмосфере. Диапазон [ 0.0; 1.0 ]. Сумма всех равна 1.0.
*/
template< size_t SX, size_t SY, size_t SZ >
void atmosphere(
    typename portulan::planet::Topology< SX, SY, SZ >::atmosphere_t&,
    double mass,
    double innerRadius,
    double depth,
    const std::map< int, double >&  chemicalSubstance
);





/**
* Создаёт образ планетарной коры.
*
* @param mass Масса коры, кг.
* @param innerRadius Внутренний радиус коры (== радиус планеты - глубина коры), км.
* @param depth Толщина коры, км.
* @param chemicalSubstance Содержание portulan::planet::Topology::CHEMICAL_SUBSTANCE
*        хим. элементов в коре. Диапазон [ 0.0; 1.0 ]. Сумма всех равна 1.0.
*/
template< size_t SX, size_t SY, size_t SZ >
void crust(
    typename portulan::planet::Topology< SX, SY, SZ >::crust_t&,
    double mass,
    double innerRadius,
    double depth,
    const std::map< int, double >&  chemicalSubstance
);





/**
* Создаёт образ метаболизма особи.
* Масса особи по жизненным циклам строится линейно по заданным массам
* новорождённой и старой особи.
*
* @todo extend Задавать функцию распределения массы особи по LIFE_CYCLE.
*
* @param massBurn Масса новорождённой особи.
* @param massDie Масса особи, прожившей свою жизнь.
*/
template< size_t SX, size_t SY, size_t SZ >
void metabolism(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::metabolism_t  metabolism[],
    const std::map< int, double >&  chemicalNeed,
    const std::map< int, double >&  chemicalWaste,
    const std::vector< double >&  energyNeed,
    const std::vector< double >&  energyWaste,
    double lifetime,
    double massBurn,
    double massDie
);





/**
* Создаёт образ условий выживания особи.
* Температуры комфорта и предельную делаем едиными для всех возрастов.
*
* @todo extend Задавать функцию распределения температуры особи по LIFE_CYCLE.
*
* @param environment Среды обитания особи.
* @param comfortTemperature Температуры комфорта особи.
* @param limitTemperature Диапазон температур для жизи особи.
*/
template< size_t SX, size_t SY, size_t SZ >
void survivor(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t&,
    const std::vector< size_t >&  environment,
    const std::pair< double, double >&  comfortTemperature,
    const std::pair< double, double >&  limitTemperature
);





/**
* Создаёт образ информации об особи.
*
* @param lifetime Время жизни особи, пульс.
* @param massBurn Масса новорождённой особи.
* @param massDie Масса особи, прожившей свою жизнь.
* @param chemicalComposition Химический состав особи.
*/
template< size_t SX, size_t SY, size_t SZ >
void specimen(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&,
    double lifetime,
    double massBurn,
    double massDie,
    double immunity,
    const std::map< int, double >&  chemicalComposition,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::metabolism_t metabolism[],
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t&
);





/**
* Создаёт образ информации об обитании особи (ареалы, кол-во особей).
*
* @param uid Уникальный идентификатор особи.
* @param fnLiving Функция, возвращающая кол-во здоровых и больных особей в
*        зависимости от ячейки 'typelib::coord_t' и среды обитания
*        'specimen_t'.
*/
/*
typedef boost::function< std::pair< double, double >(
    const typelib::coord_t& c,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&
) >  fnLiving_t;
*/
template< size_t SX, size_t SY, size_t SZ >
void living(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t&,
    const size_t uidCode,
    const boost::function< double(
        size_t pulse,
        const typelib::coord_t&,
        const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&
    ) >&  fnLiving,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t&
);





/**
* Создаёт образ информации о температуре в области планеты.
*
* @param fnTemperature Функция, возвращающая температуру в зависимости от
*        ячейки 'typelib::coord_t' и радиуса планеты.
* @param radiusPlanet Радиус планеты, км.
* @param radiusAtmosphere Радиус атмосферы, км.
*/
template< size_t SX, size_t SY, size_t SZ >
void temperature(
    typename portulan::planet::Topology< SX, SY, SZ >::temperature_t&,
    const boost::function< double(
        const typelib::coord_t&,
        double radiusPlanet,
        double radiusAtmosphere
    ) >&  fnTemperature,
    double radiusPlanet,
    double radiusAtmosphere
);






/**
* Создаёт образ области планеты.
*
* @param depth Толщина атмосферы, км.
* @param innerRadius Внутренний радиус атмосферы (== радиусу планеты), км.
* @param chemicalSubstance Содержание portulan::planet::Topology::CHEMICAL_SUBSTANCE
*        хим. элементов в атмосфере. Диапазон [ 0.0; 1.0 ]. Сумма всех равна 1.0.
*/
template< size_t SX, size_t SY, size_t SZ >
void planet(
    typename portulan::planet::Topology< SX, SY, SZ >&,
    const typename portulan::planet::Topology< SX, SY, SZ >::atmosphere_t&,
    const typename portulan::planet::Topology< SX, SY, SZ >::crust_t&,
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t&,
    const typename portulan::planet::Topology< SX, SY, SZ >::temperature_t&,
    const typename portulan::planet::Topology< SX, SY, SZ >::perceptations_t&
);

#endif






/**
* Копирует список 'src' в 'dst', умножая значения на 'k'.
* Если 'src' содержит меньше чем 'n', то остальные элементы заполняются нулями.
*/
template < typename S >
void copyFill(
    portulan::planet::structure::eportion_t  dst[],
    size_t n,
    const std::map< int, S >&  src,
    double k
);


template < typename D, typename S >
void copyFill(
    D dst[],
    size_t n,
    const std::vector< S >&  src,
    double k
);




/**
* Заполняет перечисление 'dst' указанным набором значений из 'src'.
* Не указанные в 'src' значения заполняются нулями.
*
* @see Соглашения для aboutPlanet_t::componentPlanet.
*/
template < typename S >
void copyFillComponent(
    portulan::planet::structure::componentAll_t&  dst,
    const std::map< portulan::planet::structure::CODE_COMPONENT, S >&  src
);




                } // constructor
            } // dungeoncrawl
        } // set
    } // planet
} // portulan












#include "planet.inl"
