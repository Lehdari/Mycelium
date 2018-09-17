//
// Created by Lehdari on 28.3.2018.
//

#ifndef MYCELIUM_MULTIARRAY_HPP
#define MYCELIUM_MULTIARRAY_HPP


#include <vector>
#include <cstdint>
#include <tuple>
#include <utility>


namespace mm {

    template<typename T, unsigned N, template<typename> typename T_Container = std::vector>
    class MultiArray {
    public:
        /// Construct a Multi-Array with 0 size
        MultiArray();

        /// Construct a Multi-Array with dimension lengths
        template<typename... Args>
        MultiArray(Args... args);

        /// Resize the Multi-Array
        template<typename... Args>
        void resize(Args... args);

        /// Fill the Multi-Array with single value
        void fill(const T& v);

        /// Access an element
        template<typename... Args>
        T& operator()(Args... args);

        /// Access an element (read-only)
        template<typename... Args>
        const T& operator()(Args... args) const;

        /// Get size of N-th dimension
        const int64_t& getSize(uint64_t n) const;

        /// Get raw pointer to data array (read-only)
        const T *data() const;

        /// Get reference to data container (read-only)
        const T_Container<T>& container() const;

    private:
        T_Container<T> _data;
        int64_t _size[N];
        int64_t _offset[N];

        template<typename T_First, typename... Args>
        static uint64_t countSize(T_First first, Args... args);

        static uint64_t countSize();
    };


    template<typename T, unsigned N, template<typename> typename T_Container>
    MultiArray<T, N, T_Container>::MultiArray() :
        _size{0},
        _offset{0}
    {
    };

    template<typename T, unsigned N, template<typename> typename T_Container>
    template<typename... Args>
    MultiArray<T, N, T_Container>::MultiArray(Args... args)
    {
        resize(args...);
    };

    template<typename T, unsigned N, template<typename> typename T_Container>
    template<typename... Args>
    void MultiArray<T, N, T_Container>::resize(Args... args)
    {
        static_assert(sizeof...(args) == N, "Number of dimensions mismatch");

        _data.resize(countSize(args...));

        int64_t tSize[N]{args...};
        for (auto i = 0u; i < N; ++i)
            _size[i] = tSize[i];

        _offset[0] = 1;
        for (auto i = 1u; i < N; ++i)
            _offset[i] = _offset[i-1]*_size[i-1];
    };

    template<typename T, unsigned N, template<typename> typename T_Container>
    void MultiArray<T, N, T_Container>::fill(const T& v)
    {
        for (auto& d : _data)
            d = v;
    }

    template<typename T, unsigned N, template<typename> typename T_Container>
    template<typename... Args>
    T& MultiArray<T, N, T_Container>::operator()(Args... args)
    {
        static_assert(sizeof...(args) == N, "Number of dimensions mismatch");

        int64_t x[N]{args...};
        int64_t ind = 0;

        for (auto i = 0u; i < N; ++i)
            ind += x[i]*_offset[i];

        return _data[ind];
    };

    template<typename T, unsigned N, template<typename> typename T_Container>
    template<typename... Args>
    const T& MultiArray<T, N, T_Container>::operator()(Args... args) const
    {
        static_assert(sizeof...(args) == N, "Number of dimensions mismatch");

        int64_t x[N]{args...};
        int64_t ind = 0;

        for (auto i = 0u; i < N; ++i)
            ind += x[i]*_offset[i];

        return _data[ind];
    };

    template<typename T, unsigned N, template<typename> typename T_Container>
    const int64_t& MultiArray<T, N, T_Container>::getSize(uint64_t n) const
    {
        return _size[n];
    }

    template<typename T, unsigned N, template<typename> typename T_Container>
    const T *MultiArray<T, N, T_Container>::data() const
    {
        return &_data[0];
    };

    template<typename T, unsigned int N, template<typename> typename T_Container>
    const T_Container<T>& MultiArray<T, N, T_Container>::container() const
    {
        return _data;
    }

    template<typename T, unsigned N, template<typename> typename T_Container>
    template<typename T_First, typename... Args>
    uint64_t MultiArray<T, N, T_Container>::countSize(T_First first, Args... args)
    {
        return first*countSize(args...);
    };

    template<typename T, unsigned N, template<typename> typename T_Container>
    uint64_t MultiArray<T, N, T_Container>::countSize()
    {
        return 1;
    };

}


#endif // MYCELIUM_MULTIARRAY_HPP
