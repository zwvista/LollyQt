#ifndef RX_H
#define RX_H

#include <rxqt.hpp>
namespace Rx {
    using namespace rxcpp;
    using namespace rxcpp::sources;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
}
using namespace Rx;

extern const rxqt::run_loop* pLoop;

#endif // RX_H
