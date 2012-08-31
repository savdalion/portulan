#pragma once

#include "../../configure.h"
#ifdef OPENCL_PORTULAN

#include <typelib/typelib.h>
#include <memory>
#include <CL/cl_platform.h>
#include <CL/cl.h>



namespace portulan {
    namespace planet {

template< size_t SX, size_t SY, size_t SZ >
struct Topology;

    }
}


/* - @todo ...
namespace std {

template< size_t SX, size_t SY, size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::Topology< SX, SY, SZ >& );

} // std
*/



namespace portulan {
    namespace planet {


/**
* Структура для работы с топологией планеты.
* Помимо удобства, эта структура декларирут некоторые соглашения
* (см. planet::Portulan).
*
* Соглашения
*   # Размеры топологии планеты кратны 3.
*   # Размеры сеток в комментариях приведены с учётом разбиения области
*     планеты на 81 x 81 x 81 ячейку.
*   # Типы данных топологии сразу готовы к передаче OpenCL: это позволит
*     избежать создания booster-структуры (см. porte::Booster).
*/
template< size_t SX, size_t SY, size_t SZ >
struct Topology {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Topology >  Ptr;
    typedef std::unique_ptr< Topology >  UPtr;
    typedef std::weak_ptr< Topology >    WPtr;



    /**
    * Простые типы данных.
    *//* - Попробуем уйти от необходимости создавать отдельную
           booster-структуру для эффективного обмена данными между
           CPU и GPU. См. ниже.
    typedef typelib::SignBitMap< SX, SY, SZ >  signBitLayer_t;
    typedef typelib::SignNumberMap< float, SX, SY, SZ >  signNumberLayer_t;
    typedef typelib::NumberMap< float, SX, SY, SZ >  numberLayer_t;
    typedef typelib::VectorMap< float, SX, SY, SZ >  vectorLayer_t;
    */
    typedef cl_float numberLayer_t[ SX * SY * SZ ];



    /**
    * Макс. кол-во хим. соединений (веществ), которые могут хранится в портулане.
    * Например, для земной коры можно указать след. соответствие:
    *   (0)O, (1)Si, Al, Fe, Ca, Na, K, (7)Mg, (8)H, (9)редкие
    */
    static const size_t CHEMICAL_SUBSTANCE = 15;
    typedef cl_float chemicalSubstance_t[ CHEMICAL_SUBSTANCE ];


    /**
    * Размер сетки атмосферы планеты в области планеты.
    */
    static const size_t ATMOSPHERE_GRID = SX;


    /**
    * Размер сетки давлений атмосферы планеты.
    *
    * Например, область планеты разбивается на объём 27х27х27 и для каждой
    * полученной ячейки указывается давление в Па; т.о. на уровне I
    * получаем 19683 давлений из которых значимы лишь те, содержание
    * которых - см. выше - для атмосферы не пустое; зависит от
    * температуры - см. ниже динамическую характеристику;
    * благодаря разнице в давлениях возникают ветры, тайфуны.
    */
    static const size_t PRESSURE_ATMOSPHERE_GRID = SX / 3;


    /**
    * Размер сетки ветров в атмосфере планеты.
    *
    * Сетка - объём 54х54х54, 157464 ячейки - в 2 раза больше сетки
    * давления, что позволяет определить направления ветров - 4 ветра -
    * внутри каждой ячейки давления.
    */
    static const size_t WIND_ATMOSPHERE_GRID = SX / 3 * 2;


    /**
    * Атмосфера планеты.
    */
    typedef struct {
        /**
        * Масса атмосферы, кг.
        */
        cl_float mass;

        /**
        * Внутренний радиус атмосферы, м.
        * Обычно соотв. радиусу планеты.
        */
        cl_float innerRadius;

        /**
        * Толщина атмосферы, м.
        */
        cl_float depth;

        /**
        * Содержание (по объёму).
        * Реализовано в виде % / 100 концентрации хим. элементов.
        * Сумма всех элементов = 1.0.
        *//* - Заменено. См. ниже.
        typedef struct {
            numberLayer_t N2;
            numberLayer_t O2;
            numberLayer_t Ar;
            numberLayer_t CO2;
            numberLayer_t sparse;
        } content_t;
        */

        typedef chemicalSubstance_t content_t[ ATMOSPHERE_GRID * ATMOSPHERE_GRID * ATMOSPHERE_GRID ];
        content_t content;

        /**
        * Давление атмосферы, Па.
        *//* - Попробуем уйти от необходимости создавать отдельную
               booster-структуру для эффективного обмена данными между
               CPU и GPU. Для этого используем простые типы C. См. ниже.
        typedef typelib::NumberMap< float, SX / 3, SY / 3, SZ / 3 >  pressure_t;
        */
        typedef cl_float pressure_t[ PRESSURE_ATMOSPHERE_GRID * PRESSURE_ATMOSPHERE_GRID * PRESSURE_ATMOSPHERE_GRID ];
        pressure_t pressure;


        /**
        * Ветер.
        * Вектора скорости, м/с.
        *//* - См. прим. к pressure_t выше.
        typedef typelib::NumberMap< float, SX / 3 * 2, SY / 3 * 2, SZ / 3 * 2 >  wind_t;
        */
        typedef cl_float wind_t[ WIND_ATMOSPHERE_GRID * WIND_ATMOSPHERE_GRID * WIND_ATMOSPHERE_GRID ];
        wind_t wind;

    } atmosphere_t;




    /**
    * Размер сетки планетарной коры в области планеты.
    */
    static const size_t CRUST_GRID = SX;


    /**
    * Размер сетки с информацией о поверхности планетарной коры
    * в области планеты.
    */
    static const size_t SURFACE_CRUST_GRID = SX / 3;


    /**
    * Кора планеты.
    */
    typedef struct {
        /**
        * Масса коры, кг.
        */
        cl_float mass;

        /**
        * Внутренний радиус коры, м.
        * Обычно соотв. радиусу планеты минус толщина коры.
        */
        cl_float innerRadius;

        /**
        * Толщина коры, м.
        */
        cl_float depth;

        /**
        * Содержание.
        * Реализовано в виде % / 100 концентрации хим. элементов.
        * Сумма всех элементов = 1.0.
        *//* - Заменено. См. ниже.
        typedef struct {
            numberLayer_t O;
            numberLayer_t Si;
            numberLayer_t Al;
            numberLayer_t Fe;
            numberLayer_t Ca;
            numberLayer_t Na;
            numberLayer_t K;
            numberLayer_t Mg;
            numberLayer_t H;
            numberLayer_t sparse;
        } content_t;
        */

        typedef chemicalSubstance_t content_t[ CRUST_GRID * CRUST_GRID * CRUST_GRID ];
        content_t content;


        /**
        * Поверхность.
        */
        typedef struct {
            /**
            * Максимальная глубина и высота на поверхности планеты.
            */
            cl_float depth;
            cl_float height;

            /**
            * Крутизна поверхности.
            * Задаётся максимально допустимым перепадом (высота - глубина),
            * максимальным расстоянием, на котором возможен этот перепад и
            * кол-вом перепадов в области 27x27x27 ячеек.
            */
            typedef struct {
                cl_float drop;
                cl_float distance;
            } jamb_t;
            jamb_t jamb;

        } structSurface_t;

        typedef structSurface_t surface_t[ SURFACE_CRUST_GRID * SURFACE_CRUST_GRID * SURFACE_CRUST_GRID ];
        surface_t surface;

    } crust_t;



    /**
    * Жизненный цикл особи на планете (животного, растения).
    *
    * # Цикл обрисован группами:
    *     0    Эмбрионы особей, семена.
    *     1    Дети, ростки.
    *     2    Взрослые.
    *     3    Старики.
    *     4    Мёртвые особи - тела, скелеты.
    *     5    Бессмертные особи.
    */
    static const size_t LIFE_CYCLE = 6;


    /**
    * Размер сетки ареалов обитания живых организмов в области планеты.
    */
    static const size_t LIVING_GRID = SX / 3;


    /**
    * Максимально возможное кол-во *различных* особей в области планеты.
    */
    static const size_t SPECIMEN_COUNT = 100;


    /**
    * Перечисление сред обитания особей живого мира.
    */
    typedef struct {
        /**
        * Состояние не определено.
        */
        static const size_t UNDEFINED = (0);

        /**
        * Твёрдое вещество.
        * Например: почва.
        */
        static const size_t SOLID = (1 << 1);

        /**
        * Жидкое вещество.
        * Например: вода.
        */
        static const size_t LIQUID = (1 << 2);

        /**
        * Газообразное вещество.
        * Например: воздух.
        */
        static const size_t GAS = (1 << 3);

        /**
        * Плазма.
        */
        static const size_t PLASM = (1 << 4);

        // @todo Тропики, тундра, жарко, перенаселено, ... - для группировок.

    } Environment;


    /**
    * Живой мир (растения, животные и пр.; далее - особи).
    * Кол-во особей по ареалам обитания; область планеты разбивается на объём
    * 27х27х27 и каждая полученная ячейка считается ареалом обитания групп
    * особей; т.о. *каждой* группе живого мира сопоставляется 19683 ареалов
    * обитания.
    */
    typedef struct {
        /**
        * Сетка для учёта возраста особей.
        *//* - Нет. Структура должна быть близкой к OpenCL. Заменено. См. ниже.
        typedef std::array< float, 20 >  age_t;
        */


        /**
        * Количества здоровых и больных особей.
        * Каждый ареал содержит информацию о кол-ве особей с группировкой
        * по пульсам. Кол-во особей переходит из одной группы в другую.
        */
        typedef struct {
            cl_float healthy[ LIFE_CYCLE ];
            cl_float sick[ LIFE_CYCLE ];
        } count_t;

        /**
        * Структура для работы с кол-вом особей в области планеты по группам.
        */
        typedef count_t group_t[ SPECIMEN_COUNT ];
        typedef group_t content_t[ LIVING_GRID * LIVING_GRID * LIVING_GRID ];
        content_t content;


        /**
        * Информация об особи.
        */
        typedef struct {
            /**
            * Среднее время жизни данной особи в пульсах (старость -> смерть).
            * Для бессмертных и мёртвых особей не имеет смысла.
            */
            cl_float lifetime;

            /**
            * Масса особи (мясо, кости, панцирь, листва, кора и т.д.) согласно
            * жизненному циклу "countByAge", кг.
            */
            cl_float mass[ LIFE_CYCLE ];


            /**
            * Максимальное кол-во *разных* хим. компонентов, из которых может
            * состоять особь.
            */
            static const size_t CHEMICAL_COMPOSITION = 5;

            /**
            * Макисмальное кол-во *разных* хим. компонентов, которые нужны
            * особи для поддержания жизни.
            */
            static const size_t CHEMICAL_NEED = 5;

            /**
            * Максимальное кол-во *разных* хим. компонентов, которые выделяет
            * особь при жизнедеятельности.
            */
            static const size_t CHEMICAL_WASTE = 5;

            /**
            * Максимальное кол-во *разных* видов энергии, которая необходима
            * особи для поддержания жизни.
            * Например: солнечный свет, тепло из окр. среды, электрический ток.
            */
            static const size_t ENERGY_NEED = 2;

            /**
            * Максимальное кол-во *разных* видов энергии, которя излучает
            * особь при жизнедеятельности.
            * Например: свет, тепло, электрический ток, радиация.
            */
            static const size_t ENERGY_WASTE = 2;

            /**
            * Хим. состав особи.
            * Массовые доли (от общей массы особи), сумма = 1.0.
            * Например: белки (мясо), жиры, углеводы (скелет).
            */
            typedef cl_float chemicalComposition_t[ CHEMICAL_COMPOSITION ];
            chemicalComposition_t chemicalComposition;


            /**
            * Метаболизм особи (рост, восстановление повреждённых тканей
            * и т.п.) согласно жизненному циклу "countByAge".
            *
            * @see Метаболизм > http://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%B0%D0%B1%D0%BE%D0%BB%D0%B8%D0%B7%D0%BC
            */
            typedef struct {
                typedef struct {
                    /**
                    * Потребности в хим. компонентах.
                    * Например: белки, жиры, углеводы, витамины, кислород.
                    */
                    cl_float need[ CHEMICAL_NEED ];

                    /**
                    * Продукты жизнедеятельности особи (хим. компоненты).
                    * Например: кал, моча, пот, углекислый газ, кислород.
                    */
                    cl_float waste[ CHEMICAL_WASTE ];

                } chemical_t;

                chemical_t chemical;

                typedef struct {
                    /**
                    * Энергия, необходимая особи для поддержания жизни, за
                    * исключением энергии, выделяемой от потребления пищи
                    * (хим. компонентов). Лишняя энергия может выделяться
                    * особью в виде тепла (см. ниже).
                    * Дж/пульс
                    *
                    * Например: солнечный свет, тепло окруж. среды.
                    */
                    cl_float need[ ENERGY_NEED ];

                    /**
                    * Энергия, выделяемая особью в процессе своей
                    * жизнедеятельности.
                    * Дж/пульс
                    *
                    * Например: свет, тепло, электрический ток.
                    */
                    cl_float waste[ ENERGY_WASTE ];

                } energy_t;

                energy_t energy;

            } metabolism_t;

            metabolism_t metabolism[ LIFE_CYCLE ];


            /**
            * Условия выживания данной особи.
            */
            typedef struct {
                /**
                * Максимальное количество сред, где может обитать особь.
                */
                static const size_t ENVIRONMENT_SURVIVOR = 5;

                /**
                * В каких средах может жить особь.
                *   # Среды обитания задаются комбинацией бит из Environment.
                *   # В любых других средах особь *моментально* погибает.
                *
                * Например, если особь может жить на границе газообразной и
                * твёрдой сред, пишем:
                *   topology_t::Environment::GAS | topology_t::Environment::SOLID
                */
                size_t environment[ ENVIRONMENT_SURVIVOR ];

                /**
                * Диапазон температур в которых способна жить особь согласно
                * жизненному циклу "countByAge".
                */
                typedef struct {
                    /**
                    * Температура комфорта.
                    * Вне этого диапазона - повышенная смертность и пониженная
                    * рождаемость особей.
                    * Для цивилизованных особей диапазон может варьироваться очень
                    * широко благодаря использованию ц. о. домов / огня / одежды.
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } comfort_t;
                    comfort_t comfort;

                    /**
                    * Температура выживания.
                    * Существование особи вне этого предела невозможно
                    * (100% летальный исход за 1 пульс).
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } limit_t;
                    limit_t limit;

                } temperatureRange_t;

                temperatureRange_t temperatureRange[ LIFE_CYCLE ];

            } survivor_t;

            survivor_t survivor;

        } specimen_t;

        specimen_t specimen[ SPECIMEN_COUNT ];

    } living_t;




    /**
    * Размер сетки компонентов в области планеты.
    */
    static const size_t COMPONENT_GRID = LIVING_GRID;


    /**
    * Максимально возможное кол-во *различных* компонентов в области планеты.
    */
    static const size_t TYPE_COMPONENT_COUNT = 100;



    /**
    * Учитываемые компоненты.
    * Компоненты ведут себя близко к живой особи, но проще по структуре.
    *
    * Например, особь может потреблять (1) кислород и выделять (2) углекислый
    * газ. Их следует учитывать как 2 отдельных компонента.
    * Например, особь (животное или растение) может погибнуть и разложившись
    * образовать (1) плодородную почву.
    */
    typedef struct {
        /**
        * Структура для работы с кол-вом компонентов в области планеты
        * по группам.
        */
        typedef cl_float group_t[ TYPE_COMPONENT_COUNT ];
        typedef group_t content_t[ COMPONENT_GRID * COMPONENT_GRID * COMPONENT_GRID ];
        content_t content;


        /**
        * Информация о компоненте.
        */
        typedef struct {
            /**
            * Масса компонента, кг.
            */
            cl_float mass;


            /**
            * Максимальное кол-во *разных* компонентов, из которых может
            * состоять этот компонент.
            */
            static const size_t COMPONENT_COMPOSITION = 5;

            /**
            * Состав компонента.
            * Может быть пустым (все значения UID == 0).
            * Перечисление UID компонентов и их массовой доли в этом компоненте.
            * Например: белки = 0.2, жиры = 0.1, углеводы = 0.7.
            */
            typedef struct {
                cl_uchar uid;
                cl_float count;
            } portion_t;
            typedef portion_t сomposition_t[ COMPONENT_COMPOSITION ];
            сomposition_t сomposition;


            /**
            * Условия сохранения данного компонента целостным.
            * Аналог "условий выживания" для живой особи.
            */
            typedef struct {
                /**
                * Диапазон температур в которых способен храниться компонент.
                * Аналог living_t::specimen_t::survivor_t::temperatureRange_t.
                */
                typedef struct {
                    /**
                    * Температура комфорта.
                    * Вне этого диапазона - повышенное разрушение компонента.
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } comfort_t;
                    comfort_t comfort;

                    /**
                    * Температура хранения.
                    * Существование целостного компонента вне этого предела
                    * невозможно (100% разрушение за 1 пульс).
                    */
                    typedef struct {
                        cl_float min;
                        cl_float max;
                    } limit_t;
                    limit_t limit;

                } temperatureRange_t;

                temperatureRange_t temperatureRange;

            } survivor_t;

            survivor_t survivor;

        } type_t;

        type_t type[ TYPE_COMPONENT_COUNT ];

    } component_t;




    /**
    * Размер сетки распределения температуры в области планеты.
    */
    static const size_t TEMPERATURE_GRID = SX / 3;


    /**
    * Температура области планеты.
    */
    typedef struct {
        typedef cl_float content_t[ TEMPERATURE_GRID * TEMPERATURE_GRID * TEMPERATURE_GRID ];
        content_t content;
    } temperature_t;




    /**
    * Размер сетки распределения осадков в области планеты.
    */
    static const size_t PRECIPITATIONS_GRID = SX / 3;


    /**
    * Кол-во осадков в области планеты.
    */
    typedef struct {
        typedef cl_float content_t[ PRECIPITATIONS_GRID * PRECIPITATIONS_GRID * PRECIPITATIONS_GRID ];
        content_t content;
    } precipitations_t;




    Topology();


    virtual ~Topology();




    /**
    * @return Атмосфера.
    */
    atmosphere_t atmosphere();



    /**
    * @return Кора планеты.
    */
    crust_t crust();



    /**
    * @return Живой мир.
    */
    living_t living();



    /**
    * @return Компоненты.
    */
    component_t component();



    /**
    * @return Температура.
    */
    temperature_t temperature();



    /**
    * @return Осадки.
    */
    precipitations_t precipitations();






private:
    atmosphere_t mAtmosphere;
    crust_t mCrust;
    living_t mLiving;
    component_t mComponent;
    temperature_t mTemperature;
    precipitations_t mPrecipitations;

};



    } // planet
} // portulan








#include "Topology.inl"



#else
#pragma message( "Class portulan::planet::Topology not included in project: OpenCL disable" )

#endif
