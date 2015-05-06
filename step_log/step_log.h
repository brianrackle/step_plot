#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <string>
#include <vector>
#include <functional>
#include <stddef.h>
#include "cereal/archives/json.hpp"
#include "format.h"

//library info:
//http://cppformat.readthedocs.org/en/stable/
//http://gnuplot.sourceforge.net/docs_5.0/gnuplot.pdf
namespace step_log
{
    constexpr size_t x = 0, y = 1, z = 2;


    //TODO(brian): plots seperated by an 'e'(implicit indexing), or "\n\n"(explicit indexing)
    //segments should be seperated by a single newline, polyline/polygon no seperation
    //ploting with '-' file means all plots repeated for each explicit index
    //or data listed in order with implicit indexing ('e' seperators)
    //gnuplot5 supports $VAR << EOD with indexing into data
    template<class NumericT, size_t Dimension>
    using vertex = std::array<NumericT, Dimension>;

    template <class NumericT, typename std::enable_if<std::is_integral<NumericT>::value>::type * = nullptr>
    void write(fmt::MemoryWriter & stream, const NumericT & t_num)
    {
        stream.write("{:-d}", t_num);
    }

    template <class NumericT, typename std::enable_if<std::is_floating_point<NumericT>::value>::type * = nullptr>
    void write(fmt::MemoryWriter & stream, const NumericT & t_num)
    {
        stream.write("{:-.16f}", t_num);
    }

    template <class VertexT, size_t Count> class write_helper;

    template <class VertexT>
    struct write_helper<VertexT, 1>
    {
        void operator()(fmt::MemoryWriter & stream, const VertexT & t_vertex)
        {
            write(stream, t_vertex[0]);
        }
    };

    template <class VertexT, size_t Count>
    struct write_helper : write_helper<VertexT, Count - 1>
    {
        void operator()(fmt::MemoryWriter & stream, const VertexT & t_vertex)
        {
            constexpr auto count_m = Count - 1;
            write_helper<VertexT, count_m>()(stream, t_vertex);
            stream << ' ';
            write(stream, t_vertex[count_m]);
        }
    };

    template<class NumericT, size_t Dimension>
    void write(fmt::MemoryWriter & stream, const vertex<NumericT, Dimension> & t_vertex)
    {
        using vertex_t = std::remove_cv_t<std::remove_reference_t<decltype(t_vertex)>>;
        write_helper<vertex_t, Dimension>()(stream, t_vertex);
        stream << '\n';
    }

    template<class NumericT, size_t Dimension>
    struct point {
        using data_t = vertex<NumericT, Dimension>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

        void write(fmt::MemoryWriter & stream) const
        {
            step_log::write(stream, data);
        }

        data_t data;
    };

    template<class NumericT, size_t Dimension>
    struct line {
        using data_t = std::array<vertex<NumericT, Dimension>, 2>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

        void write(fmt::MemoryWriter & stream) const
        {
            step_log::write(stream, data[0]);
            step_log::write(stream, data[1]);
        }

        data_t data;
    };

    struct plot_base
    {
        virtual void write(fmt::MemoryWriter & stream) const = 0;
    };

    template <class GeometryT>
    struct plot : public plot_base
    {
        using data_t = std::vector<GeometryT>;
        using geometry_t = GeometryT;
        using numeric_t = typename GeometryT::numeric_t;
        using dimension_t = typename GeometryT::dimension_t;

        virtual void write(fmt::MemoryWriter & stream) const
        {
            for(const auto & d : data)
            {
                d.write(stream);
            }
            stream << '\n';
            stream << '\n';
        }

        data_t data;
    };

    struct plots {
        using data_t = std::vector<std::unique_ptr<plot_base>>;
        using writer_t = fmt::MemoryWriter;

        void write(writer_t & stream, const size_t & index)
        {
            if(index >= data.size())
                return;

            data[index]->write(stream);
        }

        data_t data;
    };
}

#endif //PROJECT_STEP_LOG_H
