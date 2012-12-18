#pragma once

#include "../../../configure.h"
#include <portulan/include/world/dangeon-crawl/planet/0/set/illuminance-utils.h>
#include <portulan/include/io/world/dangeon-crawl/planet/0/VolumeVTKVisual.h>

namespace pnp = portulan::world::dungeoncrawl::planet::l0;
namespace pniop = portulan::io::world::dungeoncrawl::planet::l0;


namespace {

/**
* Фикстура для illuminance-utils.h
*/
class IlluminanceUtilsTest : public ::testing::Test {
  protected:
    inline IlluminanceUtilsTest() {
    }

    virtual inline ~IlluminanceUtilsTest() {
    }

    virtual inline void SetUp() {
    }

    virtual void TearDown() {
    }
};





/**
* starIlluminance()
*/

TEST_F( IlluminanceUtilsTest, starIlluminance ) {

    // подготавливаем структуру для тестирования
    static const size_t VOLUME =
        pnp::ILLUMINANCE_GRID * pnp::ILLUMINANCE_GRID * pnp::ILLUMINANCE_GRID;
    pnp::illuminanceContent_t ic = new pnp::illuminanceCell_t[ VOLUME ];
    // # Перерасчётом займётся визуализатор. См. ниже.

    pnp::illuminanceBody_t ib = {
#if 1
        // результат освещения
        ic,
        // тело, которое освещают
        // @source Земля > http://ru.wikipedia.org/wiki/%D0%97%D0%B5%D0%BC%D0%BB%D1%8F
        // radius
        6.3568e6,
        // coord[ 3 ]
        { 1.49598261e11, 0, 0 },
        // omega[ 3 ]
        { 0, 23.44, 0 },
        //{ 0, 0, 0 },
        // источники освещения
        // star[]
        {
            // 0
            // @source http://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D0%BB%D0%BD%D1%86%D0%B5
            {
                // radius
                6.9551e8,
                // temperature
                1.5e6,
                // luminousIntensity
                // @source http://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D0%BB%D0%B0_%D1%81%D0%B2%D0%B5%D1%82%D0%B0
                3e27,
                // coord[ 3 ]
                { 0, 0, 0 }
            },
        }
#endif
    };


    // считаем освещение (внутри 'visual') и визуализируем структуру
    pniop::VolumeVTKVisual::option_t  o;
    o[ "planet-size-point" ] = 5;
    o[ "star-size-point" ] = 10;
    o[ "auto-scale-camera" ] = false;
    o[ "without-clear" ] = false;
    o[ "size-window" ] = 950;

    pniop::VolumeVTKVisual  visual( o );
    visual << ib;

    visual.waitCircleEngine( &ib, 1000 );
}



} // namespace
