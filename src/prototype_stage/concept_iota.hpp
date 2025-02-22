// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../datatypes.hpp"
#include "concept_stage.hpp"

namespace seq {
namespace con {

template <typename I, typename S> requires Receiver<S>
struct IotaImpl {
    using Input = I;

    IotaImpl(I init, S successor) : _index{init}, _successor{successor} {}
    
    Status yield(I const count = 1) {
        assert(count >= 0);
        Status status = OK;
        for(I i = 0; i < count && status == OK; ++i) {
            status = _successor.receive(std::forward<I>(_index));
            if(status == OK) {
                ++(_index);
            }
        }
        return status;
    }
    
    Status run() {
        Status status = OK;
        while(status == OK) {
            status = _successor.receive(std::forward<I>(_index));
            if(status == OK) {
                ++(_index);
            }
        }
        return status;
    }

    I _index;
    S _successor;
};    

template <typename I, typename S> requires Receiver<S>
auto iota(I init, S successor) {
    return IotaImpl<I, S>{init, successor};
}

template <typename S> requires Receiver<S>
auto iota(S successor) {
    return IotaImpl<typename S::Input, S>{0, successor};
}

}
}
