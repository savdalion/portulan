#pragma once

#include "../planet/Portulan.h"
#include "../planet/Topology.h"
#include <silhouette/silhouette.h>
#include <typelib/typelib.h>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/function.hpp>


namespace portulan {
    namespace planet {

template< size_t SX, size_t SY, size_t SZ >
class Portulan;

    }
}



/**
* ������� ����� ������ ��� �������� ����� �������.
* �������� ������������� planet::Topology ���������� �������.
*
* @see planet::Topology ��� ���������� ��������� ������ ����������.
*/
namespace portulan {
    namespace command {
        namespace planet {

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
    const std::vector< double >&  chemicalSubstance
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
    const std::vector< double >&  chemicalSubstance
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
    const std::vector< double >&  chemicalNeed,
    const std::vector< double >&  chemicalWaste,
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
    const std::vector< double >&  chemicalComposition,
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
    size_t uid,
    const boost::function< std::tuple< double, double >(
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
    const typename portulan::planet::Topology< SX, SY, SZ >::living_t&
);







/**
* �������� ������ 'src' � 'dst', ������� �������� �� 'k'.
* ���� 'src' �������� ������ ��� 'N', �� ��������� �������� ����������� ������.
*/
template < typename D, typename S >
void copyFill(
    D dst[],
    size_t N,
    const std::vector< S >&  src,
    S k = 1
);


        } // planet
    } // command
} // portulan












#include "planet.inl"
