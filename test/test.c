#include "tst.h"  // Ensure the tst framework is included

tstsuite("Parsing test")
{    
    tstcase("Equality Checks %d, %d", 1, 1) {
      tstcheck(1 == 1, "Mismatch: %d != %d", 1, 1);
      tstcheck(1 != 1, "Failed on purpose");
    }

    
    tstnote("Testing Complete. Review for any FAIL flags.");
}