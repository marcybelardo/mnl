Marcy's Nice Libs
===

single-file C libraries, which are nice, and by Marcy

#### Usage

I'm a big fan of the stb image libraries, so I've used a similar structure. Put the header file in your project, and use the appropriate macro to enable the function definitions. Like so,

```c
#define MNL_NET_IMPL
#include "mnl_net.h"
```

#### Files

| file | usage |
| ---- | ----- |
| mnl_net.h | create tcp network connections |


Go give the [stb libraries](https://github.com/nothings/stb) a look! They are nice.

#### License

It's public domain! Use it how you wish. I'd appreciate a shoutout, but that's up to you <3
