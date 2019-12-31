#ifndef RX_H
#define RX_H

#include <rxqt.hpp>
namespace Rx {
    using namespace rxcpp;
    using namespace rxcpp::sources;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
    using observable_void = observable<void, dynamic_observable<void>>;
}
using namespace Rx;

extern const rxqt::run_loop* pRunLoop;

#define APPLY_IO \
    .subscribe_on(observe_on_event_loop()) \
    .observe_on(pRunLoop->observe_on_run_loop())

#endif // RX_H
