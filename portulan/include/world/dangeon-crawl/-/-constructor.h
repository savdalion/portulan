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
* ������� ����� ������ ��� �������� ����� �������.
* �������� ������������� planet::Topology ���������� �������.
*
* @see planet::set::* ��� ���������� ��������� ������ ����������.
*/
namespace portulan {
    namespace planet {
        namespace set {
            namespace dungeoncrawl {
                namespace consructor {

/**
* ��������� ��������� � ����� ����������� �� ������� �������.
*
* @param radius* ������� ������� � ���������, ��.
* @param mass* ����� ������� � ���������, ��.
* @param component* ���������� ����������� � ���������, % / 100.
*        �������� [ 0.0; 1.0 ]. ����� ���� ����� 1.0.
*/
void aboutPlanet(
    portulan::planet::structure::aboutPlanet_t&,
    double radiusPlanet,  double massPlanet,      
    const std::map< portulan::planet::structure::CODE_COMPONENT, double >&  componentPlanet,
    double radiusAtmosphere,  double massAtmosphere,  
    const std::map< portulan::planet::structure::CODE_COMPONENT, double >&  componentAtmosphere
);





/**
* ����������� ��� ���������� ��������� aboutOneComponent_t.
*/
portulan::planet::structure::aboutOneComponent_t aoc(
    double density,
    double meltingPoint,    double boilingPoint,
    double enthalpyFusion,  double enthalpyVaporization,
    double heatCapacity
);




/**
* ��������� ��������� � ����������� � �����������, ������������� � �������
* �������. UID ����������� ����������� � COMPONENT_CODE.
*/
void aboutComponent(
    portulan::planet::structure::aboutComponent_t&
);





/**
* ������ ����� ���������� � ������������ ����������� � ������� �������.
*
* @param aboutPlanet ���������� � �������.
* @param fn �������, ����������� �������� ���� ����������� � ����������� ��
*        ������ 'typelib::coord_t' � ���������� �� 'aboutPlanet'.
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
* ����������� ��� ���������� ��������� aboutOneLiving_t.
*/
portulan::planet::structure::aboutOneLiving_t aol(
);




/**
* ��������� ��������� � ����������� �� ������ ������ ����,
* ������������� � ������� �������. UID ������ �����������
* � LIVING_CODE.
*/
void aboutLiving(
    portulan::planet::structure::aboutLiving_t&
);





#if 0

/**
* ������ ����� ��������� �������.
*
* @param mass ����� ���������, ��.
* @param innerRadius ���������� ������ ��������� (== ������� �������), ��.
* @param depth ������� ���������, ��.
* @param chemicalSubstance ���������� portulan::planet::Topology::CHEMICAL_SUBSTANCE
*        ���. ��������� � ���������. �������� [ 0.0; 1.0 ]. ����� ���� ����� 1.0.
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
* ������ ����� ����������� ����.
*
* @param mass ����� ����, ��.
* @param innerRadius ���������� ������ ���� (== ������ ������� - ������� ����), ��.
* @param depth ������� ����, ��.
* @param chemicalSubstance ���������� portulan::planet::Topology::CHEMICAL_SUBSTANCE
*        ���. ��������� � ����. �������� [ 0.0; 1.0 ]. ����� ���� ����� 1.0.
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
* ������ ����� ����������� �����.
* ����� ����� �� ��������� ������ �������� ������� �� �������� ������
* ������������ � ������ �����.
*
* @todo extend �������� ������� ������������� ����� ����� �� LIFE_CYCLE.
*
* @param massBurn ����� ������������ �����.
* @param massDie ����� �����, ��������� ���� �����.
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
* ������ ����� ������� ��������� �����.
* ����������� �������� � ���������� ������ ������� ��� ���� ���������.
*
* @todo extend �������� ������� ������������� ����������� ����� �� LIFE_CYCLE.
*
* @param environment ����� �������� �����.
* @param comfortTemperature ����������� �������� �����.
* @param limitTemperature �������� ���������� ��� ���� �����.
*/
template< size_t SX, size_t SY, size_t SZ >
void survivor(
    typename portulan::planet::Topology< SX, SY, SZ >::living_t::specimen_t::survivor_t&,
    const std::vector< size_t >&  environment,
    const std::pair< double, double >&  comfortTemperature,
    const std::pair< double, double >&  limitTemperature
);





/**
* ������ ����� ���������� �� �����.
*
* @param lifetime ����� ����� �����, �����.
* @param massBurn ����� ������������ �����.
* @param massDie ����� �����, ��������� ���� �����.
* @param chemicalComposition ���������� ������ �����.
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
* ������ ����� ���������� �� �������� ����� (������, ���-�� ������).
*
* @param uid ���������� ������������� �����.
* @param fnLiving �������, ������������ ���-�� �������� � ������� ������ �
*        ����������� �� ������ 'typelib::coord_t' � ����� ��������
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
* ������ ����� ���������� � ����������� � ������� �������.
*
* @param fnTemperature �������, ������������ ����������� � ����������� ��
*        ������ 'typelib::coord_t' � ������� �������.
* @param radiusPlanet ������ �������, ��.
* @param radiusAtmosphere ������ ���������, ��.
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
* ������ ����� ������� �������.
*
* @param depth ������� ���������, ��.
* @param innerRadius ���������� ������ ��������� (== ������� �������), ��.
* @param chemicalSubstance ���������� portulan::planet::Topology::CHEMICAL_SUBSTANCE
*        ���. ��������� � ���������. �������� [ 0.0; 1.0 ]. ����� ���� ����� 1.0.
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
* �������� ������ 'src' � 'dst', ������� �������� �� 'k'.
* ���� 'src' �������� ������ ��� 'n', �� ��������� �������� ����������� ������.
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
* ��������� ������������ 'dst' ��������� ������� �������� �� 'src'.
* �� ��������� � 'src' �������� ����������� ������.
*
* @see ���������� ��� aboutPlanet_t::componentPlanet.
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
