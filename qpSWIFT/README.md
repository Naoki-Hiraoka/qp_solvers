``
find_package(qpSWIFT REQUIRED)

target_link_libraries([your target]
  qpSWIFT::qpSWIFT-shared
  )
```

```
#include <qpSWIFT.h>
```