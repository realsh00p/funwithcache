#include <cstdio>

#include <sched.h>
#include <sys/mman.h>

namespace funwithprofiler {
namespace realtime {

template <int Scheduler>
class Realtime {
public:
  Realtime() {
    int ret;
    ret = sched_get_priority_max(Scheduler);
    if (ret < 0) {
      perror("sched_get_priority_max");
      throw;
    }
    struct sched_param sp {
      .sched_priority = ret
    };

    ret = sched_setscheduler(0, Scheduler, &sp);
    if (-1 == ret) {
      perror("sched_setscheduler");
      throw;
    }

    if (-1 == mlockall(MCL_CURRENT | MCL_FUTURE)) {
      perror("mlockall");
      throw;
    }
  }
};

} // namespace realtime
} // namespace funwithprofiler
